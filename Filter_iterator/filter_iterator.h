#pragma once
#include <iterator>
#include <type_traits>
#include "filter_iterator_conditions.h"

namespace iterators
{
	namespace impl
	{
        template <class Iterator, class Predicate>
            requires Predicat_valid<Predicate, typename std::iterator_traits<Iterator>::value_type>
        class filter_iterator final
        {
        public:
            using value_type = typename std::iterator_traits<Iterator>::value_type;
            using reference = typename std::iterator_traits<Iterator>::reference;
            using pointer = typename std::iterator_traits<Iterator>::pointer;
            using difference_type = typename std::iterator_traits<Iterator>::difference_type;
            using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
            filter_iterator(Iterator begin_, Iterator end_, Predicate predicate_ = std::less<>())
            {
                iterator_end = end_;
                iterator_begin = next_suitable(begin_);
                m_predicate = predicate_;
            }
            reference operator*() const noexcept
            {
                return *iterator_begin;
            }
            filter_iterator& operator++()
            {
                ++iterator_begin;
                iterator_begin = next_suitable(iterator_begin);
                return *this;
            }
            bool operator==(const filter_iterator& other) const noexcept
            {
                return iterator_begin == other.iterator_begin;
            }
        private:
            Iterator next_suitable(const Iterator& begin) const
            {
                for (auto iterator = begin; iterator != iterator_end; ++iterator)
                {
                    if (m_predicate(*iterator))
                    {
                        return iterator;
                    }
                }
                return iterator_end;
            }
            Predicate m_predicate;
            Iterator iterator_begin;
            Iterator iterator_end;
        };
	}
   

    template <class Iterator>
    class range final
    {
        Iterator first;
        Iterator last;
    public:
        range(Iterator first_, Iterator last_ = Iterator()):first(first_), last(last_){}
        Iterator begin() const noexcept
        {
            return first;
        }
        Iterator end() const noexcept
        {
            return last;
        }
    };

    template <class Iterator, class Predicate>
        requires Predicat_valid<Predicate, typename std::iterator_traits<Iterator>::value_type>
    class filter_range final
    {
        range<Iterator> m_range;
        Predicate m_predicate;
    public:
        explicit filter_range(const range<Iterator>& range_, Predicate predicate = std::less<>()): m_range(range_), m_predicate(predicate){}
        impl::filter_iterator<Iterator, Predicate> begin()  noexcept
        {
            return impl::filter_iterator<Iterator, Predicate>(m_range.begin(), m_range.end(), m_predicate);
        }
        impl::filter_iterator<Iterator, Predicate> end() noexcept
        {
            return impl::filter_iterator<Iterator, Predicate>(m_range.end(), m_range.end(), m_predicate);
        }
    };
}
