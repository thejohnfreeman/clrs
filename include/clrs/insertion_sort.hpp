#ifndef CLRS_02_01_INSERTION_SORT
#define CLRS_02_01_INSERTION_SORT

#include <cstddef>
#include <utility>
#include <functional>

namespace clrs {

  template <
    typename BidirIt,
    typename Compare
      = std::less<typename std::iterator_traits<BidirIt>::value_type>>
  void insertion_sort(BidirIt begin, BidirIt end, Compare comp = Compare())
  {
    if (begin == end) return;
    BidirIt j = begin;
    for (++j; j != end; ++j) {
      typename std::iterator_traits<BidirIt>::value_type key(std::move(*j));
      // Insert `*j` into the sorted sequence `[begin, j)`.
      BidirIt i = j, iplus1 = j;
      for (--i; comp(key, *i); --iplus1) {
        *(iplus1) = std::move(*i);
        if (i-- == begin) break;
      }
      *++i = std::move(key);
    }
  }

}

#endif

