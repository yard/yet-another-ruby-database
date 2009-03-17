#include "../../../include/yard.h"
#include "../../../include/db.h"

#include <time.h>
#include <math.h>
#include <string.h>


// BDB environment control structure
static DB_ENV * db_env = NULL;
// BDB storage engine
static DB * db = NULL;

/*
    Allocates and intializes DBT struct.
    It also sets DB_DBT_MALLOC flag telling the world BDB is responsible for allocating
    the memory, and the app is responsible for freeing it.
 */
static DBT * allocate_dbt() {
  DBT * result = (DBT *)malloc(sizeof(DBT));
  memset(result, 0, sizeof(DBT));
  result->flags = DB_DBT_MALLOC;
  
  return result; 
}

static void free_dbt(DBT * dbt) {
  free(dbt);
}

/*
    Converts the given string into DBT structure to be used as a key.
    
    char * key: key to use.
 */
STORAGE_KEY * string_to_key(char * key) {
  STORAGE_KEY * result = (STORAGE_KEY *)allocate_dbt();
  
  result->data = key;
  result->size = strlen(key);
  
  return result;
}

/*
    Converts the given long into DBT structure to be used as a key.
    
    long key: key to use.
 */
STORAGE_KEY * long_to_key(long key) {
  STORAGE_KEY * result = (STORAGE_KEY *)allocate_dbt();
  
  result->data = (char *)malloc(sizeof(long));
  MEMCPY(result->data, &key, long, 1);
  result->size = sizeof(long);
  
  return result;
}

/*
    Starts the DBD storage engine and loads some auxilary items from it.
    
    char * db_file_name: name of the DB file to create/load.   
 */
static void start_bdb(char * db_file_name, char * db_home) {
  int result = 0;
  DB_TXN * txn = NULL;

  // initialize DB environment with transacations and multithreading
  result = db_env_create(&db_env, 0);
  
  if (result != 0) {
    //todo handle errors -- in what a way? 
    printf("[BDB]: Can't create environment: %d", result);
  }
  
  
  db_env->open(db_env, db_home, DB_CREATE | DB_INIT_MPOOL | DB_INIT_TXN | DB_INIT_LOG | DB_INIT_LOCK | DB_RECOVER | DB_THREAD, 0);

  if (result != 0) {
    //todo handle errors -- in what a way? 
    printf("[BDB]: Can't open environment: %d", result);
  }

  // create the DB access structure
  result = db_create(&db, db_env, 0);

  if (result != 0) {
    //todo handle errors -- in what a way? 
    printf("[BDB]: Can't create database: %d", result);
  }

  // start open transaction
  db_env->txn_begin(db_env, NULL, &txn, 0);

  // allow duplicate records
  db->set_flags(db, DB_DUP);

  // open the DB
  db->open(db, txn, db_file_name, NULL, DB_BTREE, DB_CREATE | DB_THREAD, S_IRUSR | S_IWUSR);

  // commit the open transcation
  txn->commit(txn, 0);
}

/*
    Takes care of a proper storage startup and BDB intialization.
 */
void start_storage() {
  start_bdb("./yard.db", "./");  
}

/*
    Performs a non-transactional read from the BDB.
    
    DBT key: key to use.
 */
static DBT * bdb_non_transactional_read(DBT * key) {
  DBT * result = allocate_dbt();
  db->get(db, NULL, key, result, 0);
  
  return result;
}

/*
    Performs a transactional write to BDB instance. If txn passed is NULL,
    a new transaction is created and commited instantly. Otherwise, the existing
    transaction is used and not commited after write.
    
    DBT key: key to store data under.
    DBT data: data to store.
    DB_TXN * txn: a pointer to transaction to re-use.
    long flags: flags to use to store the record.
 */
