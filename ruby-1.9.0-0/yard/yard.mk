YARD_SOURCE = $(srcdir)/yard/
YARD_OBJECTS = ./yard/
YARD_INCLUDE_FLAGS = /I $(arch_hdrdir) /I $(srcdir)/include 
LIBS=$(LIBS) $(YARD_SOURCE)/storage/local/bdb/*.lib

COMMONOBJS =  $(COMMONOBJS) \
              $(YARD_OBJECTS)yard_ruby_yard.$(OBJEXT) \
              $(YARD_OBJECTS)yard_manager.$(OBJEXT) \
              $(YARD_OBJECTS)yard_marshal.$(OBJEXT) \
              $(YARD_OBJECTS)yard_storage_manager.$(OBJEXT) \
              $(YARD_OBJECTS)yard_local_storage.$(OBJEXT) \
              $(YARD_OBJECTS)yard_bdb.$(OBJEXT) \

yardall:
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)objects/ruby_yard.c -Fo$(YARD_OBJECTS)yard_ruby_yard.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)objects/manager.c -Fo$(YARD_OBJECTS)yard_manager.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)objects/marshal.c -Fo$(YARD_OBJECTS)yard_marshal.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/proxy/storage_manager.c -Fo$(YARD_OBJECTS)yard_storage_manager.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/local/local_storage.c -Fo$(YARD_OBJECTS)yard_local_storage.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/local/bdb/bdb.c -Fo$(YARD_OBJECTS)yard_bdb.$(OBJEXT)