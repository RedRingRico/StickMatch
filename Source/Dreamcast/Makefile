###############################################################################
#                                     StickMatch Makefile [Dreamcast] Ver 1.0 #
###############################################################################

SOURCEDIR	:=	Source

LINK_FILES	= $(addprefix xlnk.,$(basename $(DEFAULT_OBJS))) $(addprefix lnk.,$(OBJS))

ifeq ($(OS),Windows_NT)
ifdef APPDATA
TRIM_QUOTES = ~
endif
endif

CC	:= shc.exe
AS	:= asmsh.exe
LIBR	:= lbr.exe
LINK	:= lnk.exe

TARGET		:=	StickMatch
LIBDIR		:=	$(KATANA_ROOT)\lib

ifndef TOPDIR
export TOPDIR	:= $(shell cd ../../ && cd)
export TOPSRC	= $(subst \,/,$(TOPDIR))/Source
export OBJSDIR = $(TOPDIR)\Obj\Dreamcast
export OBJSDIR_ALT = $(subst \,/,$(OBJSDIR))
export TARGETDIR = $(TOPDIR)\Bin
export TARGETDIR_ALT = $(subst \,/,$(TARGETDIR))
endif

DEFAULT_INCLUDE	:=	$(KATANA_ROOT)\Include
DEFAULT_LIBS	:=	KAMUI2 shinobi sh4nlfzn KAMUI2
DEFAULT_OBJS	:=	strt1.obj strt2.obj systemid.obj toc.obj sg_sec.obj \
					sg_arejp.obj sg_areus.obj sg_areec.obj sg_are00.obj \
					sg_are01.obj sg_are02.obj sg_are03.obj sg_are04.obj \
					sg_ini.obj aip.obj zero.obj
PROJECT_INCLUDE	=	$(TOPSRC)/Dreamcast/Headers
SYSTEM_INCLUDE = .

C_OPTIMISE	:=	-optimize=1
C_DEBUG		:=	-nodebug

C_LISTING	=	-list="$(OBJSDIR)\$*.lst"

C_OPTIMISE_LINK	:=	-g
OPTIMISE_TYPE	:= size

C_OPTIONS	:=	-cpu=sh4 \
				-division=cpu \
				-endian=little \
				-fpu=single \
				-round=nearest \
				-pic=0 \
				-macsave=0 \
				-string=const \
				-comment=nonest \
				-sjis \
				-section=p=P,c=C,d=D,b=B \
				-show=obj,source,expansion,w=80,l=0

CFLAGS	=	 $(C_OPTIONS) $(C_DEBUG) $(C_OPTIMISE_LINK) $(C_LISTING) $(C_OPTIMISE)
CDEFS	:=	_KAMUI2_ __SET4__ __SET5__ __KATANA__ _CLX_ _CLX2_ _STRICT_UNION_ \
			_SH4
ASFLAGS	:=	-little

LINK_LIST	=	print $*.map
LINK_EXTRA	:= entry SG_SEC
LINK_START	:= start IP(8C008000),DSGLH(8C010000)
LINK_FORM	:= form a
LINK_OPTIONS	:=	align_section \
					udfcheck \
					elf
LINK_FLAGS	= $(LINK_OPTIONS)

BUID_TYPE := debug

debug: TARGET := $(TARGET)D
debug: BUILD_TYPE = debug
debug: $(TARGET)

release: TARGET := $(TARGET)
release: BUILD_TYPE = release
release: $(TARGET)

profile: TARGET := $(TARGET)P
profile: BUILD_TYPE = profile
profile: $(TARGET)

ifneq ($(OBJSDIR_ALT), $(CURDIR))
TARGETDIR:

OBJSDIR:
	echo.> $(OBJSDIR)\Linker.sub

PROJECT_LNK	= $(addprefix xlnk.,$(basename $(DEFAULT_OBJS)))	

CFILES	:= $(foreach dir,$(SOURCEDIR),$(notdir $(wildcard $(dir)/*.c)))
export OBJS := $(CFILES:.c=.obj)
export VPATH	:= $(foreach dir,$(SOURCEDIR),$(CURDIR)/$(dir))

xlnk.%:
	echo input $(LIBDIR)\$*.obj >> "$(OBJSDIR)\Linker.sub"

lnk.%:
	echo input $* >> "$(OBJSDIR)\Linker.sub"

$(TARGET): OBJSDIR TARGETDIR $(LINK_FILES)
	$(MAKE) --no-print-directory -C $(OBJSDIR_ALT) -f $(TOPSRC)/Dreamcast/Makefile $(BUILD_TYPE)

else

$(TARGET): $(OBJS)
	echo $(LINK_START) >> "$(OBJSDIR)\Linker.sub"
	echo $(LINK_FORM) >> "$(OBJSDIR)\Linker.sub"
	echo $(LINK_EXTRA) >> "$(OBJSDIR)\Linker.sub"
	for %%x in ($(LINK_FLAGS)) do echo %%x >> "$(OBJSDIR)\Linker.sub"
	for %%x in ($(SYSTEM_LIBS) $(DEFAULT_LIBS)) do echo library $(LIBDIR)\%%x.lib >> "$(OBJSDIR)\Linker.sub"
	echo output $(TARGETDIR)\$(TARGET).elf >> "$(OBJSDIR)\Linker.sub"
	echo exit >> "$(OBJSDIR)\Linker.sub"
	$(LINK) -noecho -sub="$(OBJSDIR)\Linker.sub"
	elf2bin.exe -s 8C010000 $(TARGETDIR_ALT)/$(TARGET).elf

%.obj: %.c
	echo $(CFLAGS) > "$(OBJSDIR)\shc.sub"
	for %%x in ($(OPTIMISE_TYPE)) do echo -%%x >> "$(OBJSDIR)\shc.sub"
	echo -define= >> "$(OBJSDIR)\shc.sub"
	for %%x in ($(CDEFS)) do echo %%$(TRIM_QUOTES)x, >> "$(OBJSDIR)\shc.sub"
	echo __SHC__ -include= >> "$(OBJSDIR)\shc.sub"
	for %%x in ($(PROJECT_INCLUDE) $(SYSTEM_INCLUDE)) do echo %%x, >> "$(OBJSDIR)\shc.sub"
	echo $(DEFAULT_INCLUDE) >> "$(OBJSDIR)\shc.sub"
	$(CC) $< -ob=$(OBJSDIR)\$*.obj -sub="$(OBJSDIR)\shc.sub"

-include $(OBJSDIR)/*.d

endif
	
