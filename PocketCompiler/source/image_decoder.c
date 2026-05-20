#include "image_decoder.h"
#include <string.h>

static unsigned be32(const unsigned char*p){return((unsigned)p[0]<<24)|((unsigned)p[1]<<16)|((unsigned)p[2]<<8)|(unsigned)p[3];}
static unsigned le16(const unsigned char*p){return(unsigned)p[0]|((unsigned)p[1]<<8);}
static unsigned le32(const unsigned char*p){return(unsigned)p[0]|((unsigned)p[1]<<8)|((unsigned)p[2]<<16)|((unsigned)p[3]<<24);}
const char* image_kind_name(ImageKind k){return k==IMAGE_KIND_PNG?"PNG":k==IMAGE_KIND_JPEG?"JPEG":k==IMAGE_KIND_GIF?"GIF":k==IMAGE_KIND_BMP?"BMP":"unknown";}

bool image_decode_metadata(const unsigned char*d,size_t s,ImageInfo*out){
    if(!d||!out||s<8)return false;memset(out,0,sizeof(*out));
    if(s>=25&&d[0]==0x89&&d[1]=='P'&&d[2]=='N'&&d[3]=='G'&&d[4]==0x0D&&d[5]==0x0A&&d[6]==0x1A&&d[7]==0x0A){
        out->kind=IMAGE_KIND_PNG;out->width=(int)be32(d+16);out->height=(int)be32(d+20);out->bits_per_pixel=d[24];out->decoded_metadata=true;return true;
    }
    if(s>=10&&d[0]=='G'&&d[1]=='I'&&d[2]=='F'&&d[3]=='8'&&(d[4]=='7'||d[4]=='9')&&d[5]=='a'){
        out->kind=IMAGE_KIND_GIF;out->width=(int)le16(d+6);out->height=(int)le16(d+8);out->decoded_metadata=true;return true;
    }
    if(s>=30&&d[0]=='B'&&d[1]=='M'){
        out->kind=IMAGE_KIND_BMP;out->width=(int)le32(d+18);out->height=(int)le32(d+22);out->bits_per_pixel=(int)le16(d+28);out->decoded_metadata=true;return true;
    }
    if(s>=4&&d[0]==0xFF&&d[1]==0xD8){
        size_t p=2;while(p+9<s){if(d[p]!=0xFF){p++;continue;}unsigned char m=d[p+1];p+=2;if(m==0xD9||m==0xDA)break;if(p+2>s)break;unsigned sl=((unsigned)d[p]<<8)|d[p+1];if(sl<2||p+sl>s)break;if((m>=0xC0&&m<=0xC3)||(m>=0xC5&&m<=0xC7)||(m>=0xC9&&m<=0xCB)||(m>=0xCD&&m<=0xCF)){out->kind=IMAGE_KIND_JPEG;out->bits_per_pixel=d[p+2];out->height=((int)d[p+3]<<8)|d[p+4];out->width=((int)d[p+5]<<8)|d[p+6];out->decoded_metadata=true;return true;}p+=sl;}
        out->kind=IMAGE_KIND_JPEG;return false;
    }
    return false;
}
