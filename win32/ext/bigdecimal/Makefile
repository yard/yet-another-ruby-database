
SHELL = /bin/sh

#### Start of system configuration section. ####
top_srcdir = $(topdir)/./..
srcdir = $(top_srcdir)/ext/bigdecimal
topdir = ../..
hdrdir = $(top_srcdir)/include
arch_hdrdir = $(extout)/include/$(arch)
VPATH = $(srcdir);$(arch_hdrdir)/ruby;$(hdrdir)/ruby
RUBYLIB = -
RUBYOPT = -rpurelib.rb
prefix = $(DESTDIR)/usr
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
sbindir = $(exec_prefix)/sbin
libexecdir = $(exec_prefix)/libexec
datadir = $(prefix)/share
sysconfdir = $(prefix)/etc
sharedstatedir = $(DESTDIR)/etc
localstatedir = $(DESTDIR)/var
libdir = $(exec_prefix)/lib
includedir = $(prefix)/include
oldincludedir = $(DESTDIR)/usr/include
infodir = $(prefix)/info
mandir = $(prefix)/man
sitedir = $(prefix)/lib/ruby/site_ruby
vendordir = $(prefix)/lib/ruby/vendor_ruby
rubyhdrdir = $(includedir)/ruby-$(MAJOR).$(MINOR).$(TEENY)
sitehdrdir = $(rubyhdrdir)/site_ruby
vendorhdrdir = $(rubyhdrdir)/vendor_ruby
rubylibdir = $(libdir)/ruby/$(ruby_version)
archdir = $(rubylibdir)/$(arch)
sitelibdir = $(sitedir)/$(ruby_version)
sitearchdir = $(sitelibdir)/$(sitearch)
vendorlibdir = $(vendordir)/$(ruby_version)
vendorarchdir = $(vendorlibdir)/$(sitearch)

CC = cl -nologo
CXX = $(CC)
LIBRUBY = $(RUBY_SO_NAME).lib
LIBRUBY_A = $(RUBY_SO_NAME)-static.lib
LIBRUBYARG_SHARED = $(LIBRUBY)
LIBRUBYARG_STATIC = $(LIBRUBY_A)
OUTFLAG = -Fe
COUTFLAG = -Fo

RUBY_EXTCONF_H = extconf.h
CFLAGS   =  -MD -Zi -O2b2xg- -G6 
INCFLAGS = -I. -I$(arch_hdrdir) -I$(hdrdir) -I$(srcdir)
DEFS     = 
CPPFLAGS = -DRUBY_EXTCONF_H=\"$(RUBY_EXTCONF_H)\"  
CXXFLAGS = $(CFLAGS) -MD -Zi -O2b2xg- -G6
ldflags  = 
dldflags = -link -incremental:no -debug -opt:ref -opt:icf -dll $(LIBPATH)
archflag = 
DLDFLAGS = $(ldflags) $(dldflags) $(archflag)
LDSHARED = cl -nologo -LD
LDSHAREDXX = $(LDSHARED)
AR = lib -nologo
EXEEXT = .exe

RUBY_INSTALL_NAME = ruby
RUBY_SO_NAME = msvcrt-ruby190
arch = i386-mswin32
sitearch = i386-msvcrt
ruby_version = 1.9.0
ruby = $(topdir:/=\)\miniruby.exe -I'$(topdir)' -I'$(top_srcdir)/lib' -I'$(extout)/$(arch)' -I'$(extout)/common' -I'$(top_srcdir)/ext' -rpurelib.rb
RUBY = $(ruby)
RM = $(COMSPEC) /C $(top_srcdir:/=\)\win32\rm.bat
MAKEDIRS = @$(RUBY) -run -e mkdir -- -p
INSTALL = @$(RUBY) -run -e install -- -vp
INSTALL_PROG = $(INSTALL) -m 0755
INSTALL_DATA = $(INSTALL) -m 0644
COPY = copy > nul

#### End of system configuration section. ####

preload = 

libpath = . $(topdir)
LIBPATH =  -libpath:"." -libpath:"$(topdir)"
DEFFILE = $(srcdir)/$(TARGET).def

CLEANFILES = mkmf.log
DISTCLEANFILES = vc*.pdb

extout = $(topdir)/.ext
extout_prefix = $(extout)$(target_prefix)/
target_prefix = 
LOCAL_LIBS = 
LIBS = $(LIBRUBYARG_SHARED)  oldnames.lib user32.lib advapi32.lib shell32.lib ws2_32.lib  ./../yard//storage/local/bdb/*.lib 
SRCS = bigdecimal.c
OBJS = bigdecimal.obj
TARGET = bigdecimal
DLLIB = $(TARGET).so
EXTSTATIC = 
STATIC_LIB = $(TARGET).lib

RUBYCOMMONDIR = $(extout)/common
RUBYLIBDIR    = $(RUBYCOMMONDIR)$(target_prefix)
RUBYARCHDIR   = $(extout)/$(arch)$(target_prefix)
HDRDIR        = $(extout)/include/ruby$(target_prefix)
ARCHHDRDIR    = $(extout)/include/$(arch)/ruby$(target_prefix)

