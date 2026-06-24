#include "component.h"

#include <stdlib.h>
#include <string.h>

#include "raylib.h"

#include "config.h"

void InitColorPaletteCmp(ColorPaletteCmp *cmp) {
    cmp->rect = (Rectangle){0, CMD_LINE_Y, CMD_LINE_W, CMD_LINE_H};
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

void DrawColorPaletteCmp(ColorPaletteCmp *cmp) {
    DrawRectangleRec(cmp->rect, BACKGROUND_COLOR);

    int margin = WINDOW_SIZE * 0.05f;
    int gap = margin * 0.1f;
    int size = (WINDOW_SIZE - gap * (MAX_COLOR_COUNT + 1)) / MAX_COLOR_COUNT;
    for (size_t i = 0; i < MAX_COLOR_COUNT; ++i) {
        int step = i == 0 ? 0 : i * (size + gap);
        DrawRectangle(margin + step, CMD_LINE_Y, size, size, cmp->colors[i]);
    }
}

void InitComponent(Component *cmp) {
    cmp->color_palette_cmp = malloc(sizeof(ColorPaletteCmp));
    InitColorPaletteCmp(cmp->color_palette_cmp);
    /* ... */
}

void DestroyComponent(Component *cmp) {
    free(cmp->color_palette_cmp);
    /* ... */
}
