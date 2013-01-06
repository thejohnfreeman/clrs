#ifndef CLRS_02_03_MERGE_SORT
#define CLRS_02_03_MERGE_SORT

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>
#include <utility>

namespace clrs {

  /**
   * For arrays of size n, CLRS likes to index from 1 to n. C++ likes to
   * zero-index half-open ranges instead.
   * p, q, r are indices into A such that, unlike CLRS, p < q < r. The two
   * sub-ranges are [p, q) and [q, r).
   */
  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  void merge(RandomIt p, RandomIt q, RandomIt r, Compare comp) {
    //printf("merge: |[p, q)| = %lu, |[q, r)| = %lu\n", q - p, r - q);
    std::vector<typename std::iterator_traits<RandomIt>::value_type> L;
    L.reserve(q - p);
    L.assign(std::make_move_iterator(p), std::make_move_iterator(q));
    auto i = L.begin();
    auto ii = L.end();

    // No need to copy right side.
    auto j = q;
    auto jj = r;

    auto k = p;
    for (; k != r && i != ii && j != jj; ++k) {
      //std::cout << "R[j] = " << *j << " <? L[i] = " << *i << std::endl;
      /* Must compare this way to keep a stable sort. */
      if (comp(*j, *i)) {
        *k = std::move(*j++);
        //std::cout << "yes, A[k] = R[j] = " << *k << std::endl;
      } else {
        *k = std::move(*i++);
        //std::cout << "no, A[k] = L[i] = " << *k << std::endl;
      }
    }

    if (i != ii) {
      std::move(i, ii, k);
    }
  }

  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  void merge_sort(RandomIt begin, RandomIt end, Compare comp = Compare()) {
    if ((end - begin) < 2) return;
    RandomIt mid = begin + ((end - begin) >> 1);
    merge_sort(begin, mid, comp);
    merge_sort(mid, end, comp);
    merge(begin, mid, end, comp);
  }

}

#endif

