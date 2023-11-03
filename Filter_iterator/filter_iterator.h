#pragma once
#include <iterator>
#include "filter_iter_exception.h"
#include "filter_iterator_conditions.h"
namespace iterators
{
	template <bool IsConst, class Iterator, class Predicate>
	class filter_iterator final
	{
		Iterator m_end;
		Iterator current_iterator;
		Predicate m_predicate;

		[[nodiscard]] Iterator next_suitable(const Iterator& begin) const noexcept
		{
			for (auto iterator = begin; iterator != m_end; ++iterator)
			{
				if (m_predicate(*iterator))
				{
					return iterator;
				}
			}
			return m_end;
		}
	public:
		using value_type = typename std::iterator_traits<Iterator>::value_type;
		using reference = typename std::iterator_traits<Iterator>::reference;
		using pointer = typename std::iterator_traits<Iterator>::pointer;
		using difference_type = typename std::iterator_traits<Iterator>::difference_type;
		using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
		using condition_ref = std::conditional_t<IsConst, std::add_const_t<std::remove_reference_t<reference>>&, reference>;

		filter_iterator() = default;
		filter_iterator(const Iterator& m_begin, const Iterator& m_end_, const Predicate& predicate_)
			:m_end(std::move(m_end_)), m_predicate(std::move(predicate_))
		{
			current_iterator = next_suitable(m_begin);
		}

		condition_ref operator*()
		{
			if (current_iterator == m_end)
			{
				throw error_dereferencing_end();
			}
			return *current_iterator;
		}

		filter_iterator& operator++()
		{
			if (current_iterator == m_end)
			{
				throw std::out_of_range("out of range");
			}
			++current_iterator;
			current_iterator = next_suitable(current_iterator);
			return *this;
		}

		filter_iterator& operator++(int)
		{
			if (current_iterator == m_end)
			{
				throw std::out_of_range("out of range");
			}
			auto next_iterator = next_suitable(current_iterator);
			++current_iterator;
			return next_iterator;
		}

		bool operator==(const filter_iterator& other) const noexcept
		{
			return current_iterator == other.current_iterator;
		}

		bool operator!=(const filter_iterator& other) const noexcept
		{
			return current_iterator != other.current_iterator;
		}

		difference_type operator-(const filter_iterator& other) const noexcept
		{
			return current_iterator - other.current_iterator;
		}
	};

	template < class Iterator, class Predicate>
		requires iter_condition::is_predicate<Predicate, typename std::iterator_traits<Iterator>::value_type>&&
			std::input_or_output_iterator<Iterator>
	class filter_range final
	{
		Iterator m_begin;
		Iterator m_end;
		Predicate m_predicate;
	public:
		using iterator = filter_iterator<false, Iterator, Predicate>;
		using const_iterator = filter_iterator<true, Iterator, Predicate>;
		
		explicit filter_range(const Iterator& begin_,const Iterator& end_, const Predicate& predicate) :
			m_begin(std::move(begin_)), m_end(std::move(end_)), m_predicate(predicate) {}

		[[nodiscard]] iterator begin() noexcept
		{
			return iterator(m_begin, m_end, m_predicate);
		}
		[[nodiscard]] const_iterator cbegin() const noexcept
		{
			return const_iterator(m_begin, m_end, m_predicate);
		}
		[[nodiscard]] iterator end() noexcept
		{
			return iterator(m_end, m_end, m_predicate);
		}
		[[nodiscard]] const_iterator cend() const noexcept
		{
			return const_iterator(m_end, m_end, m_predicate);
		}
	};
}
