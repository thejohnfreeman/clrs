#ifndef CLRS_06_XX_HEAP
#define CLRS_06_XX_HEAP

#include <functional>
#include <utility>
#include <cassert>
//#include <cstdio>

namespace clrs {

  /* Helpers. */

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

  /* Constructor. */

  template <typename T, typename Cmp = std::less<T>>
  void make_heap(T* A, const size_t n, Cmp cmp = Cmp()) {
    for (size_t i = n >> 1; true; --i) {
      heap_settle(A, n, i, cmp);
      if (i == 0) break;
    }
  }

  /* Mutators. */

  template <typename T, typename Cmp = std::less<T>>
  void push_heap(T* A, size_t n, Cmp cmp = Cmp()) {
    namespace d = heap_sort_detail;
    size_t i = n - 1;
    size_t p = d::parent(i);
    while (i > 0 && cmp(A[p], A[i])) {
      std::swap(A[p], A[i]);
      i = p;
      p = d::parent(i);
    }
  }

  /* Solution to exercise 6.5-7. */
  template <typename T, typename Cmp = std::less<T>>
  void heap_delete(T* A, size_t n, size_t i, Cmp cmp = Cmp()) {
    std::swap(A[i], A[n - 1]);
    heap_settle(A, n - 1, i, cmp);
  }

  template <typename T, typename Cmp = std::less<T>>
  void pop_heap(T* A, size_t n, Cmp cmp = Cmp()) {
    heap_delete(A, n, 0, cmp);
  }

  template <typename T, typename Cmp = std::less<T>>
  void heap_promote(T* A, size_t n, size_t i, const T& key, Cmp cmp = Cmp())
  {
    assert(cmp(A[i], key));
    A[i] = key;
    push_heap(A, i + 1, cmp);
  }

  template <typename T, typename Cmp = std::less<T>>
  void heap_demote(T* A, size_t n, size_t i, const T& key, Cmp cmp = Cmp()) {
    assert(cmp(key, A[i]));
    A[i] = key;
    heap_settle(A, n, i, cmp);
  }

}

#endif

