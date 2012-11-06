#ifndef CLRS_07_01_QUICK_SORT
#define CLRS_07_01_QUICK_SORT

#include <functional>
#include <utility>

namespace clrs {

  template <typename T, typename Cmp = std::less<T>>
  size_t partition(T* A, const size_t p, const size_t r, Cmp cmp = Cmp()) {
    const T& pivot = A[p];
    size_t i = p;
    for (size_t j = p + 1; j < r; ++j) {
      if (cmp(A[j], pivot)) {
        ++i;
        std::swap(A[i], A[j]);
      }
    }
    std::swap(A[p], A[i]);
    return i;
  }

  template <typename T, typename Cmp = std::less<T>>
  void quick_sort_range(T* A, const size_t p, const size_t r,
      Cmp cmp = Cmp())
  {
    if (!(p < r)) return;

    size_t q = partition(A, p, r, cmp);
    quick_sort_range(A, p, q, cmp);
    quick_sort_range(A, q + 1, r, cmp);
  }

  template <typename T, typename Cmp = std::less<T>>
  void quick_sort(T* A, const size_t n, Cmp cmp = Cmp()) {
    return quick_sort_range(A, 0, n, cmp);
  }

}

#endif

