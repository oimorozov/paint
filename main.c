// libc
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// raylib
#include "raylib.h"

// headers
#include "component.h"
#include "config.h"

void DrawLineVec(Vector2 start_pos, Vector2 end_pos, int brush_size, Color color) {
    float dx = end_pos.x - start_pos.x;
    float dy = end_pos.y - start_pos.y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist == 0) {
        DrawCircleV(start_pos, brush_size, color);
        return;
    }

    Vector2 dir = {dx / dist, dy / dist}; // {cos(a), sin(a)}
    double step = brush_size * 0.5f;
    for (float delta = 0.0f; delta <= dist; delta += step) {
        Vector2 pos = {start_pos.x + dir.x * delta, start_pos.y + dir.y * delta};
        DrawCircleV(pos, brush_size, color);
    }
}

int main() {
    Config config = {0};
    InitConfig(&config);
    Component component = {0};
    InitComponent(&component);

    BeginTextureMode(config.canvas);
        ClearBackground(DARKGRAY);
    EndTextureMode();

    while (!WindowShouldClose()) {
        // draw
        BeginTextureMode(config.canvas);
            config.curr_pos = GetMousePosition();
            // brush
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_LEFT_SUPER)) {
                DrawLineVec(config.curr_pos, config.prev_pos, config.brush_size, BRUSH_COLOR);
            }
            // eraser
            else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsKeyDown(KEY_RIGHT_SUPER)) {
                DrawLineVec(config.curr_pos, config.prev_pos, config.eraser_size, BACKGROUND_COLOR);
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
                config.color_palette_cmp_mode = false;

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
                DrawRectangle(0, CMD_LINE_Y, CMD_LINE_W, CMD_LINE_H, CMD_LINE_COLOR);
                DrawText(config.cmd, FONT_SIZE, CMD_LINE_Y + CMD_LINE_H / 2 - FONT_SIZE / 2, FONT_SIZE, FONT_COLOR);
            }

            if (config.color_palette_cmp_mode) {
                DrawColorPaletteCmp(component.color_palette_cmp);
            }
        EndDrawing();
    }

    DestroyConfig(&config);
    DestroyComponent(&component);
    return 0;
}
