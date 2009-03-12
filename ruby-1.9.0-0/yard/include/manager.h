void launch_yard();

VALUE rb_yard_saved_object(VALUE);

enum yard_modification_ops {
  // general object modification (replacement)
  OBJECT_MODIFCATION = 0x00,
#define YARD_OBJECT_MODIFCATION OBJECT_MODIFCATION
  // object instance variable set
  OBJECT_IV_SET = 0x01,
#define YARD_OBJECT_IV_SET OBJECT_IV_SET
  // array element push
  ARRAY_ELEMENT_PUSH = 0x02,
#define YARD_ARRAY_ELEMENT_PUSH ARRAY_ELEMENT_PUSH
  // array element change
  ARRAY_ELEMENT_CHANGE = 0x03,
#define YARD_ARRAY_ELEMENT_CHANGE ARRAY_ELEMENT_CHANGE
  // array element removal
  ARRAY_ELEMENT_REMOVAL = 0x04,
#define YARD_ARRAY_ELEMENT_REMOVAL ARRAY_ELEMENT_REMOVAL
  // hash element push
  HASH_ELEMENT_PUSH = 0x05,
#define YARD_HASH_ELEMENT_PUSH HASH_ELEMENT_PUSH
  // hash element change
  HASH_ELEMENT_CHANGE = 0x06,
#define YARD_HASH_ELEMENT_CHANGE HASH_ELEMENT_CHANGE
  // hash element removal
  HASH_ELEMENT_REMOVAL = 0x07,
#define YARD_HASH_ELEMENT_REMOVAL HASH_ELEMENT_REMOVAL
  // global variable defined
  GV_SET = 0x08
#define YARD_GV_SET GV_SET
};

VALUE rb_yard_id(VALUE);

void yard_object_modification(VALUE, VALUE, enum yard_modification_ops, VALUE);
