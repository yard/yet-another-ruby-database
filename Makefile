SHELL = /bin/sh
NULLCMD = :

#### Start of system configuration section. ####

srcdir = .
hdrdir = $(srcdir)/include

CC = gcc
YACC = bison
PURIFY =
AUTOCONF = autoconf

MKFILES = Makefile
BASERUBY = ruby

prefix = /usr/local
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
datarootdir = ${prefix}/share
datadir = ${datarootdir}
arch = i686-darwin9.8.0
sitearch = i686-darwin9.8.0
sitedir = ${prefix}/lib/ruby/site_ruby

TESTUI = console
TESTS =
RDOCTARGET = install-doc

EXTOUT = .ext
RIDATADIR = $(DESTDIR)$(datadir)/ri/$(MAJOR).$(MINOR)/system
arch_hdrdir = $(EXTOUT)/include/$(arch)
VPATH = $(arch_hdrdir)/ruby:$(hdrdir)/ruby:$(srcdir)/enc:$(srcdir)/missing

empty =
OUTFLAG = -o $(empty)
COUTFLAG = -o $(empty)
CFLAGS = -g -O2 -pipe -fno-common ${cflags} 
XCFLAGS = -I. -I$(arch_hdrdir) -I$(hdrdir) -I$(srcdir)  -DRUBY_EXPORT
CPPFLAGS =  $(DEFS) ${cppflags}
LDFLAGS =  $(CFLAGS) -L. 
EXTLDFLAGS = 
XLDFLAGS =  $(EXTLDFLAGS)
EXTLIBS = 
LIBS = -lpthread -ldl -lobjc  $(EXTLIBS)
MISSING =  
LDSHARED = cc -dynamic -bundle -undefined suppress -flat_namespace
DLDFLAGS =  $(EXTLDFLAGS) 
SOLIBS = 
MAINLIBS = 
MINIOBJS = dmydln.o miniprelude.$(OBJEXT)
BUILTIN_ENCOBJS =  ascii.$(OBJEXT) euc_jp.$(OBJEXT) sjis.$(OBJEXT) unicode.$(OBJEXT) utf8.$(OBJEXT)

RUBY_INSTALL_NAME=ruby
RUBY_SO_NAME=$(RUBY_INSTALL_NAME)
EXEEXT = 
PROGRAM=$(RUBY_INSTALL_NAME)$(EXEEXT)
RUBY = $(RUBY_INSTALL_NAME)
MINIRUBY = ./miniruby$(EXEEXT) $(MINIRUBYOPT)
RUNRUBY = $(MINIRUBY) $(srcdir)/runruby.rb --extout=$(EXTOUT) $(RUNRUBYOPT) --

#### End of system configuration section. ####

MAJOR=	1
MINOR=	9
TEENY=	0

LIBRUBY_A     = lib$(RUBY_SO_NAME)-static.a
LIBRUBY_SO    = lib$(RUBY_SO_NAME).so.$(MAJOR).$(MINOR).$(TEENY)
LIBRUBY_ALIASES= lib$(RUBY_SO_NAME).so
LIBRUBY	      = $(LIBRUBY_A)
LIBRUBYARG    = $(LIBRUBYARG_STATIC)
LIBRUBYARG_STATIC = -l$(RUBY_SO_NAME)-static
LIBRUBYARG_SHARED = 

THREAD_MODEL  = pthread

PREP          = miniruby$(EXEEXT)
ARCHFILE      = 
SETUP         =
EXTSTATIC     = 

CP            = cp
MV            = mv
RM            = rm -f
NM            = 
AR            = ar
ARFLAGS       = rcu
RANLIB        = ranlib
AS            = as
ASFLAGS       = 

OBJEXT        = o
ASMEXT        = S
DLEXT         = bundle
MANTYPE	      = doc

INSTALLED_LIST= .installed.list
#### End of variables

all:

.DEFAULT: all

# Prevent GNU make v3 from overflowing arg limit on SysV.
.NOEXPORT:

miniruby$(EXEEXT):
		@$(RM) $@
		$(PURIFY) $(CC) $(LDFLAGS) $(XLDFLAGS) $(MAINLIBS) $(MAINOBJ) $(MINIOBJS) $(COMMONOBJS) $(DMYEXT) $(ARCHFILE) $(LIBS) $(OUTFLAG)$@

$(PROGRAM):
		@$(RM) $@
		$(PURIFY) $(CC) $(LDFLAGS) $(XLDFLAGS) $(MAINLIBS) $(MAINOBJ) $(EXTOBJS) $(LIBRUBYARG) $(LIBS) $(OUTFLAG)$@

# We must `rm' the library each time this rule is invoked because "updating" a
# MAB library on Apple/NeXT (see --enable-fat-binary in configure) is not
# supported.
$(LIBRUBY_A):
		@$(RM) $@
		$(AR) $(ARFLAGS) $@ $(OBJS) $(DMYEXT)
		@-$(RANLIB) $@ 2> /dev/null || true

$(LIBRUBY_SO):
		@-$(PRE_LIBRUBY_UPDATE)
		$(LDSHARED) $(DLDFLAGS) $(OBJS) $(DLDOBJS) $(SOLIBS) $(OUTFLAG)$@
		@-$(MINIRUBY) -e 'ARGV.each{|link| File.delete link if File.exist? link; \
						  File.symlink "$(LIBRUBY_SO)", link}' \
				$(LIBRUBY_ALIASES) || true

