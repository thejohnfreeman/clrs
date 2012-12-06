#include <functional>

#include <clrs/priority_queue.hpp>

#include "ArrayTest.hpp"

template <typename T, typename Cmp>
void assert_is_ordered(clrs::priority_queue<T>& pq, const Cmp& cmp) {
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

TEST_F(ArrayTest, PriorityQueueTopPop) {
  typedef int T;
  size_t n = 10000;
  std::less<T> cmp;

  auto A(sample<T>(n));
  clrs::priority_queue<T> pq(cmp, std::move(A));
  assert_is_ordered(pq, cmp);
}

TEST_F(ArrayTest, PriorityQueuePush) {
  typedef int T;
  size_t n = 10000;
  std::less<T> cmp;

  auto A(sample<T>(n));
  clrs::priority_queue<T> pq(cmp);
  for (auto item : A) {
    pq.push(item);
  }

  assert_is_ordered(pq, cmp);
}

