#include "content_decode.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#if HAVE_ZLIB
#include <zlib.h>
#endif

static int low(int c){return tolower((unsigned char)c);}
static int contains_ci(const char*h,const char*n){if(!h||!n||!*n)return 0;size_t nl=strlen(n);for(const char*p=h;*p;p++){size_t i=0;while(i<nl&&p[i]&&low(p[i])==low(n[i]))i++;if(i==nl)return 1;}return 0;}

ContentEncoding content_encoding_from_header(const char* h){
    if(!h||!*h)return CONTENT_ENCODING_IDENTITY;
    if(contains_ci(h,"gzip"))return CONTENT_ENCODING_GZIP;
    if(contains_ci(h,"deflate"))return CONTENT_ENCODING_DEFLATE;
    if(contains_ci(h,"identity"))return CONTENT_ENCODING_IDENTITY;
    return CONTENT_ENCODING_UNSUPPORTED;
}

bool content_decode_buffer(ContentEncoding enc,const unsigned char*in,size_t is,unsigned char*out,size_t cap,size_t*os,char*err,size_t es){
    if(os)*os=0;
    if(!in||!out||!cap){if(err)snprintf(err,es,"bad decode args");return false;}
    if(enc==CONTENT_ENCODING_IDENTITY){if(is>cap){if(err)snprintf(err,es,"decoded output too large");return false;}memcpy(out,in,is);if(os)*os=is;if(err)snprintf(err,es,"ok");return true;}
#if HAVE_ZLIB
    z_stream z;memset(&z,0,sizeof(z));
    int wb=enc==CONTENT_ENCODING_GZIP?15+16:enc==CONTENT_ENCODING_DEFLATE?15:0;
    if(!wb){if(err)snprintf(err,es,"unsupported content encoding");return false;}
    int r=inflateInit2(&z,wb);if(r!=Z_OK){if(err)snprintf(err,es,"inflate init failed");return false;}
    z.next_in=(Bytef*)in;z.avail_in=(uInt)is;z.next_out=out;z.avail_out=(uInt)cap;
    r=inflate(&z,Z_FINISH);
    if(r!=Z_STREAM_END){inflateEnd(&z);if(err)snprintf(err,es,"inflate failed or output too large");return false;}
    if(os)*os=z.total_out;inflateEnd(&z);if(err)snprintf(err,es,"ok");return true;
#else
    (void)enc;(void)is;if(err)snprintf(err,es,"zlib not enabled");return false;
#endif
}
