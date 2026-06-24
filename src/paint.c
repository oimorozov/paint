#include "paint.h"

#include <stdlib.h>

void InitPaint(Paint *paint) {
    paint->config = malloc(sizeof(Config));
    paint->component = malloc(sizeof(Component));
}

void UpdatePaint(Paint *paint) {

}

void RenderPaint(Paint *paint) {

}

void DestroyPaint(Paint *paint) {
    free(paint->config);
    free(paint->component);
}
