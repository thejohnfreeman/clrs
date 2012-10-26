.PHONY : all buildtests test gdb clean

all : buildtests

SOURCES :=

OBJECTS := $(SOURCES:%.cpp=/build/lib/%.o)

TESTS := \
	02.01-insertion-sort \
	02.02-merge-sort

TESTS := $(TESTS:%=build/test/%)

buildtests : $(TESTS)

CXX := clang++ -std=c++11 -stdlib=libc++ -U__STRICT_ANSI__ -g

GDB := gdb -q

$(TESTS) : build/test/% : build/test/%.o $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^

build/test/%.o : test/%.cpp test/common.hpp include/clrs/%.hpp
	@mkdir -p $(dir $@)
	$(CXX) -I ./include -o $@ -c $<

build/lib/%.o : lib/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -I ./include -o $@ -c $<

test :
	@for test in `find ./build/test -perm +111 -type f`; do \
		echo $$test; $$test; done

gdb :
	@for test in `find ./build/test -perm +111 -type f`; do \
		echo $$test; \
		$$test; \
		if [[ $$? -ne 0 ]]; then $(GDB) $$test; fi \
		done

clean :
	rm -rf build