fake.rb:	Makefile
		@echo ' \
		class Object; \
		  CROSS_COMPILING = RUBY_PLATFORM; \
		  remove_const :RUBY_PLATFORM; \
		  remove_const :RUBY_VERSION; \
		  RUBY_PLATFORM = "i686-darwin9.8.0"; \
		  RUBY_VERSION = "1.9.0"; \
		end; \
		if RUBY_PLATFORM =~ /mswin|bccwin|mingw/; \
		  class File; \
		    remove_const :ALT_SEPARATOR; \
		    ALT_SEPARATOR = "\\"; \
		  end; \
		end; \
		' > $@

Makefile:	$(srcdir)/Makefile.in

$(MKFILES): config.status $(srcdir)/common.mk
		MAKE=$(MAKE) $(SHELL) ./config.status
		@{ \
		    echo "all:; -@rm -f conftest.mk"; \
		    echo "conftest.mk: .force; @echo AUTO_REMAKE"; \
		    echo ".force:"; \
		} > conftest.mk || exit 1; \
		$(MAKE) -f conftest.mk | grep '^AUTO_REMAKE$$' >/dev/null 2>&1 || \
		{ echo "Makefile updated, restart."; exit 1; }

config.status:	$(srcdir)/configure
		MINIRUBY="$(MINIRUBY)" $(SHELL) ./config.status --recheck

$(srcdir)/configure: $(srcdir)/configure.in
		cd $(srcdir) && $(AUTOCONF)

# Things which should be considered:
# * with gperf v.s. without gperf
# * ./configure v.s. ../ruby/configure
# * GNU make v.s. HP-UX make	# HP-UX make invokes the action if lex.c and keywords has same mtime.
# * svn checkout generate a file with mtime as current time
# * XFS has a mtime with fractional part
lex.c: keywords
	if cmp -s $(srcdir)/lex.c.src $?; then \
	  cp $(srcdir)/lex.c.blt $@; \
	else \
	  gperf -C -p -j1 -i 1 -g -o -t -N rb_reserved_word -k1,3,$$ $? > $@.tmp && \
	  mv $@.tmp $@ && \
	  cp $? $(srcdir)/lex.c.src && \
	  cp $@ $(srcdir)/lex.c.blt; \
	fi

.c.o:
	$(CC) $(CFLAGS) $(XCFLAGS) $(CPPFLAGS) $(COUTFLAG)$@ -c $<

.s.o:
	$(AS) $(ASFLAGS) -o $@ $<

.c.S:
	$(CC) $(CFLAGS) $(XCFLAGS) $(CPPFLAGS) $(COUTFLAG)$@ -S $<

clean-local::
	@$(RM) ext/extinit.c ext/extinit.$(OBJEXT)

distclean-local::
	@$(RM) ext/config.cache $(RBCONFIG)

ext/extinit.$(OBJEXT): ext/extinit.c $(SETUP)
	$(CC) $(CFLAGS) $(XCFLAGS) $(CPPFLAGS) $(COUTFLAG)$@ -c ext/extinit.c

bin: $(PROGRAM) $(WPROGRAM)
lib: $(LIBRUBY)
dll: $(LIBRUBY_SO)

.SUFFIXES: .inc

RUBYOPT       =

STATIC_RUBY   = static-ruby

EXTCONF       = extconf.rb
RBCONFIG      = ./.rbconfig.time
LIBRUBY_EXTS  = ./.libruby-with-ext.time
RDOCOUT       = $(EXTOUT)/rdoc

DMYEXT	      = dmyext.$(OBJEXT)
NORMALMAINOBJ = main.$(OBJEXT)
MAINOBJ       = $(NORMALMAINOBJ)
EXTOBJS	      = 
DLDOBJS	      = $(DMYEXT)

COMMONOBJS    = array.$(OBJEXT) \
		bignum.$(OBJEXT) \
		class.$(OBJEXT) \
		compar.$(OBJEXT) \
		dir.$(OBJEXT) \
		encoding.$(OBJEXT) \
		enum.$(OBJEXT) \
		enumerator.$(OBJEXT) \
		error.$(OBJEXT) \
		eval.$(OBJEXT) \
		load.$(OBJEXT) \
		proc.$(OBJEXT) \
		file.$(OBJEXT) \
		gc.$(OBJEXT) \
		hash.$(OBJEXT) \
		inits.$(OBJEXT) \
		io.$(OBJEXT) \
		marshal.$(OBJEXT) \
		math.$(OBJEXT) \
		numeric.$(OBJEXT) \
		object.$(OBJEXT) \
		pack.$(OBJEXT) \
		parse.$(OBJEXT) \
		process.$(OBJEXT) \
		prec.$(OBJEXT) \
		random.$(OBJEXT) \
		range.$(OBJEXT) \
		re.$(OBJEXT) \
		regcomp.$(OBJEXT) \
		regenc.$(OBJEXT) \
		regerror.$(OBJEXT) \
		regexec.$(OBJEXT) \
		regparse.$(OBJEXT) \
		regsyntax.$(OBJEXT) \
		ruby.$(OBJEXT) \
		signal.$(OBJEXT) \
		sprintf.$(OBJEXT) \
		st.$(OBJEXT) \
		string.$(OBJEXT) \
		struct.$(OBJEXT) \
		time.$(OBJEXT) \
		transcode.$(OBJEXT) \
		util.$(OBJEXT) \
		variable.$(OBJEXT) \
		version.$(OBJEXT) \
		blockinlining.$(OBJEXT) \
		compile.$(OBJEXT) \
		debug.$(OBJEXT) \
		iseq.$(OBJEXT) \
		vm.$(OBJEXT) \
		vm_dump.$(OBJEXT) \
		thread.$(OBJEXT) \
		cont.$(OBJEXT) \
		id.$(OBJEXT) \
		$(BUILTIN_ENCOBJS) \
		$(MISSING)

