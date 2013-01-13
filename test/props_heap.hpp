#ifndef CLRS_PROPS_HEAP
#define CLRS_PROPS_HEAP

#define CLRS_DEFINE_PROP_HEAP(name) \
  template <typename Heap>\
  struct prop_heap_##name {\
    template <typename Container>\
    bool operator() (Container& xs);\
  };\
  template <typename Heap>\
  template <typename Container>\
  bool prop_heap_##name<Heap>::operator() (Container& xs)

CLRS_DEFINE_PROP_HEAP(empty) {
  Heap heap(xs.begin(), xs.end());
  return xs.empty() == heap.empty();
}

CLRS_DEFINE_PROP_HEAP(size) {
  Heap heap(xs.begin(), xs.end());
  return xs.size() == heap.size();
}

CLRS_DEFINE_PROP_HEAP(top) {
  Heap heap(xs.begin(), xs.end());
  return xs.empty() || *std::max_element(xs.begin(), xs.end()) == heap.top();
}

CLRS_DEFINE_PROP_HEAP(pop) {
  Heap heap(xs.begin(), xs.end());
  for (auto n = xs.size(); n--;) {
    heap.pop();
  }
  return heap.empty();
}

CLRS_DEFINE_PROP_HEAP(sort) {
  Heap heap(xs.begin(), xs.end());
  Container ys;
  ys.reserve(heap.size());
  while (!heap.empty()) {
    ys.push_back(heap.top());
    heap.pop();
  }
  std::sort(xs.begin(), xs.end());
  return std::equal(ys.rbegin(), ys.rend(), xs.begin());
}

#endif

