/* APPLE LOCAL file libstdc++ debug mode */
// Debugging vector implementation -*- C++ -*-

// Copyright (C) 2003
// Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

#ifndef _GLIBCXX_DEBUG_VECTOR_H
#define _GLIBCXX_DEBUG_VECTOR_H

#include <debug/safe_sequence.h>
#include <debug/safe_iterator.h>

_GLIBCXX_DEBUG_NAMESPACE_OPEN(std)

template<typename _Tp, typename _Allocator = std::allocator<_Tp> >
  class _GLIBCXX_DEBUG_CLASS(vector) vector 
  : public _GLIBCXX_DEBUG_BASE(std, vector)<_Tp, _Allocator>,
    public std::__debug::_Safe_sequence<vector<_Tp, _Allocator> >
  {
    typedef _GLIBCXX_DEBUG_BASE(std, vector)<_Tp, _Allocator> _Base;
    typedef std::__debug::_Safe_sequence<vector>              _Safe_base;

    typedef typename _Base::const_iterator _Base_const_iterator;
    typedef std::__debug::_After_nth_from<_Base_const_iterator> _After_nth;

  public:
    typedef typename _Base::reference             reference;
    typedef typename _Base::const_reference       const_reference;

    typedef std::__debug::_Safe_iterator<typename _Base::iterator,vector> 
                                                  iterator;
    typedef std::__debug::_Safe_iterator<typename _Base::const_iterator,vector>
                                                  const_iterator;

    typedef typename _Base::size_type             size_type;
    typedef typename _Base::difference_type       difference_type;

    typedef _Tp        			    value_type;
    typedef _Allocator 			    allocator_type;
    typedef typename _Allocator::pointer          pointer;
    typedef typename _Allocator::const_pointer    const_pointer;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // 23.2.4.1 construct/copy/destroy:
    explicit vector(const _Allocator& __a = _Allocator())
    : _Base(__a), _M_guaranteed_capacity(0)
    { }

    explicit vector(size_type __n, const _Tp& __value = _Tp(),
		      const _Allocator& __a = _Allocator())
    : _Base(__n, __value, __a), _M_guaranteed_capacity(__n)
    { }

    template <class _InputIterator>
      vector(_InputIterator __first, _InputIterator __last,
	     const _Allocator& __a = _Allocator())
      : _Base(std::__debug::__check_valid_range(__first, __last), __last, __a),
        _M_guaranteed_capacity(0)
      { _M_update_guaranteed_capacity(); }

    vector(const vector<_Tp,_Allocator>& __x) 
    : _Base(__x), _Safe_base(), _M_guaranteed_capacity(__x.size())
    { }

    /// Construction from a release-mode vector
    vector(const _Base& __x) 
    : _Base(__x), _Safe_base(), _M_guaranteed_capacity(__x.size())
    { }

    ~vector() { }

    vector<_Tp,_Allocator>& 
    operator=(const vector<_Tp,_Allocator>& __x)
    {
      static_cast<_Base&>(*this) = __x;
      this->_M_invalidate_all();
      _M_update_guaranteed_capacity();
      return *this;
    }

    template <class _InputIterator>
      void 
      assign(_InputIterator __first, _InputIterator __last)
      {
	__glibcxx_check_valid_range(__first, __last);
	_Base::assign(__first, __last);
	this->_M_invalidate_all();
	_M_update_guaranteed_capacity();
      }

    void 
    assign(size_type __n, const _Tp& __u)
    {
      _Base::assign(__n, __u);
      this->_M_invalidate_all();
      _M_update_guaranteed_capacity();
    }

    using _Base::get_allocator;

    // iterators:
    iterator 
    begin() 
    { return iterator(_Base::begin(), this); }

    const_iterator 
    begin() const 
    { return const_iterator(_Base::begin(), this); }

    iterator 
    end()
    { return iterator(_Base::end(), this); }

    const_iterator 
    end() const
    { return const_iterator(_Base::end(), this); }

    reverse_iterator 
    rbegin() 
    { return reverse_iterator(end()); }

    const_reverse_iterator 
    rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator 
    rend() 
    { return reverse_iterator(begin()); }

    const_reverse_iterator 
    rend() const 
    { return const_reverse_iterator(begin()); }

    // 23.2.4.2 capacity:
    using _Base::size;
    using _Base::max_size;

    void 
    resize(size_type __sz, _Tp __c = _Tp())
    {
      bool __realloc = _M_requires_reallocation(__sz);
      if (__sz < this->size())
	this->_M_invalidate_if(_After_nth(__sz, _M_base().begin()));
      _Base::resize(__sz, __c);
      if (__realloc)
	this->_M_invalidate_all();
    }

    using _Base::capacity;
    using _Base::empty;

    void 
    reserve(size_type __n)
    {
      bool __realloc = _M_requires_reallocation(__n);
      _Base::reserve(__n);
      if (__n > _M_guaranteed_capacity)
	_M_guaranteed_capacity = __n;
      if (__realloc)
	this->_M_invalidate_all();
    }

    // element access:
    reference 
    operator[](size_type __n)
    {
      __glibcxx_check_subscript(__n);
      return _M_base()[__n];
    }

    const_reference 
    operator[](size_type __n) const
    {
      __glibcxx_check_subscript(__n);
      return _M_base()[__n];
    }

    using _Base::at;

    reference 
    front()
    {
      __glibcxx_check_nonempty();
      return _Base::front();
    }

    const_reference 
    front() const
    {
      __glibcxx_check_nonempty();
      return _Base::front();
    }

    reference 
    back()
    {
      __glibcxx_check_nonempty();
      return _Base::back();
    }

    const_reference 
    back() const
    {
      __glibcxx_check_nonempty();
      return _Base::back();
    }

    // 23.2.4.3 modifiers:
    void 
    push_back(const _Tp& __x)
    {
      bool __realloc = _M_requires_reallocation(this->size() + 1);
      _Base::push_back(__x);
      if (__realloc)
	this->_M_invalidate_all();
      _M_update_guaranteed_capacity();
    }

    void 
    pop_back()
    {
      __glibcxx_check_nonempty();
      iterator __victim = end() - 1;
      __victim._M_invalidate();
      _Base::pop_back();
    }

    iterator 
    insert(iterator __position, const _Tp& __x)
    {
      __glibcxx_check_insert(__position);
      bool __realloc = _M_requires_reallocation(this->size() + 1);
      difference_type __offset = __position - begin();
      typename _Base::iterator __result = _Base::insert(__position.base(),__x);
      if (__realloc)
	this->_M_invalidate_all();
      else
	this->_M_invalidate_if(_After_nth(__offset, _M_base().begin()));
      _M_update_guaranteed_capacity();
      return iterator(__result, this);
    }

    void 
    insert(iterator __position, size_type __n, const _Tp& __x)
    {
      __glibcxx_check_insert(__position);
      bool __realloc = _M_requires_reallocation(this->size() + __n);
      difference_type __offset = __position - begin();
      _Base::insert(__position.base(), __n, __x);
      if (__realloc)
	this->_M_invalidate_all();
      else
	this->_M_invalidate_if(_After_nth(__offset, _M_base().begin()));
      _M_update_guaranteed_capacity();
    }

    template <class _InputIterator>
      void 
      insert(iterator __position, 
	     _InputIterator __first, _InputIterator __last)
      {
	__glibcxx_check_insert_range(__position, __first, __last);
	
	/* Hard to guess if invalidation will occur, because __last
	   - __first can't be calculated in all cases, so we just
	   punt here by checking if it did occur. */
	typename _Base::iterator __old_begin = _M_base().begin();
	difference_type __offset = __position - begin();
	_Base::insert(__position.base(), __first, __last);
	
	if (_M_base().begin() != __old_begin)
	  this->_M_invalidate_all();
	else
	  this->_M_invalidate_if(_After_nth(__offset, _M_base().begin()));
	_M_update_guaranteed_capacity();
      }

    iterator 
    erase(iterator __position)
    {
      __glibcxx_check_erase(__position);
      difference_type __offset = __position - begin();
      typename _Base::iterator __result = _Base::erase(__position.base());
      this->_M_invalidate_if(_After_nth(__offset, _M_base().begin()));
      return iterator(__result, this);
    }

    iterator 
    erase(iterator __first, iterator __last)
    {
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 151. can't currently clear() empty container
      __glibcxx_check_erase_range(__first, __last);
      
      difference_type __offset = __first - begin();
      typename _Base::iterator __result = _Base::erase(__first.base(), 
						       __last.base());
      this->_M_invalidate_if(_After_nth(__offset, _M_base().begin()));
      return iterator(__result, this);
    }

    void 
    swap(vector<_Tp,_Allocator>& __x)
    {
      _Base::swap(__x);
      this->_M_swap(__x);
    }

    void 
    clear()
    {
      _Base::clear();
      this->_M_invalidate_all();
    }

    _Base&       _M_base()       { return *this; }
    const _Base& _M_base() const { return *this; }

  private:
    size_type _M_guaranteed_capacity;

    bool 
    _M_requires_reallocation(size_type __elements)
    {
#ifdef _GLIBCXX_DEBUG_PEDANTIC
      return __elements > this->capacity();
#else
      return __elements > _M_guaranteed_capacity;
#endif
    }

    void 
    _M_update_guaranteed_capacity()
    {
      if (this->size() > _M_guaranteed_capacity)
	_M_guaranteed_capacity = this->size();
    }
  };