OBJS          = dln.$(OBJEXT) \
		prelude.$(OBJEXT) \
		$(COMMONOBJS)

GOLFOBJS      = goruby.$(OBJEXT) golf_prelude.$(OBJEXT)

SCRIPT_ARGS   =	--dest-dir="$(DESTDIR)" \
		--extout="$(EXTOUT)" \
		--make="$(MAKE)" \
		--mflags="$(MFLAGS)" \
		--make-flags="$(MAKEFLAGS)"
EXTMK_ARGS    =	$(SCRIPT_ARGS) --extension $(EXTS) --extstatic $(EXTSTATIC) --
INSTRUBY_ARGS =	$(SCRIPT_ARGS) --installed-list $(INSTALLED_LIST)

PRE_LIBRUBY_UPDATE = $(MINIRUBY) -e 'ARGV[1] or File.unlink(ARGV[0]) rescue nil' -- \
			$(LIBRUBY_EXTS) $(LIBRUBY_SO_UPDATE)

TESTSDIR      = $(srcdir)/test
TESTWORKDIR   = testwork

BOOTSTRAPRUBY = $(BASERUBY)

!include $(srcdir)/yard/yard.mk

all: $(MKFILES) yardall $(PREP) $(RBCONFIG) $(LIBRUBY)
	@$(MINIRUBY) $(srcdir)/ext/extmk.rb $(EXTMK_ARGS)
prog: $(PROGRAM) $(WPROGRAM)

miniruby$(EXEEXT): config.status $(NORMALMAINOBJ) $(MINIOBJS) $(COMMONOBJS) $(DMYEXT) $(ARCHFILE)

GORUBY = go$(RUBY_INSTALL_NAME)
golf: $(LIBRUBY) $(GOLFOBJS)
	$(MAKE) $(MFLAGS) MAINOBJ="$(GOLFOBJS)" PROGRAM=$(GORUBY)$(EXEEXT) program

program: $(PROGRAM)

$(PROGRAM): $(LIBRUBY) $(MAINOBJ) $(OBJS) $(EXTOBJS) $(SETUP) $(PREP)

$(LIBRUBY_A):	$(OBJS) $(DMYEXT) $(ARCHFILE)

$(LIBRUBY_SO):	$(OBJS) $(DLDOBJS) $(LIBRUBY_A) $(PREP) $(LIBRUBY_SO_UPDATE)

$(LIBRUBY_EXTS):
	@exit > $@

$(STATIC_RUBY)$(EXEEXT): $(MAINOBJ) $(DLDOBJS) $(EXTOBJS) $(LIBRUBY_A)
	@$(RM) $@
	$(PURIFY) $(CC) $(MAINOBJ) $(DLDOBJS) $(EXTOBJS) $(LIBRUBY_A) $(MAINLIBS) $(EXTLIBS) $(LIBS) $(OUTFLAG)$@ $(LDFLAGS) $(XLDFLAGS)

ruby.imp: $(COMMONOBJS)
	@$(NM) -Pgp $(COMMONOBJS) | awk 'BEGIN{print "#!"}; $$2~/^[BD]$$/{print $$1}' | sort -u -o $@

install: install-nodoc $(RDOCTARGET)
install-all: install-nodoc install-doc

install-nodoc: pre-install-nodoc do-install-nodoc post-install-nodoc
pre-install-nodoc:: pre-install-local pre-install-ext
do-install-nodoc: 
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --mantype="$(MANTYPE)"
post-install-nodoc:: post-install-local post-install-ext

install-local: pre-install-local do-install-local post-install-local
pre-install-local:: pre-install-bin pre-install-lib pre-install-man
do-install-local:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=local --mantype="$(MANTYPE)"
post-install-local:: post-install-bin post-install-lib post-install-man

install-ext: pre-install-ext do-install-ext post-install-ext
pre-install-ext:: pre-install-ext-arch pre-install-ext-comm
do-install-ext:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=ext
post-install-ext:: post-install-ext-arch post-install-ext-comm

install-arch: pre-install-arch do-install-arch post-install-arch
pre-install-arch:: pre-install-bin pre-install-ext-arch
do-install-arch:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=bin --install=ext-arch
post-install-arch:: post-install-bin post-install-ext-arch

install-comm: pre-install-comm do-install-comm post-install-comm
pre-install-comm:: pre-install-lib pre-install-ext-comm pre-install-man
do-install-comm:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=lib --install=ext-comm --install=man
post-install-comm:: post-install-lib post-install-ext-comm post-install-man

install-bin: pre-install-bin do-install-bin post-install-bin
pre-install-bin:: install-prereq
do-install-bin:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=bin
post-install-bin::
	@$(NULLCMD)

