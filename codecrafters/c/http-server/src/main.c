#include "http.h"

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

char *PATH_ECHO = "/echo/";
char *PATH_UA = "/user-agent";
char *PATH_FILES = "/files";

char *directory = NULL;

void render_resp(int client_fd, http_resp resp) {
    int n;
    char *enc = find_header(resp.headers, resp.num_headers, CONTENT_ENCODING);

    if (enc != NULL && strcasecmp(enc, "gzip") == 0) {
        // compress
        int buf_size = 8096 * sizeof(char);
        char *comp = malloc(buf_size);
        gz_compress(resp.body, resp.content_len, comp, &buf_size);
        free(resp.body);
        resp.body = comp;
        resp.content_len = buf_size;
    }

    send(client_fd, resp.version, strlen(resp.version), 0);
    send(client_fd, " ", strlen(" "), 0);
    send(client_fd, resp.status, strlen(resp.status), 0);
    send(client_fd, HTTP_DELIM, strlen(HTTP_DELIM), 0);
    for (int i = 0; i < resp.num_headers; i++) {
        send(client_fd, resp.headers[i].key, strlen(resp.headers[i].key), 0);
        send(client_fd, ": ", strlen(": "), 0);
        send(client_fd, resp.headers[i].val, strlen(resp.headers[i].val), 0);
        send(client_fd, HTTP_DELIM, strlen(HTTP_DELIM), 0);
    }

    if (resp.body != NULL) {
        send(client_fd, CONTENT_TYPE, strlen(CONTENT_TYPE), 0);
        send(client_fd, ": ", strlen(": "), 0);
        send(client_fd, resp.content_type, strlen(resp.content_type), 0);
        send(client_fd, HTTP_DELIM, strlen(HTTP_DELIM), 0);

        send(client_fd, CONTENT_LENGTH, strlen(CONTENT_LENGTH), 0);
        send(client_fd, ": ", strlen(": "), 0);
        char buf[20] = {0};
        snprintf(buf, 19, "%ld", resp.content_len);
        send(client_fd, buf, strlen(buf), 0);
        send(client_fd, HTTP_DELIM, strlen(HTTP_DELIM), 0);

        send(client_fd, HTTP_DELIM, strlen(HTTP_DELIM), 0);
        send(client_fd, resp.body, resp.content_len, 0);
        free(resp.body);
    } else {
        send(client_fd, HTTP_DELIM, strlen(HTTP_DELIM), 0);
    }
}

http_resp handle_req(http_req req, int *keep_alive) {
    http_resp resp = new_resp();
    resp.version = HTTP_VERSION;
    resp.body = NULL;

    char *ench = find_header(req.headers, req.num_headers, ACCEPT_ENCODING);
    if (ench != NULL && strstr(ench, "gzip") != NULL) {
        add_header(&resp, CONTENT_ENCODING, "gzip");
    }

    if (strcmp(req.uri.path, "/") == 0) {
        resp.status = HTTP_200;
    } else if (strncmp(req.uri.path, PATH_ECHO, strlen(PATH_ECHO)) == 0) {
        resp.status = HTTP_200;
        resp.content_type = TEXT_PLAIN;
        resp.content_len = strlen(req.uri.path + strlen(PATH_ECHO));
        resp.body = malloc(resp.content_len + 1);
        strcpy(resp.body, req.uri.path + strlen(PATH_ECHO));
    } else if (strncmp(req.uri.path, PATH_UA, strlen(PATH_UA)) == 0) {
        resp.status = HTTP_200;
        resp.content_type = TEXT_PLAIN;
        char *ua = find_header(req.headers, req.num_headers, USER_AGENT);
        resp.content_len = strlen(ua);
        resp.body = malloc(resp.content_len + 1);
        strcpy(resp.body, ua);
    } else if (strncmp(req.uri.path, PATH_FILES, strlen(PATH_FILES)) == 0) {
        char *fname = strchr(req.uri.path + 1, '/') + 1;

        if (strcmp(req.method, HTTP_GET) == 0) {
            FILE *file = fopen(fname, "r");

            if (file == NULL) {
                resp.status = HTTP_404;
            } else {
                resp.status = HTTP_200;
                resp.content_type = APP_OCTET_STREAM;
                fseek(file, 0L, SEEK_END);
                int sz = ftell(file);
                rewind(file);
                resp.content_len = sz;
                resp.body = malloc(sz + 1);
                fread(resp.body, 1024, sizeof(char), file);
                fclose(file);
            }
        } else if (strcmp(req.method, HTTP_POST) == 0) {
            FILE *file = fopen(fname, "w");
            if (file == NULL) {
                resp.status = HTTP_404;
            } else {
                resp.status = HTTP_201;
                int n = fwrite(req.body, sizeof(char), req.content_len, file);
                if (n == -1) {
                    perror("Write failed");
                }
                fclose(file);
            }
        }
    } else {
        resp.status = HTTP_404;
        resp.body = NULL;
    }

    char *connh = find_header(req.headers, req.num_headers, CONNECTION);
    *keep_alive = connh == NULL || strcasecmp(connh, "close") != 0;
    if (!*keep_alive) {
        add_header(&resp, CONNECTION, "close");
    }

    return resp;
}

