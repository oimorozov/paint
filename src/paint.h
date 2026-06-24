#ifndef PAINT_H
#define PAINT_H

#include "config.h"
#include "component.h"

struct Paint {
    Config *config;
    Component *component;
};
typedef struct Paint Paint;

void InitPaint(Paint *paint);

void UpdatePaint(Paint *paint);
void RenderPaint(Paint *paint);

void DestroyPaint(Paint *paint);

#endif // PAINT_H
