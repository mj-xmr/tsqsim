LIB_SRC_DIR = ../src/cpp
EXAMPLES_SRC_DIR = ../examples
BIN_DIR = ../bin

.PHONY: all clean clean-objs static dynamic example-console example-wxCarriage

all: static dynamic example-console example-wxCarriage

dynamic: 
	cd $(LIB_SRC_DIR) && make dynamic

static:
	cd $(LIB_SRC_DIR) && make static

example-console: static
	cd $(EXAMPLES_SRC_DIR)/console && make
  
example-wxCarriage: static
	cd $(EXAMPLES_SRC_DIR)/wxCarriage && make

clean: clean-objs
	cd $(BIN_DIR) && rm *

clean-objs:
	cd $(LIB_SRC_DIR) && make clean-objs
	cd $(EXAMPLES_SRC_DIR)/console && make clean-objs
	cd $(EXAMPLES_SRC_DIR)/wxCarriage && make clean-objs

