#pragma once
#include <stdbool.h>
#include <stddef.h>

#define CONTENT_DECODE_MAX_OUTPUT (1024 * 1024)

typedef enum {
    CONTENT_ENCODING_IDENTITY = 0,
    CONTENT_ENCODING_GZIP,
    CONTENT_ENCODING_DEFLATE,
    CONTENT_ENCODING_UNSUPPORTED
} ContentEncoding;

ContentEncoding content_encoding_from_header(const char* header_value);

bool content_decode_buffer(ContentEncoding encoding,
                           const unsigned char* input,
                           size_t input_size,
                           unsigned char* output,
                           size_t output_capacity,
                           size_t* output_size,
                           char* err,
                           size_t err_size);