int main(int argc, char **argv) {
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    int c;
    static struct option options[] = {{"directory", required_argument, 0, 'd'},
                                      {0, 0, 0, 0}};
    while (1) {
        int option_index = 0;
        c = getopt_long(argc, argv, "d:", options, &option_index);

        if (c == -1)
            break;

        switch (c) {
        case 0:
            break;
        case 'd':
            directory = optarg;
            if (chdir(directory) != 0)
                perror("directory doesn't exist");
            break;
        case '?':
            break;
        default:
            abort();
        }
    }

    // You can use print statements as follows for debugging, they'll be visible
    // when running tests.
    printf("Logs from your program will appear here!\n");

    //  Uncomment this block to pass the first stage

    int server_fd, client_fd;
    socklen_t client_addr_len;
    struct sockaddr_in client_addr;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        printf("Socket creation failed: %s...\n", strerror(errno));
        return 1;
    }

    // Since the tester restarts your program quite often, setting SO_REUSEADDR
    // ensures that we don't run into 'Address already in use' errors
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
        0) {
        printf("SO_REUSEADDR failed: %s \n", strerror(errno));
        return 1;
    }

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(4221),
        .sin_addr = {htonl(INADDR_ANY)},
    };

    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) !=
        0) {
        printf("Bind failed: %s \n", strerror(errno));
        return 1;
    }

    int connection_backlog = 5;
    if (listen(server_fd, connection_backlog) != 0) {
        printf("Listen failed: %s \n", strerror(errno));
        return 1;
    }

    printf("Waiting for a client to connect...\n");
    client_addr_len = sizeof(client_addr);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                           &client_addr_len);
        printf("Client connected\n");

        size_t ppid = getpid();
        size_t cpid = fork();

        if (cpid != 0) { // parent process
            close(client_fd);
            continue;
        }
        int keep_alive = 1;
        int flags = fcntl(client_fd, F_GETFL, 0) | O_NONBLOCK;
        fcntl(client_fd, F_SETFL, flags);

        while (keep_alive) {
            memset(buffer, 0, sizeof(buffer));
            int n = read(client_fd, buffer, sizeof(buffer));
            if (n == 0) {
                break;
            } else if (n == -1) {
                usleep(100000);
                continue;
                /* break; */
            }

            http_req req = parse_req(buffer);
            http_resp resp = handle_req(req, &keep_alive);
            render_resp(client_fd, resp);
        }

        close(client_fd);
        if (getpid() != ppid) {
            exit(0);
        }
    }

    close(server_fd);

    return 0;
}
