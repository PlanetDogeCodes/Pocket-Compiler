#include "editor.h"
#include <string.h>

void editor_init(Editor* e){if(!e)return;e->text[0]=0;e->len=0;e->cursor=0;e->scroll_line=0;}
void editor_set(Editor* e,const char* s){if(!e)return;if(!s)s="";strncpy(e->text,s,EDITOR_MAX-1);e->text[EDITOR_MAX-1]=0;e->len=strlen(e->text);e->cursor=e->len;e->scroll_line=0;}
bool editor_insert(Editor* e,const char* s){if(!e||!s)return false;size_t n=strlen(s);if(!n||e->len+n>=EDITOR_MAX)return false;if(e->cursor>e->len)e->cursor=e->len;memmove(e->text+e->cursor+n,e->text+e->cursor,e->len-e->cursor+1);memcpy(e->text+e->cursor,s,n);e->cursor+=n;e->len+=n;e->text[e->len]=0;return true;}
bool editor_backspace(Editor* e){if(!e||!e->cursor||!e->len)return false;if(e->cursor>e->len)e->cursor=e->len;memmove(e->text+e->cursor-1,e->text+e->cursor,e->len-e->cursor+1);e->cursor--;e->len--;e->text[e->len]=0;return true;}
void editor_left(Editor* e){if(e&&e->cursor>0)e->cursor--;}
void editor_right(Editor* e){if(e&&e->cursor<e->len)e->cursor++;}
const char* editor_text(const Editor* e){return e?e->text:"";}
