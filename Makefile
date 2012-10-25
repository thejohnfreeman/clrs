.PHONY : buildtests runtests

SOURCES :=

OBJECTS := $(SOURCES:%.cpp=/build/lib/%.o)

TESTS := \
	02.01-insertion-sort

TESTS := $(TESTS:%=build/test/%)

buildtests : $(TESTS)

CXX := clang++

$(TESTS) : build/test/% : build/test/%.o $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) -o $@ $^

build/test/%.o : test/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -I ./include -o $@ -c $^

$(OBJECTS) : build/lib/%.o : lib/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -I ./include -o $@ -c $^

runtests :
	@for test in `find ./build/test -perm +111 -type f`; do \
		echo $$test; $$test; done

