#ifndef CLRS_06_01_HEAP_SORT
#define CLRS_06_01_HEAP_SORT

#include <functional>
#include <utility>

#include "heap.hpp"

namespace clrs {

  template <typename T, typename Cmp = std::less<T>>
  void heap_sort(T* A, size_t n, Cmp cmp = Cmp()) {
    if (n < 2) return;
    make_heap(A, n, cmp);
    for (size_t i = n - 1; i > 0; --i) {
      pop_heap(A, n--, cmp);
    }
  }

}

#endif