install-lib: pre-install-lib do-install-lib post-install-lib
pre-install-lib:: install-prereq
do-install-lib:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=lib
post-install-lib::
	@$(NULLCMD)

install-ext-comm: pre-install-ext-comm do-install-ext-comm post-install-ext-comm
pre-install-ext-comm:: install-prereq
do-install-ext-comm:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=ext-comm
post-install-ext-comm::
	@$(NULLCMD)

install-ext-arch: pre-install-ext-arch do-install-ext-arch post-install-ext-arch
pre-install-ext-arch:: install-prereq
do-install-ext-arch:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=ext-arch
post-install-ext-arch::
	@$(NULLCMD)

install-man: pre-install-man do-install-man post-install-man
pre-install-man:: install-prereq
do-install-man:
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=man --mantype="$(MANTYPE)"
post-install-man::
	@$(NULLCMD)

what-where: no-install
no-install: no-install-nodoc no-install-doc
what-where-all: no-install-all
no-install-all: no-install-nodoc

what-where-nodoc: no-install-nodoc
no-install-nodoc: pre-no-install-nodoc dont-install-nodoc post-no-install-nodoc
pre-no-install-nodoc:: pre-no-install-local pre-no-install-ext
dont-install-nodoc: 
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --mantype="$(MANTYPE)"
post-no-install-nodoc:: post-no-install-local post-no-install-ext

what-where-local: no-install-local
no-install-local: pre-no-install-local dont-install-local post-no-install-local
pre-no-install-local:: pre-no-install-bin pre-no-install-lib pre-no-install-man
dont-install-local:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=local --mantype="$(MANTYPE)"
post-no-install-local:: post-no-install-bin post-no-install-lib post-no-install-man

what-where-ext: no-install-ext
no-install-ext: pre-no-install-ext dont-install-ext post-no-install-ext
pre-no-install-ext:: pre-no-install-ext-arch pre-no-install-ext-comm
dont-install-ext:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=ext
post-no-install-ext:: post-no-install-ext-arch post-no-install-ext-comm

what-where-arch: no-install-arch
no-install-arch: pre-no-install-arch dont-install-arch post-no-install-arch
pre-no-install-arch:: pre-no-install-bin pre-no-install-ext-arch
dont-install-arch:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=bin --install=ext-arch
post-no-install-arch:: post-no-install-lib post-no-install-man post-no-install-ext-arch

what-where-comm: no-install-comm
no-install-comm: pre-no-install-comm dont-install-comm post-no-install-comm
pre-no-install-comm:: pre-no-install-lib pre-no-install-ext-comm pre-no-install-man
dont-install-comm:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=lib --install=ext-comm --install=man
post-no-install-comm:: post-no-install-lib post-no-install-ext-comm post-no-install-man

what-where-bin: no-install-bin
no-install-bin: pre-no-install-bin dont-install-bin post-no-install-bin
pre-no-install-bin:: install-prereq
dont-install-bin:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=bin
post-no-install-bin::
	@$(NULLCMD)

what-where-lib: no-install-lib
no-install-lib: pre-no-install-lib dont-install-lib post-no-install-lib
pre-no-install-lib:: install-prereq
dont-install-lib:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=lib
post-no-install-lib::
	@$(NULLCMD)

what-where-ext-comm: no-install-ext-comm
no-install-ext-comm: pre-no-install-ext-comm dont-install-ext-comm post-no-install-ext-comm
pre-no-install-ext-comm:: install-prereq
dont-install-ext-comm:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=ext-comm
post-no-install-ext-comm::
	@$(NULLCMD)

what-where-ext-arch: no-install-ext-arch
no-install-ext-arch: pre-no-install-ext-arch dont-install-ext-arch post-no-install-ext-arch
pre-no-install-ext-arch:: install-prereq
dont-install-ext-arch:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=ext-arch
post-no-install-ext-arch::
	@$(NULLCMD)

what-where-man: no-install-man
no-install-man: pre-no-install-man dont-install-man post-no-install-man
pre-no-install-man:: install-prereq
dont-install-man:
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=man --mantype="$(MANTYPE)"
post-no-install-man::
	@$(NULLCMD)

install-doc: rdoc pre-install-doc do-install-doc post-install-doc
pre-install-doc:: install-prereq
do-install-doc: $(PROGRAM)
	$(MINIRUBY) $(srcdir)/instruby.rb $(INSTRUBY_ARGS) --install=rdoc --rdoc-output="$(RDOCOUT)"
post-install-doc::
	@$(NULLCMD)

rdoc: $(PROGRAM) PHONY
	@echo Generating RDoc documentation
	$(RUNRUBY) "$(srcdir)/bin/rdoc" --all --ri --op "$(RDOCOUT)" "$(srcdir)"

what-where-doc: no-install-doc
no-install-doc: pre-no-install-doc dont-install-doc post-no-install-doc
pre-no-install-doc:: install-prereq
dont-install-doc::
	$(MINIRUBY) $(srcdir)/instruby.rb -n $(INSTRUBY_ARGS) --install=rdoc --rdoc-output="$(RDOCOUT)"
post-no-install-doc::
	@$(NULLCMD)

CLEAR_INSTALLED_LIST = clear-installed-list

install-prereq: $(CLEAR_INSTALLED_LIST)

clear-installed-list:
	@exit > $(INSTALLED_LIST)

