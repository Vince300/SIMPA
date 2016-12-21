MAKEFILENAME ?= makefile
CC ?= scc

#################################################################
### STOP HERE IF NECESSARY

ifndef QA_TOOLS
  $(error "The variable QA_TOOLS must be defined.")
endif



#################################################################
### ACCESS PROTOTYPES AND COMMON SOURCES: it depends on the OS.

SYS_OS := $(shell uname -s)

ifeq (,$(findstring CYGWIN,$(SYS_OS)))
  stdpath = $(1)
else
  stdpath = $(shell cygpath -w -m -s '$(1)')
endif


ifeq "$(CC)" "gcc"
  PROTO ?= NPR
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the gcc compiler are: BASIC_OP, NPR.")
  endif
endif
ifeq "$(CC)" "scc"
  PROTO ?= EMULATE
  ifeq "$(PROTO)" ""
    $(error "The available values of the PROTO variable for the scc compiler are: EMULATE, BASIC_OP, NPR.")
  endif
endif
ifeq "$(CC)" "ppc"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the ppc compiler are: BASIC_OP, NPR.")
  endif
endif
ifeq "$(CC)" "mwccarm"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the mwarm compiler are: BASIC_OP, NPR.")
  endif
endif
ifeq "$(CC)" "armcc"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the armcc compiler are: BASIC_OP, NPR.")
  endif
endif
ifeq "$(CC)" "gccarm"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the ppc compiler are: BASIC_OP, NPR.")
  endif
endif
ifeq "$(CC)" "win32_x86"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the win32_x86 compiler are: BASIC_OP")
  endif
endif
ifeq "$(CC)" "dsp56800e"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the dsp56800e compiler are: BASIC_OP")
  endif
endif
ifeq "$(CC)" "mac_ppc"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the mac_ppc compiler are: BASIC_OP")
  endif
endif
ifeq "$(CC)" "dsp56800"
  PROTO ?= BASIC_OP
  ifeq "$(PROTO)" "EMULATE"
    $(error "The available values of the PROTO variable for the dsp56800 compiler are: BASIC_OP")
  endif
endif

