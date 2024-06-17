#include <gtest/gtest.h>

#include <clrs/priority_queue.hpp>

#include "check_container.hpp"
#include "props_heap.hpp"

#define CHECK_PROP(name, type) \
  check_container<type>(prop_heap_##name<clrs::priority_queue<type>>());

TEST(PriorityQueue, Empty) {
  CHECK_PROP(empty, int);
  CHECK_PROP(empty, std::string);
}

TEST(PriorityQueue, Size) {
  CHECK_PROP(size, int);
  CHECK_PROP(size, std::string);
}

TEST(PriorityQueue, Top) {
  CHECK_PROP(top, int);
  CHECK_PROP(top, std::string);
}

TEST(PriorityQueue, Pop) {
  CHECK_PROP(pop, int);
  CHECK_PROP(pop, std::string);
}

TEST(PriorityQueue, Sort) {
  CHECK_PROP(sort, int);
  CHECK_PROP(sort, std::string);
}

