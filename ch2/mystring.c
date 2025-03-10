#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "mystring.h"
#include "new.h"

static void* String_ctor(void* _self, va_list* app);
static void* String_dtor(void* _self);
static void* String_clone(const void* _self);
static bool String_differ(const void* _self, const void* _b);

const struct Class _String = {
    sizeof(struct String),
    String_ctor,
    String_dtor,
    String_clone,
    String_differ
};

const void* String = &_String; // extern

static void* String_ctor(void* _self, va_list* app) {
    struct String* self = _self;
    const char* text = va_arg(*app, const char* );

    self->text = malloc(strlen(text) + 1);
    
    assert(self->text);

    strcpy(self->text, text);

    return self;
}

static void* String_dtor(void* _self) {
    struct String* self = _self;

    free(self->text);
    self->text = NULL;

    return self;
}

static void* String_clone(const void* _self) {
    const struct String* self = _self;

    return new(String, self->text);
}

static bool String_differ(const void* _self, const void* _b) {
    const struct String* self = _self;
    const struct String* b = _b;

    if (self == b) {
        return false; 
    }
    
    if (!b || b->class != String) {
        return true;
    }

    return strcmp(self->text, b->text);
}