clean: clean-ext clean-local
clean-local::
	@$(RM) $(OBJS) $(MINIOBJS) $(MAINOBJ) $(WINMAINOBJ) $(LIBRUBY_A) $(LIBRUBY_SO) $(LIBRUBY) $(LIBRUBY_ALIASES)
	@$(RM) $(PROGRAM) $(WPROGRAM) miniruby$(EXEEXT) dmyext.$(OBJEXT) $(ARCHFILE) .*.time
	@$(RM) *.inc
clean-ext:
	@-$(MINIRUBY) $(srcdir)/ext/extmk.rb $(EXTMK_ARGS) clean
clean-enc:
	@-$(MAKE) -f enc.mk $(MFLAGS) clean

distclean: distclean-ext distclean-local
distclean-local:: clean-local
	@$(RM) $(MKFILES) config.h rbconfig.rb
	@$(RM) config.cache config.log config.status
	@$(RM) *~ *.bak *.stackdump core *.core gmon.out y.tab.c y.output $(PREP)
distclean-ext:
	@-$(MINIRUBY) $(srcdir)/ext/extmk.rb $(EXTMK_ARGS) distclean
#	-$(RM) $(INSTALLED_LIST) $(arch_hdrdir)/ruby/config.h
#	-rmdir -p $(arch_hdrdir)/ruby
distclean-enc: clean-enc
	@-$(MAKE) -f enc.mk $(MFLAGS) distclean

realclean:: realclean-ext realclean-local
realclean-local:: distclean-local
	@$(RM) parse.c lex.c
realclean-ext::
	@-$(MINIRUBY) $(srcdir)/ext/extmk.rb $(EXTMK_ARGS) realclean
realclean-enc:: distclean-enc

check: test test-all

btest: miniruby$(EXEEXT) PHONY
	$(BOOTSTRAPRUBY) "$(srcdir)/bootstraptest/runner.rb" --ruby="$(MINIRUBY)" $(OPTS)

btest-miniruby: miniruby$(EXEEXT) $(RBCONFIG) $(PROGRAM) PHONY
	@$(MINIRUBY) "$(srcdir)/bootstraptest/runner.rb" --ruby="$(MINIRUBY)" -q

test-sample: miniruby$(EXEEXT) $(RBCONFIG) $(PROGRAM) PHONY
	@$(MINIRUBY) $(srcdir)/rubytest.rb

test: test-sample btest-miniruby

test-all:
	$(RUNRUBY) "$(srcdir)/test/runner.rb" --basedir="$(TESTSDIR)" --runner=$(TESTUI) $(TESTS)

extconf:
	$(MINIRUBY) -I$(srcdir)/lib -run -e mkdir -- -p "$(EXTCONFDIR)"
	$(RUNRUBY) -C "$(EXTCONFDIR)" $(EXTCONF) $(EXTCONFARGS)

$(RBCONFIG): $(srcdir)/mkconfig.rb config.status $(PREP)
	@$(MINIRUBY) $(srcdir)/mkconfig.rb -timestamp=$@ \
		-install_name=$(RUBY_INSTALL_NAME) \
		-so_name=$(RUBY_SO_NAME) rbconfig.rb

encs: enc.mk
	$(MAKE) -f enc.mk $(MFLAGS)

enc.mk: $(srcdir)/enc/make_encmake.rb $(srcdir)/enc/Makefile.in $(srcdir)/enc/depend \
	$(srcdir)/lib/mkmf.rb $(RBCONFIG)
	$(MINIRUBY) $(srcdir)/enc/make_encmake.rb --builtin-encs="$(BUILTIN_ENCOBJS)" $@

.PRECIOUS: $(MKFILES)

.PHONY: test install install-nodoc install-doc dist

PHONY:

parse.c: parse.y $(srcdir)/tool/ytab.sed

.y.c:
	$(YACC) $(YFLAGS) -o y.tab.c $<
	sed -f $(srcdir)/tool/ytab.sed -e "/^#/s!y\.tab\.c!$@!" y.tab.c > $@.new
	@$(RM) $@ y.tab.c
	@$(MV) $@.new $@

acosh.$(OBJEXT): acosh.c
alloca.$(OBJEXT): alloca.c
crypt.$(OBJEXT): crypt.c
dup2.$(OBJEXT): dup2.c
erf.$(OBJEXT): erf.c
finite.$(OBJEXT): finite.c
flock.$(OBJEXT): flock.c
memcmp.$(OBJEXT): memcmp.c
memmove.$(OBJEXT): memmove.c
mkdir.$(OBJEXT): mkdir.c
strcasecmp.$(OBJEXT): strcasecmp.c
strncasecmp.$(OBJEXT): strncasecmp.c
strchr.$(OBJEXT): strchr.c
strdup.$(OBJEXT): strdup.c
strerror.$(OBJEXT): strerror.c
strftime.$(OBJEXT): strftime.c
strstr.$(OBJEXT): strstr.c
strtod.$(OBJEXT): strtod.c
strtol.$(OBJEXT): strtol.c
strtoul.$(OBJEXT): strtoul.c
nt.$(OBJEXT): nt.c
x68.$(OBJEXT): x68.c
os2.$(OBJEXT): os2.c
dl_os2.$(OBJEXT): dl_os2.c
ia64.$(OBJEXT): ia64.s
	$(CC) $(CFLAGS) -c $<

