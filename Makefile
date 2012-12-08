SRCDIR := lib
SOURCES := \

OBJDIR := build
OBJECTS := $(SOURCES:%.c=$(OBJDIR)/$(SRCDIR)/%.o)

TESTDIR := test
TESTS := \
	02.01-insertion-sort \
	02.02-merge-sort \
	06.03-make-heap \
	06.04-heap-sort \
	06.05-priority-queue \
	07.01-partition \
	07.01-quick-sort \
	19.02-binomial-heap \
	ex-06.05-08-k-way-merge \
	intro-sort

INSTALLDIR := bin
INSTALLDIR := $(abspath $(INSTALLDIR))


## default target

.PHONY : all

all : test


## dependencies

include $(shell find $(OBJDIR) -name '*.make' 2>/dev/null)

# $1 = target ($@)
# $2 = source ($<)
# $3 = extra flags
dep_cxx = \
	DEP=$1.make; \
	  $(CXX) $(CXXFLAGS) $3 -o $$DEP -MM $2; \
	  cat $$DEP | sed -e 's![^[:space:]]*[[:space:]]*:!$1 :!' \
	    -e 's!/usr[^[:space:]]*!!g' \
	    -e '/^[:space:]*\\$$/ d' \
	    > $$DEP.tmp && mv $$DEP.tmp $$DEP


## compiler

CXX := clang++

FLAGS += -I./include
#FLAGS += -O2 -DNDEBUG
FLAGS += -O0 -g3

CXXFLAGS += $(FLAGS)
CXXFLAGS += -std=c++11
CXXFLAGS += -stdlib=libc++ -U__STRICT_ANSI__

LXXFLAGS += -stdlib=libc++ 


## library

$(OBJECTS) : $(OBJDIR)/$(SRCDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(call dep_cxx,$@,$<)
	$(CXX) $(CXXFLAGS) -o $@ -c $<


## tests

GTEST_SRCDIR := $(HOME)/work/googletest/source
GTEST_LIBDIR := $(HOME)/work/googletest/build

TESTOBJECTS  := $(TESTS:%=$(OBJDIR)/$(TESTDIR)/%.o)
TESTCXXFLAGS := -I$(GTEST_SRCDIR)/include
TESTLXXFLAGS := -L$(GTEST_LIBDIR) -lgtest -lgtest_main

.PHONY : test verbose

verbose : $(INSTALLDIR)/test
	GTEST_OUTPUT=verbose $(INSTALLDIR)/test

test : $(INSTALLDIR)/test
	$(INSTALLDIR)/test 2>/dev/null

$(INSTALLDIR)/test : $(TESTOBJECTS) $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(LXXFLAGS) $(TESTLXXFLAGS) -o $@ $^

$(TESTOBJECTS) : $(OBJDIR)/$(TESTDIR)/%.o : $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(call dep_cxx,$@,$<,$(TESTCXXFLAGS))
	$(CXX) $(CXXFLAGS) $(TESTCXXFLAGS) -o $@ -c $<


## debug

.PHONY : gdb

GDB := ggdb -q

gdb : $(INSTALLDIR)/test
	$(GDB) $(INSTALLDIR)/test


## cleaning

.PHONY : clean

clean :
	rm -rf $(OBJDIR)
	rm -rf $(INSTALLDIR)

