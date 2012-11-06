#include <functional>
#include <algorithm>

#include <clrs/quick_sort.hpp>

#include "ArrayTest.hpp"

TEST_F(ArrayTest, Partition) {
  typedef int T;
  size_t n = 10000;
  std::less<T> cmp;

  auto A(sample<T>(n));
  size_t i = clrs::partition(A.data(), 0, n, cmp);
  const T& pivot = A[i];
  ASSERT_TRUE(std::is_partitioned(A.begin(), A.end(),
        [&] (const T& x) { return cmp(x, pivot); }));
}

