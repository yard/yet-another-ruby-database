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


void yard_setup_storage_settings(int, int, char *, char *);

void initialize_local_storage();

void replay_modification_result(YARD_MODIFICATION_RESULT *);

void yard_apply_modification_async(YARD_MODIFICATION *);

void yard_apply_modification_sync(YARD_MODIFICATION *);

void yard_revert_object_sync(VALUE object, char *);

typedef YARD_MODIFICATION_RESULT * (*YardStoreMethod)(YARD_MODIFICATION *);

YARD_MODIFICATION_RESULT * yard_local_persist_objects(YARD_MODIFICATION *);

VALUE yard_local_load_object(YID *);

VALUE yard_local_load_global_variable(char * name);

VALUE yard_fetch_stored_object(YID *, int);

VALUE yard_fetch_global_variable(char *, int);

int yard_local_cookie();

int yard_master();

/*
    Initializes the dispatching of the requests from remote machines.
*/
void yard_net_initialize_network_dispatcher();

/*
    Performs a request to save and assign to a global variable.  
*/
void yard_remote_assign_to_global_variable(char * name, VALUE object);

/*
    Attempts to fetch the object being given its id.
*/
VALUE yard_remote_fetch_object(YID *);

char * yard_db_file_name, * yard_db_dir;