ifeq "$(PROTO)" "NPR"
  ifndef SC100_HOME
    $(error "The variable SC100_HOME must be defined.")
  endif

  PROTO_SRC_DIR := $(subst //,/,$(call stdpath,$(SC100_HOME))/src/host)
  PROTO_INC_DIR := $(subst //,/,$(call stdpath,$(SC100_HOME))/include)
endif
COM_DIR      := $(subst //,/,$(call stdpath,$(QA_TOOLS))/generic_test/codec)

#################################################################
### COMPILER SPECIFIC

C_EXT     = c
CPP_EXT   = cpp
C_EXTLIST = $(C_EXT) $(CPP_EXT)

ifeq "$(CC)" "gcc"
  O = o
  E = exe
  COMPILER = gcc
  LINKER   = gcc

  OBJ_IN_ROOT := 1

  CMDFLAGS = $(filter-out , $(CFLAGS))
  CCFLAGS = $(filter-out $(FORBIDDEN_GCC), $(CFLAGS))
  ifneq ($(CCFLAGS),$(CMDFLAGS))
     $(warning "Warning : The following flags are not supported: $(FORBIDDEN_GCC)") ;
  endif

  QA_CFLAGS = -I"$(INC_DIR)" $(CCFLAGS) $(MANDATORY_CFLAGS)
  QA_LFLAGS = -I"$(INC_DIR)" $(CCFLAGS) $(MANDATORY_CFLAGS)

  ENDIANNESS := $(shell $(CC) -o is_big_endian.exe $(QA_TOOLS)/Other_src/is_big_endian.c >/dev/null 2>&1 ;\
                ./is_big_endian.exe || echo BIG_ENDIAN ;\
                ./is_big_endian.exe && echo LITTLE_ENDIAN ;\
                \rm -f is_big_endian.exe >/dev/null 2>&1 ;\
                )

  SPECIAL_COMPILER_CFLAGS := -D$(ENDIANNESS) $(patsubst %,-idirafter "%",$(PROTO_INC_DIR)) $(MANDATORY_GCC)
  SPECIAL_COMPILER_LFLAGS := -D$(ENDIANNESS) $(patsubst %,-idirafter "%",$(PROTO_INC_DIR)) $(MANDATORY_GCC)
endif

ifeq "$(CC)" "scc"
  O = eln
  A = sl
  E = eld
  COMPILER = scc
  LINKER   = scc

  CMDFLAGS = $(filter-out , $(CFLAGS))
  CCFLAGS = $(filter-out $(FORBIDDEN_SCC), $(CFLAGS))
  ifneq ($(CCFLAGS),$(CMDFLAGS))
     $(warning "Warning : The following flags are not supported: $(FORBIDDEN_SCC)") ;
  endif

  QA_CFLAGS = -I"$(INC_DIR)" $(CCFLAGS) $(MANDATORY_CFLAGS)
  QA_LFLAGS = -I"$(INC_DIR)" $(CCFLAGS) $(MANDATORY_CFLAGS)

  SPECIAL_COMPILER_CFLAGS := -r $(OBJ_DIR) $(MANDATORY_SCC)
  SPECIAL_COMPILER_LFLAGS := $(MANDATORY_SCC)
  SPECIAL_COMPILER_DASM_CFLAGS := -r $(DASM_DIR) $(MANDATORY_SCC)
  SPECIAL_COMPILER_DASM_LFLAGS := $(MANDATORY_SCC)
endif

ifeq "$(CC)" "ppc"
  O = o
  E = elf
  COMPILER = mwcceppc
  LINKER   = mwldeppc

  CMDFLAGS = $(filter-out , $(CFLAGS))
  CCFLAGS = $(filter-out $(FORBIDDEN_PPC), $(CFLAGS))
  ifneq ($(CCFLAGS),$(CMDFLAGS))
     $(warning "Warning : The following flags are not supported: $(FORBIDDEN_PPC)") ;
  endif

  QA_CFLAGS = -I"$(INC_DIR)" $(CCFLAGS) $(MANDATORY_CFLAGS)
  QA_LFLAGS = $(patsubst -D%,,$(MANDATORY_CFLAGS))

  # This is the zen processor
  PROC     = zen
  PREFIX   = prefix.h

  LIB += ${CWFOLDER}/PowerPC_EABI_Support/Runtime/Lib/Runtime.PPCEABI.Z5.a \
         $(wildcard ${CWFOLDER}/PowerPC_EABI_Support/M[Ss][Ll]/MSL_C/PPC_EABI/Lib/MSL_C.PPCEABI.bare.Z5.a) \
         $(wildcard ${CWFOLDER}/PowerPC_EABI_Support/M[Ss][Ll]/MSL_C/PPC_EABI/Lib/fdlibm.PPCEABI.Z5.a)

  COMMON_SRC += $(COM_DIR)/src/sim-syscall.c

  ENDIANNESS := LITTLE_ENDIAN

  SPECIAL_COMPILER_INC_PATH = -I$(COM_DIR)/src  -I- -ir ${CWFOLDER}/PowerPC_EABI_Support $(patsubst %,-ir "%",$(PROTO_INC_DIR))

  SPECIAL_COMPILER_CFLAGS := -o obj/ $(SPECIAL_COMPILER_INC_PATH) -D$(ENDIANNESS) $(MANDATORY_PPC) \
                             -nodefaults     -bool off       -Cpp_exceptions off   -lang c \
                             -enum min       -inline smart   -RTTI off             -wchar_t off \
                             -proc $(PROC)   -fp soft        -prefix $(PREFIX)

  SPECIAL_COMPILER_LFLAGS := $(patsubst -D%,,$(MANDATORY_PPC)) \
                             -nodefaults     -application    -proc $(PROC)         -fp soft     -w on
endif

ifeq "$(CC)" "mwccarm"
  O = o
  E = axf
  COMPILER = $(CWFOLDER)/ARM_Tools/Command_Line_Tools/mwccarm
  LINKER   = $(CWFOLDER)/ARM_Tools/Command_Line_Tools/mwldarm

  CMDFLAGS = $(filter-out , $(CFLAGS))
  CCFLAGS = $(filter-out $(FORBIDDEN_MWCCARM), $(CFLAGS))
  ifneq ($(CCFLAGS),$(CMDFLAGS))
     $(warning "Warning : The following flags are not supported: $(FORBIDDEN_MWCCARM)") ;
  endif

  QA_CFLAGS =  $(CCFLAGS) $(MANDATORY_CFLAGS)
  QA_LFLAGS =  -big

  # This is the arm processors
  PROC     ?= arm7

ifeq "$(ARM_MODE)" "thumb"
  LIB +=  $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/Mathlib/Lib/mw_fj_t_p.b.a))) \
          $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/Runtime/Lib/Thumb_Runtime_BE.a))) \
          $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/msl/MSL_C/MSL_ARM/Lib/MSL_C_Thumb_BE.a))) \
          $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/msl/MSL_Extras/MSL_ARM/Lib/MSL_Extras_Thumb_BE.a))) \
          $(subst //,/,$(call stdpath,$(wildcard $(CWFOLDER)/ARM_Tools/Command_Line_Tools/ARM.lcf)))
else
  LIB +=  $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/Mathlib/Lib/mw_fj_a_p.b.a))) \
          $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/Runtime/Lib/ARM_Runtime_BE.a))) \
          $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/msl/MSL_C/MSL_ARM/Lib/MSL_C_ARM_BE.a))) \
          $(subst //,/,$(call stdpath,$(wildcard ${CWFOLDER}/ARM_EABI_Support/msl/MSL_Extras/MSL_ARM/Lib/MSL_Extras_ARM_BE.a))) \
          $(subst //,/,$(call stdpath,$(wildcard $(CWFOLDER)/ARM_Tools/Command_Line_Tools/ARM.lcf)))
endif

  ENDIANNESS := BIG_ENDIAN

  SPECIAL_COMPILER_INC_PATH = -I- -ir $(subst //,/,$(call stdpath,${CWFOLDER}/ARM_EABI_Support)) -ir $(INC_DIR) \
                              -ir $(subst //,/,$(call stdpath,${CWFOLDER}/ARM_EABI_Support/msl/MSL_C/MSL_Common/Include)) \
                              $(patsubst %,-ir "%",$(PROTO_INC_DIR))

  SPECIAL_COMPILER_CFLAGS := -o obj/ $(SPECIAL_COMPILER_INC_PATH) -D$(ENDIANNESS) $(MANDATORY_ARM) \
                             -nodefaults     -bool off       -Cpp_exceptions off   -lang c \
                             -enum min       -inline smart   -RTTI off             -wchar_t off \
                             -proc $(PROC)   -fp soft -big

ifeq "$(ARM_MODE)" "thumb"
  SPECIAL_COMPILER_CFLAGS += -thumb -interworking -maxwarnings 1
endif

  SPECIAL_COMPILER_LFLAGS := $(MANDATORY_ARM) \
                             -nodefaults     -application    -proc $(PROC)         -fp soft     -w on -big

ifeq "$(ARM_MODE)" "thumb"
  SPECIAL_COMPILER_LFLAGS += -thumb -interworking -maxwarnings 1
endif

endif



ifeq "$(CC)" "armcc"
  O = o
  E = axf

  OBJ_IN_ROOT := 1

  ARMCONF ?=      $(subst //,/,$(call stdpath,$(CWFOLDER)/Bin))
  ARMHOME ?=      $(subst //,/,$(call stdpath,$(CWFOLDER)))
  ARMINC  ?=      $(subst //,/,$(call stdpath,$(CWFOLDER)/Include))
  ARMLIB  ?=      $(subst //,/,$(call stdpath,$(CWFOLDER)/Lib))
  LM_LICENSE_FILE ?=  $(subst //,/,$(call stdpath,$(CWFOLDER)/License.dat))

ifeq "$(ARM_MODE)" "thumb"
  COMPILER = export ARMCONF=$(ARMCONF) ;\
             export ARMHOME=$(ARMHOME) ;\
             export ARMINC=$(ARMINC) ;\
             export ARMLIB=$(ARMLIB) ;\
             export LM_LICENSE_FILE=$(LM_LICENSE_FILE) ;\
             $(CWFOLDER)/Bin/tcc
else
  COMPILER = export ARMCONF=$(ARMCONF) ;\
             export ARMHOME=$(ARMHOME) ;\
             export ARMINC=$(ARMINC) ;\
             export ARMLIB=$(ARMLIB) ;\
             export LM_LICENSE_FILE=$(LM_LICENSE_FILE) ;\
             $(CWFOLDER)/Bin/armcc
endif
  LINKER   = export ARMCONF=$(ARMCONF) ;\
             export ARMHOME=$(ARMHOME) ;\
             export ARMINC=$(ARMINC) ;\
             export ARMLIB=$(ARMLIB) ;\
             export LM_LICENSE_FILE=$(LM_LICENSE_FILE) ;\
             $(CWFOLDER)/Bin/armlink

  CMDFLAGS = $(filter-out , $(CFLAGS))
  CCFLAGS = $(filter-out $(FORBIDDEN_ARMCC), $(CFLAGS))
  ifneq ($(CCFLAGS),$(CMDFLAGS))
     $(warning "Warning : The following flags are not supported: $(FORBIDDEN_ARMCC)") ;
  endif

  QA_CFLAGS =  $(CCFLAGS) $(MANDATORY_CFLAGS)
  QA_LFLAGS =

  # This is the arm processors
  PROC     ?= arm7tdmi

  ENDIANNESS := BIG_ENDIAN

  SPECIAL_COMPILER_INC_PATH = -I $(INC_DIR) -I- -I $(subst //,/,$(call stdpath,${CWFOLDER}/Include)) $(patsubst %,-I "%",$(PROTO_INC_DIR)')

ifeq "$(PROTO)" "NPR"
  SPECIAL_COMPILER_CFLAGS := $(SPECIAL_COMPILER_INC_PATH) -D$(ENDIANNESS) $(MANDATORY_ARM) \
                             -cpu $(PROC) -bi -fpu softvfp -interwork
else
  SPECIAL_COMPILER_CFLAGS := $(SPECIAL_COMPILER_INC_PATH) -D$(ENDIANNESS) $(MANDATORY_ARM) \
                             -ansi -cpu $(PROC) -bi -fpu softvfp -interwork
endif
  SPECIAL_COMPILER_LFLAGS :=
endif




ifeq "$(CC)" "gccarm"
  O = o
  E = elf
  COMPILER = $(CWFOLDER)/bin/arm-elf-gcc
  LINKER   = $(CWFOLDER)/bin/arm-elf-gcc

  CMDFLAGS = $(filter-out , $(CFLAGS))
  CCFLAGS = $(filter-out $(FORBIDDEN_GCCARM), $(CFLAGS))
  ifneq ($(CCFLAGS),$(CMDFLAGS))
     $(warning "Warning : The following flags are not supported: $(FORBIDDEN_GCCARM)") ;
  endif

  QA_CFLAGS =  $(CCFLAGS) $(MANDATORY_CFLAGS)
  QA_LFLAGS =

  # This is the arm processors
  PROC     = arm7tdmi

  ENDIANNESS := BIG_ENDIAN

  SPECIAL_COMPILER_INC_PATH = -I $(CWFOLDER)/arm-elf/include -I $(INC_DIR) $(patsubst %,-I "%",$(PROTO_INC_DIR))

  SPECIAL_COMPILER_CFLAGS := $(SPECIAL_COMPILER_INC_PATH) -D$(ENDIANNESS) $(MANDATORY_ARM) \
                             -mcpu=$(PROC)

ifeq "$(ARM_MODE)" "thumb"
  SPECIAL_COMPILER_CFLAGS += -mthumb -mcallee-super-interworking
endif

  SPECIAL_COMPILER_LFLAGS := $(MANDATORY_ARM) \
                             -mcpu=$(PROC)

ifeq "$(ARM_MODE)" "thumb"
	SPECIAL_COMPILER_LFLAGS += -mthumb -mthumb-interwork
endif

endif
### end gccarm ###

ifeq "$(CC)" "win32_x86"
  O = obj
  E = exe

  COMPILER = $(QA_TOOLS)/compilers/$(CC)/compile
  LINKER   = $(QA_TOOLS)/compilers/$(CC)/linkruntime

  QA_CFLAGS = -I"$(INC_DIR)" $(CFLAGS) $(MANDATORY_CFLAGS)

  MW_CYGDRIVE_PREFIX ?= /cygdrive
  LM_LICENSE_FILE ?=  $(subst //,/,$(call stdpath,$(CWFOLDER)/License.dat))

# CW doesn't take cygwin root too well, convert it before using
  ENDIANNESS := $(shell $(COMPILER) -o is_big_endian.exe $(subst //,/,$(call stdpath,${QA_TOOLS}/Other_src)/is_big_endian.c) >/dev/null 2>&1 ;\
                ./is_big_endian.exe || echo BIG_ENDIAN ;\
                ./is_big_endian.exe && echo LITTLE_ENDIAN ;\
                rm -f is_big_endian.exe >/dev/null 2>&1 ;\
                )

  SPECIAL_COMPILER_CFLAGS := -D$(ENDIANNESS) $(patsubst %,-idirafter "%",$(PROTO_INC_DIR)) $(MANDATORY_WIN32_X86)
endif
### end win32_x86 ###

ifeq "$(CC)" "dsp56800e"
  O = o
  E = out
  COMPILER = $(QA_TOOLS)/compilers/$(CC)/compile
  LINKER   = $(QA_TOOLS)/compilers/$(CC)/linkruntime

  OBJ_IN_ROOT := 1

  QA_CFLAGS = -gccinc -I"$(INC_DIR)" $(CFLAGS) $(MANDATORY_CFLAGS)

#  MW_CYGDRIVE_PREFIX ?= /cygdrive
  LM_LICENSE_FILE ?=  $(subst //,/,$(call stdpath,$(CWFOLDER)/License.dat))

# CW doesn't take cygwin root too well, convert it before using
  ENDIANNESS := LITTLE_ENDIAN

  SPECIAL_COMPILER_CFLAGS := -D$(ENDIANNESS) $(patsubst %,-i- -i "%",$(PROTO_INC_DIR)) $(MANDATORY_DSP56800E)
endif
### end dsp56800e ###

ifeq "$(CC)" "mac_ppc"
  O = o
  E = out
  COMPILER = $(QA_TOOLS)/compilers/$(CC)/compile
  LINKER   = $(QA_TOOLS)/compilers/$(CC)/linkruntime

  QA_CFLAGS = -I"$(INC_DIR)" $(CFLAGS) $(MANDATORY_CFLAGS)

  LM_LICENSE_FILE ?=  $(subst //,/,$(call stdpath,$(CWFOLDER)/License.dat))

# CW doesn't take cygwin root too well, convert it before using
  ENDIANNESS := BIG_ENDIAN

  SPECIAL_COMPILER_CFLAGS := -D$(ENDIANNESS) $(patsubst %,-idirafter "%",$(PROTO_INC_DIR)) $(MANDATORY_MAC_PPC)
endif
### end mac_ppc ###

ifeq "$(CC)" "dsp56800"
  O = o
  E = out
  COMPILER = $(QA_TOOLS)/compilers/$(CC)/compile
  LINKER   = $(QA_TOOLS)/compilers/$(CC)/linkruntime

  OBJ_IN_ROOT := 1

  QA_CFLAGS = -gccinc -I"$(INC_DIR)" $(CFLAGS) $(MANDATORY_CFLAGS)

#  MW_CYGDRIVE_PREFIX ?= /cygdrive
  LM_LICENSE_FILE ?=  $(subst //,/,$(call stdpath,$(CWFOLDER)/License.dat))

# CW doesn't take cygwin root too well, convert it before using
  ENDIANNESS := LITTLE_ENDIAN

  SPECIAL_COMPILER_CFLAGS := -D$(ENDIANNESS) $(patsubst %,-i- -i "%",$(PROTO_INC_DIR)) $(MANDATORY_DSP56800)
endif
### end dsp56800 ###


#################################################################
### CC FLAGS depending on the COMPILATION MODE: I.E.  BASIC_OP / EMULATE / NPR

ifeq ($(PROTO),BASIC_OP)
  vpath %.c   $(SRC_DIR)
  vpath %.h   $(INC_DIR)
  # Mandatory compiler options, this variable must not be renamed
  MANDATORY_CFLAGS :=
  #
  QA_CFLAGS +=
  QA_LFLAGS +=
  PROTO_SRC =
else

ifeq ($(PROTO),EMULATE)
  vpath %.c   $(SRC_DIR)
  vpath %.h   $(INC_DIR)
  # Mandatory compiler options, this variable must not be renamed
  MANDATORY_CFLAGS := -D_USE_CW_PROTO_
  #
  QA_CFLAGS +=
  QA_LFLAGS +=
  PROTO_SRC =
else

ifeq ($(PROTO),NPR)
  vpath %.c   $(SRC_DIR) "$(PROTO_SRC_DIR)"
  vpath %.h   $(INC_DIR) "$(PROTO_INC_DIR)"
  # Mandatory compiler options, this variable must not be renamed
  MANDATORY_CFLAGS := -D_USE_CW_PROTO_
  #
  QA_CFLAGS +=
  ifeq "$(CC)" "scc"
     QA_CFLAGS += -npr
  endif
  QA_LFLAGS +=
  PROTO_SRC = $(PROTO_SRC_DIR)/prototype.c
else
  $(error "The available values for the PROTO variable are: BASIC_OP, NPR.")
endif
endif
endif

vpath %.$(O) $(OBJ_DIR)
vpath %.$(E) $(BIN_DIR)

#################################################################
### UPDATE THE SOURCES IF NECESSARY.

COMMON_SRC += $(PROTO_SRC)

ifeq "$(CC)" "scc"
ifneq (,$(findstring -D_QA_SWPROBING_,$(QA_CFLAGS))$(findstring -D_MSC8101ADS_,$(QA_CFLAGS))$(findstring -D_MSC8102ADS_,$(QA_CFLAGS)))
  COMMON_SRC += $(COM_DIR)/src/eoncecnt.c
  QA_CFLAGS  += -I$(COM_DIR)/src
  QA_LFLAGS  += -I$(COM_DIR)/src
endif
endif

COMMON_ASM_SRC += $(ASM_SRC)

################################################################
### HERE ARE THE OBJECTS REALLY CREATED.

COD_OBJ    =     $(notdir $(patsubst %.$(C_EXT),%.$(O),$(patsubst %.$(CPP_EXT),%.$(O),$(COD_SRC))) )
DEC_OBJ    =     $(notdir $(patsubst %.$(C_EXT),%.$(O),$(patsubst %.$(CPP_EXT),%.$(O),$(DEC_SRC))) )
COMMON_OBJ =     $(notdir $(patsubst %.$(C_EXT),%.$(O),$(patsubst %.$(CPP_EXT),%.$(O),$(COMMON_SRC))) )
COD_ASM_OBJ    = $(notdir $(COD_ASM_SRC:.asm=.$(O))) )
COMMON_ASM_OBJ = $(notdir $(COMMON_ASM_SRC:.asm=.$(O))) )
DEC_ASM_OBJ    = $(notdir $(DEC_ASM_SRC:.asm=.$(O))) )

################################################################
### HERE ARE THE OBJECTS REALLY CREATED.

REAL_COD_OBJ    = $(foreach f,$(COD_OBJ),    $(wildcard $(OBJ_DIR)/$(f)))
REAL_DEC_OBJ    = $(foreach f,$(DEC_OBJ),    $(wildcard $(OBJ_DIR)/$(f)))
REAL_COMMON_OBJ = $(foreach f,$(COMMON_OBJ), $(wildcard $(OBJ_DIR)/$(f)))
REAL_COD_ASM_OBJ    = $(foreach f,$(COD_ASM_OBJ),    $(wildcard $(OBJ_DIR)/$(f)))
REAL_COMMON_ASM_OBJ = $(foreach f,$(COMMON_ASM_OBJ),    $(wildcard $(OBJ_DIR)/$(f)))
REAL_DEC_ASM_OBJ    = $(foreach f,$(DEC_ASM_OBJ),    $(wildcard $(OBJ_DIR)/$(f)))

################################################################
### HERE ARE THE DISASSEMBLED OBJECTS FILES REALLY CREATED.

DASM_COD_SL     = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_COD_OBJ:.$(O)=.$(A) )) )
DASM_DEC_SL     = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_DEC_OBJ:.$(O)=.$(A) )) )
DASM_COMMON_SL  = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_COMMON_OBJ:.$(O)=.$(A) )) )
DASM_COD_ASM_SL     = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_COD_ASM_OBJ:.$(O)=.$(A) )) )
DASM_COMMON_ASM_SL  = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_COMMON_ASM_OBJ:.$(O)=.$(A) )) )
DASM_DEC_ASM_SL     = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_DEC_ASM_OBJ:.$(O)=.$(A) )) )

