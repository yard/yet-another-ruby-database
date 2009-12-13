#include "../../../include/yard.h"
#include "../../../include/db.h"

#include <time.h>
#include <math.h>
#include <string.h>


// BDB environment control structure
static DB_ENV * db_env = NULL;
// BDB storage engine
static DB ** dbs = NULL;

static char * OBJECT_SPACE_DB_NAME = "objectspace";
static char * GLOBAL_NAMES_DB_NAME = "namespace";
static char * SYSTEM_DB_NAME = "system";

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
  result->size = strlen(key) + 1;
  
  return result;
}

/*
    Converts the given YID structure into DBT structure to be used as a key.
    
    char * key: key to use.
 */
STORAGE_KEY * yid_to_key(YID * key) {
  STORAGE_KEY * result = (STORAGE_KEY *)allocate_dbt();
  
  result->data = key;
  result->size = sizeof(YID);
  
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

static void init_single_db(DB ** db, DB_ENV * env, char * file_name, char * db_name) {
  int result = 0;
  DB_TXN * txn = NULL;

  // create the DB access structure
  result = db_create(db, env, 0);

  if (result != 0) {
    //todo handle errors -- in what a way? 
    printf("[BDB]: Can't create database: %d", result);
  }

  // start open transaction
  // env->txn_begin(env, NULL, &txn, 0);

  // open the DB
  result = (*db)->open(*db, txn, file_name, db_name, DB_BTREE, DB_CREATE | DB_THREAD, S_IRUSR | S_IWUSR);

  if (result != 0) {
	  (*db)->err(*db, result, "Database  open failed");
	  printf("[BDB]: Can't open database: %d", result);
	  exit(1);
  }

  // commit the open transcation
  // txn->commit(txn, 0);  
}

/*
    Starts the DBD storage engine and loads some auxilary items from it.
    
    char * db_file_name: name of the DB file to create/load.   
 */
static void start_bdb(char * db_file_name, char * db_home) {
  int result = 0;

  dbs = malloc(5 * sizeof(DB *));
  
  // initialize DB environment with transacations and multithreading
  result = db_env_create(&db_env, 0);
  
  if (result != 0) {
    //todo handle errors -- in what a way? 
    db_env->err(db_env, result, "Database  open failed");
    printf("[BDB]: Can't create environment: %d", result);
	exit(1);
  }
  
  result = db_env->open(db_env, db_home, DB_CREATE | DB_INIT_MPOOL | DB_INIT_TXN | DB_INIT_LOG | DB_INIT_LOCK | DB_RECOVER | DB_THREAD, 0);

  if (result != 0) {
    //todo handle errors -- in what a way? 
	db_env->err(db_env, result, "Database  open failed");
    printf("[BDB]: Can't open environment: %d", result);
	exit(1);
  }

  printf("Just created an environemnt. Going to open DBs\n");

  init_single_db(dbs, db_env, db_file_name, OBJECT_SPACE_DB_NAME);
  init_single_db(dbs + 1, db_env, db_file_name, GLOBAL_NAMES_DB_NAME);
  init_single_db(dbs + 2, db_env, db_file_name, SYSTEM_DB_NAME);
}

/*
    Takes care of a proper storage startup and BDB intialization.
 */
void start_storage() {
  start_bdb(yard_db_file_name, yard_db_dir);  
}

/*
    Performs a non-transactional read from the BDB.
    
    DBT key: key to use.
 */
static DBT * bdb_non_transactional_read(int schema, DBT * key) {
  DB * db = dbs[schema];
  DBT * result = allocate_dbt();
  db->get(db, NULL, key, result, 0);
  
  return result;
}

/*  
    Begins a transaction. The transaction object is returned as the result.
 */
STORAGE_TRANSACTION * begin_transaction() {
  STORAGE_TRANSACTION * txn = NULL;
  
  db_env->txn_begin(db_env, NULL, &txn, 0);
  
  return txn;
}

/*
    Commits the transaction passed as the only argument.
    
    STORAGE_TRANSACTION * txn: transaction object to commit.
 */
void commit_transaction(STORAGE_TRANSACTION * txn) {
  txn->commit(txn, 0);
}

/*
    Aborts the transaction passed as the only argument.
    
    STORAGE_TRANSACTION * txn: transaction object to abort.
 */
void abort_transaction(STORAGE_TRANSACTION * txn) {
  txn->abort(txn, 0);
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
static void bdb_transactional_write(int schema, DBT * key, DBT * data, DB_TXN * txn, long flags) {
  long put_result = 0;
  DB * db = dbs[schema];
  DB_TXN * temp_txn = txn;
  
  if (txn == NULL) {
    db_env->txn_begin(db_env, NULL, &temp_txn, 0);
  }
  
  data->flags = key->flags = 0;
  db->put(db, temp_txn, key, data, flags);  
  
  // if the transaction is our, commit it
  if (txn == NULL) {
    temp_txn->commit(temp_txn, 0);
  }
}

/*
    Reads out data from the BDB storage being given a string key.
  
    int schema: schema to use.  
    STORAGE_STRING_KEY key: key to fetch data with.
 */
STORAGE_DATA * read_data(int schema, STORAGE_KEY * key) {
  return bdb_non_transactional_read(schema, key);
}

/*
    Performs a transactional write to BDB.
    
    int schema: schema to use.
    STORAGE_KEY key: key to use.
    STORAGE_DATA data: data to write.
    STORAGE_TRANSACTION * txn: transaction to use (NULL to omit).
 */
void write_data(int schema, STORAGE_KEY * key, STORAGE_DATA * data, STORAGE_TRANSACTION * txn) {
  bdb_transactional_write(schema, key, data, txn, 0);
}

/*
    Reads all the records from the schema given.
    
    int schema: schema to read out records from.
 */
STORAGE_PAIR * enumerate_records(int schema) {
  DBC * cursor = NULL;
  DB * db = dbs[schema];
  db_recno_t record_count = 0;
  int return_code = 0;
  
  STORAGE_PAIR * result = (STORAGE_PAIR *)malloc(sizeof(STORAGE_PAIR));
  STORAGE_PAIR * current = result;
  
  memset(result, 0, sizeof(STORAGE_PAIR));
  
  // initialize a cursor
  db->cursor(db, NULL, &cursor, 0);
  
  // put the cursor to the first record
  current->data.flags = current->key.flags = DB_DBT_MALLOC;
  return_code = cursor->c_get(cursor, &current->key, &current->data, DB_FIRST);
  
  // if no data has been found, just get out of there 
  if (return_code == DB_NOTFOUND) {
    return NULL;
  }
  
  while (return_code == 0) {
    current->next = (STORAGE_PAIR *)malloc(sizeof(STORAGE_PAIR));
    memset(current->next, 0, sizeof(STORAGE_PAIR));   
  
    current->next->data.flags = current->next->key.flags = DB_DBT_MALLOC;
      
    return_code = cursor->c_get(cursor, &current->next->key, &current->next->data, DB_NEXT);
    
    if (return_code == 0) {
      current = current->next;
    }
  }
  
  // mark our end
  current->next = NULL;
  
  cursor->c_close(cursor);

  return result;
}