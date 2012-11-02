.PHONY : all test clean

all : $(OBJECTS)

SOURCES :=

OBJECTS := $(SOURCES:%.cpp=/build/lib/%.o)

build/lib/%.o : lib/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -I ./include -o $@ -c $<

TESTS := \
	02.01-insertion-sort \
	02.02-merge-sort

TESTOBJECTS := $(TESTS:%=build/test/%.o)

GTEST_SRCDIR := $(HOME)/work/googletest/source
GTEST_LIBDIR := $(HOME)/work/googletest/build

TESTCFLAGS := -I./include -I$(GTEST_SRCDIR)/include
TESTLFLAGS := -L$(GTEST_LIBDIR) -lgtest -lgtest_main

CXX := clang++

CFLAGS := -std=c++11 -stdlib=libc++ -U__STRICT_ANSI__ -g
LFLAGS := -stdlib=libc++ 
#CFLAGS := -std=c++11 -g
#LFLAGS :=

bin/test : $(TESTOBJECTS) $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(LFLAGS) $(TESTLFLAGS) -o $@ $^

build/test/%.o : test/%.cpp include/clrs/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(TESTCFLAGS) -o $@ -c $<

test : bin/test
	./bin/test

clean :
	rm -rf build
	rm -rf bin

