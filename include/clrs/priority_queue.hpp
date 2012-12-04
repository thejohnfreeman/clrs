#ifndef CLRS_06_05_PRIORITY_QUEUE
#define CLRS_06_05_PRIORITY_QUEUE

#include <functional>
#include <vector>
#include <utility>
#include <cassert>
#include <cstdio>

#include "heap.hpp"

namespace clrs {

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
        clrs::make_heap(c.begin(), c.end(), comp);
      }

    explicit priority_queue(const Compare& _comp = Compare(),
        Container&& _c = Container()) :
      comp(std::move(_comp)), c(std::move(_c)) {
        clrs::make_heap(c.begin(), c.end(), comp);
      }

    priority_queue(const priority_queue& other) :
      comp(other.comp), c(other.c) {}

    /* Why not use `std::forward` here and get rid of the const-reference
     * copy constructor? */
    priority_queue(priority_queue&& other) :
      comp(std::move(other.comp)), c(std::move(other.c)) {}

    template <typename InputIt>
    priority_queue(InputIt first, InputIt last,
        const Compare& _comp = Compare()) :
      comp(_comp), c(first, last) {
        clrs::make_heap(c.begin(), c.end(), comp);
      }

    const_reference top() const { return c.front(); }

    bool      empty() const { return c.empty(); }
    size_type size()  const { return c.size(); }

    void pop() {
      assert(c.size() > 0);
      clrs::pop_heap(c.begin(), c.end(), comp);
      c.resize(c.size() - 1);
    }

    void push(const T& value) {
      c.push_back(value);
      clrs::push_heap(c.begin(), c.end(), comp);
    }

    void push(T&& value) {
      c.push_back(std::move(value));
      clrs::push_heap(c.begin(), c.end(), comp);
    }

    template <typename... Args>
    void emplace(Args&&... args) {
      c.emplace_back(std::forward<Args>(args)...);
      clrs::push_heap(c.begin(), c.end(), comp);
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