DASM_COD_OBJ    = $(patsubst %.$(O),%.$(A),$(DASM_COD_SL))
DASM_DEC_OBJ    = $(patsubst %.$(O),%.$(A),$(DASM_DEC_SL))
DASM_COMMON_OBJ = $(patsubst %.$(O),%.$(A),$(DASM_COMMON_SL))
DASM_COD_ASM_OBJ    = $(patsubst %.$(O),%.$(A),$(DASM_COD_ASM_SL))
DASM_COMMON_ASM_OBJ = $(patsubst %.$(O),%.$(A),$(DASM_COMMON_ASM_SL))
DASM_DEC_ASM_OBJ    = $(patsubst %.$(O),%.$(A),$(DASM_DEC_ASM_SL))


########################################################################################################
########################################################################################################
############################################ GENERIC RULES #############################################
########################################################################################################
########################################################################################################

all:
	$(MAKE) -f $(MAKEFILENAME) coder
	$(MAKE) -f $(MAKEFILENAME) light_clean
	$(MAKE) -f $(MAKEFILENAME) decoder
	$(MAKE) -f $(MAKEFILENAME) light_clean
	$(MAKE) -f $(MAKEFILENAME) coder_decoder
	$(MAKE) -f $(MAKEFILENAME) light_clean

coder: $(BIN_DIR)/coder.$(E)
	- @echo "coder done"
