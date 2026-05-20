#pragma once
#include "app.h"
#include "resource_loader.h"

#define ENG_MAX_NODES 256
#define ENG_MAX_BOXES 160
#define ENG_MAX_CSS 32
#define ENG_MAX_ERRS 16

typedef enum { NODE_DOCUMENT = 0, NODE_ELEMENT, NODE_TEXT, NODE_COMMENT } NodeType;
typedef enum { BOX_BLOCK = 0, BOX_TEXT, BOX_INLINE, BOX_IMAGE } BoxType;

typedef struct {
    NodeType type;
    int parent;
    int first_child;
    int next_sibling;
    char tag[24];
    char text[192];
} Node;

typedef struct {
    char selector[48];
    char color[32];
    char background[32];
    int font_size;
} CssRule;

typedef struct {
    BoxType type;
    int node_index;
    int x;
    int y;
    int w;
    int h;
    char tag[24];
    char text[96];
    char color[32];
    char background[32];
} LayoutBox;

typedef struct {
    char title[128];
    char render_text[PREVIEW_TEXT_MAX];
    Node nodes[ENG_MAX_NODES];
    int node_count;
    CssRule css[ENG_MAX_CSS];
    int css_count;
    LayoutBox boxes[ENG_MAX_BOXES];
    int box_count;
    char errors[ENG_MAX_ERRS][160];
    int error_count;
    int script_count;
    int style_count;
    int text_box_count;
    int block_box_count;
    int image_box_count;
    int content_height;
    ResourceManifest resources;
} EngineDoc;

typedef struct {
    int errors;
    char message[512];
} HtmlCheck;

void engine_parse_and_layout(const char* html, EngineDoc* out);
HtmlCheck engine_check(const char* html);
