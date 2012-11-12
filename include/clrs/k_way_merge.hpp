#ifndef CLRS_K_WAY_MERGE
#define CLRS_K_WAY_MERGE

#include <functional>
#include <utility>

#include "priority_queue.hpp"

namespace clrs {

  /* Solution to exercise 6.5-8. */
  template <typename T, typename Cmp = std::less<T>>
  void k_way_merge(const T* const * As, const size_t* ns, size_t k, T* O,
      Cmp cmp = Cmp())
  {
    /* head_t is a pair: a value (T) and the index (size_t) of the array from
     * which it was taken.  */
    typedef std::tuple<const T*, size_t> head_t;
    auto headcmp = [&] (const head_t& lhs, const head_t& rhs) {
      return cmp(*std::get<0>(lhs), *std::get<0>(rhs));
    };

    /* TODO: make_priority_queue */
    priority_queue<head_t, std::vector<head_t>, decltype(headcmp)> pq(headcmp);

    for (size_t i = 0; i < k; ++i) {
      pq.emplace(&As[i][0], i);
    }

    while (pq.size() > 1) {

    }
  }

}

#endif

