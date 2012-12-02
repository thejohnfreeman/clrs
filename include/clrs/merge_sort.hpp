#ifndef CLRS_02_03_MERGE_SORT
#define CLRS_02_03_MERGE_SORT

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
    //printf("merge: %lu < %lu < %lu\n", p, q, r);
    std::vector<typename std::iterator_traits<RandomIt>::value_type> L(p, q);
    RandomIt i {L.begin()};
    RandomIt ii {L.end()};

    // No need to copy right side.
    RandomIt j {q};
    RandomIt jj {r};

    RandomIt k {p};
    for (; k != r && i != ii && j != jj; ++k) {
      //printf("L[i] = %d <=? R[j] = %d\n", L[i], R[j]);
      /* Must compare this way to keep a stable sort. */
      if (comp(*j, *i)) {
        //printf("A[%lu] = R[%lu] = %d\n", k, j, R[j]);
        *k = std::move(*j++);
      } else {
        //printf("A[%lu] = L[%lu] = %d\n", k, i, L[i]);
        *k = std::move(*i++);
      }
    }

    if (i != ii) {
      std::move(i, ii, k);
    } else if (j != jj) {
      std::move(j, jj, k);
    }
  }

  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  void merge_sort(RandomIt begin, RandomIt end, Compare comp) {
    if ((end - begin) < 2) return;
    RandomIt mid = begin + ((end - begin) >> 1);
    merge_sort(begin, mid, comp);
    merge_sort(mid, end, comp);
    merge(begin, mid, end, comp);
  }

}

#endif

