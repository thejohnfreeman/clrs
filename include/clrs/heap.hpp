#ifndef CLRS_06_XX_HEAP
#define CLRS_06_XX_HEAP

#include <functional>
#include <utility>
#include <cassert>
//#include <cstdio>

#define VAL_T typename std::iterator_traits<RandomIt>::value_type

namespace clrs {

  /* Helpers. */

  namespace heap_sort_detail {

    inline size_t parent(size_t i) { return (i - 1) >> 1; }
    inline size_t left  (size_t i) { return (i << 1) | 1; }
    inline size_t right (size_t i) { return (i + 1) << 1; }

  }

  /* Renamed from max_heapify. */
  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void heap_settle(RandomIt A, const size_t n, const size_t i,
      Compare comp = Compare())
  {
    namespace d = heap_sort_detail;
    size_t l = d::left(i), r = d::right(i), largest = i;
    //printf("heap_settle(A, %lu, %lu)\n", n, i);
    if (l < n && comp(A[i], A[l])) {
      //printf("left child (A[%lu] = %d) was greater than %d\n",
          //l, A[l], A[i]);
      largest = l;
    }
    if (r < n && comp(A[largest], A[r])) {
      //printf("right child (A[%lu] = %d) was greater than %d\n",
          //r, A[r], A[largest]);
      largest = r;
    }
    if (largest != i) {
      std::iter_swap(A + i, A + largest);
      heap_settle(A, n, largest, comp);
    }
  }

  /* Constructor. */

  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void make_heap(RandomIt A, const size_t n, Compare comp = Compare()) {
    if (n < 2) return;
    for (size_t i = n >> 1; true; --i) {
      heap_settle(A, n, i, comp);
      if (i == 0) break;
    }
  }

  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void make_heap(RandomIt begin, RandomIt end, Compare comp = Compare()) {
    return make_heap(begin, end - begin, comp);
  }

  /* Mutators. */

  /* Inserts the element at the position `end - 1` into the heap defined by
   * the range `[begin, end - 1)`. */
  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void push_heap(RandomIt begin, RandomIt end, Compare comp = Compare()) {
    namespace d = heap_sort_detail;
    size_t i = (end - begin) - 1;
    size_t p = d::parent(i);
    while (i > 0 && comp(begin[p], begin[i])) {
      std::iter_swap(begin + p, begin + i);
      i = p;
      p = d::parent(i);
    }
  }

  /* Swaps the elements at position `i` and `end - 1` and restores the heap
   * over the range `[begin, end - 1)`. */
  /* Solution to exercise 6.5-7. */
  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void heap_delete(RandomIt begin, RandomIt end, size_t i,
      Compare comp = Compare())
  {
    std::iter_swap(begin + i, --end);
    heap_settle(begin, end - begin, i, comp);
  }

  /* Swaps the value in the position first and the value in the position
   * `end - 1` and makes the subrange `[begin, end - 1)` into a heap. This
   * has the effect of removing the first (largest) element from the heap
   * defined by the range `[begin, end)`. */
  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void pop_heap(RandomIt begin, RandomIt end, Compare comp = Compare()) {
    heap_delete(begin, end, 0, comp);
  }

  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void heap_promote(RandomIt A, size_t n, size_t i, const VAL_T& key,
      Compare comp = Compare())
  {
    assert(comp(A[i], key));
    A[i] = key;
    /* Not sure why this is ambiguous with std::push_heap. */
    clrs::push_heap(A, A + i + 1, comp);
  }

  template <typename RandomIt, typename Compare = std::less<VAL_T>>
  void heap_demote(RandomIt A, size_t n, size_t i, const VAL_T& key,
      Compare comp = Compare())
  {
    assert(comp(key, A[i]));
    A[i] = key;
    heap_settle(A, n, i, comp);
  }

}

#undef VAL_T

#endif

