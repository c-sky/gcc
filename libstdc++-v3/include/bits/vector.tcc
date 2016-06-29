// Vector implementation (out of line) -*- C++ -*-

// Copyright (C) 2001-2016 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this  software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/** @file bits/vector.tcc
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{vector}
 */

#ifndef _VECTOR_TCC
#define _VECTOR_TCC 1

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_CONTAINER

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    reserve(size_type __n)
    {
      if (__n > this->max_size())
	__throw_length_error(__N("vector::reserve"));
      if (this->capacity() < __n)
	{
	  const size_type __old_size = size();
	  pointer __tmp = _M_allocate_and_copy(__n,
	    _GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(this->_M_impl._M_start),
	    _GLIBCXX_MAKE_MOVE_IF_NOEXCEPT_ITERATOR(this->_M_impl._M_finish));
	  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			_M_get_Tp_allocator());
	  _M_deallocate(this->_M_impl._M_start,
			this->_M_impl._M_end_of_storage
			- this->_M_impl._M_start);
	  this->_M_impl._M_start = __tmp;
	  this->_M_impl._M_finish = __tmp + __old_size;
	  this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __n;
	}
    }

#if __cplusplus >= 201103L
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      vector<_Tp, _Alloc>::
      emplace_back(_Args&&... __args)
      {
	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	  {
	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
				     std::forward<_Args>(__args)...);
	    ++this->_M_impl._M_finish;
	  }
	else
	  _M_emplace_back_aux(std::forward<_Args>(__args)...);
      }
#endif

  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
#if __cplusplus >= 201103L
    insert(const_iterator __position, const value_type& __x)
#else
    insert(iterator __position, const value_type& __x)
