
SHELL = /bin/sh

#### Start of system configuration section. ####
top_srcdir = $(topdir)/./..
srcdir = $(top_srcdir)/ext/socket
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
CPPFLAGS = -DRUBY_EXTCONF_H=\"$(RUBY_EXTCONF_H)\" -I.  
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
DEFFILE = $(TARGET)-$(arch).def

CLEANFILES = mkmf.log
DISTCLEANFILES = vc*.pdb constants.h $(DEFFILE)

extout = $(topdir)/.ext
extout_prefix = $(extout)$(target_prefix)/
target_prefix = 
LOCAL_LIBS = 
LIBS = $(LIBRUBYARG_SHARED) ws2_32.lib  oldnames.lib user32.lib advapi32.lib shell32.lib ws2_32.lib  ./../yard//storage/local/bdb/*.lib 
SRCS = socket.obj getaddrinfo.obj getnameinfo.obj
OBJS = socket.obj getaddrinfo.obj getnameinfo.obj
TARGET = socket
DLLIB = $(TARGET).so
EXTSTATIC = socket
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
$(RUBYARCHDIR):
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

$(RUBYARCHDIR)/$(DLLIB): $(DEFFILE) $(OBJS)
	@-$(RM) $(@:/=\)
	@-$(MAKEDIRS) $(@D)
	$(LDSHARED) -Fe$(@) $(OBJS) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:$(*F:.so=)-$(arch).lib -pdb:$(*F:.so=)-$(arch).pdb -def:$(DEFFILE)

$(STATIC_LIB): $(OBJS)
	@-$(RM) $(@:/=\)
	$(AR) -machine:x86 -out:$@ $(OBJS)

$(DEFFILE): 
	$(RUBY) -e "puts 'EXPORTS', 'Init_$(TARGET)'"  > $@

###
$(OBJS): $(RUBY_EXTCONF_H)

socket.obj: {.;$(VPATH)}socket.c $(hdrdir)/ruby/ruby.h $(arch_hdrdir)/ruby/config.h \
	$(hdrdir)/ruby/defines.h $(hdrdir)/ruby/io.h $(hdrdir)/ruby/signal.h \
	{.;$(VPATH)}sockport.h {.;$(VPATH)}constants.h
getnameinfo.obj: {.;$(VPATH)}getnameinfo.c $(arch_hdrdir)/ruby/config.h {.;$(VPATH)}addrinfo.h {.;$(VPATH)}sockport.h
getaddrinfo.obj: {.;$(VPATH)}getaddrinfo.c $(arch_hdrdir)/ruby/config.h {.;$(VPATH)}addrinfo.h {.;$(VPATH)}sockport.h

constants.h: $(srcdir)/mkconstants.rb
	@echo "generating constants.h"
	@$(RUBY) $(srcdir)/mkconstants.rb > $@
