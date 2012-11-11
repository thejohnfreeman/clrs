#include <functional>
#include <algorithm>

#include <clrs/heap.hpp>

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

  size_t i = n >> 1;
  clrs::heap_promote(A.data(), n, i, A[i] + 1, cmp);
  ASSERT_TRUE(std::is_heap(A.begin(), A.end(), cmp)) <<
    "heap_promote";

  clrs::heap_demote(A.data(), n, i, A[i] - 1, cmp);
  ASSERT_TRUE(std::is_heap(A.begin(), A.end(), cmp)) <<
    "heap_demote";
}

