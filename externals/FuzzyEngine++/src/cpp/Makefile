CXX = g++
CXXFLAGS = -fPIC -Wall -c -O3 -Os
LDFLAGS = -s
BIN_DIR = ../../bin

OBJS = \
EvaluationException.o FuzzyRule.o ForDefuzzification.o HedgeNot.o MembershipFunction.o \
FuzzyBlockOfRules.o HedgeSomewhat.o NoRulesFiredException.o FuzzyEngine.o HedgeVery.o \
RulesParsingException.o FuzzyExpression.o LinguisticVariable.o

ifeq ($(OPERATING_SYS),Msys)
	DYN_LIBRARY_EXTENSION = .la
else 
	ifeq ($(OPERATING_SYS),Cygwin)
		DYN_LIBRARY_EXTENSION = .la
	else
		DYN_LIBRARY_EXTENSION = .so
	endif
endif


.PHONY: all clean clean-objs static dynamic

all: dynamic examples-console examples-wx

dynamic: $(OBJS)
	$(CXX) -shared -o $(BIN_DIR)/libFuzzyEngine++$(DYN_LIBRARY_EXTENSION) $(OBJS)

static: $(OBJS)
	ar -cvq $(BIN_DIR)/libFuzzyEngine++.a $(OBJS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean: clean-objs

clean-objs:
	rm *.o
