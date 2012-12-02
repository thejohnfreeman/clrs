#include <algorithm>

#include <clrs/k_way_merge.hpp>

#include "ArrayTest.hpp"

TEST_F(ArrayTest, KWayMerge) {
  typedef int T;

  auto comp = std::less<T>();
  size_t n  = 10000;
  auto a(sample<T>(n)), b(sample<T>(n)), c(sample<T>(n)), d(sample<T>(n));

  /* TODO: sorted_sample<T> */
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  std::sort(c.begin(), c.end());
  std::sort(d.begin(), d.end());

  auto begins = {
    a.begin(),
    b.begin(),
    c.begin(),
    d.begin()
  };

  auto ends = {
    a.end(),
    b.end(),
    c.end(),
    d.end()
  };

  std::vector<T> out;
  out.reserve(4 * n);

  clrs::k_way_merge(begins.begin(), ends.begin(), /*k=*/4,
      std::back_inserter(out), comp);

  ASSERT_EQ(4 * n, out.size());
  ASSERT_TRUE(std::is_sorted(out.begin(), out.end()))
    << take(10, out);
}

