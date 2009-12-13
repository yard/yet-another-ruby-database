#ifndef _MANAGER_H_
#define _MANAGER_H_

void launch_yard();

VALUE rb_yard_saved_object(VALUE);

enum yard_modification_ops {
  // general object modification (replacement)
  OBJECT_MODIFICATION = 0x00,
#define YARD_OBJECT_MODIFICATION OBJECT_MODIFICATION
  // global variable assigned
  GV_SET = 0x08
#define YARD_GV_SET GV_SET
};

int RUBY_TYPE_SIZES[];

VALUE rb_yard_id(VALUE);

VALUE rb_yard_fetch(VALUE, VALUE);

VALUE rb_yard_configure(VALUE, VALUE);

void yard_object_modification(VALUE, VALUE, enum yard_modification_ops, VALUE);

VALUE yard_get_object_by_yid(YID *);

void yard_reset_object_cache(YID * yid);

void yard_set_object_by_yid(YID *, VALUE);

VALUE yard_resolve_stub(VALUE object);

#endif /* _MANAGER_H_ */