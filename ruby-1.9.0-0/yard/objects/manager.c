#include "../include/yard.h"

#include "ruby/st.h"

int __yard_started = 0;

int RUBY_TYPE_SIZES[] = {0, 
                         sizeof(Qnil), 
                         sizeof(struct RObject), 
                         sizeof(struct RClass),
                         0,
                         0,
                         sizeof(struct RFloat),
                         sizeof(struct RString),
                         sizeof(struct RRegexp),
                         sizeof(struct RArray),
                         sizeof(long),
                         sizeof(struct RHash),
                         sizeof(struct RStruct),
                         0};

st_table * __yard_cache = NULL;

static int st_yidcmp(st_data_t, st_data_t);
static int st_yidhash(st_data_t);

static const struct st_hash_type type_yidhash = {
    st_yidcmp,
    st_yidhash,
};

int st_yidcmp(st_data_t x, st_data_t y)
{
    return (((struct YID *)x)->id == ((struct YID *)y)->id) && (((struct YID *)x)->cookie == ((struct YID *)y)->cookie);
}

int st_yidhash(st_data_t id)
{
    return (int)(((struct YID *)id)->id << 16 + ((struct YID *)id)->cookie);
}

/*
  Checks if the passed object should be saved separately.
      
  VALUE object: object to check.
 */
int yard_type_persistable(VALUE object) {
  enum ruby_value_type object_type = TYPE(object);
  
  if (object_type == RUBY_T_FLOAT ||
      object_type == RUBY_T_STRING ||
      object_type == RUBY_T_BIGNUM ||
      object_type == RUBY_T_STRING ||
      object_type == RUBY_T_SYMBOL ||
      object_type == RUBY_T_TRUE ||
      object_type == RUBY_T_NIL ||
      object_type == RUBY_T_CLASS ||
      object_type == RUBY_T_MODULE ||
      object_type == RUBY_T_FALSE ||
      object_type == RUBY_T_FIXNUM) {
    return 0;
  }
  
  return 1;
}

/*
    Fetches a pointer to some data stored in yard symbol table.
    
    struct YID * yid: id to fetch the object by.
 */
VALUE yard_get_object_by_yid(struct YID * yid) {
  VALUE result = NULL;
  st_lookup(__yard_cache, yid, &result);    

  if (!result) {
    result = yard_local_load_object(yid);
    yard_set_object_by_yid(yid, result);
  }
  
  return result;
}

/*
    Saves the given pointer to the symbol table.
    
    struct YID * yid: yid to use.
    void * data: data to save.
 */
void yard_set_object_by_yid(struct YID * yid, VALUE data) {
  st_insert(__yard_cache, yid, data);
}

/*
    Takes care of loading and replacing the object's content with true one.
    
    VALUE object: object to load & replace.
 */
static VALUE _yard_resolve_stub(VALUE object) {
  // load real value for the object
  VALUE not_a_stub = yard_get_object_by_yid(&YARD_ID(object));
  
  // copy everything in place of this object
  memcpy(object, not_a_stub, RUBY_TYPE_SIZES[BUILTIN_TYPE(not_a_stub)]);
  
  return object; 
}

/*
    Inlined method just to make it run hell fast.
    
    VALUE object: object to check for stubbness.
 */
VALUE yard_resolve_stub(VALUE object) {
  if (!YARD_IS_STUB(object)) {
    return object;
  }
  
  return _yard_resolve_stub(object);
}

/*
    Initializes a hash to be used by YARD's cache.
 */
static void init_yard_cache() {
  __yard_cache = st_init_table(&type_yidhash);
}

/*
    Starts up the YARD engine. It sets global flag __yard_started,
    should also initialize storage (if attached), networking, preload
    all the objects.
      
 */
void launch_yard() {
  // launch yard object cache.
  init_yard_cache();
  // launch local storage engine
  initialize_local_storage("default.db");
  // mark the yard engine as started
  __yard_started = 1;
}