#endif
    {
      const size_type __n = __position - begin();
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
	  && __position == end())
	{
	  _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, __x);
	  ++this->_M_impl._M_finish;
	}
      else
	{
#if __cplusplus >= 201103L
	  const auto __pos = begin() + (__position - cbegin());
	  if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	    {
	      _Tp __x_copy = __x;
	      _M_insert_aux(__pos, std::move(__x_copy));
	    }
	  else
	    _M_insert_aux(__pos, __x);
#else
	    _M_insert_aux(__position, __x);
#endif
	}
      return iterator(this->_M_impl._M_start + __n);
    }

  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    _M_erase(iterator __position)
    {
      if (__position + 1 != end())
	_GLIBCXX_MOVE3(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      _Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
      return __position;
    }

  template<typename _Tp, typename _Alloc>
    typename vector<_Tp, _Alloc>::iterator
    vector<_Tp, _Alloc>::
    _M_erase(iterator __first, iterator __last)
    {
      if (__first != __last)
	{
	  if (__last != end())
	    _GLIBCXX_MOVE3(__last, end(), __first);
	  _M_erase_at_end(__first.base() + (end() - __last));
	}
      return __first;
    }

  template<typename _Tp, typename _Alloc>
    vector<_Tp, _Alloc>&
    vector<_Tp, _Alloc>::
    operator=(const vector<_Tp, _Alloc>& __x)
    {
      if (&__x != this)
	{
#if __cplusplus >= 201103L
	  if (_Alloc_traits::_S_propagate_on_copy_assign())
	    {
	      if (!_Alloc_traits::_S_always_equal()
	          && _M_get_Tp_allocator() != __x._M_get_Tp_allocator())
	        {
		  // replacement allocator cannot free existing storage
		  this->clear();
		  _M_deallocate(this->_M_impl._M_start,
				this->_M_impl._M_end_of_storage
				- this->_M_impl._M_start);
		  this->_M_impl._M_start = nullptr;
		  this->_M_impl._M_finish = nullptr;
		  this->_M_impl._M_end_of_storage = nullptr;
		}
	      std::__alloc_on_copy(_M_get_Tp_allocator(),
				   __x._M_get_Tp_allocator());
	    }
#endif
	  const size_type __xlen = __x.size();
	  if (__xlen > capacity())
	    {
	      pointer __tmp = _M_allocate_and_copy(__xlen, __x.begin(),
						   __x.end());
	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			    _M_get_Tp_allocator());
	      _M_deallocate(this->_M_impl._M_start,
			    this->_M_impl._M_end_of_storage
			    - this->_M_impl._M_start);
	      this->_M_impl._M_start = __tmp;
	      this->_M_impl._M_end_of_storage = this->_M_impl._M_start + __xlen;
	    }
	  else if (size() >= __xlen)
	    {
	      std::_Destroy(std::copy(__x.begin(), __x.end(), begin()),
			    end(), _M_get_Tp_allocator());
	    }
	  else
	    {
	      std::copy(__x._M_impl._M_start, __x._M_impl._M_start + size(),
			this->_M_impl._M_start);
	      std::__uninitialized_copy_a(__x._M_impl._M_start + size(),
					  __x._M_impl._M_finish,
					  this->_M_impl._M_finish,
					  _M_get_Tp_allocator());
	    }
	  this->_M_impl._M_finish = this->_M_impl._M_start + __xlen;
	}
      return *this;
    }

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_assign(size_t __n, const value_type& __val)
    {
      if (__n > capacity())
	{
	  vector __tmp(__n, __val, _M_get_Tp_allocator());
	  __tmp._M_impl._M_swap_data(this->_M_impl);
	}
      else if (__n > size())
	{
	  std::fill(begin(), end(), __val);
	  this->_M_impl._M_finish =
	    std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
					  __n - size(), __val,
					  _M_get_Tp_allocator());
	}
      else
        _M_erase_at_end(std::fill_n(this->_M_impl._M_start, __n, __val));
    }

  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_InputIterator __first, _InputIterator __last,
		    std::input_iterator_tag)
      {
	pointer __cur(this->_M_impl._M_start);
	for (; __first != __last && __cur != this->_M_impl._M_finish;
	     ++__cur, ++__first)
	  *__cur = *__first;
	if (__first == __last)
	  _M_erase_at_end(__cur);
	else
	  _M_range_insert(end(), __first, __last,
			  std::__iterator_category(__first));
      }

  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_assign_aux(_ForwardIterator __first, _ForwardIterator __last,
		    std::forward_iterator_tag)
      {
	const size_type __len = std::distance(__first, __last);

	if (__len > capacity())
	  {
	    pointer __tmp(_M_allocate_and_copy(__len, __first, __last));
	    std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			  _M_get_Tp_allocator());
	    _M_deallocate(this->_M_impl._M_start,
			  this->_M_impl._M_end_of_storage
			  - this->_M_impl._M_start);
	    this->_M_impl._M_start = __tmp;
	    this->_M_impl._M_finish = this->_M_impl._M_start + __len;
	    this->_M_impl._M_end_of_storage = this->_M_impl._M_finish;
	  }
	else if (size() >= __len)
	  _M_erase_at_end(std::copy(__first, __last, this->_M_impl._M_start));
	else
	  {
	    _ForwardIterator __mid = __first;
	    std::advance(__mid, size());
	    std::copy(__first, __mid, this->_M_impl._M_start);
	    this->_M_impl._M_finish =
	      std::__uninitialized_copy_a(__mid, __last,
					  this->_M_impl._M_finish,
					  _M_get_Tp_allocator());
	  }
      }

#if __cplusplus >= 201103L
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      typename vector<_Tp, _Alloc>::iterator
      vector<_Tp, _Alloc>::
      emplace(const_iterator __position, _Args&&... __args)
      {
	const size_type __n = __position - begin();
	if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage
	    && __position == end())
	  {
	    _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
				     std::forward<_Args>(__args)...);
	    ++this->_M_impl._M_finish;
	  }
	else
	  _M_insert_aux(begin() + (__position - cbegin()),
			std::forward<_Args>(__args)...);
	return iterator(this->_M_impl._M_start + __n);
      }

  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      vector<_Tp, _Alloc>::
      _M_insert_aux(iterator __position, _Args&&... __args)
#else
  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_insert_aux(iterator __position, const _Tp& __x)
