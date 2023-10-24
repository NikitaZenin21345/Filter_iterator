#pragma once
#include <concepts>
#include <type_traits>

namespace iter_condition
{
	template <class Predicate, class value_type >
	concept is_predicate = std::is_copy_constructible_v<Predicate> && requires(Predicate predicate, const Predicate const_predicate, const  value_type value)
	{
		{predicate.operator()(value)} -> std::same_as<bool>;
		{const_predicate.operator()(value)} -> std::same_as<bool>;
	};

	template <class Iterator>
	concept is_iter = std::is_base_of_v<std::input_iterator_tag,
		typename  std::iterator_traits<Iterator>::iterator_category> &&
			std::is_copy_constructible_v<Iterator> && requires(Iterator iter, Iterator other)
	{

		{iter.operator++()} -> std::same_as<Iterator&>;
		{iter.operator*()} -> std::same_as<typename std::iterator_traits<Iterator>::value_type&>;
		{iter.operator==(other)} -> std::same_as<bool>;
	};

}

