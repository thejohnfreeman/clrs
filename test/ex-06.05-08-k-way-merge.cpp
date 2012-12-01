#include <algorithm>

#include <clrs/k_way_merge.hpp>

#include "ArrayTest.hpp"

TEST_F(ArrayTest, KWayMerge) {
  typedef int T;

  auto cmp = std::less<T>();
  size_t n = 10000;
  auto a(sample<T>(n)), b(sample<T>(n)), c(sample<T>(n)), d(sample<T>(n));

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  std::sort(c.begin(), c.end());
  std::sort(d.begin(), d.end());

  T* As[] = {
    a.data(),
    b.data(),
    c.data(),
    d.data()
  };

  size_t ns[] = { n, n, n, n };

  std::vector<T> o(4 * n, 0);

  clrs::k_way_merge(As, ns, /*k=*/4, o.data(), cmp);

  ASSERT_TRUE(std::is_sorted(o.begin(), o.end()));
}

