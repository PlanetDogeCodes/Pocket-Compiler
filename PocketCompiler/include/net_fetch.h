#pragma once
#include <stdbool.h>
#include <stddef.h>

#define NET_FETCH_LIMIT_BYTES (1024 * 1024)
#define NET_FETCH_MAX_REDIRECTS 5

bool net_init(void);
void net_exit(void);

bool net_fetch_url_limit_ex(const char* url,
                            char* out,
                            size_t out_size,
                            size_t max_bytes,
                            size_t* bytes_read,
                            char* err,
                            size_t err_size);

bool net_fetch_http_limit_ex(const char* url,
                             char* out,
                             size_t out_size,
                             size_t max_bytes,
                             size_t* bytes_read,
                             char* err,
                             size_t err_size);

bool net_fetch_http_limit(const char* url,
                          char* out,
                          size_t out_size,
                          size_t max_bytes,
                          char* err,
                          size_t err_size);
