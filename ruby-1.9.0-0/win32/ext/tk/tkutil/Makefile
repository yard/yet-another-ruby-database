
SHELL = /bin/sh

#### Start of system configuration section. ####
top_srcdir = $(topdir)/./..
srcdir = $(top_srcdir)/ext/tk/tkutil
topdir = ../../..
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

RUBY_EXTCONF_H = 
CFLAGS   =  -MD -Zi -O2b2xg- -G6 
INCFLAGS = -I. -I$(arch_hdrdir) -I$(hdrdir) -I$(srcdir)
DEFS     = 
CPPFLAGS =   
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
CLEANFILES = mkmf.log
DISTCLEANFILES = vc*.pdb

all install static install-so install-rb: Makefile


clean:
		@-$(RM) $(CLEANLIBS:/=\) $(CLEANOBJS:/=\) $(CLEANFILES:/=\)

distclean:	clean
		@-$(RM) Makefile $(RUBY_EXTCONF_H) conftest.* mkmf.log
		@-$(RM) core ruby$(EXEEXT) *~ $(DISTCLEANFILES:/=\)

realclean:	distclean