# when I use -I., there is confliction at "OpenFile" 
# so, set . into environment varible "include"
win32.$(OBJEXT): win32.c

###

array.$(OBJEXT): array.c ruby.h config.h \
  defines.h intern.h missing.h \
  util.h st.h
bignum.$(OBJEXT): bignum.c ruby.h config.h \
  defines.h intern.h missing.h
class.$(OBJEXT): class.c ruby.h config.h \
  defines.h intern.h missing.h \
  signal.h node.h st.h
compar.$(OBJEXT): compar.c ruby.h config.h \
  defines.h intern.h missing.h
dir.$(OBJEXT): dir.c ruby.h config.h \
  defines.h intern.h missing.h \
  util.h
dln.$(OBJEXT): dln.c ruby.h config.h \
  defines.h intern.h missing.h \
  dln.h
dmydln.$(OBJEXT): dmydln.c dln.c ruby.h \
  config.h defines.h intern.h missing.h \
  dln.h
dmyext.$(OBJEXT): dmyext.c
encoding.$(OBJEXT): encoding.c ruby.h config.h \
  defines.h encoding.h oniguruma.h \
  regenc.h
enum.$(OBJEXT): enum.c ruby.h config.h \
  defines.h intern.h missing.h \
  node.h util.h
enumerator.$(OBJEXT): enumerator.c ruby.h config.h \
  defines.h intern.h missing.h
error.$(OBJEXT): error.c ruby.h config.h \
  defines.h intern.h missing.h \
  st.h vm_opts.h signal.h \
  vm_core.h id.h node.h debug.h \
  thread_$(THREAD_MODEL).h
eval.$(OBJEXT): eval.c eval_error.c eval_intern.h \
  eval_method.c eval_safe.c eval_jump.c \
  ruby.h config.h vm_core.h id.h \
  defines.h intern.h missing.h \
  node.h util.h signal.h \
  st.h dln.h debug.h \
  vm_opts.h thread_$(THREAD_MODEL).h
load.$(OBJEXT): load.c eval_intern.h \
  ruby.h config.h \
  defines.h intern.h missing.h \
  node.h util.h vm_core.h id.h \
  signal.h st.h dln.h debug.h \
  vm_opts.h thread_$(THREAD_MODEL).h
file.$(OBJEXT): file.c ruby.h config.h \
  defines.h intern.h missing.h \
  io.h signal.h util.h \
  dln.h
gc.$(OBJEXT): gc.c ruby.h config.h \
  defines.h intern.h missing.h \
  signal.h st.h node.h \
  re.h io.h regex.h oniguruma.h \
  vm_core.h id.h debug.h vm_opts.h \
  thread_$(THREAD_MODEL).h
hash.$(OBJEXT): hash.c ruby.h config.h \
  defines.h intern.h missing.h \
  st.h util.h signal.h
inits.$(OBJEXT): inits.c ruby.h config.h \
  defines.h intern.h missing.h
io.$(OBJEXT): io.c ruby.h config.h \
  defines.h intern.h missing.h \
  io.h signal.h util.h
main.$(OBJEXT): main.c ruby.h config.h \
  defines.h intern.h missing.h
marshal.$(OBJEXT): marshal.c ruby.h config.h \
  defines.h intern.h missing.h \
  io.h st.h util.h
math.$(OBJEXT): math.c ruby.h config.h \
  defines.h intern.h missing.h
numeric.$(OBJEXT): numeric.c ruby.h config.h \
  defines.h intern.h encoding.h \
  missing.h
object.$(OBJEXT): object.c ruby.h config.h \
  defines.h intern.h missing.h \
  st.h util.h debug.h
pack.$(OBJEXT): pack.c ruby.h config.h \
  defines.h intern.h missing.h
parse.$(OBJEXT): parse.c ruby.h config.h \
  defines.h intern.h missing.h \
  node.h st.h oniguruma.h \
  regenc.h regex.h util.h lex.c
prec.$(OBJEXT): prec.c ruby.h config.h \
  defines.h intern.h missing.h
proc.$(OBJEXT): proc.c eval_intern.h \
  ruby.h config.h vm_core.h id.h \
  defines.h intern.h missing.h \
  node.h util.h gc.h \
  signal.h st.h dln.h \
  debug.h vm_opts.h \
  thread_$(THREAD_MODEL).h
process.$(OBJEXT): process.c ruby.h config.h \
  defines.h intern.h missing.h \
  signal.h st.h vm_core.h id.h 
random.$(OBJEXT): random.c ruby.h config.h \
  defines.h intern.h missing.h
range.$(OBJEXT): range.c ruby.h config.h \
  defines.h intern.h missing.h
re.$(OBJEXT): re.c ruby.h config.h \
  defines.h intern.h missing.h \
  oniguruma.h re.h regex.h \
  regint.h regenc.h signal.h
regcomp.$(OBJEXT): regcomp.c ruby.h config.h \
  defines.h intern.h missing.h \
  oniguruma.h regint.h regparse.h \
  regenc.h signal.h
regenc.$(OBJEXT): regenc.c regint.h \
  regenc.h oniguruma.h ruby.h \
  defines.h missing.h intern.h \
  signal.h config.h
regerror.$(OBJEXT): regerror.c regint.h \
  regenc.h oniguruma.h config.h \
  ruby.h defines.h missing.h \
  intern.h signal.h
