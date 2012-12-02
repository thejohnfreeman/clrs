#include <functional>
#include <algorithm>

#include <clrs/quick_sort.hpp>

#include "ArrayTest.hpp"

TEST_F(ArrayTest, Partition) {
  typedef int T;
  size_t n = 10000;
  std::less<T> comp;

  auto A(sample<T>(n));
  auto i = clrs::partition(A.begin(), A.end(), comp);
  const T& pivot = *i;
  ASSERT_TRUE(std::is_partitioned(A.begin(), A.end(),
        [&] (const T& x) { return comp(x, pivot); }));
}

