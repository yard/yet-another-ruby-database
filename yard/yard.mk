YARD_SOURCE = $(srcdir)/yard/
YARD_OBJECTS = ./yard/
YARD_INCLUDE_FLAGS = /I $(arch_hdrdir) /I $(srcdir)/include 
LIBS=$(LIBS) $(YARD_SOURCE)/storage/local/bdb/*.lib
_WIN32=1


COMMONOBJS =  $(COMMONOBJS) \
              $(YARD_OBJECTS)yard_ruby_yard.$(OBJEXT) \
              $(YARD_OBJECTS)yard_manager.$(OBJEXT) \
              $(YARD_OBJECTS)yard_storage_manager.$(OBJEXT) \
              $(YARD_OBJECTS)yard_local_storage.$(OBJEXT) \
              $(YARD_OBJECTS)yard_bdb.$(OBJEXT) \
              $(YARD_OBJECTS)yard_threads.$(OBJEXT) \
              $(YARD_OBJECTS)yard_storage_worker.$(OBJEXT) \
              $(YARD_OBJECTS)yard_txn.$(OBJEXT) \
              $(YARD_OBJECTS)yard_net_server.$(OBJEXT) \
              $(YARD_OBJECTS)yard_net_client.$(OBJEXT) \
              $(YARD_OBJECTS)yard_net_common.$(OBJEXT) \
              $(YARD_OBJECTS)yard_storage_remote_calls.$(OBJEXT)
              

yardall:
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)objects/ruby_yard.c -Fo$(YARD_OBJECTS)yard_ruby_yard.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)objects/manager.c -Fo$(YARD_OBJECTS)yard_manager.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/proxy/storage_manager.c -Fo$(YARD_OBJECTS)yard_storage_manager.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/proxy/txn.c -Fo$(YARD_OBJECTS)yard_txn.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/proxy/storage_worker.c -Fo$(YARD_OBJECTS)yard_storage_worker.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/local/local_storage.c -Fo$(YARD_OBJECTS)yard_local_storage.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/remote/remote_storage.c -Fo$(YARD_OBJECTS)yard_storage_remote_calls.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)storage/local/bdb/bdb.c -Fo$(YARD_OBJECTS)yard_bdb.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)threads/win32_threads.c -Fo$(YARD_OBJECTS)yard_threads.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)net/server.c -Fo$(YARD_OBJECTS)yard_net_server.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)net/client.c -Fo$(YARD_OBJECTS)yard_net_client.$(OBJEXT)
  $(CC) $(CFLAGS) $(YARD_INCLUDE_FLAGS) -c $(YARD_SOURCE)net/common.c -Fo$(YARD_OBJECTS)yard_net_common.$(OBJEXT)