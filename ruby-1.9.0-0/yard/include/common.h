#ifndef COMMON_H
#define COMMON_H 1

#include "ruby.h"

// marks the object as persitent one
#define YARD_SAVED_OBJECT 1

// marks the object as local one (=saved on this machine)
#define YARD_LOCAL_OBJECT 2

// setting this flag means the object is just a stub for a YARD object stored somewhere else
#define YARD_OBJECT_STUB 4

#define YARD_OBJECT_SAVED(obj) (RBASIC(obj)->yard_flags & YARD_SAVED_OBJECT == YARD_SAVED_OBJECT)

#endif