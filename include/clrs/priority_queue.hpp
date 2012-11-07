#ifndef CLRS_06_05_PRIORITY_QUEUE
#define CLRS_06_05_PRIORITY_QUEUE

#include <functional>
#include <vector>
#include <utility>
#include <cassert>
#include <cstdio>

#include "heap_sort.hpp"

namespace clrs {

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

  template <typename T, typename Cmp = std::less<T>>
  void promote(T* A, size_t n, size_t i, const T& key, Cmp cmp = Cmp()) {
    assert(cmp(A[i], key));
    A[i] = key;
    push_heap(A, i + 1, cmp);
  }

  template <typename T, typename Cmp = std::less<T>>
  void demote(T* A, size_t n, size_t i, const T& key, Cmp cmp = Cmp()) {
    assert(cmp(key, A[i]));
    A[i] = key;
    heap_settle(A, n, i, cmp);
  }

  template <
    typename T,
    typename Container = std::vector<T>,
    typename Compare   = std::less<typename Container::value_type>>
  class priority_queue {
  private:

    Compare   comp;
    Container c;

  public:

    typedef Container                           container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

    priority_queue(const Compare& _comp, const Container& _c) :
      comp(_comp), c(_c) {
        make_heap(c.data(), c.size(), comp);
      }

    explicit priority_queue(const Compare& _comp = Compare(),
        Container&& _c = Container()) :
      comp(std::move(_comp)), c(std::move(_c)) {
        make_heap(c.data(), c.size(), comp);
      }

    priority_queue(const priority_queue& other) :
      comp(other.comp), c(other.c) {}

    priority_queue(priority_queue&& other) :
      comp(std::move(other.comp)), c(std::move(other.c)) {}

    template <typename InputIt>
    priority_queue(InputIt first, InputIt last,
        const Compare& _comp = Compare()) :
      comp(_comp), c(first, last) {
        make_heap(c.data(), c.size(), comp);
      }

    const_reference top() const { return c.front(); }

    bool empty() const { return c.empty(); }
    bool size()  const { return c.size(); }

    void pop() {
      c.front() = c.back();
      c.resize(c.size() - 1);
      heap_settle(c.data(), c.size(), 0, comp);
    }

    void push(const T& value) {
      c.push_back(value);
      push_heap(c.begin(), c.size(), comp);
    }

    void push(T&& value) {
      c.push_back(std::move(value));
      push_heap(c.begin(), c.size(), comp);
    }

    template <typename... Args>
    void emplace(Args&&... args) {
      c.emplace_back(std::forward<Args>(args)...);
      push_heap(c.begin(), c.size(), comp);
    }

    void swap(priority_queue<T, Container, Compare>& other) {
      using std::swap;
      swap(comp, other.comp);
      swap(c, other.c);
    }

  };

}

namespace std {

  template <typename T, typename Container, typename Compare>
  void swap(clrs::priority_queue<T, Container, Compare>& lhs,
      clrs::priority_queue<T, Container, Compare>& rhs)
  {
    lhs.swap(rhs);
  }

}

#endif

