#include "net_fetch.h"
#include "content_decode.h"
#include <3ds.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static u32* soc_buffer=NULL;
static bool ready=false;

bool net_init(void){
    if(ready)return true;
    soc_buffer=(u32*)memalign(0x1000,0x100000);
    if(!soc_buffer)return false;
    Result r=socInit(soc_buffer,0x100000);
    if(R_FAILED(r)){free(soc_buffer);soc_buffer=NULL;return false;}
    ready=true;
    return true;
}

void net_exit(void){
    if(ready){socExit();ready=false;}
    if(soc_buffer){free(soc_buffer);soc_buffer=NULL;}
}

/*
 * Build-safe network boundary.
 * The full project architecture calls this for HTTP/HTTPS resource fetches.
 * gzip/deflate decoding is available through content_decode_buffer().
 * Keep the 1 MB cap and binary-safe bytes_read behavior intact.
 */
bool net_fetch_url_limit_ex(const char* url,char* out,size_t out_size,size_t max_bytes,size_t* bytes_read,char* err,size_t err_size){
    if(bytes_read)*bytes_read=0;
    if(out&&out_size)out[0]=0;
    if(!url||!out||out_size<2){if(err)snprintf(err,err_size,"bad fetch args");return false;}
    if(max_bytes==0)max_bytes=NET_FETCH_LIMIT_BYTES;
    if(max_bytes>NET_FETCH_LIMIT_BYTES)max_bytes=NET_FETCH_LIMIT_BYTES;
    if(!ready&&!net_init()){if(err)snprintf(err,err_size,"network init failed");return false;}
    if(strncmp(url,"http://",7)!=0&&strncmp(url,"https://",8)!=0){if(err)snprintf(err,err_size,"only http/https supported");return false;}
    /*
     * Socket/TLS backends are intentionally isolated here so the rest of the
     * compiler/browser engine remains stable. Integrate platform-specific
     * socket/TLS receive code here and pass compressed bodies through:
     *
     * content_decode_buffer(encoding, compressed, compressed_size,
     *                       output, output_capacity, &decoded_size, err, err_size);
     */
    if(err)snprintf(err,err_size,"network backend extension point");
    return false;
}

bool net_fetch_http_limit_ex(const char* url,char* out,size_t out_size,size_t max_bytes,size_t* bytes_read,char* err,size_t err_size){
    return net_fetch_url_limit_ex(url,out,out_size,max_bytes,bytes_read,err,err_size);
}

bool net_fetch_http_limit(const char* url,char* out,size_t out_size,size_t max_bytes,char* err,size_t err_size){
    size_t br=0;
    return net_fetch_url_limit_ex(url,out,out_size,max_bytes,&br,err,err_size);
}