#endif
    {
      if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
	{
	  _Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish,
			           _GLIBCXX_MOVE(*(this->_M_impl._M_finish
				                   - 1)));
	  ++this->_M_impl._M_finish;
#if __cplusplus < 201103L
	  _Tp __x_copy = __x;
#endif
	  _GLIBCXX_MOVE_BACKWARD3(__position.base(),
				  this->_M_impl._M_finish - 2,
				  this->_M_impl._M_finish - 1);
#if __cplusplus < 201103L
	  *__position = __x_copy;
#else
	  _S_insert_aux_assign(__position, std::forward<_Args>(__args)...);
#endif
	}
      else
	{
	  const size_type __len =
	    _M_check_len(size_type(1), "vector::_M_insert_aux");
	  const size_type __elems_before = __position - begin();
	  pointer __new_start(this->_M_allocate(__len));
	  pointer __new_finish(__new_start);
	  __try
	    {
	      // The order of the three operations is dictated by the C++0x
	      // case, where the moves could alter a new element belonging
	      // to the existing vector.  This is an issue only for callers
	      // taking the element by const lvalue ref (see 23.1/13).
	      _Alloc_traits::construct(this->_M_impl,
		                       __new_start + __elems_before,
#if __cplusplus >= 201103L
				       std::forward<_Args>(__args)...);
#else
	                               __x);
#endif
	      __new_finish = pointer();

	      __new_finish
		= std::__uninitialized_move_if_noexcept_a
		(this->_M_impl._M_start, __position.base(),
		 __new_start, _M_get_Tp_allocator());

	      ++__new_finish;

	      __new_finish
		= std::__uninitialized_move_if_noexcept_a
		(__position.base(), this->_M_impl._M_finish,
		 __new_finish, _M_get_Tp_allocator());
	    }
          __catch(...)
	    {
	      if (!__new_finish)
		_Alloc_traits::destroy(this->_M_impl,
		                       __new_start + __elems_before);
	      else
		std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
	      _M_deallocate(__new_start, __len);
	      __throw_exception_again;
	    }
	  std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			_M_get_Tp_allocator());
	  _M_deallocate(this->_M_impl._M_start,
			this->_M_impl._M_end_of_storage
			- this->_M_impl._M_start);
	  this->_M_impl._M_start = __new_start;
	  this->_M_impl._M_finish = __new_finish;
	  this->_M_impl._M_end_of_storage = __new_start + __len;
	}
    }

#if __cplusplus >= 201103L
  template<typename _Tp, typename _Alloc>
    template<typename... _Args>
      void
      vector<_Tp, _Alloc>::
      _M_emplace_back_aux(_Args&&... __args)
      {
	const size_type __len =
	  _M_check_len(size_type(1), "vector::_M_emplace_back_aux");
	pointer __new_start(this->_M_allocate(__len));
	pointer __new_finish(__new_start);
	__try
	  {
	    _Alloc_traits::construct(this->_M_impl, __new_start + size(),
				     std::forward<_Args>(__args)...);
	    __new_finish = pointer();

	    __new_finish
	      = std::__uninitialized_move_if_noexcept_a
	      (this->_M_impl._M_start, this->_M_impl._M_finish,
	       __new_start, _M_get_Tp_allocator());

	    ++__new_finish;
	  }
	__catch(...)
	  {
	    if (!__new_finish)
	      _Alloc_traits::destroy(this->_M_impl, __new_start + size());
	    else
	      std::_Destroy(__new_start, __new_finish, _M_get_Tp_allocator());
	    _M_deallocate(__new_start, __len);
	    __throw_exception_again;
	  }
	std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
		      _M_get_Tp_allocator());
	_M_deallocate(this->_M_impl._M_start,
		      this->_M_impl._M_end_of_storage
		      - this->_M_impl._M_start);
	this->_M_impl._M_start = __new_start;
	this->_M_impl._M_finish = __new_finish;
	this->_M_impl._M_end_of_storage = __new_start + __len;
      }
