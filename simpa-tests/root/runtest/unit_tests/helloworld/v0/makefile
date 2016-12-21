
######################################################################
### MANDATORY FLAGS SPECIAL FOR THIS APPLICATION (-mb, -mem ...)

MANDATORY_GCC =
MANDATORY_PPC =
MANDATORY_SCC =
MANDATORY_WIN32_X86 =

######################################################################
### DIRECTORIES

SRC_DIR     := src
INC_DIR     := include
OBJ_DIR     := obj
BIN_DIR     := bin

######################################################################
### SOURCES

SRC_FILES =\
	$(SRC_DIR)/hello1.c\
	$(SRC_DIR)/hello2.c

ASM_SRC =

LIB =


######################################################################
### GENERIC MAKEFILE INCLUSION

SYS_OS := $(shell uname -s)

ifeq (,$(findstring CYGWIN,$(SYS_OS)))
    WHERE_THE_GENERIC_MAKEFILE_IS = $(QA_TOOLS)/generic_test/unit_tests
else
    WHERE_THE_GENERIC_MAKEFILE_IS := $(shell cygpath -d -m "$(QA_TOOLS)/generic_test/unit_tests")
endif


include  $(WHERE_THE_GENERIC_MAKEFILE_IS)/makefile_generic.mk
