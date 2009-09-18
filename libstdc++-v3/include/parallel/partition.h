// -*- C++ -*-

// Copyright (C) 2007, 2008, 2009 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation; either version 3, or (at your option) any later
// version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file parallel/partition.h
 *  @brief Parallel implementation of std::partition(),
 *  std::nth_element(), and std::partial_sort().
 *  This file is a GNU parallel extension to the Standard C++ Library.
 */

// Written by Johannes Singler and Felix Putze.

#ifndef _GLIBCXX_PARALLEL_PARTITION_H
#define _GLIBCXX_PARALLEL_PARTITION_H 1

#include <parallel/basic_iterator.h>
#include <parallel/sort.h>
#include <parallel/random_number.h>
#include <bits/stl_algo.h>
#include <parallel/parallel.h>

/** @brief Decide whether to declare certain variables volatile. */
#define _GLIBCXX_VOLATILE volatile

namespace __gnu_parallel
{
/** @brief Parallel implementation of std::partition.
  *  @param __begin Begin iterator of input sequence to split.
  *  @param __end End iterator of input sequence to split.
  *  @param __pred Partition predicate, possibly including some kind of pivot.
  *  @param __num_threads Maximum number of threads to use for this task.
  *  @return Number of elements not fulfilling the predicate. */
template<typename _RAIter, typename _Predicate>
  typename std::iterator_traits<_RAIter>::difference_type
  __parallel_partition(_RAIter __begin, _RAIter __end,
                     _Predicate __pred, _ThreadIndex __num_threads)
  {
    typedef std::iterator_traits<_RAIter> _TraitsType;
    typedef typename _TraitsType::value_type _ValueType;
    typedef typename _TraitsType::difference_type _DifferenceType;

    _DifferenceType __n = __end - __begin;

    _GLIBCXX_CALL(__n)

    const _Settings& __s = _Settings::get();

    // Shared.
    _GLIBCXX_VOLATILE _DifferenceType __left = 0, __right = __n - 1;
    _GLIBCXX_VOLATILE _DifferenceType __leftover_left, __leftover_right;
    _GLIBCXX_VOLATILE _DifferenceType __leftnew, __rightnew;

    bool* __reserved_left = NULL, * __reserved_right = NULL;

    _DifferenceType __chunk_size;

    omp_lock_t __result_lock;
    omp_init_lock(&__result_lock);

    //at least two chunks per thread
    if(__right - __left + 1 >= 2 * __num_threads * __chunk_size)
#   pragma omp parallel num_threads(__num_threads)
      {
#       pragma omp single
          {
            __num_threads = omp_get_num_threads();
            __reserved_left = new bool[__num_threads];
            __reserved_right = new bool[__num_threads];

            if (__s.partition_chunk_share > 0.0)
              __chunk_size = std::max<_DifferenceType>(
                __s.partition_chunk_size,
                (double)__n * __s.partition_chunk_share /
                    (double)__num_threads);
            else
              __chunk_size = __s.partition_chunk_size;
          }

        while (__right - __left + 1 >= 2 * __num_threads * __chunk_size)
          {
#           pragma omp single
              {
                _DifferenceType __num_chunks
                    = (__right - __left + 1) / __chunk_size;

                for (int __r = 0; __r < __num_threads; ++__r)
                  {
                    __reserved_left[__r] = false;
                    __reserved_right[__r] = false;
                  }
                __leftover_left = 0;
                __leftover_right = 0;
              } //implicit barrier

            // Private.
            _DifferenceType __thread_left, __thread_left_border,
                            thread_right, __thread_right_border;
            __thread_left = __left + 1;

            // Just to satisfy the condition below.
            __thread_left_border = __thread_left - 1;
            thread_right = __n - 1;
            __thread_right_border = thread_right + 1;

            bool __iam_finished = false;
            while (!__iam_finished)
              {
                if (__thread_left > __thread_left_border)
                  {
                    omp_set_lock(&__result_lock);
                    if (__left + (__chunk_size - 1) > __right)
                      __iam_finished = true;
                    else
                      {
                        __thread_left = __left;
                        __thread_left_border = __left + (__chunk_size - 1);
                        __left += __chunk_size;
                      }
                    omp_unset_lock(&__result_lock);
                  }

                if (thread_right < __thread_right_border)
                  {
                    omp_set_lock(&__result_lock);
                    if (__left > __right - (__chunk_size - 1))
                      __iam_finished = true;
                    else
                      {
                        thread_right = __right;
                        __thread_right_border = __right - (__chunk_size - 1);
                        __right -= __chunk_size;
                      }
                    omp_unset_lock(&__result_lock);
                  }

                if (__iam_finished)
                  break;

                // Swap as usual.
                while (__thread_left < thread_right)
                  {
                    while (__pred(__begin[__thread_left])
                            && __thread_left <= __thread_left_border)
                      ++__thread_left;
                    while (!__pred(__begin[thread_right])
                            && thread_right >= __thread_right_border)
                      --thread_right;

                    if (__thread_left > __thread_left_border
                        || thread_right < __thread_right_border)
                      // Fetch new chunk(__s).
                      break;

                    std::swap(__begin[__thread_left], __begin[thread_right]);
                    ++__thread_left;
                    --thread_right;
                  }
              }

            // Now swap the leftover chunks to the right places.
            if (__thread_left <= __thread_left_border)
#             pragma omp atomic
              ++__leftover_left;
            if (thread_right >= __thread_right_border)
#             pragma omp atomic
              ++__leftover_right;

#           pragma omp barrier

#           pragma omp single
              {
                __leftnew = __left - __leftover_left * __chunk_size;
                __rightnew = __right + __leftover_right * __chunk_size;
              }

#           pragma omp barrier

            // <=> __thread_left_border + (__chunk_size - 1) >= __leftnew
            if (__thread_left <= __thread_left_border
                && __thread_left_border >= __leftnew)
              {
                // Chunk already in place, reserve spot.
                __reserved_left
                  [(__left - (__thread_left_border + 1)) / __chunk_size]
                    = true;
              }

            // <=> __thread_right_border - (__chunk_size - 1) <= __rightnew
            if (thread_right >= __thread_right_border
                && __thread_right_border <= __rightnew)
              {
                // Chunk already in place, reserve spot.
                __reserved_right[((__thread_right_border - 1) - __right)
                               / __chunk_size] = true;
              }

#           pragma omp barrier

            if (__thread_left <= __thread_left_border
                && __thread_left_border < __leftnew)
              {
                // Find spot and swap.
                _DifferenceType __swapstart = -1;
                omp_set_lock(&__result_lock);
                for (int __r = 0; __r < __leftover_left; ++__r)
                  if (!__reserved_left[__r])
                    {
                      __reserved_left[__r] = true;
                      __swapstart = __left - (__r + 1) * __chunk_size;
                      break;
                    }
                omp_unset_lock(&__result_lock);

#if _GLIBCXX_ASSERTIONS
                _GLIBCXX_PARALLEL_ASSERT(__swapstart != -1);
#endif

                std::swap_ranges(__begin + __thread_left_border
                                 - (__chunk_size - 1),
                                 __begin + __thread_left_border + 1,
                                 __begin + __swapstart);
              }

            if (thread_right >= __thread_right_border
                && __thread_right_border > __rightnew)
              {
                // Find spot and swap
                _DifferenceType __swapstart = -1;
                omp_set_lock(&__result_lock);
                for (int __r = 0; __r < __leftover_right; ++__r)
                  if (!__reserved_right[__r])
                    {
                      __reserved_right[__r] = true;
                      __swapstart = __right + __r * __chunk_size + 1;
                      break;
                    }
                omp_unset_lock(&__result_lock);

#if _GLIBCXX_ASSERTIONS
                _GLIBCXX_PARALLEL_ASSERT(__swapstart != -1);
#endif

                std::swap_ranges(
                    __begin + __thread_right_border,
                    __begin + __thread_right_border + __chunk_size,
                    __begin + __swapstart);
              }
#if _GLIBCXX_ASSERTIONS
#             pragma omp barrier

#             pragma omp single
                {
                  for (int __r = 0; __r < __leftover_left; ++__r)
                    _GLIBCXX_PARALLEL_ASSERT(__reserved_left[__r]);
                  for (int __r = 0; __r < __leftover_right; ++__r)
                    _GLIBCXX_PARALLEL_ASSERT(__reserved_right[__r]);
                }

#             pragma omp barrier
#endif

#             pragma omp barrier

              __left = __leftnew;
              __right = __rightnew;
          }
#         pragma omp flush(__left, __right)
      } // end "recursion" //parallel

    _DifferenceType __final_left = __left, __final_right = __right;

    while (__final_left < __final_right)
      {
        // Go right until key is geq than pivot.
        while (__pred(__begin[__final_left]) && __final_left < __final_right)
          ++__final_left;

        // Go left until key is less than pivot.
        while (!__pred(__begin[__final_right]) && __final_left < __final_right)
          --__final_right;

        if (__final_left == __final_right)
          break;
        std::swap(__begin[__final_left], __begin[__final_right]);
        ++__final_left;
        --__final_right;
      }

    // All elements on the left side are < piv, all elements on the
    // right are >= piv
    delete[] __reserved_left;
    delete[] __reserved_right;

    omp_destroy_lock(&__result_lock);

    // Element "between" __final_left and __final_right might not have
    // been regarded yet
    if (__final_left < __n && !__pred(__begin[__final_left]))
      // Really swapped.
      return __final_left;
    else
      return __final_left + 1;
  }

/**
  *  @brief Parallel implementation of std::nth_element().
  *  @param __begin Begin iterator of input sequence.
  *  @param __nth _Iterator of element that must be in position afterwards.
  *  @param __end End iterator of input sequence.
  *  @param __comp Comparator.
  */
template<typename _RAIter, typename _Compare>
  void 
  parallel_nth_element(_RAIter __begin, _RAIter __nth, 
                       _RAIter __end, _Compare __comp)
  {
    typedef std::iterator_traits<_RAIter> _TraitsType;
    typedef typename _TraitsType::value_type _ValueType;
    typedef typename _TraitsType::difference_type _DifferenceType;

    _GLIBCXX_CALL(__end - __begin)

    _RAIter __split;
    _RandomNumber __rng;

    _DifferenceType minimum_length =
      std::max<_DifferenceType>(2, _Settings::get().partition_minimal_n);

    // Break if input range to small.
    while (static_cast<_SequenceIndex>(__end - __begin) >= minimum_length)
      {
        _DifferenceType __n = __end - __begin;

        _RAIter __pivot_pos = __begin +  __rng(__n);

        // Swap __pivot_pos value to end.
        if (__pivot_pos != (__end - 1))
          std::swap(*__pivot_pos, *(__end - 1));
        __pivot_pos = __end - 1;

        // XXX _Compare must have first__ValueType, second__ValueType,
        // _ResultType
        // _Compare == __gnu_parallel::_Lexicographic<S, int,
        // __gnu_parallel::_Less<S, S> >
        // __pivot_pos == std::pair<S, int>*
        // XXX binder2nd only for _RAIters??
        __gnu_parallel::binder2nd<_Compare, _ValueType, _ValueType, bool>
          __pred(__comp, *__pivot_pos);

        // Divide, leave pivot unchanged in last place.
        _RAIter __split_pos1, __split_pos2;
        __split_pos1 = __begin
                       + __parallel_partition(__begin, __end - 1, __pred,
                                              __get_max_threads());

        // Left side: < __pivot_pos; __right side: >= __pivot_pos

        // Swap pivot back to middle.
        if (__split_pos1 != __pivot_pos)
          std::swap(*__split_pos1, *__pivot_pos);
        __pivot_pos = __split_pos1;

        // In case all elements are equal, __split_pos1 == 0
        if ((__split_pos1 + 1 - __begin) < (__n >> 7)
            || (__end - __split_pos1) < (__n >> 7))
          {
            // Very unequal split, one part smaller than one 128th
            // elements not strictly larger than the pivot.
            __gnu_parallel::__unary_negate<__gnu_parallel::
              __binder1st<_Compare, _ValueType, _ValueType, bool>, _ValueType>
              __pred(__gnu_parallel::__binder1st<_Compare, _ValueType,
                   _ValueType, bool>(__comp, *__pivot_pos));

            // Find other end of pivot-equal range.
            __split_pos2 = __gnu_sequential::partition(__split_pos1 + 1,
                                                     __end, __pred);
          }
        else
          // Only skip the pivot.
          __split_pos2 = __split_pos1 + 1;

        // Compare iterators.
        if (__split_pos2 <= __nth)
          __begin = __split_pos2;
        else if (__nth < __split_pos1)
          __end = __split_pos1;
        else
          break;
      }

    // Only at most _Settings::partition_minimal_n __elements __left.
    __gnu_sequential::sort(__begin, __end, __comp);
  }

/** @brief Parallel implementation of std::partial_sort().
*  @param __begin Begin iterator of input sequence.
*  @param __middle Sort until this position.
*  @param __end End iterator of input sequence.
*  @param __comp Comparator. */
template<typename _RAIter, typename _Compare>
  void
  parallel_partial_sort(_RAIter __begin,
                        _RAIter __middle,
                        _RAIter __end, _Compare __comp)
  {
    parallel_nth_element(__begin, __middle, __end, __comp);
    std::sort(__begin, __middle, __comp);
  }

} //namespace __gnu_parallel

#undef _GLIBCXX_VOLATILE

#endif /* _GLIBCXX_PARALLEL_PARTITION_H */
