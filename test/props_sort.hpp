#ifndef CLRS_PROPS_SORT
#define CLRS_PROPS_SORT

#define CLRS_DEFINE_PROP_SORT(name, sort2) \
  struct name {\
    template <typename Container>\
    bool operator() (Container& xs) {\
      Container ys(xs);\
      std::sort(xs.begin(), xs.end());\
      sort2(ys.begin(), ys.end());\
      return xs == ys;\
    }\
  };

#endif

