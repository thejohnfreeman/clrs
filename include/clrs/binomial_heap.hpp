#ifndef CLRS_19_XX_BINOMIAL_HEAP
#define CLRS_19_XX_BINOMIAL_HEAP

#include <functional>
#include <cassert>
#include <initializer_list>
#ifndef NDEBUG
#include <iostream>
#endif

namespace clrs {

  template <typename T, typename Compare>
  class binomial_heap;

  template <typename T>
  class binomial_tree {
  public:
    typedef binomial_tree           tree_t;
    typedef std::unique_ptr<tree_t> tree_ptr;

  private:
    T        value;
    size_t   degree  = 0;
    tree_ptr child   = nullptr;
    tree_ptr sibling = nullptr;

#ifndef NDEBUG
    static int alive;
#endif

  public:
    explicit binomial_tree(const T& _value) :
      value(_value)
    {
#ifndef NDEBUG
      ++alive;
#endif
    }

    explicit binomial_tree(T&& _value) :
      value(std::forward<T>(_value))
    {
#ifndef NDEBUG
      ++alive;
#endif
    }

    ~binomial_tree() {
#ifndef NDEBUG
      --alive;
#endif
    }

#ifndef NDEBUG
    static int leaks() { return alive; }
#endif

    /* Binomial-Link(y = orphan, z = this) */
    void adopt(tree_ptr&& orphan) {
      assert(!orphan->sibling);
      assert(this->degree == orphan->degree);

      orphan->sibling.reset(this->child.release());
      this->child    .swap(orphan);
      ++this->degree;
    }

    const T& get() const { return value; }
    T&       get()       { return value; }

    template <typename U, typename Compare>
    friend class binomial_heap;

    template <typename Compare>
    friend const tree_ptr* max(const tree_ptr* largest, Compare comp) {
      assert(*largest && "list must have at least one tree");
      for (const tree_ptr* i = &(*largest)->sibling; (*i);
          i = &(*i)->sibling)
      {
        if (comp((*largest)->get(), (*i)->get())) {
          largest = i;
        }
      }
      return largest;
    }

#ifndef NDEBUG
    friend std::ostream& operator<< (std::ostream& out, const tree_t& t) {
      return out << "tree(" << t.get() << ")[" << t.degree << "]";
    }

    friend std::ostream& operator<< (std::ostream& out, const tree_ptr& t) {
      return t ? (out << *t) : (out << "nullptr");
    }

    friend void print(std::ostream& out, const tree_ptr& t,
        std::string& indent, bool is_first_child)
    {
      typedef binomial_tree<T> tree_t;
      assert(t && "cannot print empty tree");

      if (t->child) {
        /* Add indentation for children. Shouldn't re-allocate if we reserved
         * enough space. */
        if (is_first_child) {
          indent += "  ";
        } else {
          indent += "| ";
        }

        print(out, t->child, indent, true);

        /* Pop the last two characters. Find a new way if this re-allocates. */
        indent.resize(indent.size() - 2);

        out << indent;
        if (is_first_child) {
          out << ' ';
        } else {
          out << '|';
        }
        out << '/' << std::endl;
      }

      /* Print myself. */
      out << indent << "* " << t->get() << std::endl;

      /* Print my siblings. */
      if (t->sibling) {
        out << indent << '|' << std::endl;
        print(out, t->sibling, indent, false);
      }
    }

    friend void print(std::ostream& out, const tree_ptr& t,
        const size_t max_degree = 2)
    {
      if (!t) return;
      std::string indent;
      indent.reserve(max_degree << 1);
      print(out, t, indent, true);
    }
#endif

  };

#ifndef NDEBUG
  template <typename T>
  int binomial_tree<T>::alive = 0;
#endif

  template <typename T, typename Compare = std::less<T>>
  class binomial_heap {
  private:
    typedef binomial_tree<T>           tree_t;
    typedef typename tree_t::tree_ptr  tree_ptr;

    Compare  comp;
    tree_ptr head = nullptr;

  public:
    typedef T        value_type;
    typedef size_t   size_type;
    typedef T&       reference;
    typedef const T& const_reference;

