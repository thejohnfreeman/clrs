#ifndef CLRS_06_01_HEAP_SORT
#define CLRS_06_01_HEAP_SORT

#include <functional>
#include <utility>
#include <cstdio>

namespace clrs {

  namespace heap_sort_detail {

    inline size_t parent(size_t i) { return (i - 1) >> 1; }
    inline size_t left  (size_t i) { return (i << 1) | 1; }
    inline size_t right (size_t i) { return (i + 1) << 1; }

  }

  /* Renamed from max_heapify. */
  template <typename T, typename Cmp = std::less<T>>
  void heap_settle(T* A, const size_t n, const size_t i, Cmp cmp = Cmp()) {
    namespace d = heap_sort_detail;
    size_t l = d::left(i), r = d::right(i), largest = i;
    //printf("heap_settle(A, %lu, %lu)\n", n, i);
    if (l < n && cmp(A[i], A[l])) {
      //printf("left child (A[%lu] = %d) was greater than %d\n",
          //l, A[l], A[i]);
      largest = l;
    }
    if (r < n && cmp(A[largest], A[r])) {
      //printf("right child (A[%lu] = %d) was greater than %d\n",
          //r, A[r], A[largest]);
      largest = r;
    }
    if (largest != i) {
      std::swap(A[i], A[largest]);
      heap_settle(A, n, largest, cmp);
    }
  }

  template <typename T, typename Cmp = std::less<T>>
  void make_heap(T* A, const size_t n, Cmp cmp = Cmp()) {
    for (size_t i = n >> 1; true; --i) {
      heap_settle(A, n, i, cmp);
      if (i == 0) break;
    }
  }

  template <typename T, typename Cmp = std::less<T>>
  void heap_sort(T* A, size_t n, Cmp cmp = Cmp()) {
    if (n < 2) return;
    make_heap(A, n, cmp);
    for (size_t i = n - 1; i > 0; --i) {
      std::swap(A[0], A[i]);
      --n;
      heap_settle(A, n, 0, cmp);
    }
  }

}

#endif