template<typename _Tp, typename _Alloc>
  inline bool
  operator==(const vector<_Tp, _Alloc>& __lhs,
	       const vector<_Tp, _Alloc>& __rhs)
  { return __lhs._M_base() == __rhs._M_base(); }

template<typename _Tp, typename _Alloc>
  inline bool
  operator!=(const vector<_Tp, _Alloc>& __lhs,
	       const vector<_Tp, _Alloc>& __rhs)
  { return __lhs._M_base() != __rhs._M_base(); }

template<typename _Tp, typename _Alloc>
  inline bool
  operator<(const vector<_Tp, _Alloc>& __lhs, 
	      const vector<_Tp, _Alloc>& __rhs)
  { return __lhs._M_base() < __rhs._M_base(); }

template<typename _Tp, typename _Alloc>
  inline bool
  operator<=(const vector<_Tp, _Alloc>& __lhs, 
	       const vector<_Tp, _Alloc>& __rhs)
  { return __lhs._M_base() <= __rhs._M_base(); }

template<typename _Tp, typename _Alloc>
  inline bool
  operator>=(const vector<_Tp, _Alloc>& __lhs, 
	       const vector<_Tp, _Alloc>& __rhs)
  { return __lhs._M_base() >= __rhs._M_base(); }

template<typename _Tp, typename _Alloc>
  inline bool
  operator>(const vector<_Tp, _Alloc>& __lhs, 
	      const vector<_Tp, _Alloc>& __rhs)
  { return __lhs._M_base() > __rhs._M_base(); }

template<typename _Tp, typename _Alloc>
  inline void
  swap(vector<_Tp, _Alloc>& __lhs, vector<_Tp, _Alloc>& __rhs)
  { __lhs.swap(__rhs); }

_GLIBCXX_DEBUG_NAMESPACE_CLOSE

#endif /* _GLIBCXX_DEBUG_VECTOR_H */
