encsrcdir = ./../enc
topdir = .
libdir = $(exec_prefix)/lib
top_srcdir = $(encsrcdir:/enc=)
srcdir = $(top_srcdir)
arch = i386-mswin32
EXTOUT = .ext
hdrdir = $(srcdir)/include
arch_hdrdir = $(EXTOUT)/include/$(arch)
ENCSODIR = $(EXTOUT)/$(arch)/enc
TRANSSODIR = $(ENCSODIR)/trans
DLEXT = so
OBJEXT = obj

BUILTIN_ENCS	= ascii.c \
		  euc_jp.c sjis.c \
		  unicode.c utf8.c

RUBY_SO_NAME = msvcrt-ruby190
LIBRUBY = $(RUBY_SO_NAME).lib
LIBRUBYARG_SHARED = $(LIBRUBY)
LIBRUBYARG_STATIC = $(LIBRUBYARG_SHARED)

empty =
CC = cl -nologo
OUTFLAG = -Fe$(empty)
COUTFLAG = -Fo$(empty)
CFLAGS = $(CCDLFLAGS) -MD -Zi -O2b2xg- -G6 
CCDLFLAGS = 
INCFLAGS = -I. -I$(arch_hdrdir) -I$(hdrdir) -I$(top_srcdir)
DEFS = 
CPPFLAGS =   -DONIG_ENC_REGISTER=rb_enc_register
LDFLAGS =  $(CFLAGS) 
XLDFLAGS = -stack:0x200000 $(EXTLDFLAGS)
LIBS = $(LIBRUBYARG_SHARED) oldnames.lib user32.lib advapi32.lib shell32.lib ws2_32.lib  $(EXTLIBS)
LDSHARED = cl -nologo -LD
DLDFLAGS = -link -incremental:no -debug -opt:ref -opt:icf -dll $(LIBPATH) $(EXTLDFLAGS) 

RM = $(COMSPEC) /C $(top_srcdir:/=\)\win32\rm.bat

all:

clean:

distclean: clean
	$(RM) enc.mk

#### depend ####


VPATH = $(arch_hdrdir)/ruby;$(hdrdir)/ruby;$(srcdir);$(encsrcdir)
LIBPATH =  -libpath:"." -libpath:"$(topdir)"

ENCOBJS = enc/iso_8859_1.$(OBJEXT) \
	  enc/iso_8859_2.$(OBJEXT) \
	  enc/iso_8859_3.$(OBJEXT) \
	  enc/iso_8859_4.$(OBJEXT) \
	  enc/iso_8859_5.$(OBJEXT) \
	  enc/iso_8859_6.$(OBJEXT) \
	  enc/iso_8859_7.$(OBJEXT) \
	  enc/iso_8859_8.$(OBJEXT) \
	  enc/iso_8859_9.$(OBJEXT) \
	  enc/iso_8859_10.$(OBJEXT) \
	  enc/iso_8859_11.$(OBJEXT) \
	  enc/iso_8859_13.$(OBJEXT) \
	  enc/iso_8859_14.$(OBJEXT) \
	  enc/iso_8859_15.$(OBJEXT) \
	  enc/iso_8859_16.$(OBJEXT) \
	  enc/us_ascii.$(OBJEXT)

ENCDEFS = enc/iso_8859_1.def \
	  enc/iso_8859_2.def \
	  enc/iso_8859_3.def \
	  enc/iso_8859_4.def \
	  enc/iso_8859_5.def \
	  enc/iso_8859_6.def \
	  enc/iso_8859_7.def \
	  enc/iso_8859_8.def \
	  enc/iso_8859_9.def \
	  enc/iso_8859_10.def \
	  enc/iso_8859_11.def \
	  enc/iso_8859_13.def \
	  enc/iso_8859_14.def \
	  enc/iso_8859_15.def \
	  enc/iso_8859_16.def \
	  enc/us_ascii.def

ENCSOS = $(ENCSODIR)/iso_8859_1.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_2.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_3.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_4.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_5.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_6.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_7.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_8.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_9.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_10.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_11.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_13.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_14.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_15.$(DLEXT) \
	 $(ENCSODIR)/iso_8859_16.$(DLEXT) \
	 $(ENCSODIR)/us_ascii.$(DLEXT)

