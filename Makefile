.PHONY : all buildtests test

all : buildtests

SOURCES :=

OBJECTS := $(SOURCES:%.cpp=/build/lib/%.o)

TESTS := \
	02.01-insertion-sort

TESTS := $(TESTS:%=build/test/%)

buildtests : $(TESTS)

CXX := clang++ -std=c++11 -stdlib=libc++ -U__STRICT_ANSI__

$(TESTS) : build/test/% : build/test/%.o $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^

build/test/%.o : test/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -I ./include -o $@ -c $^

$(OBJECTS) : build/lib/%.o : lib/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -I ./include -o $@ -c $^

test :
	@for test in `find ./build/test -perm +111 -type f`; do \
		echo $$test; $$test; done

