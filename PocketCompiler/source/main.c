#include <3ds.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "app.h"
#include "editor.h"
#include "engine.h"
#include "fs_io.h"
#include "net_fetch.h"
#include "ui.h"

static const char* sample =
"<!doctype html>\\n"
"<html>\\n<head>\\n<title>Pocket Compiler v0.11</title>\\n"
"<style>body { color: white; background: black; } h1 { color: cyan; } p { color: #dddddd; } div { background: #111111; }</style>\\n"
"<link rel=\\"stylesheet\\" href=\\"https://cdnjs.cloudflare.com/ajax/libs/normalize/8.0.1/normalize.min.css\\">\\n"
"</head>\\n<body>\\n"
"<h1>v0.11 Media + JS</h1>\\n"
"<p>gzip/deflate, lightweight JS, and image placeholders are enabled.</p>\\n"
"<script>var msg='JavaScript document.write executed.'; document.write(msg); console.log('Inline JS ran');</script>\\n"
"<div><p>Images are detected and represented as placeholders.</p></div>\\n"
"<img src=\\"https://via.placeholder.com/64.png\\">\\n"
"</body>\\n</html>\\n";

static Editor ed;
static EngineDoc doc;

void app_status(AppState*a,const char*fmt,...){if(!a)return;va_list ap;va_start(ap,fmt);vsnprintf(a->status,sizeof(a->status),fmt,ap);va_end(ap);}
static void run(AppState*a){engine_parse_and_layout(editor_text(&ed),&doc);app_status(a,"Rendered: DOM %d CSS %d JS %d Img %d Res %d.",doc.node_count,doc.css_count,doc.script_count,doc.image_box_count,doc.resources.count);}
static void check(AppState*a){HtmlCheck c=engine_check(editor_text(&ed));if(c.errors)app_status(a,"%d issue(s): %.220s",c.errors,c.message);else app_status(a,"No engine diagnostics.");}
static void save_file(AppState*a){if(!fs_make_app_dir()){app_status(a,"SD dir create failed.");return;}if(fs_save_text(APP_FILE,editor_text(&ed))){a->dirty=false;app_status(a,"Saved index.html.");}else app_status(a,"Save failed.");}
static void load_file(AppState*a){static char buf[EDITOR_MAX];if(fs_load_text(APP_FILE,buf,sizeof(buf))){editor_set(&ed,buf);a->dirty=false;app_status(a,"Loaded index.html.");}else{editor_set(&ed,sample);a->dirty=false;app_status(a,"Load failed; sample restored.");}run(a);}

int main(int argc,char**argv){
    (void)argc;(void)argv;
    gfxInitDefault();
    AppState app;memset(&app,0,sizeof(app));app.running=true;app_status(&app,"Ready.");
    editor_init(&ed);editor_set(&ed,sample);memset(&doc,0,sizeof(doc));
    ui_init();fs_make_app_dir();fs_make_cache_dir();net_init();run(&app);

    while(aptMainLoop()&&app.running){
        hidScanInput();
        u32 down=hidKeysDown(),held=hidKeysHeld();
        if(down&KEY_START)app.running=false;
        if(down&KEY_A)run(&app);
        if(down&KEY_X)check(&app);
        if(down&KEY_Y)save_file(&app);
        if(down&KEY_B)load_file(&app);
        if(down&KEY_SELECT){if(ui_keyboard(&ed,&app)){app.dirty=true;run(&app);}}
        if(down&KEY_LEFT)editor_left(&ed);
        if(down&KEY_RIGHT)editor_right(&ed);
        if(down&KEY_L&&ed.scroll_line>0)ed.scroll_line--;
        if(down&KEY_R)ed.scroll_line++;
        if(down&KEY_CPAD_UP&&editor_insert(&ed,"<div>"))app.dirty=true;
        if(down&KEY_CPAD_DOWN&&editor_insert(&ed,"</div>"))app.dirty=true;
        if(down&KEY_CPAD_LEFT&&editor_insert(&ed,"<p>"))app.dirty=true;
        if(down&KEY_CPAD_RIGHT&&editor_insert(&ed,"</p>"))app.dirty=true;
        if((held&KEY_ZL)&&editor_backspace(&ed))app.dirty=true;
        ui_draw_top(&app,&doc);
        ui_draw_bottom(&app,&ed);
    }

    net_exit();ui_shutdown();gfxExit();return 0;
}
