#ifndef CLRS_K_WAY_MERGE
#define CLRS_K_WAY_MERGE

#include <functional>
#include <utility>

#include "priority_queue.hpp"

namespace clrs {

  /* Solution to exercise 6.5-8. */
  template <
    typename ForwardItIt,
    typename OutputIt,
    typename Compare
      = std::less<typename std::iterator_traits<
        typename std::iterator_traits<ForwardItIt>>::value_type>>
  void k_way_merge(ForwardItIt begins, ForwardItIt ends, const size_t k,
      OutputIt out, Compare comp = Compare())
  {
    typedef typename std::iterator_traits<ForwardItIt>::value_type ForwardIt;

    /* head_t is a pair of iterators:
     * - the first points to the current item in the list
     * - the second points to the end of the list
     */
    typedef std::tuple<ForwardIt, ForwardIt> head_t;
    auto headcomp = [&] (const head_t& lhs, const head_t& rhs) {
      return comp(*std::get<0>(rhs), *std::get<0>(lhs));
    };

    /* TODO: make_priority_queue */
    priority_queue<head_t, std::vector<head_t>, decltype(headcomp)> pq(headcomp);

    for (size_t i = 0; i < k; ++i) {
      // Not sure why this would happen, but allow it.
      if (begins[i] == ends[i]) continue;
      pq.emplace(std::move(begins[i]), std::move(ends[i]));
    }

    //std::printf("merging %lu lists\n", k);

    ForwardIt head, end;
    while (!pq.empty()) {
      std::tie(head, end) = pq.top();
      pq.pop();
      *out++ = *head++;

      //auto i = std::find(ends, ends + k, end) - ends;
      //std::printf("popped list %lu\n", i);

      if (head != end) {
        pq.emplace(head, end);
      }
    }
  }

}

#endif

