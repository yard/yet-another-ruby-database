#include "db.h"
#include "ruby.h"

struct __storage_data {
  void * data;
  long size;
};

typedef struct __db_dbt STORAGE_KEY;
typedef struct __storage_data STORAGE_DATA;

struct __global_variable {
  char name[255];
  struct YID id;
};

typedef struct __global_variable GLOBAL_VARIABLE;

// the routine used to start the storage
void start_storage();

STORAGE_DATA read_data(STORAGE_KEY *);
void write_data(STORAGE_KEY *, STORAGE_DATA);
void append_data(STORAGE_KEY *, STORAGE_DATA);
STORAGE_DATA * read_multi_data(STORAGE_KEY *);

STORAGE_KEY * long_to_key(long key);
STORAGE_KEY * string_to_key(char * key);