#endif

  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, const value_type& __x)
    {
      if (__n != 0)
	{
	  if (size_type(this->_M_impl._M_end_of_storage
			- this->_M_impl._M_finish) >= __n)
	    {
	      value_type __x_copy = __x;
	      const size_type __elems_after = end() - __position;
	      pointer __old_finish(this->_M_impl._M_finish);
	      if (__elems_after > __n)
		{
		  std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
					      this->_M_impl._M_finish,
					      this->_M_impl._M_finish,
					      _M_get_Tp_allocator());
		  this->_M_impl._M_finish += __n;
		  _GLIBCXX_MOVE_BACKWARD3(__position.base(),
					  __old_finish - __n, __old_finish);
		  std::fill(__position.base(), __position.base() + __n,
			    __x_copy);
		}
	      else
		{
		  this->_M_impl._M_finish =
		    std::__uninitialized_fill_n_a(this->_M_impl._M_finish,
						  __n - __elems_after,
						  __x_copy,
						  _M_get_Tp_allocator());
		  std::__uninitialized_move_a(__position.base(), __old_finish,
					      this->_M_impl._M_finish,
					      _M_get_Tp_allocator());
		  this->_M_impl._M_finish += __elems_after;
		  std::fill(__position.base(), __old_finish, __x_copy);
		}
	    }
	  else
	    {
	      const size_type __len =
		_M_check_len(__n, "vector::_M_fill_insert");
	      const size_type __elems_before = __position - begin();
	      pointer __new_start(this->_M_allocate(__len));
	      pointer __new_finish(__new_start);
	      __try
		{
		  // See _M_insert_aux above.
		  std::__uninitialized_fill_n_a(__new_start + __elems_before,
						__n, __x,
						_M_get_Tp_allocator());
		  __new_finish = pointer();

		  __new_finish
		    = std::__uninitialized_move_if_noexcept_a
		    (this->_M_impl._M_start, __position.base(),
		     __new_start, _M_get_Tp_allocator());

		  __new_finish += __n;

		  __new_finish
		    = std::__uninitialized_move_if_noexcept_a
		    (__position.base(), this->_M_impl._M_finish,
		     __new_finish, _M_get_Tp_allocator());
		}
	      __catch(...)
		{
		  if (!__new_finish)
		    std::_Destroy(__new_start + __elems_before,
				  __new_start + __elems_before + __n,
				  _M_get_Tp_allocator());
		  else
		    std::_Destroy(__new_start, __new_finish,
				  _M_get_Tp_allocator());
		  _M_deallocate(__new_start, __len);
		  __throw_exception_again;
		}
	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			    _M_get_Tp_allocator());
	      _M_deallocate(this->_M_impl._M_start,
			    this->_M_impl._M_end_of_storage
			    - this->_M_impl._M_start);
	      this->_M_impl._M_start = __new_start;
	      this->_M_impl._M_finish = __new_finish;
	      this->_M_impl._M_end_of_storage = __new_start + __len;
	    }
	}
    }

#if __cplusplus >= 201103L
  template<typename _Tp, typename _Alloc>
    void
    vector<_Tp, _Alloc>::
    _M_default_append(size_type __n)
    {
      if (__n != 0)
	{
	  if (size_type(this->_M_impl._M_end_of_storage
			- this->_M_impl._M_finish) >= __n)
	    {
	      this->_M_impl._M_finish =
		std::__uninitialized_default_n_a(this->_M_impl._M_finish,
						 __n, _M_get_Tp_allocator());
	    }
	  else
	    {
	      const size_type __len =
		_M_check_len(__n, "vector::_M_default_append");
	      const size_type __old_size = this->size();
	      pointer __new_start(this->_M_allocate(__len));
	      pointer __new_finish(__new_start);
	      __try
		{
		  __new_finish
		    = std::__uninitialized_move_if_noexcept_a
		    (this->_M_impl._M_start, this->_M_impl._M_finish,
		     __new_start, _M_get_Tp_allocator());
		  __new_finish =
		    std::__uninitialized_default_n_a(__new_finish, __n,
						     _M_get_Tp_allocator());
		}
	      __catch(...)
		{
		  std::_Destroy(__new_start, __new_finish,
				_M_get_Tp_allocator());
		  _M_deallocate(__new_start, __len);
		  __throw_exception_again;
		}
	      std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			    _M_get_Tp_allocator());
	      _M_deallocate(this->_M_impl._M_start,
			    this->_M_impl._M_end_of_storage
			    - this->_M_impl._M_start);
	      this->_M_impl._M_start = __new_start;
	      this->_M_impl._M_finish = __new_finish;
	      this->_M_impl._M_end_of_storage = __new_start + __len;
	    }
	}
    }

  template<typename _Tp, typename _Alloc>
    bool
    vector<_Tp, _Alloc>::
    _M_shrink_to_fit()
    {
      if (capacity() == size())
	return false;
      return std::__shrink_to_fit_aux<vector>::_S_do_it(*this);
    }