decoder: $(BIN_DIR)/decoder.$(E)
	- @echo "decoder done"
coder_decoder: $(BIN_DIR)/coder_decoder.$(E)
	- @echo "coder_decoder done"



######################################################################
### FOR THE CODER

$(BIN_DIR)/coder.$(E): $(COD_SRC) $(COMMON_SRC) $(COMMON_ASM_SRC) $(COD_ASM_SRC)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) -D_QA_CODER_ $(COD_SRC) $(COMMON_SRC) $(COMMON_ASM_SRC) $(COD_ASM_SRC)
ifdef OBJ_IN_ROOT
	-mv -f $(COD_OBJ) $(COMMON_OBJ) $(OBJ_DIR)/.
endif
	$(MAKE) -f $(MAKEFILENAME) coder_obj2exe
ifdef DASM
	$(MAKE) -f $(MAKEFILENAME) coder_obj2exe_dasm_$(DASM)
endif

coder_obj2exe: $(REAL_COD_OBJ) $(REAL_COMMON_OBJ) $(REAL_COMMON_ASM_OBJ) $(REAL_COD_ASM_OBJ)
	$(LINKER) -o $(BIN_DIR)/coder.$(E) $(SPECIAL_COMPILER_LFLAGS) $(REAL_COD_OBJ) $(REAL_COMMON_OBJ) $(REAL_COMMON_ASM_OBJ) $(REAL_COD_ASM_OBJ) $(LIB) $(QA_LFLAGS)
