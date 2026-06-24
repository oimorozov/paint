#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <math.h>

#include "raylib.h"


// general
#define WINDOW_SIZE 800
#define BACKGROUND_COLOR DARKGRAY
#define INIT_BRUSH_SIZE 5
#define INIT_ERASER_SIZE 5
#define INIT_BRUSH_COLOR LIGHTGRAY 

#define CMD_CAP 128

#define FONT_SIZE fmin(16, WINDOW_SIZE / 2)

// component
#define MARGIN_CMP WINDOW_SIZE * 0.05f
#define BORDER_THICKNESS_CMP 20
#define GAP_CMP 4

// command line component
#define COMMAND_LINE_CMP_W WINDOW_SIZE - MARGIN_CMP * 2
#define COMMAND_LINE_CMP_H fmin(100, WINDOW_SIZE / 2)
#define COMMAND_LINE_CMP_X MARGIN_CMP
#define COMMAND_LINE_CMP_Y WINDOW_SIZE / 2 - COMMAND_LINE_CMP_H / 2

#define COMMAND_LINE_CMP_COLOR LIGHTGRAY

#define COMMAND_LINE_CMP_FONT_SIZE fmin(22, COMMAND_LINE_CMP_W / 2)
#define COMMAND_LINE_CMP_FONT_COLOR WHITE

// color palette component
#define COLOR_PALETTE_CMP_W COMMAND_LINE_CMP_W
#define COLOR_PALETTE_CMP_H COMMAND_LINE_CMP_H
#define COLOR_PALETTE_CMP_X COMMAND_LINE_CMP_X
#define COLOR_PALETTE_CMP_Y COMMAND_LINE_CMP_Y

#define COLOR_PALETTE_CMP_COLOR LIGHTGRAY

#define COLOR_PALETTE_CMP_MARGIN ((MARGIN_CMP + BORDER_THICKNESS_CMP) * 1.05f)

struct Config {
    RenderTexture2D canvas;

    Vector2 curr_pos;
    Vector2 prev_pos;

    int brush_size;
    int eraser_size;
    Color brush_color;

    bool command_line_cmp_mode;
    size_t cmd_idx;
    char cmd[CMD_CAP];

    bool color_palette_cmp_mode;
};
typedef struct Config Config;

void InitConfig(Config *config);

void DestroyConfig(Config *config);

void execute_command(Config *config, const char *cmd);

bool CanDraw(Config *config);

#endif // CONFIG_H
