#include <functional>
#include <algorithm>

#include <clrs/heap_sort.hpp>

#include "ArrayTest.hpp"

TEST_F(ArrayTest, MakeHeap) {
  typedef int T;
  size_t n = 10000;
  std::less<T> cmp;

  auto A(sample<T>(n));
  clrs::make_heap(A.data(), n, cmp);
  ASSERT_EQ(n, A.size());
  ASSERT_TRUE(std::is_heap(A.begin(), A.end(), cmp)) <<
    take(10, A);
}

