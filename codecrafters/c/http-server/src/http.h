#ifndef HTTP_H_
#define HTTP_H_

#define HTTP_VERSION "HTTP/1.1"
#define HTTP_200 "200 OK"
#define HTTP_201 "201 Created"
#define HTTP_404 "404 Not Found"
#define CONTENT_TYPE "Content-Type"
#define CONNECTION "Connection"
#define TEXT_PLAIN "text/plain"
#define ACCEPT_ENCODING "Accept-Encoding"
#define CONTENT_ENCODING "Content-Encoding"
#define APP_OCTET_STREAM "application/octet-stream"
#define CONTENT_LENGTH "Content-Length"
#define USER_AGENT "User-Agent"
#define HTTP_DELIM "\r\n"

#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define MAX_HEADERS 5

struct kv {
    char *key;
    char *val;
};

typedef struct kv http_query_param;
typedef struct kv http_header;

typedef struct http_uri {
    char *path;
    http_query_param q_params[5];
    int nparams;
} http_uri;

typedef struct http_req {
    char *method;
    http_uri uri;
    char *version;
    http_header headers[5];
    int num_headers;
    int content_len;
    char *body;
} http_req;

typedef struct http_resp {
    char *version;
    char *status;
    char *content_type;
    unsigned long content_len;
    http_header headers[5];
    int num_headers;
    char *body;
} http_resp;

int parse_query_params(char *query, http_query_param *params);

http_uri parse_uri(char *raw_uri);

void parse_req_line(char *req_line, http_req *req);

http_req parse_req(char *raw_req);

char *find_header(http_header *headers, int num_headers, char *key);

http_uri new_uri();
http_req new_req();
http_resp new_resp();
void add_header(http_resp *resp, char *key, char *val);


void gz_compress(char *data, int size, char *output, int *outsize);

#endif // HTTP_H_