    binomial_heap(Compare&& _comp = Compare()) :
      comp(std::forward<Compare>(_comp)) {}

    template <typename InputIt>
    binomial_heap(InputIt first, InputIt last,
        const Compare& _comp = Compare()) :
      comp(_comp)
    {
      while (first != last) {
        push(*first++);
      }
    }

    binomial_heap(std::initializer_list<T> list,
        const Compare& _comp = Compare()) :
      binomial_heap(list.begin(), list.end(), _comp) {}

  public:
    /* Binomial-Heap-Minimum(H = this) */
    const_reference top() const {
      return (*max(&this->head, comp))->get();
    }

    bool empty() const { return !head; }

    size_type size() const {
      /* TODO: Keep track ourselves instead? */
      size_type s = 0;
      for (const tree_t* i = head.get(); i; i = i->sibling.get()) {
        s += 1 << i->degree;
      }
      return s;
    }

    /* Binomial-Heap-Union(this, other) */
    /* Empties the other heap into this one. */
    void absorb(binomial_heap&& other) {
      this->absorb(std::move(other.head));
    }

  private:
    void absorb(tree_ptr&& other) {
      /* Walk along the linked list of trees, inserting `other`'s nodes
       * between ours. */

      /* Binomial-Heap-Merge(this, other) */
      /* Keep a pointer to the link to the tree (whether its `head` or
       * `sibling`) so that we can easily change it without managing two
       * pointers. */
      tree_ptr* i = &this->head;
      tree_ptr j(std::move(other));

      while (j) {
        /* Find the next tree in our list whose degree is not less than the
         * next tree in the other list. */
        while (*i && ((*i)->degree < j->degree)) {
          i = &(*i)->sibling;
        }
        /* Insert the tree from the other list right before the tree in our
         * list. */
        j->sibling.swap(*i);
        /* Remove the tree from the other list. */
        j.swap(*i);
      }

      if (!this->head) return;

      tree_ptr* x      = &this->head;
      tree_ptr* x_next = &this->head->sibling;
      while (*x_next) {
        if (((*x)->degree != (*x_next)->degree) ||
            ((*x_next)->sibling &&
             (*x_next)->sibling->degree == (*x_next)->degree))
        {
          x = &(*x)->sibling;
        } else {
          tree_ptr child;
          /* Splice out the smaller key. */
          if (comp((*x)->get(), (*x_next)->get())) {
            child.swap(*x);
            x->swap(child->sibling);
          } else {
            child.swap(*x_next);
            x_next->swap(child->sibling);
          }
          /* Merge the two trees. */
          assert(!child->sibling);
          (*x)->adopt(std::move(child));
        }
        x_next = &(*x)->sibling;
      }
    }

  public:
    /* Binomial-Heap-Insert(this, value) */
    void push(const T& value) {
      tree_ptr elt(new tree_t(value));
      this->absorb(std::move(elt));
    }

    void push(T&& value) {
      tree_ptr elt(new tree_t(std::forward<T>(value)));
      this->absorb(std::move(elt));
    }

    /* Binomial-Heap-Extract-Min(this) */
    void pop() {
      tree_ptr* largest = const_cast<tree_ptr*>(max(&this->head, comp));

      /* Remove `*largest` from the list. */
      tree_ptr x(std::move(*largest));
      largest->swap(x->sibling);
      assert(!x->sibling);

      /* Reverse the order of `x`'s children. */
      tree_ptr x_prev(nullptr);
      /* Note: deletes the tree that had the largest key. */
      x.reset(x->child.release());
      while (x) {
        x->sibling.swap(x_prev);
        x_prev.swap(x);
      }
      assert(!x);

      this->absorb(std::move(x_prev));
    }
    
#ifndef NDEBUG
    friend void print(std::ostream& out, const binomial_heap& bh) {
      size_t max_degree = 0;
      for (const tree_t* t = bh.head.get(); t; t = t->sibling.get()) {
        if (t->degree > max_degree) {
          max_degree = t->degree;
        }
      }

      print(out, bh.head, max_degree);
    }
#endif

  };

}

#endif

