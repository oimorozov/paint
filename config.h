#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <math.h>

#include "raylib.h"

#include "component.h"

#define WINDOW_SIZE 800
#define INIT_BRUSH_SIZE 5
#define INIT_ERASER_SIZE 5
#define CMD_CAP 128

#define FONT_SIZE fmin(16, WINDOW_SIZE / 2)

#define CMD_LINE_W WINDOW_SIZE
#define CMD_LINE_H fmin(20, WINDOW_SIZE / 2)
#define CMD_LINE_Y WINDOW_SIZE - CMD_LINE_H

#define BACKGROUND_COLOR DARKGRAY
#define BRUSH_COLOR      WHITE
#define CMD_LINE_COLOR   LIGHTGRAY
#define FONT_COLOR       BLACK

struct Config {
    RenderTexture2D canvas;

    Vector2 curr_pos;
    Vector2 prev_pos;

    int brush_size;
    int eraser_size;

    bool command_mode;
    size_t cmd_idx;
    char cmd[CMD_CAP];

    bool color_palette_cmp_mode;
};
typedef struct Config Config;

void InitConfig(Config *config);

void DestroyConfig(Config *config);

void execute_command(Config *config, const char *cmd);

#endif // CONFIG_H
