#ifndef CLRS_INTRO_SORT
#define CLRS_INTRO_SORT

#include <functional>
#include <cassert>
#include <cmath>

#include "quick_sort.hpp"
#include "heap_sort.hpp"

namespace clrs {

  template <typename T, typename Cmp = std::less<T>>
  void intro_sort_range(T* A, const size_t threshold,
      const size_t p, const size_t r,
      Cmp cmp = Cmp())
  {
    assert(0 <= p);
    assert(p < r);

    if ((r - p) < threshold) {
      heap_sort(A + p, r - p, cmp);
    } else {
      size_t q = partition(A, p, r, cmp);
      intro_sort_range(A, threshold, p, q, cmp);
      intro_sort_range(A, threshold, q + 1, r, cmp);
    }
  }

  template <typename T, typename Cmp = std::less<T>>
  void intro_sort(T* A, const size_t n, Cmp cmp = Cmp()) {
    size_t threshold = std::log(n) + 1;
    return intro_sort_range(A, threshold, 0, n, cmp);
  }

}

#endif