ifeq (gcc,$(findstring gcc,$(CC))$(findstring -g,$(QA_CFLAGS)))
	-strip $(BIN_DIR)/coder.$(E)
endif


coder_obj2exe_dasm_eln: $(DASM_COD_SL) $(DASM_COMMON_SL) $(REAL_COMMON_ASM_SL) $(REAL_COD_ASM_SL)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) -D_QA_CODER_ $(DASM_COD_SL) $(DASM_COMMON_SL) $(REAL_COMMON_ASM_SL) $(REAL_COD_ASM_SL)
	$(LINKER) -o $(DASM_DIR)/coder.$(E) $(SPECIAL_COMPILER_DASM_LFLAGS) $(DASM_COD_OBJ) $(DASM_COMMON_OBJ) $(REAL_COMMON_ASM_OBJ) $(REAL_COD_ASM_OBJ) $(LIB) $(QA_LFLAGS)


coder_obj2exe_dasm_eld: $(BIN_DIR)/coder.$(E)
	disasmsc100 -p -q -r $(BIN_DIR)/coder.$(E) > $(DASM_DIR)/coder.$(A)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) -D_QA_CODER_ $(DASM_DIR)/coder.$(A)
	$(LINKER) -o $(DASM_DIR)/coder.$(E) $(SPECIAL_COMPILER_DASM_LFLAGS) $(DASM_DIR)/coder.$(O) $(QA_LFLAGS)


