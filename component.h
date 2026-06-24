#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "raylib.h"

#define MAX_COLOR_COUNT 21

struct ColorPaletteCmp {
    Rectangle rect;
    Color colors[MAX_COLOR_COUNT];
};
typedef struct ColorPaletteCmp ColorPaletteCmp;

void InitColorPaletteCmp(ColorPaletteCmp *cmp);

void DrawColorPaletteCmp(ColorPaletteCmp *cmp);

struct Component {
    ColorPaletteCmp *color_palette_cmp;
    /* ... */
};
typedef struct Component Component;

void InitComponent(Component *cmp);

void DestroyComponent(Component *cmp);

#endif // COMPONENTS_H
