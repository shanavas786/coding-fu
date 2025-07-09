#include "http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <zlib.h>

int parse_query_params(char *query, http_query_param *params) {
    int num_params = 0;
    char *rest = query;
    char *kv;
    while ((kv = strtok_r(rest, "&", &rest)) != NULL) {
        http_query_param param = params[num_params++];
        param.key = strtok_r(kv, "=", &param.val);
    }

    return num_params;
}

http_uri new_uri() {
    http_uri uri;
    uri.nparams = 0;
    uri.path = NULL;
    for (int i = 0; i < 5; i++) {
        uri.q_params[i].key = NULL;
        uri.q_params[i].val = NULL;
    }
    return uri;
}

http_uri parse_uri(char *raw_uri) {
    http_uri uri = new_uri();
    char *rest = raw_uri;
    char *path = strtok_r(rest, "?", &rest);
    uri.nparams = parse_query_params(rest, uri.q_params);
    uri.path = path;
    return uri;
}

http_resp new_resp() {
    http_resp resp;
    resp.num_headers = 0;
    for (int i = 0; i < 5; i++) {
        resp.headers[i].key = NULL;
        resp.headers[i].val = NULL;
    }
    resp.body = NULL;
    resp.content_len = 0;
    resp.content_type = NULL;
    return resp;
}

void parse_req_line(char *req_line, http_req *req) {
    char *rest = req_line;

    char *method = strtok_r(rest, " ", &rest);
    char *uri = strtok_r(rest, " ", &rest);
    char *http_version = rest;

    req->method = method;
    req->uri = parse_uri(uri);
    req->version = rest;
}

http_req new_req() {
    http_req req;
    req.method = NULL;
    req.version = NULL;
    req.num_headers = 0;
    req.content_len = 0;
    req.body = NULL;
    for (int i = 0; i < 5; i++) {
        req.headers[i].key = NULL;
        req.headers[i].val = NULL;
    }
    return req;
}

http_req parse_req(char *raw_req) {
    http_req req = new_req();
    char *rest = raw_req;
    char *req_line = strtok_r(raw_req, "\r\n", &rest);
    parse_req_line(req_line, &req);

    char *raw_header = NULL;
    int n = 0;
    while ((raw_header = strtok_r(rest, "\r\n", &rest)) != NULL) {
        char *key, *val;

        key = strtok_r(raw_header, ":", &val);
        if (strcasecmp(key, CONTENT_LENGTH) == 0) {
            req.content_len = strtol(val, NULL, 10);
        }

        if (n < MAX_HEADERS) {
            req.headers[n].key = key;

            if (val[0] == ' ') {
                val++;
            }
            req.headers[n].val = val;
            n++;
        }

        if (strncmp("\n\r\n", rest, 3) == 0) {
            break;
        }
    }
    req.num_headers = n;
    req.body = rest + 3;

    return req;
}

char *find_header(http_header *headers, int num_headers, char *key) {
    for (int i = 0; i < num_headers; i++) {
        if (strcasecmp(key, headers[i].key) == 0) {
            return headers[i].val;
        }
    }

    return NULL;
}

void add_header(http_resp *resp, char *key, char *val) {
    resp->headers[resp->num_headers].key = key;
    resp->headers[resp->num_headers].val = val;
    resp->num_headers++;
}

void gz_compress(char *data, int size, char *output, int *outsize) {
    z_stream stream = {0};
    deflateInit2(&stream, Z_BEST_COMPRESSION, Z_DEFLATED, 15 + 16, 8,
                 Z_DEFAULT_STRATEGY);

    stream.next_in = (unsigned char *)data;
    stream.avail_in = size;

    stream.next_out = (Bytef *)output;
    stream.avail_out = *outsize;

    deflate(&stream, Z_FINISH);
    *outsize = stream.total_out;
    deflateEnd(&stream);
}
