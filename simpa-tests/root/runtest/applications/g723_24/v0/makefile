
######################################################################
### MANDATORY FLAGS SPECIAL FOR THIS APPLICATION (-mb, -mem ...)

MANDATORY_GCC = -D__DSP__
MANDATORY_PPC = -D__DSP__
MANDATORY_SCC = -D__DSP__

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
	coder/encode.c\
	coder/g721_encoder.c\
	coder/g723_24_encoder.c\
	coder/g723_40_encoder.c



DEC_SRC =\
	decoder/decode.c\
	decoder/g721_decoder.c\
	decoder/g723_24_decoder.c\
	decoder/g723_40_decoder.c



COMMON_SRC = \
	common/simpa.hit.main.c\
	common/perf_table.c\
	common/g711.c\
	common/g72x.c\
	common/check.c

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
 
