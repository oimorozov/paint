#include <Cocoa/Cocoa.h>

char *save_file(void) {
    NSSavePanel *panel = [NSSavePanel savePanel];
    [panel setAllowedFileTypes:@[@"png"]];
    if ([panel runModal] == NSModalResponseOK) {
        return strdup([[panel.URL path] UTF8String]);
    }
    return NULL;
}
