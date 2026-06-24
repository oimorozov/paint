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

// NOW
int main() {
    Config config = {0};
    InitConfig(&config);
    Component component = {0};
    InitComponent(&component);

    BeginTextureMode(config.canvas);
        ClearBackground(BACKGROUND_COLOR);
    EndTextureMode();

    while (!WindowShouldClose()) {
        // draw
        BeginTextureMode(config.canvas);
            config.curr_pos = GetMousePosition();
            // brush
            if (CanDraw(&config) || (!CanDraw(&config) && !CheckCollisionPointRec(config.curr_pos, component.command_line_cmp->rect))) {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_LEFT_SUPER)) {
                    DrawLineVec(config.curr_pos, config.prev_pos, config.brush_size, config.brush_color);
                }
                // eraser
                else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsKeyDown(KEY_RIGHT_SUPER)) {
                    DrawLineVec(config.curr_pos, config.prev_pos, config.eraser_size, BACKGROUND_COLOR);
                }
            }
            config.prev_pos = config.curr_pos;
        EndTextureMode();

        // commands
        if (IsKeyPressed(KEY_SEMICOLON) && IsKeyDown(KEY_LEFT_SHIFT)) {
            config.command_line_cmp_mode = true;
        }

        if (config.command_line_cmp_mode) {
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
                config.command_line_cmp_mode = false;
                config.cmd_idx = 0;
                config.cmd[0] = '\0';
            }
        }

        // copy canvas to window
        BeginDrawing();
            DrawTextureRec(config.canvas.texture, (Rectangle){0, 0, (float)config.canvas.texture.width, (float)-config.canvas.texture.height}, (Vector2){0, 0}, WHITE);
            DrawRectangleLinesEx((Rectangle){0, 0, config.canvas.texture.width, config.canvas.texture.height}, BORDER_THICKNESS_CMP, BLACK);

            if (config.command_line_cmp_mode) {
                DrawCommandLineCmp(component.command_line_cmp);
                DrawCommandLineTextCmp(config.cmd);
            }

            if (config.color_palette_cmp_mode) {
                DrawColorPaletteCmp(component.color_palette_cmp, &config);
            }
            DrawFPS(0, 0);
        EndDrawing();
    }

    DestroyConfig(&config);
    DestroyComponent(&component);
    return 0;
}

// TODO
//
// goal
/*
 * int main(void) {
 *     Paint paint = {0};
 *     InitPaint(paint);
 *
 *     while (!WindowShouldClose()) {
 *         UpdatePaint(&paint);
 *         RenderPaint(&paint);
 *     }
 *
 *     DestroyPaint(&paint);
 * }
 *
 */
