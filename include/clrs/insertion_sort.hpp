#ifndef CLRS_02_01_INSERTION_SORT
#define CLRS_02_01_INSERTION_SORT

#include <cstring> // for size_t

namespace clrs {

  template <typename T>
  void insertion_sort(T* A, size_t n) {
    for (size_t j = 1; j < n; ++j) {
      T& key = A[j];
      // Insert `A[j]` into the sorted sequence `A[1..j-1]`.
      size_t i = j - 1;
      while (A[i] > key) {
        A[i + 1] = A[i];
        if (--i == 0) break;
      }
    }
  }

}

#endif

