#ifndef COMMON_H
#define COMMON_H 1

#include "ruby.h"

// marks the object as persitent one
#define YARD_SAVED_OBJECT 1

// marks the object as local one (=saved on this machine)
#define YARD_LOCAL_OBJECT 2

// setting this flag means the object is just a stub for a YARD object stored somewhere else
#define YARD_OBJECT_STUB 4

// means the object is being saved right now. It's ok to attach 
#define YARD_OBJECT_SAVING 8

#define YARD_FLAGS(obj) (RBASIC(obj)->yard_flags)

#define YARD_OBJECT_SAVED(obj) (!IMMEDIATE_P(obj) && RTEST(obj) && (YARD_FLAGS(obj) & YARD_SAVED_OBJECT) == YARD_SAVED_OBJECT)

#define YARD_IS_STUB(obj) (!IMMEDIATE_P(obj) && RTEST(obj) && ((YARD_FLAGS(obj) & YARD_OBJECT_STUB) == YARD_OBJECT_STUB))

#define YARD_ID(obj) (RBASIC(obj)->yard_id)

// checks whether the given global symbol is already defined in this VM
int rb_global_entry_defined(ID id);

// grab at least one level of object graph; deeper nodes may be replaced with links
#define YARD_SHALLOW 1
// grab the whole object graph
#define YARD_FULL 2
// grab as few levels as possible; ideally, grab jsut a reference to the object
#define YARD_REF_ONLY 4

#endif