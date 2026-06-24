#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "raylib.h"

#include "config.h"

struct CommandLineCmp {
    Rectangle rect;
};
typedef struct CommandLineCmp CommandLineCmp;

void InitCommandLineCmp(CommandLineCmp *cmp);

void DrawCommandLineCmp(CommandLineCmp *cmp);
void DrawCommandLineTextCmp(const char *text);

#define MAX_COLOR_COUNT 21
struct ColorPaletteCmp {
    Rectangle rect;
    Color colors[MAX_COLOR_COUNT];
};
typedef struct ColorPaletteCmp ColorPaletteCmp;

void InitColorPaletteCmp(ColorPaletteCmp *cmp);

void DrawColorPaletteCmp(ColorPaletteCmp *cmp, Config *config);

struct Component {
    ColorPaletteCmp *color_palette_cmp;
    CommandLineCmp *command_line_cmp;
    /* ... */
};
typedef struct Component Component;

void InitComponent(Component *cmp);

void DestroyComponent(Component *cmp);

#endif // COMPONENTS_H