regexec.$(OBJEXT): regexec.c regint.h \
  regenc.h oniguruma.h config.h \
  ruby.h defines.h missing.h \
  intern.h signal.h
regparse.$(OBJEXT): regparse.c oniguruma.h \
  regint.h regparse.h regenc.h config.h \
  ruby.h defines.h missing.h \
  intern.h signal.h
regsyntax.$(OBJEXT): regsyntax.c oniguruma.h \
  regint.h regenc.h config.h \
  ruby.h defines.h missing.h
ruby.$(OBJEXT): ruby.c ruby.h config.h \
  defines.h intern.h missing.h \
  dln.h node.h util.h encoding.h
signal.$(OBJEXT): signal.c ruby.h config.h \
  defines.h intern.h missing.h \
  signal.h vm_core.h id.h node.h \
  debug.h vm_opts.h \
  thread_$(THREAD_MODEL).h
sprintf.$(OBJEXT): sprintf.c ruby.h config.h \
  defines.h intern.h missing.h \
  re.h regex.h oniguruma.h \
  vsnprintf.c
st.$(OBJEXT): st.c config.h st.h defines.h
string.$(OBJEXT): string.c ruby.h config.h \
  defines.h intern.h missing.h \
  re.h regex.h encoding.h
struct.$(OBJEXT): struct.c ruby.h config.h \
  defines.h intern.h missing.h
thread.$(OBJEXT): thread.c eval_intern.h \
  thread_win32.h thread_pthread.h \
  thread_win32.c thread_pthread.c \
  ruby.h vm_core.h id.h config.h \
  defines.h intern.h missing.h \
  node.h util.h \
  signal.h st.h dln.h
transcode.$(OBJEXT): transcode.c transcode_data.h ruby.h config.h \
  defines.h intern.h missing.h  encoding.h
cont.$(OBJEXT):  cont.c eval_intern.h \
  ruby.h vm_core.h id.h config.h \
  defines.h intern.h missing.h \
  node.h util.h \
  signal.h st.h dln.h
time.$(OBJEXT): time.c ruby.h config.h \
  defines.h intern.h missing.h
util.$(OBJEXT): util.c ruby.h config.h \
  defines.h intern.h missing.h \
  util.h
variable.$(OBJEXT): variable.c ruby.h config.h \
  defines.h intern.h missing.h \
  node.h st.h util.h
version.$(OBJEXT): version.c ruby.h config.h \
  defines.h intern.h missing.h \
  version.h revision.h

compile.$(OBJEXT): compile.c vm_core.h id.h \
        compile.h debug.h ruby.h config.h \
        defines.h missing.h intern.h \
        st.h node.h signal.h \
        insns_info.inc optinsn.inc \
        opt_sc.inc optunifs.inc vm_opts.h \
        thread_$(THREAD_MODEL).h
iseq.$(OBJEXT): iseq.c vm_core.h id.h debug.h \
        ruby.h defines.h missing.h \
        intern.h st.h signal.h \
        gc.h vm_opts.h  config.h node.h \
        thread_$(THREAD_MODEL).h insns_info.inc \
        node_name.inc
vm.$(OBJEXT): vm.c vm.h vm_core.h id.h \
	debug.h ruby.h config.h st.h \
	node.h util.h signal.h dln.h \
	insnhelper.h vm_insnhelper.c vm_evalbody.c \
        insns.inc vm.inc vmtc.inc \
	vm_opts.h eval_intern.h \
        defines.h missing.h intern.h \
        gc.h thread_$(THREAD_MODEL).h
vm_dump.$(OBJEXT):  vm_dump.c vm_core.h id.h vm.h \
        ruby.h config.h defines.h missing.h \
        intern.h st.h node.h debug.h \
        signal.h vm_opts.h thread_$(THREAD_MODEL).h
debug.$(OBJEXT): debug.h ruby.h defines.h \
        missing.h intern.h st.h config.h \
        st.h
blockinlining.$(OBJEXT): blockinlining.c \
        ruby.h defines.h \
        missing.h intern.h st.h config.h \
        node.h vm_core.h id.h signal.h \
        debug.h vm_opts.h \
        thread_$(THREAD_MODEL).h
id.$(OBJEXT): id.c ruby.h
miniprelude.$(OBJEXT): miniprelude.c ruby.h vm_core.h
prelude.$(OBJEXT): prelude.c ruby.h vm_core.h
golf_prelude.$(OBJEXT): golf_prelude.c ruby.h vm_core.h
goruby.$(OBJEXT): goruby.c main.c ruby.h config.h \
  defines.h intern.h missing.h

ascii.$(OBJEXT): ascii.c regenc.h \
  oniguruma.h config.h defines.h
euc_jp.$(OBJEXT): euc_jp.c regenc.h \
  oniguruma.h config.h defines.h
sjis.$(OBJEXT): sjis.c regenc.h \
  oniguruma.h config.h defines.h
unicode.$(OBJEXT): unicode.c regenc.h \
  oniguruma.h config.h defines.h
utf8.$(OBJEXT): utf8.c regenc.h \
  oniguruma.h config.h defines.h

INSNS	= opt_sc.inc optinsn.inc optunifs.inc insns.inc \
	  vmtc.inc vm.inc

INSNS2VMOPT = --srcdir="$(srcdir)"

