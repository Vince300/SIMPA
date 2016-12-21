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

  # Transitional files
  # set here the extensions for files that can be used as source files for the compiler
  # others than object .$(O) and assembler .$(A) files
  TRANS = i obj s1
.PRECIOUS : $(OBJ_DIR)/%.i   $(OBJ_DIR)/%.obj   $(OBJ_DIR)/%.s1

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
  COMMON_OBJ += sim-syscall.$(O)

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
  PROTO_OBJ =
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
  PROTO_OBJ =
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
  PROTO_OBJ = prototype.$(O)
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
COMMON_OBJ += $(PROTO_OBJ)

ifeq "$(CC)" "scc"
ifneq (,$(findstring -D_QA_SWPROBING_,$(QA_CFLAGS))$(findstring -D_MSC8101ADS_,$(QA_CFLAGS))$(findstring -D_MSC8102ADS_,$(QA_CFLAGS)))
  COMMON_SRC += $(COM_DIR)/src/eoncecnt.c
  COMMON_OBJ += eoncecnt.$(O)
  QA_CFLAGS  += -I$(COM_DIR)/src
  QA_LFLAGS  += -I$(COM_DIR)/src
endif
endif


################################################################
### SEPARATE THE TARGETS WITH AND WITHOUT A MAIN FUNCTION.

# We don't want to delete the intermediate files
#
.PRECIOUS : $(BIN_DIR)/%.$(E) $(OBJ_DIR)/%.$(O) $(OBJ_DIR)/%.$(A) $(DASM_DIR)/%.$(E) $(DASM_DIR)/%.$(O) $(DASM_DIR)/%.$(A)

C_EXT     = c
CPP_EXT   = cpp
SRC_EXTLIST = $(C_EXT) $(CPP_EXT) $(O) $(A) $(TRANS)

