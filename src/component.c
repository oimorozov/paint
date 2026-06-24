#include "component.h"

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#include "config.h"


void InitCommandLineCmp(CommandLineCmp *cmp) {
    cmp->rect = (Rectangle){
        COMMAND_LINE_CMP_X, COMMAND_LINE_CMP_Y,
        COMMAND_LINE_CMP_W, COMMAND_LINE_CMP_H,
    };
}

void DrawCommandLineCmp(CommandLineCmp *cmp) {
    DrawRectangleRec(cmp->rect, COLOR_PALETTE_CMP_COLOR);
    DrawRectangleLinesEx(cmp->rect, 10, BLACK);
}
void DrawCommandLineTextCmp(const char *text) {
    int size = MeasureText(text, COMMAND_LINE_CMP_FONT_SIZE);
    DrawText(
        text,
        WINDOW_SIZE / 2 - size / 2,
        WINDOW_SIZE / 2 - COMMAND_LINE_CMP_FONT_SIZE / 2,
        COMMAND_LINE_CMP_FONT_SIZE,
        COMMAND_LINE_CMP_FONT_COLOR
    );
}

void InitColorPaletteCmp(ColorPaletteCmp *cmp) {
    cmp->rect = (Rectangle){
        COLOR_PALETTE_CMP_X, COLOR_PALETTE_CMP_Y,
        COLOR_PALETTE_CMP_W, COLOR_PALETTE_CMP_H
    };

    Color preset[MAX_COLOR_COUNT] = {
        BLACK, LIGHTGRAY, GRAY,
        YELLOW, GOLD, ORANGE,
        PINK, RED, MAROON,
        GREEN, LIME, DARKGREEN,
        SKYBLUE, BLUE, DARKBLUE,
        PURPLE, VIOLET, DARKPURPLE,
        BEIGE, BROWN, DARKBROWN,
    };

    memcpy(cmp->colors, preset, MAX_COLOR_COUNT * sizeof(Color));
}

void DrawColorPaletteCmp(ColorPaletteCmp *cmp, Config *config) {
    // background
    DrawRectangleRec(cmp->rect, COMMAND_LINE_CMP_COLOR);
    DrawRectangleLinesEx(cmp->rect, 10, BLACK);

    // colors
    Rectangle rects[MAX_COLOR_COUNT] = {0};
    
    int size = (WINDOW_SIZE - COLOR_PALETTE_CMP_MARGIN * 2 - GAP_CMP * MAX_COLOR_COUNT) / MAX_COLOR_COUNT;
    for (size_t i = 0; i < MAX_COLOR_COUNT; ++i) {
        rects[i] = (Rectangle){
            COLOR_PALETTE_CMP_MARGIN + i * (size + GAP_CMP),
            COLOR_PALETTE_CMP_Y + COLOR_PALETTE_CMP_H / 2 - size / 2,
            size, size
        };
    }

    Vector2 mouse = GetMousePosition();

    for (size_t i = 0; i < MAX_COLOR_COUNT; ++i) {
        DrawRectangleRec(rects[i], cmp->colors[i]);
        if (CheckCollisionPointRec(mouse, rects[i]) && !ColorIsEqual(cmp->colors[i], config->brush_color)) {
            DrawRectangleLinesEx(rects[i], 3, (Color){235, 235, 235, 200});
        } else if (ColorIsEqual(cmp->colors[i], config->brush_color)) {
            DrawRectangleLinesEx(rects[i], 3, (Color){180, 180, 180, 230});
        } else {
            DrawRectangleLinesEx(rects[i], 2, (Color){230, 230, 230, 100});
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (size_t j = 0; j < MAX_COLOR_COUNT; ++j) {
                Vector2 click = GetMousePosition();
                if (CheckCollisionPointRec(click, rects[j])) {
                    config->brush_color = cmp->colors[j];
                    DrawRectangleRec(
                        rects[j],
                        (Color){
                            cmp->colors[j].r + 40,
                            cmp->colors[j].g + 40,
                            cmp->colors[j].b + 40,
                            200
                        }
                    );
                }
            }
        }
    }
}

void InitComponent(Component *cmp) {
    cmp->color_palette_cmp = malloc(sizeof(ColorPaletteCmp));
    InitColorPaletteCmp(cmp->color_palette_cmp);

    cmp->command_line_cmp = malloc(sizeof(CommandLineCmp));
    InitCommandLineCmp(cmp->command_line_cmp);
    /* ... */
}

void DestroyComponent(Component *cmp) {
    free(cmp->color_palette_cmp);
    free(cmp->command_line_cmp);
    /* ... */
}
