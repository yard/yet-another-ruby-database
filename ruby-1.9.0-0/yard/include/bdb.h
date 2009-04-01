#include "db.h"
#include "ruby.h"

typedef struct __db_dbt STORAGE_KEY;
typedef struct __db_dbt STORAGE_DATA;

typedef DB_TXN STORAGE_TRANSACTION;

struct __global_variable {
  char name[255];
  struct YID id;
};

typedef struct __global_variable GLOBAL_VARIABLE;

struct __storage_pair {
  struct __storage_pair * next;
  STORAGE_KEY key;
  STORAGE_DATA data;
};

typedef struct __storage_pair STORAGE_PAIR;

enum storage_schemas {
  OBJECT_SPACE = 0x00,
#define YARD_OBJECT_SPACE_SCHEMA OBJECT_SPACE
  GLOBAL_NAMES = 0x01,
#define YARD_GLOBAL_NAMES_SCHEMA GLOBAL_NAMES
  SYSTEM = 0x02
#define YARD_SYSTEM_SCHEMA SYSTEM  
};

// the routine used to start the storage
void start_storage();

STORAGE_DATA * read_data(int, STORAGE_KEY *);
void write_data(int, STORAGE_KEY *, STORAGE_DATA *, STORAGE_TRANSACTION *);
STORAGE_PAIR * enumerate_records(int);

STORAGE_TRANSACTION * begin_transaction();
void commit_transaction(STORAGE_TRANSACTION *);
void abort_transaction(STORAGE_TRANSACTION *);

STORAGE_KEY * long_to_key(long key);
STORAGE_KEY * string_to_key(char * key);
STORAGE_KEY * yid_to_key(struct YID * key);