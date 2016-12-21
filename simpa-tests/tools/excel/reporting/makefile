# XML reports reader Makefile

#### Tools ###############################################################
.PHONY: all clean lex

ifdef PURIFY
DBG = 1
CC = purify -best_effort gcc
else
CC = gcc
endif

host-type := ${OSTYPE}
wind_host := ${OS}

ifdef wind_host
	EXTENSION = .exe
else
	EXTENSION =
endif

YACC = bison
LEX = flex

#### Flags  ##############################################################
ifdef DBG
ifdef PURIFY
YFLAGS  = -d --debug
LFLAGS  = -L -i
CCFLAGS = -g -Wall -Wbad-function-cast -Wtraditional
else
YFLAGS  = -d --debug --verbose --token-table
LFLAGS  = -L -i -d
CCFLAGS = -DDBG -g -Wall -Wbad-function-cast -Wtraditional -fstack-check
endif
else
YFLAGS  = -d
LFLAGS  = -L -i
CCFLAGS = -Wall -Wbad-function-cast -Wtraditional
endif

#### List of source files to be used ########################

SRC_DIR = src

YACCSRC1  = $(SRC_DIR)/xml_hist.y
CYACC1    = $(SRC_DIR)/xml_hist-yacc.c
LEXSRC1   = $(SRC_DIR)/xml_hist.lex
CLEX1     = $(SRC_DIR)/xml_hist-lex.c


CFILES = $(CYACC1) \
	 $(CLEX1) \
	 $(SRC_DIR)/util.c \
	 $(SRC_DIR)/common_yacc_lex.c \
	 $(SRC_DIR)/cmp_functions.c \
	 $(SRC_DIR)/compiler_support.c \
	 $(SRC_DIR)/qa_xml.c \
	 $(SRC_DIR)/cmp_out.c \
	 $(SRC_DIR)/simpa.hit.main.c

CHEADERS = $(SRC_DIR)/util.h \
	   $(SRC_DIR)/common_yacc_lex.h \
	   $(SRC_DIR)/cmp_functions.h \
	   $(SRC_DIR)/compiler_support.h \
	   $(SRC_DIR)/qa_xml.h \
	   $(SRC_DIR)/cmp_out.h

ALL_OBJS = $(patsubst %.c,%.o,$(notdir $(CFILES)))

PGM := xml_hist$(EXTENSION)

all:    $(PGM)

$(PGM): lex ${ALL_OBJS}
	${CC} $(CCFLAGS) $(CFLAGS) -I . -I $(SRC_DIR) -o $@ $(ALL_OBJS)
	chmod ug+rwx $(PGM)

clean :
	/bin/rm -f *.o $(PGM)\
	$(SRC_DIR)/*-yacc.* $(SRC_DIR)/*-lex.c

lex:	$(CYACC1)\
	$(CLEX1)

$(CYACC1) : $(YACCSRC1)
	    $(YACC) $(YFLAGS) -p yy1 $(YACCSRC1) -o $(CYACC1)

$(CLEX1) : $(LEXSRC1)
	   $(LEX) $(LFLAGS) -o$(CLEX1) -Pyy1 $(LEXSRC1)

%.o : $(SRC_DIR)/%.c $(CHEADERS)
	${CC} ${CCFLAGS} $(CFLAGS) -I . -I $(SRC_DIR) -o $@ -c $<


