
######################################################################
### MANDATORY FLAGS SPECIAL FOR THIS APPLICATION (-mb, -mem ...)

MANDATORY_GCC = 
MANDATORY_PPC = 
MANDATORY_SCC = 

######################################################################
### DIRECTORIES

SRC_DIR     := src
CODER_DIR   := coder
DECODER_DIR := decoder
COMMON_DIR  := common
INC_DIR     := include

OBJ_DIR     := obj
DASM_DIR    := dasm
BIN_DIR     := bin

######################################################################
### SOURCES

COD_SRC =\
	$(CODER_DIR)/encoder.c



DEC_SRC =\
	$(DECODER_DIR)/decoder.c


COMMON_SRC = \
	$(COMMON_DIR)/ecc.c\
	$(COMMON_DIR)/perf_table.c\
	$(COMMON_DIR)/version.c\
	$(COMMON_DIR)/rslib.c\
	$(COMMON_DIR)/gflib.c\



ASM_SRC = 


LIB = 


######################################################################
### GENERIC MAKEFILE INCLUSION

SYS_OS := $(shell uname -s)

ifeq (,$(findstring CYGWIN,$(SYS_OS)))
    WHERE_THE_GENERIC_MAKEFILE_IS = $(QA_TOOLS)/generic_test/codec
else
    WHERE_THE_GENERIC_MAKEFILE_IS := $(shell cygpath -d -m "$(QA_TOOLS)/generic_test/codec")
endif


include  $(WHERE_THE_GENERIC_MAKEFILE_IS)/makefile_generic.mk

