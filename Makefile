SRDDIR := lib
SOURCES := \

OBJDIR := build
OBJECTS := $(SOURCES:%.cpp=/$(OBJDIR)/$(SRCDIR)/%.o)

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


## dependencies

include $(shell find $(OBJDIR) -name '*.make' 2>/dev/null)

# $1 = target ($@)
# $2 = source ($<)
# $3 = extra flags
dep_c = \
	DEP=$1.make; \
	  $(CXX) $(CFLAGS) $3 -o $$DEP -MM $2; \
	  cat $$DEP | sed -e 's![^[:space:]]*[[:space:]]*:!$1 :!' \
	    -e 's!/usr[^[:space:]]*!!g' \
	    -e '/^[:space:]*\\$$/ d' \
	    > $$DEP.tmp && mv $$DEP.tmp $$DEP


## default target

.PHONY : all

all : test


## compiler

CXX := clang++

CFLAGS += -I./include
#CFLAGS += -O2 -DNDEBUG
CFLAGS += -O0 -g3
CFLAGS += -std=c++11
CFLAGS += -stdlib=libc++ -U__STRICT_ANSI__
LFLAGS += -stdlib=libc++ 


## library

$(OBJECTS) : $(OBJDIR)/$(SRCDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(call dep_c,$@,$<)
	$(CXX) $(CFLAGS) -o $@ -c $<


## tests

GTEST_SRCDIR := $(HOME)/work/googletest/source
GTEST_LIBDIR := $(HOME)/work/googletest/build

TESTOBJECTS := $(TESTS:%=$(OBJDIR)/$(TESTDIR)/%.o)
TESTCFLAGS := -I$(GTEST_SRCDIR)/include
TESTLFLAGS := -L$(GTEST_LIBDIR) -lgtest -lgtest_main

.PHONY : test

test : $(INSTALLDIR)/test
	$(INSTALLDIR)/test 2>/dev/null

$(INSTALLDIR)/test : $(TESTOBJECTS) $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(LFLAGS) $(TESTLFLAGS) -o $@ $^

$(TESTOBJECTS) : $(OBJDIR)/$(TESTDIR)/%.o : $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(call dep_c,$@,$<,$(TESTCFLAGS))
	$(CXX) $(CFLAGS) $(TESTCFLAGS) -o $@ -c $<


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

