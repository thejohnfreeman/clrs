#ifndef CLRS_19_XX_BINOMIAL_HEAP
#define CLRS_19_XX_BINOMIAL_HEAP

#include <functional>
#include <cassert>

namespace clrs {

  template <typename T, typename Compare>
  class binomial_heap;

  template <typename T>
  class binomial_tree {
  public:
    typedef binomial_tree tree_t;

  private:
    T              value;
    size_t         degree;
    /* TODO: Make these `std::unique_ptr`s. */
    binomial_tree* child;
    binomial_tree* sibling;

  public:
    binomial_tree(T&& _value) :
      value(_value), degree(0), child(nullptr), sibling(nullptr) {}

    /* Binomial-Link(y = orphan, z = this) */
    tree_t* adopt(tree_t* orphan) {
      assert(orphan->sibling == nullptr);
      // Disable this test for easier heap implementation.
      //assert(this->sibling   == nullptr);
      assert(this->degree == orphan->degree);
      orphan->sibling = this->child;
      this->child     = orphan;
      ++this->degree;
      return this;
    }

    const T& get() const { return value; }
    T&       get()       { return value; }

    template <typename U, typename Compare>
    friend class binomial_heap;

    template <typename Compare>
    friend tree_t** max(tree_t** largest, Compare comp) {
      assert(*largest && "list must have at least one tree");
      for (tree_t** i = &largest->sibling; (*i); i = &(*i)->sibling) {
        if (comp((*largest)->get(), (*i)->get())) {
          largest = i;
        }
      }
      return largest;
    }
  };

  //template <typename T, typename Compare>
  //binomial_tree<T>** max(binomial_tree<T>** largest, Compare comp) {

  template <typename T, typename Compare = std::less<T>>
  class binomial_heap {
  private:
    typedef binomial_tree<T> tree_t;
    Compare                  comp;
    std::unique_ptr<tree_t>  head;

  public:
    typedef T        value_type;
    typedef size_t   size_type;
    typedef T&       reference;
    typedef const T& const_reference;

    binomial_heap(Compare&& _comp = Compare()) :
      comp(std::forward<Compare>(_comp)), head(nullptr) {}

  public:
    /* Binomial-Heap-Minimum(H = this) */
    const_reference top() const {
      tree_t* x = head;
      return (*max(x, comp))->get();
    }

    bool empty() const { return head == nullptr; }

    size_type size()  const {
      /* TODO: Keep track ourselves instead? */
      size_type s = 0;
      for (tree_t* i = head; i; i = i->sibling) {
        s += 1 << i->degree;
      }
      return s;
    }

    void absorb(binomial_heap&& other) {
      this->absorb(other.head.release());
    }

  private:
    /* Binomial-Heap-Union(this, other) */
    /* Empties the other heap into this one. */
    void absorb(tree_t* other) {
      /* Walk along the linked list of trees, inserting `other`'s nodes
       * between ours. */

      /* Binomial-Heap-Merge(this, other) */
      /* We may change head. Easier to release now than put in a special
       * check later. */
      tree_t* stage = this->head.release();
      /* Keep a pointer to the link to the tree (whether its `head` or
       * `sibling`) so that we can easily change it without managing two
       * pointers. */
      tree_t** i    = &stage;
      tree_t* j     = other;
      while (j) {
        /* Find the next tree in our list whose degree is not less than the
         * next tree in the other list. */
        while (*i && ((*i)->degree < j->degree)) {
          i = &(*i)->sibling;
        }
        /* Remove the tree from the other list. */
        tree_t* y = j;
        j = j->sibling;
        /* Insert the tree from the other list right before the tree in our
         * list. */
        y->sibling = *i;
        *i = y;
      }

      if (!stage) return;

      tree_t** x      = &stage;
      tree_t*  x_next = x->sibling;
      while (x_next) {
        if (((*x)->degree != x_next->degree) ||
            (x_next->sibling && x_next->sibling->degree == x_next->degree))
        {
          x = &(*x)->sibling;
        } else {
          /* Make sure `x` has the larger key. */
          if (comp((*x)->get(), x_next->get())) {
            /* Links the head or previous tree in the list to `x`. */
            std::swap(*x, x_next);
          } else {
            /* Links `x` to the next tree in the list. */
            (*x)->sibling = x_next->sibling;
          }
          /* Merge the two trees. */
          (*x)->adopt(x_next);
        }
        x_next = (*x)->sibling;
      }

      this->head = stage;
    }

  public:
    /* Binomial-Heap-Insert(this, value) */
    void push(T&& value) {
      tree_t* elt = new tree_t(std::forward<T>(value));
      this->absorb(elt);
    }

    /* Binomial-Heap-Extract-Min(this) */
    void pop() {
      assert(this->head && "must have at least one node");

      tree_t* stage    = this->head.release();
      tree_t** largest = max(&stage, comp);

      /* Remove `*largest` from the list. */
      tree_t* x = *largest;
      /* Might clear head. */
      *largest  = x->sibling;

      /* Reverse the order of `x`'s children. */
      tree_t* x_prev = nullptr;
      x              = x->child;
      while (x) {
        tree_t* x_next = x->sibling;
        x->sibling     = x_prev;
        x_prev         = x;
        x              = x_next;
      }

      /* Sets head if we cleared it. */
      this->absorb(x);
    }
    
  };

}

#endif

