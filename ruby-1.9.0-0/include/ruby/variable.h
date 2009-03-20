struct global_variable {
  int   counter;
  void *data;
  VALUE (*getter)();
  void  (*setter)();
  void  (*marker)();
  int block_trace;
  
  struct trace_var *trace;
};

struct global_entry {
  struct global_variable *var;
  ID id;
};