ifdef MULTIPLE_SOURCE_FILES

  TARGETS_DIRS     := $(patsubst %/.,%,$(wildcard $(SRC_DIR)/*/.) )

# gmake is recursively called defining TARGET and the real SRC_FILES
ifndef TARGET
  SRC_FILES        := $(foreach EXT,$(SRC_EXTLIST),$(wildcard $(SRC_DIR)/*/*.$(EXT)))

  DIR_WITH_MAIN    := $(ADD_TO_DIR_WITH_MAIN) $(patsubst %/,%,$(sort $(dir $(shell $(QA_TOOLS)/have_main.pl $(foreach EXT,$(SRC_EXTLIST),$(wildcard $(SRC_DIR)/*/*.$(EXT)))))))
  DIR_WITHOUT_MAIN := $(filter-out $(DIR_WITH_MAIN),$(TARGETS_DIRS))

  ALLOWED_TARGETS  := $(basename $(notdir $(TARGETS_DIRS)))
  TARGETS_OBJ      := $(basename $(notdir $(DIR_WITHOUT_MAIN)))
  TARGETS_EXE      := $(basename $(notdir $(DIR_WITH_MAIN)))
endif
export DIR_WITH_MAIN DIR_WITHOUT_MAIN

else

# gmake is recursively called defining TARGET and the real SRC_FILES
ifndef TARGET
  SRC_FILES        := $(foreach EXT,$(SRC_EXTLIST),$(wildcard $(SRC_DIR)/*.$(EXT)))
  # We test if the source file contains a "simpa.hit.main"
  #
  SRC_WITH_MAIN    := $(ADD_TO_SRC_WITH_MAIN) $(shell $(QA_TOOLS)/have_main.pl $(SRC_FILES))
  SRC_WITHOUT_MAIN := $(filter-out $(SRC_WITH_MAIN),$(SRC_FILES))
  #
  ALLOWED_TARGETS  := $(basename $(notdir $(SRC_FILES)))
  TARGETS_OBJ      := $(basename $(notdir $(SRC_WITHOUT_MAIN)))
  TARGETS_EXE      := $(basename $(notdir $(SRC_WITH_MAIN)))
endif
export SRC_WITH_MAIN SRC_WITHOUT_MAIN

endif

export ALLOWED_TARGETS TARGETS_OBJ TARGETS_EXE

################################################################
### HERE ARE THE OBJECTS TO BE CREATED.
OBJ_FILES  = $(notdir $(foreach EXT,$(SRC_EXTLIST),$(patsubst %.$(EXT),%.$(O),$(filter %.$(EXT),$(SRC_FILES)))) )
COMMON_OBJ = $(notdir $(foreach EXT,$(SRC_EXTLIST),$(patsubst %.$(EXT),%.$(O),$(filter %.$(EXT),$(COMMON_SRC)))) )
ASM_OBJ    = $(notdir $(ASM_SRC:.asm=.$(O)) )

################################################################
### HERE ARE THE OBJECTS REALLY CREATED.
REAL_OBJ_FILES  = $(foreach f,$(OBJ_FILES), $(wildcard $(OBJ_DIR)/$(f)))
REAL_COMMON_OBJ = $(foreach f,$(COMMON_OBJ), $(wildcard $(OBJ_DIR)/$(f)))
REAL_ASM_OBJ    = $(foreach f,$(ASM_OBJ),    $(wildcard $(OBJ_DIR)/$(f)))

################################################################
### HERE ARE THE DISASSEMBLED OBJECTS FILES REALLY CREATED.
DASM_FILES_SL   = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_OBJ_FILES:.$(O)=.$(A) )) )
DASM_COMMON_SL  = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_COMMON_OBJ:.$(O)=.$(A) )) )
DASM_ASM_SL     = $(addprefix $(DASM_DIR)/, $(notdir $(REAL_ASM_OBJ:.$(O)=.$(A) )) )

DASM_FILES_OBJ  = $(patsubst %.$(O),%.$(A),$(DASM_FILES_SL))
DASM_COMMON_OBJ = $(patsubst %.$(O),%.$(A),$(DASM_COMMON_SL))
DASM_ASM_OBJ    = $(patsubst %.$(O),%.$(A),$(DASM_ASM_SL))


########################################################################################################
########################################################################################################
############################################ GENERIC RULES #############################################
########################################################################################################
########################################################################################################

all :
	$(error "use with a target such that: " $(ALLOWED_TARGETS))

####################################
###%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%###
##% if not MULTIPLE_SOURCE_FILES %##
###%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%###
####################################
ifndef MULTIPLE_SOURCE_FILES

########################################################################################################
############################################ GLOBAL RULES ##############################################
########################################################################################################

######################################################################
### DEFINE THE OBJECT FILES TARGETS.

ifdef DASM
$(TARGETS_OBJ) : % : $(OBJ_DIR)/%.$(O)  $(DASM_DIR)/%.$(O)
	@echo "$@ done"
else
$(TARGETS_OBJ) : % : $(OBJ_DIR)/%.$(O)
	@echo "$@ done"
endif

######################################################################
### DEFINE THE EXECUTABLE TARGETS.

ifdef DASM
$(TARGETS_EXE) : % : $(BIN_DIR)/%.$(E)  $(DASM_DIR)/%.$(E)
	@echo "$@ done"
else
$(TARGETS_EXE) : % : $(BIN_DIR)/%.$(E)
	@echo "$@ done"
endif


########################################################################################################
######################################### DIRECT WAY RULES #############################################
########################################################################################################

######################################################################
### BUILD THE OBJECT FILES.

$(OBJ_DIR)/%.$(O) : $(SRC_DIR)/%.$(C_EXT) $(PROTO_SRC)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) $^
ifdef OBJ_IN_ROOT
	-mv -f $(notdir $@) $(PROTO_OBJ) $(OBJ_DIR)/.
endif

$(OBJ_DIR)/%.$(O) : $(SRC_DIR)/%.$(CPP_EXT) $(PROTO_SRC)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) $^
ifdef OBJ_IN_ROOT
	-mv -f $(notdir $@) $(PROTO_OBJ) $(OBJ_DIR)/.
endif


######################################################################
### BUILD THE EXECUTABLE.

$(BIN_DIR)/%.$(E) : $(OBJ_DIR)/%.$(O)
	-set -x ; \
	if test -f $(OBJ_DIR)/$(PROTO_OBJ) ; then \
		proto=$(OBJ_DIR)/$(PROTO_OBJ) ; \
	else \
		proto=; \
	fi ; \
	$(LINKER) -o $@ $^ $$proto $(QA_LFLAGS) $(SPECIAL_COMPILER_LFLAGS) $(LIB)


########################################################################################################
########################################### DASM WAY RULES #############################################
########################################################################################################

######################################################################
### DISASSEMBLE THE OBJ/ OBJECT FILES.

ifeq "$(DASM)" "eln"
$(DASM_DIR)/%.$(A) : $(OBJ_DIR)/%.$(O)
	disasmsc100 -p -q -r $^ > $@
	-set -x ; \
	if test -f $(OBJ_DIR)/$(PROTO_OBJ) ; then \
		disasmsc100 -p -q -r $(OBJ_DIR)/$(PROTO_OBJ) > $(DASM_DIR)/$(PROTO_OBJ:.$(O)=.$(A)) ; \
	fi ;
endif


######################################################################
### DISASSEMBLE THE BIN/ EXECUTABLE.

ifeq "$(DASM)" "eld"
$(DASM_DIR)/%.$(A) : $(BIN_DIR)/%.$(E)
	disasmsc100 -p -q -r $^ > $@
endif




######################################################################
### BUILD THE DASM/ OBJECT FILES.

$(DASM_DIR)/%.$(O) : $(DASM_DIR)/%.$(A)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) $^
	-set -x ; \
	if test -f $(DASM_DIR)/$(PROTO_OBJ:.$(O)=.$(A)) ; then \
		$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) $(DASM_DIR)/$(PROTO_OBJ:.$(O)=.$(A)) ; \
	fi ;

######################################################################
### BUILD THE DASM/ EXECUTABLE.

$(DASM_DIR)/%.$(E) : $(DASM_DIR)/%.$(O)
	-set -x ; \
	if test -f $(DASM_DIR)/$(PROTO_OBJ) ; then \
		proto=$(DASM_DIR)/$(PROTO_OBJ) ; \
	else \
		proto=; \
	fi ; \
	$(LINKER) -o $@ $^ $$proto $(QA_LFLAGS)


################################
###%%%%%%%%%%%%%%%%%%%%%%%%%%###
##% if MULTIPLE_SOURCE_FILES %##
###%%%%%%%%%%%%%%%%%%%%%%%%%%###
################################
else

########################################################################################################
############################################ GLOBAL RULES ##############################################
########################################################################################################

######################################################################
### DEFINE THE OBJECT FILES TARGETS.

ifdef DASM
$(TARGETS_OBJ) : % : $(OBJ_DIR)/%.$(O)  $(DASM_DIR)/%.$(O)
	-set -x ; \
	one_obj=$(firstword $(wildcard $(addprefix $(OBJ_DIR)/,$(foreach EXT,$(SRC_EXTLIST),$(patsubst %.$(EXT),%.$(O),$(notdir $(wildcard $(SRC_DIR)/$@/*.$(EXT)))))))) ; \
	if [ ! -f $< ] && [ -f "$$one_obj" ]; then \
	  mv "$$one_obj" $< ; \
	fi
	@echo "$@ done"
else
$(TARGETS_OBJ) : % : $(OBJ_DIR)/%.$(O)
	-set -x ; \
	one_obj=$(firstword $(wildcard $(addprefix $(OBJ_DIR)/,$(foreach EXT,$(SRC_EXTLIST),$(patsubst %.$(EXT),%.$(O),$(notdir $(wildcard $(SRC_DIR)/$@/*.$(EXT)))))))) ; \
	if [ ! -f $< ] && [ -f "$$one_obj" ]; then \
	  mv "$$one_obj" $< ; \
	fi
	@echo "$@ done"
endif

######################################################################
### DEFINE THE EXECUTABLE TARGETS.

$(TARGETS_EXE) : % : $(BIN_DIR)/%.$(E)
	@echo "$@ done"


########################################################################################################
######################################### DIRECT WAY RULES #############################################
########################################################################################################

######################################################################
### BUILD THE OBJECT FILES.

ifdef TARGET

$(OBJ_DIR)/%.$(O) : $(SRC_FILES) $(PROTO_SRC)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) $^
ifdef OBJ_IN_ROOT
	-mv -f $(notdir $@) $(PROTO_OBJ) $(OBJ_DIR)/.
endif

else

$(OBJ_DIR)/%.$(O) :
	$(MAKE) -f $(MAKEFILENAME) $@ "SRC_FILES=$(COMMON_SRC) $(foreach EXT,$(SRC_EXTLIST),$(wildcard $(SRC_DIR)/$*/*.$(EXT)))" "TARGET=$*"
	@echo "$@ done"

endif


######################################################################
### BUILD THE EXECUTABLE.

ifdef TARGET

$(BIN_DIR)/$(TARGET).$(E) : $(SRC_FILES)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) $(SRC_FILES)
ifdef OBJ_IN_ROOT
	-mv -f $(foreach EXT,$(SRC_EXTLIST),$(patsubst %.$(EXT),%.$(O),$(filter %.$(EXT),$(notdir $(SRC_FILES))))) $(OBJ_DIR)/.
endif
	$(MAKE) -f $(MAKEFILENAME) $(TARGET)_obj2exe "SRC_FILES=$(SRC_FILES)" "TARGET=$(TARGET)"
ifdef DASM
	$(MAKE) -f $(MAKEFILENAME) $(TARGET)_obj2exe_dasm_$(DASM) "SRC_FILES=$(SRC_FILES)" "TARGET=$(TARGET)"
endif

# Object files that are source files
SRC_OBJ_FILES     = $(filter %.$(O),$(SRC_FILES))
OBJ_SRC_FILES     = $(addprefix $(OBJ_DIR)/,$(notdir $(filter %.$(O),$(SRC_FILES))))

$(TARGET)_obj2exe : $(REAL_OBJ_FILES) $(SRC_OBJ_FILES)
	-set -x ;\
	for i in $(SRC_OBJ_FILES); do \
	  fname=`basename $$i` ;\
	  [ -f $(OBJ_DIR)/$$fname ] && continue ;\
	  cp $$i $(OBJ_DIR)/$$fname ;\
	done
	$(LINKER) -o $(BIN_DIR)/$(TARGET).$(E) $(SPECIAL_COMPILER_LFLAGS) $(QA_LFLAGS) $(REAL_OBJ_FILES) $(OBJ_SRC_FILES)

$(TARGET)_obj2exe_dasm_eln : $(DASM_FILES_SL)
	$(COMPILER) -c $(SPECIAL_COMPILER_CFLAGS) $(QA_CFLAGS) $(DASM_FILES_SL)
	$(LINKER) -o $(BIN_DIR)/$(TARGET).$(E) $(SPECIAL_COMPILER_LFLAGS) $(QA_LFLAGS) $(DASM_FILES_OBJ)

$(TARGET)_obj2exe_dasm_eld :
	disasmsc100 -p -q -r $(BIN_DIR)/$(TARGET).$(E) > $(DASM_DIR)/$(TARGET).$(A)
	$(COMPILER) -c $(SPECIAL_COMPILER_DASM_CFLAGS) $(QA_CFLAGS) $(DASM_DIR)/$(TARGET).$(A)
	$(LINKER) -o $(DASM_DIR)/$(TARGET).$(E) $(SPECIAL_COMPILER_LFLAGS) $(QA_LFLAGS) $(REAL_OBJ_FILES)

else

$(BIN_DIR)/%.$(E) :
	$(MAKE) -f $(MAKEFILENAME) $@ "SRC_FILES=$(COMMON_SRC) $(foreach EXT,$(SRC_EXTLIST),$(wildcard $(SRC_DIR)/$*/*.$(EXT)))" "TARGET=$*"
	@echo "$@ done"

endif

######################################################################
### GENERIC RULES.

ifeq "$(CC)" "scc"
$(DASM_DIR)/%.$(A) : $(OBJ_DIR)/%.$(O)
	disasmsc100 -p -q -r $^ > $@

$(DASM_DIR)/%.$(A) : $(BIN_DIR)/%.$(E)
	disasmsc100 -p -q -r $^ > $@
endif

endif # MULTIPLE_SOURCE_FILES


########################################################################################################
############################################## CLEANING ################################################
########################################################################################################


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