######################################################################
### FOR THE DECODER

$(BIN_DIR)/decoder.$(E): $(DEC_SRC) $(COMMON_SRC) $(COMMON_ASM_SRC) $(DEC_ASM_SRC)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) -D_QA_DECODER_ $(DEC_SRC) $(COMMON_SRC) $(COMMON_ASM_SRC) $(DEC_ASM_SRC)
ifdef OBJ_IN_ROOT
	-mv -f $(DEC_OBJ) $(COMMON_OBJ) $(OBJ_DIR)/.
endif
	$(MAKE) -f $(MAKEFILENAME) decoder_obj2exe
ifdef DASM
	$(MAKE) -f $(MAKEFILENAME) decoder_obj2exe_dasm_$(DASM)
endif


decoder_obj2exe: $(REAL_DEC_OBJ) $(REAL_COMMON_OBJ) $(REAL_COMMON_ASM_OBJ) $(REAL_DEC_ASM_OBJ)
	$(LINKER) -o $(BIN_DIR)/decoder.$(E) $(SPECIAL_COMPILER_LFLAGS) $(REAL_DEC_OBJ) $(REAL_COMMON_OBJ) $(REAL_COMMON_ASM_OBJ) $(REAL_DEC_ASM_OBJ) $(LIB) $(QA_LFLAGS)
