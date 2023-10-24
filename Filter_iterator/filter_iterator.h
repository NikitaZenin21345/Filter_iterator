#pragma once
#include <iterator>
#include "filter_iter_exception.h"
#include "filter_iterator_conditions.h"

namespace iterators
{
	template <class Iterator, class Predicate>
		requires iter_condition::is_predicate<Predicate, typename std::iterator_traits<Iterator>::value_type>
	class filter_iterator final
	{
	public:
		using value_type = typename std::iterator_traits<Iterator>::value_type;
		using reference = typename std::iterator_traits<Iterator>::reference;
		using pointer = typename std::iterator_traits<Iterator>::pointer;
		using difference_type = typename std::iterator_traits<Iterator>::difference_type;
		using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;

		filter_iterator() = default;
		filter_iterator(Iterator begin_, Iterator end_, Predicate predicate_)
		{
			iterator_end = end_;
			current_iterator = next_suitable(begin_);
			m_predicate = predicate_;
		}
		reference operator*() const 
		{
			if(current_iterator == iterator_end)
			{
				throw error_dereferencing_end();
			}
			return *current_iterator;
		}
		filter_iterator& operator++()
		{
			if (current_iterator == iterator_end)
			{
				throw std::out_of_range("out of range");
			}
			++current_iterator;
			current_iterator = next_suitable(current_iterator);
			return *this;
		}
		bool operator==(const filter_iterator& other) const noexcept
		{
			return current_iterator == other.current_iterator;
		}

		difference_type operator-(const filter_iterator& other) const {
			return current_iterator - other.current_iterator;
		}

	private:
		[[nodiscard]] Iterator next_suitable(const Iterator& begin) const
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
		Iterator current_iterator;
		Iterator iterator_end;
	};

	template <class Iterator>
	class range final
	{
		Iterator first;
		Iterator last;
	public:
		explicit range(Iterator first_, Iterator last_ = Iterator()) :first(first_), last(last_) {}
		[[nodiscard]] Iterator begin() const noexcept
		{
			return first;
		}
		[[nodiscard]] Iterator begin() noexcept
		{
			return first;
		}
		[[nodiscard]] Iterator end() const noexcept
		{
			return last;
		}
		[[nodiscard]] Iterator end() noexcept
		{
			return last;
		}
	};

	template <class Iterator, class Predicate>
		requires iter_condition::is_predicate<Predicate, typename std::iterator_traits<Iterator>::value_type>
	class filter_range final
	{
		range<Iterator> m_range;
		Predicate m_predicate;
	public:
		explicit filter_range(const range<Iterator>& range_,const Predicate& predicate) : m_range(range_), m_predicate(predicate) {}
		filter_iterator<Iterator, Predicate> begin()  noexcept
		{
			return filter_iterator<Iterator, Predicate>(m_range.begin(), m_range.end(), m_predicate);
		}
		[[nodiscard]] filter_iterator<Iterator, Predicate> begin() const noexcept
		{
			return filter_iterator<Iterator, Predicate>(m_range.begin(), m_range.end(), m_predicate);
		}
		filter_iterator<Iterator, Predicate> end() noexcept
		{
			return filter_iterator<Iterator, Predicate>(m_range.end(), m_range.end(), m_predicate);
		}
		[[nodiscard]] filter_iterator<Iterator, Predicate> end() const noexcept
		{
			return filter_iterator<Iterator, Predicate>(m_range.end(), m_range.end(), m_predicate);
		}
	};
}