#endif

  template<typename _Tp, typename _Alloc>
    template<typename _InputIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __pos, _InputIterator __first,
		      _InputIterator __last, std::input_iterator_tag)
      {
	for (; __first != __last; ++__first)
	  {
	    __pos = insert(__pos, *__first);
	    ++__pos;
	  }
      }

  template<typename _Tp, typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<_Tp, _Alloc>::
      _M_range_insert(iterator __position, _ForwardIterator __first,
		      _ForwardIterator __last, std::forward_iterator_tag)
      {
	if (__first != __last)
	  {
	    const size_type __n = std::distance(__first, __last);
	    if (size_type(this->_M_impl._M_end_of_storage
			  - this->_M_impl._M_finish) >= __n)
	      {
		const size_type __elems_after = end() - __position;
		pointer __old_finish(this->_M_impl._M_finish);
		if (__elems_after > __n)
		  {
		    std::__uninitialized_move_a(this->_M_impl._M_finish - __n,
						this->_M_impl._M_finish,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
		    this->_M_impl._M_finish += __n;
		    _GLIBCXX_MOVE_BACKWARD3(__position.base(),
					    __old_finish - __n, __old_finish);
		    std::copy(__first, __last, __position);
		  }
		else
		  {
		    _ForwardIterator __mid = __first;
		    std::advance(__mid, __elems_after);
		    std::__uninitialized_copy_a(__mid, __last,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
		    this->_M_impl._M_finish += __n - __elems_after;
		    std::__uninitialized_move_a(__position.base(),
						__old_finish,
						this->_M_impl._M_finish,
						_M_get_Tp_allocator());
		    this->_M_impl._M_finish += __elems_after;
		    std::copy(__first, __mid, __position);
		  }
	      }
	    else
	      {
		const size_type __len =
		  _M_check_len(__n, "vector::_M_range_insert");
		pointer __new_start(this->_M_allocate(__len));
		pointer __new_finish(__new_start);
		__try
		  {
		    __new_finish
		      = std::__uninitialized_move_if_noexcept_a
		      (this->_M_impl._M_start, __position.base(),
		       __new_start, _M_get_Tp_allocator());
		    __new_finish
		      = std::__uninitialized_copy_a(__first, __last,
						    __new_finish,
						    _M_get_Tp_allocator());
		    __new_finish
		      = std::__uninitialized_move_if_noexcept_a
		      (__position.base(), this->_M_impl._M_finish,
		       __new_finish, _M_get_Tp_allocator());
		  }
		__catch(...)
		  {
		    std::_Destroy(__new_start, __new_finish,
				  _M_get_Tp_allocator());
		    _M_deallocate(__new_start, __len);
		    __throw_exception_again;
		  }
		std::_Destroy(this->_M_impl._M_start, this->_M_impl._M_finish,
			      _M_get_Tp_allocator());
		_M_deallocate(this->_M_impl._M_start,
			      this->_M_impl._M_end_of_storage
			      - this->_M_impl._M_start);
		this->_M_impl._M_start = __new_start;
		this->_M_impl._M_finish = __new_finish;
		this->_M_impl._M_end_of_storage = __new_start + __len;
	      }
	  }
      }


  // vector<bool>
  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_reallocate(size_type __n)
    {
      _Bit_pointer __q = this->_M_allocate(__n);
      iterator __start(std::__addressof(*__q), 0);
      this->_M_impl._M_finish = _M_copy_aligned(begin(), end(), __start);
      this->_M_deallocate();
      this->_M_impl._M_start = __start;
      this->_M_impl._M_end_of_storage = __q + _S_nword(__n);
    }

  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_fill_insert(iterator __position, size_type __n, bool __x)
    {
      if (__n == 0)
	return;
      if (capacity() - size() >= __n)
	{
	  std::copy_backward(__position, end(),
			     this->_M_impl._M_finish + difference_type(__n));
	  std::fill(__position, __position + difference_type(__n), __x);
	  this->_M_impl._M_finish += difference_type(__n);
	}
      else
	{
	  const size_type __len = 
	    _M_check_len(__n, "vector<bool>::_M_fill_insert");
	  _Bit_pointer __q = this->_M_allocate(__len);
	  iterator __start(std::__addressof(*__q), 0);
	  iterator __i = _M_copy_aligned(begin(), __position, __start);
	  std::fill(__i, __i + difference_type(__n), __x);
	  this->_M_impl._M_finish = std::copy(__position, end(),
					      __i + difference_type(__n));
	  this->_M_deallocate();
	  this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
	  this->_M_impl._M_start = __start;
	}
    }

  template<typename _Alloc>
    template<typename _ForwardIterator>
      void
      vector<bool, _Alloc>::
      _M_insert_range(iterator __position, _ForwardIterator __first, 
		      _ForwardIterator __last, std::forward_iterator_tag)
      {
	if (__first != __last)
	  {
	    size_type __n = std::distance(__first, __last);
	    if (capacity() - size() >= __n)
	      {
		std::copy_backward(__position, end(),
				   this->_M_impl._M_finish
				   + difference_type(__n));
		std::copy(__first, __last, __position);
		this->_M_impl._M_finish += difference_type(__n);
	      }
	    else
	      {
		const size_type __len =
		  _M_check_len(__n, "vector<bool>::_M_insert_range");
		_Bit_pointer __q = this->_M_allocate(__len);
		iterator __start(std::__addressof(*__q), 0);
		iterator __i = _M_copy_aligned(begin(), __position, __start);
		__i = std::copy(__first, __last, __i);
		this->_M_impl._M_finish = std::copy(__position, end(), __i);
		this->_M_deallocate();
		this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
		this->_M_impl._M_start = __start;
	      }
	  }
      }

  template<typename _Alloc>
    void
    vector<bool, _Alloc>::
    _M_insert_aux(iterator __position, bool __x)
    {
      if (this->_M_impl._M_finish._M_p != this->_M_impl._M_end_addr())
	{
	  std::copy_backward(__position, this->_M_impl._M_finish, 
			     this->_M_impl._M_finish + 1);
	  *__position = __x;
	  ++this->_M_impl._M_finish;
	}
      else
	{
	  const size_type __len =
	    _M_check_len(size_type(1), "vector<bool>::_M_insert_aux");
	  _Bit_pointer __q = this->_M_allocate(__len);
	  iterator __start(std::__addressof(*__q), 0);
	  iterator __i = _M_copy_aligned(begin(), __position, __start);
	  *__i++ = __x;
	  this->_M_impl._M_finish = std::copy(__position, end(), __i);
	  this->_M_deallocate();
	  this->_M_impl._M_end_of_storage = __q + _S_nword(__len);
	  this->_M_impl._M_start = __start;
	}
    }

  template<typename _Alloc>
    typename vector<bool, _Alloc>::iterator
    vector<bool, _Alloc>::
    _M_erase(iterator __position)
    {
      if (__position + 1 != end())
        std::copy(__position + 1, end(), __position);
      --this->_M_impl._M_finish;
      return __position;
    }

  template<typename _Alloc>
    typename vector<bool, _Alloc>::iterator
    vector<bool, _Alloc>::
    _M_erase(iterator __first, iterator __last)
    {
      if (__first != __last)
	_M_erase_at_end(std::copy(__last, end(), __first));
      return __first;
    }

#if __cplusplus >= 201103L
  template<typename _Alloc>
    bool
    vector<bool, _Alloc>::
    _M_shrink_to_fit()
    {
      if (capacity() - size() < int(_S_word_bit))
	return false;
      __try
	{
	  _M_reallocate(size());
	  return true;
	}
      __catch(...)
	{ return false; }
    }
#endif

_GLIBCXX_END_NAMESPACE_CONTAINER
} // namespace std

#if __cplusplus >= 201103L

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  template<typename _Alloc>
    size_t
    hash<_GLIBCXX_STD_C::vector<bool, _Alloc>>::
    operator()(const _GLIBCXX_STD_C::vector<bool, _Alloc>& __b) const noexcept
    {
      size_t __hash = 0;
      using _GLIBCXX_STD_C::_S_word_bit;
      using _GLIBCXX_STD_C::_Bit_type;

      const size_t __words = __b.size() / _S_word_bit;
      if (__words)
	{
	  const size_t __clength = __words * sizeof(_Bit_type);
	  __hash = std::_Hash_impl::hash(__b._M_impl._M_start._M_p, __clength);
	}

      const size_t __extrabits = __b.size() % _S_word_bit;
      if (__extrabits)
	{
	  _Bit_type __hiword = *__b._M_impl._M_finish._M_p;
	  __hiword &= ~((~static_cast<_Bit_type>(0)) << __extrabits);

	  const size_t __clength
	    = (__extrabits + __CHAR_BIT__ - 1) / __CHAR_BIT__;
	  if (__words)
	    __hash = std::_Hash_impl::hash(&__hiword, __clength, __hash);
	  else
	    __hash = std::_Hash_impl::hash(&__hiword, __clength);
	}

      return __hash;
    }

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std

#endif // C++11

#endif /* _VECTOR_TCC */
