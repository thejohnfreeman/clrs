#include <functional>

#include <clrs/priority_queue.hpp>

#include "ArrayTest.hpp"

TEST_F(ArrayTest, PriorityQueueTopPop) {
  typedef int T;
  size_t n = 10000;
  std::less<T> cmp;

  auto A(sample<T>(n));
  clrs::priority_queue<T> pq(cmp, std::move(A));

  auto last = pq.top();
  pq.pop();
  while (!pq.empty()) {
    auto next = pq.top();
    pq.pop();
    ASSERT_TRUE(cmp(next, last)) <<
      "cmp(" << next << ", " << last << ")";
    last = next;
  }
}

