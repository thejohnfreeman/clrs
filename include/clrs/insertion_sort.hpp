#ifndef CLRS_02_01_INSERTION_SORT
#define CLRS_02_01_INSERTION_SORT

#include <cstddef>
#include <utility>
#include <functional>

namespace clrs {

  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  void insertion_sort(RandomIt begin, RandomIt end, Compare comp = Compare())
  {
    for (RandomIt j = begin; j != end; ++j) {
      typename std::iterator_traits<RandomIt>::value_type key(*j);
      // Insert `*j` into the sorted sequence `[begin, j)`.
      for (RandomIt i = j - 1; comp(key, *i); --i) {
        *(i + 1) = std::move(*i);
        if (i == begin) break;
      }
    }
  }

}

#endif

