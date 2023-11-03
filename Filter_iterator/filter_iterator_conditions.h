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


}