TRANSOBJS = enc/trans/japanese.$(OBJEXT) \
	    enc/trans/single_byte.$(OBJEXT)

TRANSDEFS = enc/trans/japanese.def \
	    enc/trans/single_byte.def

TRANSSOS = $(ENCSODIR)/trans/japanese.$(DLEXT) \
	   $(ENCSODIR)/trans/single_byte.$(DLEXT)

all: $(ENCSOS) $(TRANSSOS)

{$(hdrdir)}.c{}.$(OBJEXT):
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)

{$(topdir)}.c{}.$(OBJEXT):
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)

{$(srcdir)}.c{}.$(OBJEXT):
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)

.c.$(OBJEXT):
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(<:\=/)


$(ENCOBJS): {.;$(VPATH)}regenc.h {.;$(VPATH)}oniguruma.h {.;$(VPATH)}config.h {.;$(VPATH)}defines.h
$(TRANSOBJS): {.;$(VPATH)}ruby.h {.;$(VPATH)}intern.h {.;$(VPATH)}config.h {.;$(VPATH)}defines.h {.;$(VPATH)}transcode_data.h

$(ENCSODIR)/iso_8859_1.$(DLEXT): enc/iso_8859_1.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_1.def
	echo Init_iso_8859_1 >> enc/iso_8859_1.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_1.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_1.def

$(ENCSODIR)/iso_8859_2.$(DLEXT): enc/iso_8859_2.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_2.def
	echo Init_iso_8859_2 >> enc/iso_8859_2.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_2.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_2.def

$(ENCSODIR)/iso_8859_3.$(DLEXT): enc/iso_8859_3.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_3.def
	echo Init_iso_8859_3 >> enc/iso_8859_3.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_3.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_3.def

$(ENCSODIR)/iso_8859_4.$(DLEXT): enc/iso_8859_4.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_4.def
	echo Init_iso_8859_4 >> enc/iso_8859_4.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_4.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_4.def

$(ENCSODIR)/iso_8859_5.$(DLEXT): enc/iso_8859_5.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_5.def
	echo Init_iso_8859_5 >> enc/iso_8859_5.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_5.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_5.def

$(ENCSODIR)/iso_8859_6.$(DLEXT): enc/iso_8859_6.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_6.def
	echo Init_iso_8859_6 >> enc/iso_8859_6.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_6.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_6.def

$(ENCSODIR)/iso_8859_7.$(DLEXT): enc/iso_8859_7.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_7.def
	echo Init_iso_8859_7 >> enc/iso_8859_7.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_7.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_7.def

$(ENCSODIR)/iso_8859_8.$(DLEXT): enc/iso_8859_8.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_8.def
	echo Init_iso_8859_8 >> enc/iso_8859_8.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_8.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_8.def

$(ENCSODIR)/iso_8859_9.$(DLEXT): enc/iso_8859_9.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_9.def
	echo Init_iso_8859_9 >> enc/iso_8859_9.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_9.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_9.def

$(ENCSODIR)/iso_8859_10.$(DLEXT): enc/iso_8859_10.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_10.def
	echo Init_iso_8859_10 >> enc/iso_8859_10.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_10.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_10.def

$(ENCSODIR)/iso_8859_11.$(DLEXT): enc/iso_8859_11.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_11.def
	echo Init_iso_8859_11 >> enc/iso_8859_11.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_11.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_11.def

$(ENCSODIR)/iso_8859_13.$(DLEXT): enc/iso_8859_13.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_13.def
	echo Init_iso_8859_13 >> enc/iso_8859_13.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_13.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_13.def

$(ENCSODIR)/iso_8859_14.$(DLEXT): enc/iso_8859_14.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_14.def
	echo Init_iso_8859_14 >> enc/iso_8859_14.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_14.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_14.def

$(ENCSODIR)/iso_8859_15.$(DLEXT): enc/iso_8859_15.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_15.def
	echo Init_iso_8859_15 >> enc/iso_8859_15.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_15.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_15.def

