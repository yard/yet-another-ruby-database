#include "../../include/yard.h"
#include "../../include/db.h"

#include <time.h>
#include <math.h>
#include <string.h>


// BDB environment control structure
static DB_ENV * db_env = NULL;
// BDB storage engine
static DB * db = NULL;

/*
    Converts the given string into DBT structure to be used as a key.
    
    char * key: key to use.
 */
static DBT string_to_key(char * key) {
  DBT result;
  
  result.data = key;
  result.size = strlen(key);
  
  return result;
}

/*
    Converts the given long into DBT structure to be used as a key.
    
    long key: key to use.
 */
static DBT long_to_key(long key) {
  DBT result;
  
  result.data = (char *)malloc(sizeof(long));
  MEMCPY(result.key, &key, long, 1);
  result.size = sizeof(long);
  
  return result;
}

/*
    Starts the DBD storage engine and loads some auxilary items from it.
    
    char * db_file_name: name of the DB file to create/load.   
 */
static void start_bdb(char * db_file_name) {
  int result = 0;
  DB_TXN * txn = NULL;
  
  // initialize DB environment with transacations and multithreading
  result = db_env_create(&db_env, DB_CREATE | DB_INIT_MPOOL | DB_INIT_TXN | DB_INIT_LOG | DB_INIT_LOCK | DB_RECOVER | DB_THREAD);
  
  if (result != 0) {
    //todo handle errors -- in what a way? 
  }
  
  // create the DB access structure
  result = db_create(&db, db_env, 0);
  
  if (result != 0) {
    //todo handle errors -- in what a way? 
  }
  
  // start open transaction
  db_env->txn_begin(db_env, NULL, &txn, 0);
  // open the DB
  db->open(db, txn, db_file_name, NULL, DB_BTREE, DB_CREATE | DB_THREAD, S_IRUSR | S_IWUSR);
  // commit the open transcation
  db_env->txn_commit(db_env, 0);
}

/*
    Takes care of a proper storage startup and BDB intialization.
 */
void start_storage() {
  start_bdb();  
}

/*
    Performs a non-transactional read from the BDB.
    
    DBT key: key to use.
 */
static DBT bdb_non_transactional_read(DBT key) {
  DBT result;
  db->get(db, &key, &result, 0);
  
  return result;
}

/*
    Reads out data from the BDB storage being given a string key.
    
    STORAGE_STRING_KEY key: key to fetch data with.
 */
STORAGE_DATA read_data(STORAGE_STRING_KEY key) {
  DBT key = string_to_key(key);
  DBT bdb_result = bdb_non_transactional_read(key)
  
  STORAGE_DATA result;
  
  result.data = bdb_result.data;
  result.size = bdb_result.size;
  
  return result;
}

/*
    Reads out data from the BDB storage being given a numeric key.
    
    STORAGE_NUM_KEY key: key to fetch data with.
 */
STORAGE_DATA read_data(STORAGE_NUM_KEY key) {
  DBT key = string_to_key(key);
  DBT bdb_result = bdb_non_transactional_read(key)
  
  STORAGE_DATA result;
  
  result.data = bdb_result.data;
  result.size = bdb_result.size;
  
  return result;
}
