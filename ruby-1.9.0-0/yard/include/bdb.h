struct __storage_data {
  void * data;
  long size;
};

typedef char * STORAGE_STRING_KEY;
typedef long STORAGE_NUM_KEY;
typedef struct __storage_data STORAGE_DATA;

// the routine used to start the storage
void start_storage();

STORAGE_DATA read_data(STORAGE_STRING_KEY);
STORAGE_DATA read_data(STORAGE_NUM_KEY);