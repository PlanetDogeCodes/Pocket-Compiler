#include "js_engine.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct{char name[32];char value[192];}JsVar;
static int low(int c){return tolower((unsigned char)c);}
static int sci(const char*s,const char*p){while(*p){if(!*s||low(*s)!=low(*p))return 0;s++;p++;}return 1;}
static const char*fci(const char*h,const char*n){if(!h||!n||!*n)return NULL;size_t l=strlen(n);for(const char*p=h;*p;p++){size_t i=0;while(i<l&&p[i]&&low(p[i])==low(n[i]))i++;if(i==l)return p;}return NULL;}
static void tc(char*o,size_t os,const char*s,size_t n){while(n&&isspace((unsigned char)*s)){s++;n--;}while(n&&isspace((unsigned char)s[n-1]))n--;if(n>=os)n=os-1;memcpy(o,s,n);o[n]=0;}
static void app(EngineDoc*d,const char*t){if(!d||!t||!*t)return;size_t u=strlen(d->render_text),r=PREVIEW_TEXT_MAX-u-1;if(!r)return;strncat(d->render_text,t,r);u=strlen(d->render_text);if(u+2<PREVIEW_TEXT_MAX)strcat(d->render_text," ");}
static int strarg(const char*c,char*out,size_t os){const char*p=strchr(c,'(');if(!p)return 0;p++;while(*p&&isspace((unsigned char)*p))p++;if(*p!='"'&&*p!='\'')return 0;char q=*p++;size_t i=0;while(*p&&*p!=q&&i+1<os){if(*p=='\\'&&p[1])p++;out[i++]=*p++;}out[i]=0;return i>0;}
static int idarg(const char*c,char*out,size_t os){const char*p=strchr(c,'(');if(!p)return 0;p++;while(*p&&isspace((unsigned char)*p))p++;size_t i=0;while((isalnum((unsigned char)*p)||*p=='_'||*p=='$')&&i+1<os)out[i++]=*p++;out[i]=0;return i>0;}
static const char*lookup(JsVar*v,int n,const char*name){for(int i=0;i<n;i++)if(strcmp(v[i].name,name)==0)return v[i].value;return NULL;}
static void assign(const char*s,JsVar*v,int*n){if(!s||*n>=16)return;const char*p=s;if(sci(p,"var "))p+=4;else if(sci(p,"let "))p+=4;else if(sci(p,"const "))p+=6;else return;while(*p&&isspace((unsigned char)*p))p++;const char*ns=p;while(*p&&(isalnum((unsigned char)*p)||*p=='_'||*p=='$'))p++;char name[32];tc(name,sizeof(name),ns,(size_t)(p-ns));while(*p&&isspace((unsigned char)*p))p++;if(*p!='=')return;p++;while(*p&&isspace((unsigned char)*p))p++;if(*p!='"'&&*p!='\'')return;char q=*p++;char val[192];size_t i=0;while(*p&&*p!=q&&i+1<sizeof(val)){if(*p=='\\'&&p[1])p++;val[i++]=*p++;}val[i]=0;if(name[0]){snprintf(v[*n].name,32,"%s",name);snprintf(v[*n].value,192,"%s",val);(*n)++;}}
static void exec(const char*s,size_t l,EngineDoc*d){char b[2048];if(l>=sizeof(b))l=sizeof(b)-1;memcpy(b,s,l);b[l]=0;JsVar vars[16];int vc=0;memset(vars,0,sizeof(vars));char*st=strtok(b,";\n");while(st){while(*st&&isspace((unsigned char)*st))st++;assign(st,vars,&vc);if(sci(st,"document.write")){char x[256];if(strarg(st,x,sizeof(x)))app(d,x);else{char id[64];if(idarg(st,id,sizeof(id))){const char*v=lookup(vars,vc,id);if(v)app(d,v);}}}else if(sci(st,"console.log")){char x[256];if(strarg(st,x,sizeof(x))){app(d,"[console]");app(d,x);}}st=strtok(NULL,";\n");}}
void js_execute_inline_scripts(const char*h,EngineDoc*d){if(!h||!d)return;const char*p=h;while((p=fci(p,"<script"))){const char*gt=strchr(p,'>');if(!gt)break;const char*src=fci(p,"src=");if(src&&src<gt){p=gt+1;continue;}const char*e=fci(gt+1,"</script>");if(!e)break;exec(gt+1,(size_t)(e-gt-1),d);p=e+9;}}
