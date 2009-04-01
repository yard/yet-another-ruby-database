#include "yard.h"

/*
 * The structure represents an internal change being performed on some object.
 */
struct YardModification {
  VALUE object;
  VALUE data;
  VALUE arg;
  
  enum yard_modification_ops operation;
};

/*
 * Maps some YID to an object.
 */
struct YardIdAssignment {
  long src_object_id;
  struct YID yard_id;
  
  struct YardIdAssignment * next;  
};

/*
 * Holds the info about modification results.
 */
struct YardModificationResult {
  int success;
  
  long id_assignment_length;
  struct YardIdAssignment * id_assignments;
};

void initialize_local_storage(char * db_file_name);

void replay_modification_result(struct YardModificationResult *);

void yard_apply_modification(struct YardModification *);

typedef struct YardModificationResult * (*YardStoreMethod)(struct YardModification *);

struct YardModificationResult * yard_local_persist_objects(struct YardModification *);

VALUE yard_local_load_object(struct YID *);

VALUE yard_fetch_stored_object(struct YID *, int);

int yard_local_cookie();