$(INSNS): $(srcdir)/insns.def vm_opts.h
	$(RM) $(PROGRAM)
	$(BASERUBY) $(srcdir)/tool/insns2vm.rb $(INSNS2VMOPT)

minsns.inc: $(srcdir)/template/minsns.inc.tmpl

opt_sc.inc: $(srcdir)/template/opt_sc.inc.tmpl

optinsn.inc: $(srcdir)/template/optinsn.inc.tmpl

optunifs.inc: $(srcdir)/template/optunifs.inc.tmpl

insns.inc: $(srcdir)/template/insns.inc.tmpl

insns_info.inc: $(srcdir)/template/insns_info.inc.tmpl

vmtc.inc: $(srcdir)/template/vmtc.inc.tmpl

vm.inc: $(srcdir)/template/vm.inc.tmpl

srcs: parse.c lex.c $(srcdir)/ext/ripper/ripper.c

incs: $(INSNS) node_name.inc revision.h

node_name.inc: node.h
	$(BASERUBY) -n $(srcdir)/tool/node_name.rb $? > $@

miniprelude.c: $(srcdir)/tool/compile_prelude.rb $(srcdir)/prelude.rb
	$(BASERUBY) -I$(srcdir) $(srcdir)/tool/compile_prelude.rb $(srcdir)/prelude.rb $@

prelude.c: $(srcdir)/tool/compile_prelude.rb $(srcdir)/prelude.rb $(srcdir)/gem_prelude.rb $(RBCONFIG)
	$(MINIRUBY) -I$(srcdir) -I$(srcdir)/lib -rrbconfig $(srcdir)/tool/compile_prelude.rb $(srcdir)/prelude.rb $(srcdir)/gem_prelude.rb $@

golf_prelude.c: $(srcdir)/tool/compile_prelude.rb $(srcdir)/prelude.rb $(srcdir)/golf_prelude.rb
	$(BASERUBY) -I$(srcdir) -I$(srcdir)/lib -rrbconfig $(srcdir)/tool/compile_prelude.rb $(srcdir)/golf_prelude.rb $@

prereq: incs srcs preludes

preludes: miniprelude.c
preludes: golf_prelude.c

docs:
	$(BASERUBY) -I$(srcdir) $(srcdir)/tool/makedocs.rb $(INSNS2VMOPT)

revision.h:
	exit > $@

$(srcdir)/ext/ripper/ripper.c:
	cd $(srcdir)/ext/ripper && exec $(MAKE) -f depend $(MFLAGS) top_srcdir=../.. srcdir=.

##

run: miniruby$(EXEEXT) PHONY
	$(MINIRUBY) -I$(srcdir)/lib $(srcdir)/test.rb $(RUNOPT)

runruby: $(PROGRAM) PHONY
	$(RUNRUBY) $(srcdir)/test.rb

parse: miniruby$(EXEEXT) PHONY
	$(MINIRUBY) $(srcdir)/tool/parse.rb $(srcdir)/test.rb

COMPARE_RUBY = $(BASERUBY)
ITEM = 
OPTS = 

benchmark: $(PROGRAM) PHONY
	$(BASERUBY) $(srcdir)/benchmark/driver.rb -v \
	            --executables="$(COMPARE_RUBY); $(RUNRUBY)" \
	            --pattern='bm_' --directory=$(srcdir)/benchmark $(OPTS)

benchmark-each: $(PROGRAM) PHONY
	$(BASERUBY) $(srcdir)/benchmark/driver.rb -v \
	            --executables="$(COMPARE_RUBY); $(RUNRUBY)" \
	            --pattern=$(ITEM) --directory=$(srcdir)/benchmark $(OPTS)

tbench: $(PROGRAM) PHONY
	$(BASERUBY) $(srcdir)/benchmark/driver.rb -v \
	            --executables="$(COMPARE_RUBY); $(RUNRUBY)" \
	            --pattern='bmx_' --directory=$(srcdir)/benchmark $(OPTS)

aotc: $(PROGRAM) PHONY
	./$(PROGRAM) -I$(srcdir)/lib $(srcdir)/bin/ruby2cext $(srcdir)/test.rb

vmasm: vm.$(ASMEXT)

# vm.o : CFLAGS += -fno-crossjumping

run.gdb:
	echo b ruby_debug_breakpoint           > run.gdb
	echo '# handle SIGINT nostop'         >> run.gdb
	echo '# handle SIGPIPE nostop'        >> run.gdb
	echo '# b rb_longjmp'                 >> run.gdb
	echo source $(srcdir)/breakpoints.gdb >> run.gdb
	echo source $(srcdir)/.gdbinit        >> run.gdb
	echo run                              >> run.gdb

gdb: miniruby$(EXEEXT) run.gdb PHONY
	gdb -x run.gdb --quiet --args $(MINIRUBY) -I$(srcdir)/lib $(srcdir)/test.rb

# Intel VTune

vtune: miniruby$(EXEEXT)
	vtl activity -c sampling -app ".\miniruby$(EXEEXT)","-I$(srcdir)/lib $(srcdir)/test.rb" run
	vtl view -hf -mn miniruby$(EXEEXT) -sum -sort -cd
	vtl view -ha -mn miniruby$(EXEEXT) -sum -sort -cd | $(RUNRUBY) $(srcdir)/tool/vtlh.rb > ha.lines

dist: $(PROGRAM)
	$(RUNRUBY) $(srcdir)/distruby.rb
