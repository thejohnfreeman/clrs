include $(shell find build -name '*.make')

.PHONY : all test clean

all : $(OBJECTS)

CXX := clang++

CFLAGS += -I./include -g
CFLAGS += -std=c++11
CFLAGS += -stdlib=libc++ -U__STRICT_ANSI__
LFLAGS += -stdlib=libc++ 

SOURCES :=

OBJECTS := $(SOURCES:%.cpp=/build/lib/%.o)

build/lib/%.o : lib/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -o $@.make -MM $<
	$(CXX) $(CFLAGS) -o $@ -c $<

TESTS := \
	02.01-insertion-sort \
	02.02-merge-sort

TESTOBJECTS := $(TESTS:%=build/test/%.o)

GTEST_SRCDIR := $(HOME)/work/googletest/source
GTEST_LIBDIR := $(HOME)/work/googletest/build

TESTCFLAGS := -I$(GTEST_SRCDIR)/include
TESTLFLAGS := -L$(GTEST_LIBDIR) -lgtest -lgtest_main

bin/test : $(TESTOBJECTS) $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(LFLAGS) $(TESTLFLAGS) -o $@ $^

build/test/%.o : test/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(TESTCFLAGS) -o $@.make -MM $<
	$(CXX) $(CFLAGS) $(TESTCFLAGS) -o $@ -c $<

test : bin/test
	./bin/test

clean :
	rm -rf build
	rm -rf bin