TARGET_SO     = $(RUBYARCHDIR)/$(DLLIB)
CLEANLIBS     = $(RUBYARCHDIR)/$(TARGET).so $(RUBYARCHDIR)/$(TARGET).il? $(RUBYARCHDIR)/$(TARGET).tds $(RUBYARCHDIR)/$(TARGET).map
CLEANOBJS     = *.obj *.lib *.s[ol] *.pdb *.exp *.bak

all:		install
static:		$(STATIC_LIB) install-rb

clean:
		@-$(RM) $(CLEANLIBS:/=\) $(CLEANOBJS:/=\) $(CLEANFILES:/=\)

distclean:	clean
		@-$(RM) Makefile $(RUBY_EXTCONF_H) conftest.* mkmf.log
		@-$(RM) core ruby$(EXEEXT) *~ $(DISTCLEANFILES:/=\)

realclean:	distclean
install: install-so install-rb

install-so: $(RUBYARCHDIR)
install-so: $(RUBYARCHDIR)/$(DLLIB)
install-rb: pre-install-rb install-rb-default
install-rb-default: pre-install-rb-default
pre-install-rb: Makefile
pre-install-rb-default: Makefile
pre-install-rb-default: $(RUBYLIBDIR)/bigdecimal
install-rb-default: $(RUBYLIBDIR)/bigdecimal/jacobian.rb
$(RUBYLIBDIR)/bigdecimal/jacobian.rb: $(srcdir)/lib/bigdecimal/jacobian.rb $(RUBYLIBDIR)/bigdecimal
	$(COPY) $(srcdir:/=\)\lib\bigdecimal\jacobian.rb $(@D:/=\)
install-rb-default: $(RUBYLIBDIR)/bigdecimal/ludcmp.rb
$(RUBYLIBDIR)/bigdecimal/ludcmp.rb: $(srcdir)/lib/bigdecimal/ludcmp.rb $(RUBYLIBDIR)/bigdecimal
	$(COPY) $(srcdir:/=\)\lib\bigdecimal\ludcmp.rb $(@D:/=\)
install-rb-default: $(RUBYLIBDIR)/bigdecimal/math.rb
$(RUBYLIBDIR)/bigdecimal/math.rb: $(srcdir)/lib/bigdecimal/math.rb $(RUBYLIBDIR)/bigdecimal
	$(COPY) $(srcdir:/=\)\lib\bigdecimal\math.rb $(@D:/=\)
install-rb-default: $(RUBYLIBDIR)/bigdecimal/newton.rb
$(RUBYLIBDIR)/bigdecimal/newton.rb: $(srcdir)/lib/bigdecimal/newton.rb $(RUBYLIBDIR)/bigdecimal
	$(COPY) $(srcdir:/=\)\lib\bigdecimal\newton.rb $(@D:/=\)
install-rb-default: $(RUBYLIBDIR)/bigdecimal/util.rb
$(RUBYLIBDIR)/bigdecimal/util.rb: $(srcdir)/lib/bigdecimal/util.rb $(RUBYLIBDIR)/bigdecimal
	$(COPY) $(srcdir:/=\)\lib\bigdecimal\util.rb $(@D:/=\)
$(RUBYARCHDIR):
	$(MAKEDIRS) $@
$(RUBYLIBDIR)/bigdecimal:
	$(MAKEDIRS) $@

site-install: site-install-so site-install-rb
site-install-so: install-so
site-install-rb: install-rb

.SUFFIXES: .c .m .cc .cxx .cpp .obj

{$(hdrdir)}.cc{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(topdir)}.cc{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(srcdir)}.cc{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

.cc.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(hdrdir)}.cxx{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(topdir)}.cxx{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(srcdir)}.cxx{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

.cxx.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(hdrdir)}.cpp{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(topdir)}.cpp{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(srcdir)}.cpp{}.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

.cpp.obj:
	$(CXX) $(INCFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tp$(<:\=/)

{$(hdrdir)}.c{}.obj:
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)

{$(topdir)}.c{}.obj:
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)

{$(srcdir)}.c{}.obj:
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)

.c.obj:
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)

$(RUBYARCHDIR)/$(DLLIB): $(OBJS)
	@-$(RM) $(@:/=\)
	@-$(MAKEDIRS) $(@D)
	$(LDSHARED) -Fe$(@) $(OBJS) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:$(*F:.so=)-$(arch).lib -pdb:$(*F:.so=)-$(arch).pdb -def:$(DEFFILE)

$(STATIC_LIB): $(OBJS)
	@-$(RM) $(@:/=\)
	$(AR) -machine:x86 -out:$@ $(OBJS)

###
$(OBJS): $(RUBY_EXTCONF_H)

bigdecimal.obj: {.;$(VPATH)}bigdecimal.c {.;$(VPATH)}bigdecimal.h $(hdrdir)/ruby/ruby.h