$(ENCSODIR)/iso_8859_16.$(DLEXT): enc/iso_8859_16.$(OBJEXT)
	echo EXPORTS > enc/iso_8859_16.def
	echo Init_iso_8859_16 >> enc/iso_8859_16.def
	$(LDSHARED) -Fe$(@) enc/iso_8859_16.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/iso_8859_16.def

$(ENCSODIR)/us_ascii.$(DLEXT): enc/us_ascii.$(OBJEXT)
	echo EXPORTS > enc/us_ascii.def
	echo Init_us_ascii >> enc/us_ascii.def
	$(LDSHARED) -Fe$(@) enc/us_ascii.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/$(*F:.so=).lib -pdb:enc/$(*F:.so=).pdb -def:enc/us_ascii.def

$(ENCSODIR)/trans/japanese.$(DLEXT): enc/trans/japanese.$(OBJEXT)
	echo EXPORTS > enc/trans/japanese.def
	echo Init_japanese >> enc/trans/japanese.def
	$(LDSHARED) -Fe$(@) enc/trans/japanese.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/trans/$(*F:.so=).lib -pdb:enc/trans/$(*F:.so=).pdb -def:enc/trans/japanese.def

$(ENCSODIR)/trans/single_byte.$(DLEXT): enc/trans/single_byte.$(OBJEXT)
	echo EXPORTS > enc/trans/single_byte.def
	echo Init_single_byte >> enc/trans/single_byte.def
	$(LDSHARED) -Fe$(@) enc/trans/single_byte.$(OBJEXT) $(LIBS) $(LOCAL_LIBS) $(DLDFLAGS) -implib:enc/trans/$(*F:.so=).lib -pdb:enc/trans/$(*F:.so=).pdb -def:enc/trans/single_byte.def

enc/iso_8859_1.$(OBJEXT): $(srcdir)/enc/iso_8859_1.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_1.c
enc/iso_8859_2.$(OBJEXT): $(srcdir)/enc/iso_8859_2.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_2.c
enc/iso_8859_3.$(OBJEXT): $(srcdir)/enc/iso_8859_3.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_3.c
enc/iso_8859_4.$(OBJEXT): $(srcdir)/enc/iso_8859_4.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_4.c
enc/iso_8859_5.$(OBJEXT): $(srcdir)/enc/iso_8859_5.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_5.c
enc/iso_8859_6.$(OBJEXT): $(srcdir)/enc/iso_8859_6.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_6.c
enc/iso_8859_7.$(OBJEXT): $(srcdir)/enc/iso_8859_7.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_7.c
enc/iso_8859_8.$(OBJEXT): $(srcdir)/enc/iso_8859_8.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_8.c
enc/iso_8859_9.$(OBJEXT): $(srcdir)/enc/iso_8859_9.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_9.c
enc/iso_8859_10.$(OBJEXT): $(srcdir)/enc/iso_8859_10.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_10.c
enc/iso_8859_11.$(OBJEXT): $(srcdir)/enc/iso_8859_11.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_11.c
enc/iso_8859_13.$(OBJEXT): $(srcdir)/enc/iso_8859_13.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_13.c
enc/iso_8859_14.$(OBJEXT): $(srcdir)/enc/iso_8859_14.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_14.c
enc/iso_8859_15.$(OBJEXT): $(srcdir)/enc/iso_8859_15.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_15.c
enc/iso_8859_16.$(OBJEXT): $(srcdir)/enc/iso_8859_16.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/iso_8859_16.c
enc/us_ascii.$(OBJEXT): $(srcdir)/enc/us_ascii.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/us_ascii.c
enc/trans/japanese.$(OBJEXT): $(srcdir)/enc/trans/japanese.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/trans/japanese.c
enc/trans/single_byte.$(OBJEXT): $(srcdir)/enc/trans/single_byte.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(CPPFLAGS) $(COUTFLAG)$(@) -c -Tc$(srcdir)/enc/trans/single_byte.c

clean:
	$(RM) $(ENCSOS)
	$(RM) $(ENCDEFS)
	$(RM) $(ENCOBJS)
	$(RM) $(TRANSSOS)
	$(RM) $(TRANSDEFS)
	$(RM) $(TRANSOBJS)
