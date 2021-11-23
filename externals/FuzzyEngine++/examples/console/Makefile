OPERATING_SYS = $(shell uname -o)
OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
BIN_DIR = ../../bin
INCLUDES = -I../../src/include
CXXFLAGS = -Wall -O3 -c -Os $(INCLUDES)
LDFLAGS = -s $(BIN_DIR)/libFuzzyEngine++.a

ifeq ($(OPERATING_SYS),Msys)
	EXTENSION = .exe
else 
	ifeq ($(OPERATING_SYS),Cygwin)
		EXTENSION = .exe
	else
		EXTENSION = 
	endif
endif

EXECUTABLE = $(BIN_DIR)/example-console$(EXTENSION)


.PHONY: all clean clean-objs example-console

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJFILES)
	$(CXX) -o $@ $(OBJFILES) $(LDFLAGS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean: clean-objs
	rm $(EXECUTABLE)

clean-objs:
	rm *.o

