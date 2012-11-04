#ifndef CLRS_02_03_MERGE_SORT
#define CLRS_02_03_MERGE_SORT

#include <vector>
#include <cassert>
#include <algorithm>

namespace clrs {

  /**
   * For arrays of size n, CLRS likes to index from 1 to n. C++ likes to
   * zero-index half-open ranges instead.
   * p, q, r are indices into A such that, unlike CLRS, p < q < r. The two
   * sub-ranges are [p, q) and [q, r).
   */
  template <typename T>
  void merge(T* A, size_t p, size_t q, size_t r) {
    //printf("merge: %lu < %lu < %lu\n", p, q, r);
    size_t nl = q - p;
    std::vector<T> L(A + p, A + q);
    assert(L.size() == nl);

    size_t nr = r - q;
    std::vector<T> R(A + q, A + r);
    assert(R.size() == nr);

    size_t i = 0, j = 0, k = p;
    for (; k < r && i < nl && j < nr; ++k) {
      //printf("L[i] = %d <=? R[j] = %d\n", L[i], R[j]);
      if (L[i] <= R[j]) {
        //printf("A[%lu] = L[%lu] = %d\n", k, i, L[i]);
        A[k] = L[i++];
      } else {
        //printf("A[%lu] = R[%lu] = %d\n", k, j, R[j]);
        A[k] = R[j++];
      }
    }

    if (i < nl) {
      std::copy(L.begin() + i, L.begin() + nl, A + k);
    } else if (j < nr) {
      std::copy(R.begin() + j, R.begin() + nr, A + k);
    }
  }

  template <typename T>
  void merge_sort_(T* A, size_t p, size_t r) {
    if (r - p < 2) return;
    size_t q = (p + r) >> 1;
    merge_sort_(A, p, q);
    merge_sort_(A, q, r);
    merge(A, p, q, r);
  }

  template <typename T>
  void merge_sort(T* A, size_t n) {
    merge_sort_(A, 0, n);
  }

}

#endif

