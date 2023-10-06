#pragma once
#include <iterator>
#include <type_traits>
#include "filter_iterator_conditions.h"

namespace iterators
{
    template <class Predicate, class Iterator>
    requires Predicat_valid<Predicate, typename std::iterator_traits<Iterator>::value_type>
    class filter_iterator final
    {
    public:
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using reference = typename std::iterator_traits<Iterator>::reference;
        using pointer = typename std::iterator_traits<Iterator>::pointer;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
        filter_iterator(Predicate user_predicate, Iterator iterator_):
            m_predicate(user_predicate)
        {
            iterator = next_suitable(iterator_);
        }
        filter_iterator(Iterator iterator):filter_iterator(std::less<>(), iterator) {}
        [[nodiscard]] Predicate predicate() const noexcept
        {
            return m_predicate;
        }
        reference operator*() const noexcept
        {
            return *iterator;
        }
        filter_iterator& operator++()
        {
            ++iterator;
            iterator = next_suitable(iterator);
            return *this;
        }
        bool operator==(const filter_iterator& other) const noexcept
        {
            return iterator == other.iterator;
        }
    private:
        Iterator next_suitable(const Iterator& begin) 
        {
            auto start = begin;
            while(!m_predicate(*start))
            {
                ++start;
            }
            return start;
        }
        Predicate m_predicate;
        Iterator iterator;  
    };

    template <class Iterator>
    class filter_range final
    {
        Iterator first;
        Iterator last;
    public:
        filter_range(Iterator first_, Iterator last_): first(first_), last(last_) {}
        Iterator begin() const noexcept
        {
            return first;
        }
        Iterator end() const noexcept
        {
            return last;
        }
    };
}