ifeq (gcc,$(findstring gcc,$(CC))$(findstring -g,$(QA_CFLAGS)))
	-strip $(BIN_DIR)/decoder.$(E)
endif


decoder_obj2exe_dasm_eln: $(DASM_DEC_SL) $(DASM_COMMON_SL) $(REAL_COMMON_ASM_SL) $(REAL_DEC_ASM_SL)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) -D_QA_DECODER_ $(DASM_DEC_SL) $(DASM_COMMON_SL) $(REAL_COMMON_ASM_SL) $(REAL_DEC_ASM_SL)
	$(LINKER) -o $(DASM_DIR)/decoder.$(E) $(SPECIAL_COMPILER_DASM_LFLAGS) $(DASM_DEC_SL) $(DASM_COMMON_SL) $(REAL_COMMON_ASM_OBJ) $(REAL_DEC_ASM_OBJ) $(LIB) $(QA_LFLAGS)


decoder_obj2exe_dasm_eld: $(BIN_DIR)/decoder.$(E)
	disasmsc100 -p -q -r $(BIN_DIR)/decoder.$(E) > $(DASM_DIR)/decoder.$(A)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) -D_QA_DECODER_ $(DASM_DIR)/coder.$(A)
	$(LINKER) -o $(DASM_DIR)/decoder.$(E) $(SPECIAL_COMPILER_DASM_LFLAGS) $(DASM_DIR)/decoder.$(O) $(QA_LFLAGS)

