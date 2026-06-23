#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "raylib.h"


#define WINDOW_SIZE 800
#define BRUSH_SIZE 5
#define CMD_CAP 128

#define CMD_LINE_W WINDOW_SIZE * 0.9f
#define CMD_LINE_H WINDOW_SIZE * 0.3f
#define CMD_LINE_X (float)WINDOW_SIZE / 2 - CMD_LINE_W / 2
#define CMD_LINE_Y (float)WINDOW_SIZE / 2 - CMD_LINE_H / 2


struct Config {
    RenderTexture2D canvas;

    Vector2 curr_pos;
    Vector2 prev_pos;

    int brush_size;

    bool command_mode;
    size_t cmd_idx;
    char cmd[CMD_CAP];
};
typedef struct Config Config;

/* returns 1 if succes, else 0 */
int InitConfig(Config *config) {
    // window
    InitWindow(WINDOW_SIZE, WINDOW_SIZE, "paint");
    SetTargetFPS(60);

    // canvas
    config->canvas = LoadRenderTexture(WINDOW_SIZE, WINDOW_SIZE);

    // mouse positions
    config->curr_pos = (Vector2){0};
    config->prev_pos = (Vector2){0};

    // brush_size
    config->brush_size = BRUSH_SIZE;

    // command mode
    config->command_mode = false;
    config->cmd_idx = 0;
    config->cmd[config->cmd_idx] = '\0';

    return 1;
}

void DestroyConfig(Config *config) {
    // canvas
    UnloadRenderTexture(config->canvas);

    // window
    CloseWindow();
}

void DrawLineVec(Vector2 start_pos, Vector2 end_pos, int brush_size, Color color) {
    float dx = end_pos.x - start_pos.x;
    float dy = end_pos.y - start_pos.y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist == 0) {
        DrawCircleV(start_pos, brush_size, color);
        return;
    }

    Vector2 dir = {dx / dist, dy / dist}; // {cos(a), sin(a)}
    double step = brush_size;
    for (float delta = 0.0f; delta <= dist; delta += step) {
        Vector2 pos = {start_pos.x + dir.x * delta, start_pos.y + dir.y * delta};
        DrawCircleV(pos, brush_size, color);
    }
}

void execute_command(Config *config, const char *cmd) {
    char name[CMD_CAP / 2] = {0};
    char args[CMD_CAP / 2] = {0};

    sscanf(cmd, "%s %s", name, args);

    if (strcmp(name, ":b") == 0) {
        int size = atoi(args);

        if (size > 0) {
            config->brush_size = size;
        }
    } else if (strcmp(name, ":clear") == 0) {
        BeginTextureMode(config->canvas);
            ClearBackground(DARKGRAY);
        EndTextureMode();
    } else if (strcmp(name, ":help") == 0) {
        // TODO
    }
}

int main() {
    Config config = {0};
    InitConfig(&config);

    BeginTextureMode(config.canvas);
        ClearBackground(DARKGRAY);
    EndTextureMode();

    while (!WindowShouldClose()) {
        // draw
        BeginTextureMode(config.canvas);
            config.curr_pos = GetMousePosition();
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_LEFT_SUPER)) {
                DrawLineVec(config.curr_pos, config.prev_pos, config.brush_size, WHITE);
            } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsKeyDown(KEY_RIGHT_SUPER)) {
                DrawLineVec(config.curr_pos, config.prev_pos, config.brush_size, DARKGRAY);
            }
            config.prev_pos = config.curr_pos;
        EndTextureMode();

        // commands
        if (IsKeyPressed(KEY_SEMICOLON) && IsKeyDown(KEY_LEFT_SHIFT)) {
            config.command_mode = true;
        }

        if (config.command_mode) {
            int ch = GetCharPressed();

            // if user pressed multiple times during one frame
            while (ch > 0) {
                if (config.cmd_idx < CMD_CAP - 1) {
                    config.cmd[config.cmd_idx++] = ch;
                    config.cmd[config.cmd_idx] = '\0';
                }
                ch = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (config.cmd_idx != 0) {
                    config.cmd[--config.cmd_idx] = '\0';
                }
            }

            if (IsKeyPressed(KEY_ENTER) || config.cmd_idx == 0) {
                execute_command(&config, config.cmd);
                config.command_mode = false;
                config.cmd_idx = 0;
                config.cmd[0] = '\0';
            }
        }

        // copy canvas to window
        BeginDrawing();
            DrawTextureRec(config.canvas.texture, (Rectangle){0, 0, (float)config.canvas.texture.width, (float)-config.canvas.texture.height}, (Vector2){0, 0}, GRAY);

            if (config.command_mode) {
                DrawRectangle(CMD_LINE_X, CMD_LINE_Y, CMD_LINE_W, CMD_LINE_H, LIGHTGRAY);
                DrawText(config.cmd, CMD_LINE_X * 0.9f, CMD_LINE_Y + CMD_LINE_H / 2 - 40, 80, WHITE);
            }
        EndDrawing();
    }

    DestroyConfig(&config);
    return 0;
}
