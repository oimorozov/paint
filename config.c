#include "config.h"
#include "raylib.h"

#include <stdio.h>
#include <string.h>

/* returns 1 if succes, else 0 */
void InitConfig(Config *config) {
    // window
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "paint");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    // canvas
    config->canvas = LoadRenderTexture(WINDOW_SIZE, WINDOW_SIZE);

    // mouse positions
    config->curr_pos = (Vector2){0};
    config->prev_pos = (Vector2){0};

    // brush_size
    config->brush_size = INIT_BRUSH_SIZE;
    config->eraser_size = INIT_ERASER_SIZE;

    // command mode
    config->command_mode = false;
    config->cmd_idx = 0;
    config->cmd[config->cmd_idx] = '\0';

    // components
    config->color_palette_cmp_mode = false;
}

void DestroyConfig(Config *config) {
    // canvas
    UnloadRenderTexture(config->canvas);

    // window
    CloseWindow();
}

void execute_command(Config *config, const char *cmd) {
    char name[CMD_CAP / 2] = {0};
    char args[CMD_CAP / 2] = {0};

    sscanf(cmd, "%s %s", name, args);

    if (strcmp(name, ":b") == 0) {
        int brush_size = atoi(args);

        if (0 < brush_size && brush_size < 101) {
            config->brush_size = brush_size;
        }
    } else if (strcmp(name, ":e") == 0) {
        int eraser_size = atoi(args);

        if (0 < eraser_size && eraser_size < 101) {
            config->eraser_size = eraser_size;
        }
    } else if (strcmp(name, ":clear") == 0) {
        BeginTextureMode(config->canvas);
            ClearBackground(DARKGRAY);
        EndTextureMode();
    } else if (strcmp(name, ":save") == 0) {
        Image image = LoadImageFromTexture(config->canvas.texture);
        ImageFlipVertical(&image);
    }else if (strcmp(name, ":colors") == 0) {
        config->color_palette_cmp_mode = true;
    } else if (strcmp(name, ":help") == 0) {
        // TODO
    }
}