######################################################################
### FOR THE CODER_DECODER

$(BIN_DIR)/coder_decoder.$(E): $(COD_SRC) $(DEC_SRC) $(COMMON_SRC) $(COD_ASM_SRC) $(COMMON_ASM_SRC) $(DEC_ASM_SRC)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) -D_QA_CODER_DECODER_ $(COD_SRC) $(DEC_SRC) $(COMMON_SRC) $(COD_ASM_SRC) $(COMMON_ASM_SRC) $(DEC_ASM_SRC)
ifdef OBJ_IN_ROOT
	-mv -f $(COD_OBJ) $(DEC_OBJ) $(COMMON_OBJ) $(OBJ_DIR)/.
endif
	$(MAKE) -f $(MAKEFILENAME) coder_decoder_obj2exe
ifdef DASM
	$(MAKE) -f $(MAKEFILENAME) coder_decoder_obj2exe_dasm_$(DASM)
endif


coder_decoder_obj2exe: $(REAL_COD_OBJ) $(REAL_DEC_OBJ) $(REAL_COMMON_OBJ) $(REAL_COD_ASM_OBJ) $(REAL_COMMON_ASM_OBJ) $(REAL_DEC_ASM_OBJ)
	$(LINKER) -o $(BIN_DIR)/coder_decoder.$(E) $(SPECIAL_COMPILER_LFLAGS) $(REAL_COD_OBJ) $(REAL_DEC_OBJ) $(REAL_COMMON_OBJ) $(REAL_COD_ASM_OBJ) $(REAL_COMMON_ASM_OBJ) $(REAL_DEC_ASM_OBJ) $(LIB) $(QA_LFLAGS)
ifeq (gcc,$(findstring gcc,$(CC))$(findstring -g,$(QA_CFLAGS)))
	-strip $(BIN_DIR)/coder_decoder.$(E)
endif


coder_decoder_obj2exe_dasm_eln: $(DASM_COD_SL) $(DASM_DEC_SL) $(DASM_COMMON_SL) $(REAL_COD_ASM_SL) $(REAL_COMMON_ASM_SL) $(REAL_DEC_ASM_SL)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) -D_QA_CODER_DECODER_ $(DASM_COD_SL) $(DASM_DEC_SL) $(DASM_COMMON_SL) $(REAL_COD_ASM_SL) $(REAL_COMMON_ASM_SL) $(REAL_DEC_ASM_SL) $(LIB)
	$(LINKER) -o $(DASM_DIR)/coder_decoder.$(E) $(SPECIAL_COMPILER_DASM_LFLAGS) $(DASM_COD_SL) $(DASM_DEC_SL) $(DASM_COMMON_SL) $(QA_LFLAGS)


coder_decoder_obj2exe_dasm_eld: $(BIN_DIR)/coder_decoder.$(E)
	disasmsc100 -p -q -r $(BIN_DIR)/coder_decoder.$(E) > $(DASM_DIR)/coder_decoder.$(A)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) -D_QA_CODER_DECODER_ $(DASM_DIR)/coder_decoder.$(A)
	$(LINKER) -o $(DASM_DIR)/coder_decoder.$(E) $(SPECIAL_COMPILER_DASM_LFLAGS) $(DASM_DIR)/coder_decoder.$(O) $(QA_LFLAGS)

######################################################################
### GENERIC RULES.

ifeq "$(CC)" "scc"
$(DASM_DIR)/%.$(A) : $(OBJ_DIR)/%.$(O)
	disasmsc100 -p -q -r $^ > $@

$(DASM_DIR)/%.$(A) : $(BIN_DIR)/%.$(E)
	disasmsc100 -p -q -r $^ > $@
endif

######################################################################
### CLEANING

.PHONY: clean light_clean

light_clean:
	rm -f $(OBJ_DIR)/*.$(O)
ifdef DASM
	rm -f $(DASM_DIR)/*.$(O)
endif

clean:	light_clean
	rm -f $(BIN_DIR)/*.$(E)
ifdef DASM
	rm -f $(DASM_DIR)/*.$(E)
endif

