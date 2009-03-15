#include "../../include/yard.h"

YardStoreMethod yard_storage_method = NULL;

/*
    Being given a nicely prepared structure, applies ID updates to the object graph.
 
    struct YardModificationResult * replay: what to replay
 */
void replay_modification_result(struct YardModificationResult * replay) {
      
}

/*
    Being given a specially filled structure, invokes neccessary callbacks to store and
    update the objects.
    
    YardModification * modification: modification to perform.
 */
void yard_apply_modification(struct YardModification * modification) {
  struct YardModificationResult * replay = yard_storage_method(modification);
  
  replay_modification_result(replay);
  
  free(replay);   
}
