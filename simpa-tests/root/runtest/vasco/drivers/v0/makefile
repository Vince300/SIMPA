
PROTO := BASIC_OP
######################################################################
### MANDATORY FLAGS SPECIAL FOR THIS APPLICATION (-mb, -mem ...)

MANDATORY_GCC =
MANDATORY_PPC =
MANDATORY_SCC =

# MULTIPLE_SOURCE_FILES=1

######################################################################
### DIRECTORIES

SRC_DIR     := $(SIMPA)/hit/src
INC_DIR     := 

OBJ_DIR     := 
DASM_DIR    := 
BIN_DIR     := bin

######################################################################
### SOURCES


SIMPA_SRC := $(wildcard $(SRC_DIR)/*/*.java $(SRC_DIR)/*/*/*.java $(SRC_DIR)/*/*/*/*.java $(SRC_DIR)/*/*/*/*/*.java $(SRC_DIR)/*/*/*/*/*/*.java)

# SIMPA_SRC   := $(foreach SDIR, automata crawler datamining detection drivers learner main stats tools ,$(wildcard $(SRC_DIR)/$(SDIR)/*.java $(SRC_DIR)/$(SDIR)/*/*.java $(SRC_DIR)/$(SDIR)/*/*/*.java $(SRC_DIR)/$(SDIR)/*/*/*/*.java $(SRC_DIR)/$(SDIR)/*/*/*/*/*.java ))
# TARGETS_SRC := $(wildcard $(SRC_DIR)/drivers/*/*.java)


######################################################################
### NON GENERIC RULES

all : main.simpa.SIMPA transparent.CounterMealyDriver transparent.CombinedMealyDriver transparent.RandomAndCounterMealyDriver

transparent.CounterMealyDriver : main.simpa.SIMPA

transparent.CombinedMealyDriver : main.simpa.SIMPA
                                       
transparent.RandomAndCounterMealyDriver : main.simpa.SIMPA

main.simpa.SIMPA : $(SIMPA_SRC)
	javac -g -d bin $(SIMPA_SRC)



main/simpa/SIMPA : $(BIN_DIR)/main/simpa/SIMPA.class

$(BIN_DIR)/main/simpa/SIMPA.class :
	javac -g -d bin $(SIMPA_SRC)


	
# */*.java */*/*.java */*/*/*.java */*/*/*/*.java */*/*/*/*/*.java


######################################################################
### GENERIC MAKEFILE INCLUSION

SYS_OS := $(shell uname -s)

ifeq (,$(findstring CYGWIN,$(SYS_OS)))
	WHERE_THE_GENERIC_MAKEFILE_IS = $(QA_TOOLS)/generic_test/unit_tests
else
	WHERE_THE_GENERIC_MAKEFILE_IS := $(shell cygpath -d -m "$(QA_TOOLS)/generic_test/unit_tests")
endif

include  $(WHERE_THE_GENERIC_MAKEFILE_IS)/makefile_generic.mk