static void bdb_transactional_write(DBT * key, DBT * data, DB_TXN * txn, long flags) {
  long put_result = 0;
  DB_TXN * temp_txn = txn;
  DBC * cursor = NULL;
  DBT * temp = allocate_dbt();
  
  if (txn == NULL) {
    db_env->txn_begin(db_env, NULL, &temp_txn, 0);
  }
    
  db->cursor(db, temp_txn, &cursor, 0);
  
  // let's check whether to add entry to a chain or just start a new chain
  put_result = cursor->c_get(cursor, key, temp, DB_SET);
  if (put_result == 0) {
    // got such record -- append/replace
    cursor->c_put(cursor, key, data, flags);
  } else {
    // no such record -- just add
    cursor->c_put(cursor, key, data, DB_KEYFIRST);
  }
  
  // we need to close the cursor in any way :)
  cursor->c_close(cursor);  
  
  // and free dbt structure
  free_dbt(temp);
  
  // if the transaction is our, commit it
  if (txn == NULL) {
    temp_txn->commit(temp_txn, 0);
  }
}

/*
    Reads out data from the BDB storage being given a string key.
    
    STORAGE_STRING_KEY key: key to fetch data with.
 */
STORAGE_DATA read_data(STORAGE_KEY * key) {
  DBT * bdb_result = bdb_non_transactional_read(key);
  
  STORAGE_DATA result;
  
  result.data = bdb_result->data;
  result.size = bdb_result->size;
  
  return result;
}

/*
    Performs a transactional write to BDB.
    
    STORAGE_KEY key: key to use.
    STORAGE_DATA data: data to write.
 */
void write_data(STORAGE_KEY * key, STORAGE_DATA data) {
  DBT * bdb_data = allocate_dbt();
   
  bdb_data->data = data.data; bdb_data->size = data.size;
  
  bdb_transactional_write(key, bdb_data, NULL, DB_CURRENT);
  
  free_dbt(bdb_data);
}

/*  
    Writes a chunk of data appending it to previously save entries for the given key.
    
    STORAGE_KEY * key: key to append data to.
    STORAGE_DATA data: data to append.
 */
void append_data(STORAGE_KEY * key, STORAGE_DATA data) {
  DBT * bdb_data = allocate_dbt();
   
  bdb_data->data = data.data; bdb_data->size = data.size;
  
  bdb_transactional_write(key, bdb_data, NULL, DB_KEYFIRST);
  
  free_dbt(bdb_data);
}

/*
    Reads out all the records stored under the given key and places them into a linked
    list structure.
    
    STORAGE_KEY * key: key to read records for.
 */
STORAGE_DATA * read_multi_data(STORAGE_KEY * key) {
  DBC * cursor = NULL;
  STORAGE_DATA * result = NULL;
  DBT * data = allocate_dbt();
  int i = 0;
  int ret = 0;
  db_recno_t record_count = 0;
  
  // initialize a cursor
  db->cursor(db, NULL, &cursor, 0);
  
  // point the cursor to the first duplicate
  ret = cursor->c_get(cursor, key, data, DB_SET);
  
  if (ret == 0) {
    // count records associated with the cursor
    cursor->c_count(cursor, &record_count, 0);
     
    // allocate memory for result and intermediate data
    result = (STORAGE_DATA *)malloc(sizeof(STORAGE_DATA) * record_count + 1);  
    
    // let's do it record_count times
    for(i = 0; i < record_count; i++) {  
      // save the data to results    
      result[i].data = data->data;
      result[i].size = data->size;
      
      // fetch next duplicate
      cursor->c_get(cursor, key, data, DB_NEXT_DUP);
    } 
   
    // mark the last result (c-style, I know)
    // btw, can you propose anything better? it's quite late and I'm kinda slow now :(
    // while proposing a brand new approach, please ensure it's O(n) with good constants; here we have 1
    result[record_count].data = 0;
  } else {
    result = NULL;
  }
  
  free_dbt(data);

  // free cursor 
  cursor->c_close(cursor);   
  
  return result;
}