#ifndef CLRS_07_01_QUICK_SORT
#define CLRS_07_01_QUICK_SORT

#include <functional>
#include <utility>

namespace clrs {

  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  RandomIt partition(RandomIt begin, RandomIt end, Compare comp = Compare())
  {
    const typename std::iterator_traits<RandomIt>::value_type& pivot
      = *begin;
    RandomIt i = begin;
    for (RandomIt j = begin + 1; j != end; ++j) {
      if (comp(*j, pivot)) {
        std::iter_swap(++i, j);
      }
    }
    std::iter_swap(begin, i);
    return i;
  }

  template <
    typename RandomIt,
    typename Compare
      = std::less<typename std::iterator_traits<RandomIt>::value_type>>
  void quick_sort(RandomIt begin, RandomIt end,
      Compare comp = Compare())
  {
    if (begin == end) return;

    RandomIt mid = clrs::partition(begin, end, comp);
    quick_sort(begin, mid, comp);
    quick_sort(mid + 1, end, comp);
  }

}

#endif

