#include "yard.h"

/*
 * The structure represents an internal change being performed on some object.
 */
struct _yard_modification {
  VALUE object;
  VALUE data;
  VALUE arg;
  
  enum yard_modification_ops operation;
};

typedef struct _yard_modification YARD_MODIFICATION; 

/*
 * Maps some YID to an object.
 */
struct __yard_id_assignment {
  long src_object_id;
  YID yard_id;
  
  struct __yard_id_assignment * next;  
};

typedef struct __yard_id_assignment YARD_ID_ASSIGNMENT; 

/*
 * Holds the info about modification results.
 */
struct __yard_modification_result {
  int success;
  
  long id_assignment_length;
  YARD_ID_ASSIGNMENT * id_assignments;
};

typedef struct __yard_modification_result YARD_MODIFICATION_RESULT;



void initialize_local_storage(char * db_file_name);

void replay_modification_result(YARD_MODIFICATION_RESULT *);

void yard_apply_modification_async(YARD_MODIFICATION *);

void yard_apply_modification_sync(YARD_MODIFICATION *);

typedef YARD_MODIFICATION_RESULT * (*YardStoreMethod)(YARD_MODIFICATION *);

YARD_MODIFICATION_RESULT * yard_local_persist_objects(YARD_MODIFICATION *);

VALUE yard_local_load_object(YID *);

VALUE yard_fetch_stored_object(YID *, int);

int yard_local_cookie();
