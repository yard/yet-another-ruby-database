struct global_variable {
  int   counter;
  void *data;
  VALUE (*getter)();
  void  (*setter)();
  void  (*marker)();
  int block_trace;
  
  struct trace_var *trace;
};

#ifndef __STRUCT_GLOBAL_ENTRY
#define __STRUCT_GLOBAL_ENTRY
struct global_entry {
    struct global_variable *var;
    ID id;
};
#endif