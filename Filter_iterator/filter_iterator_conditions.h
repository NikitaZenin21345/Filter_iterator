#pragma once
#include <concepts>

template <class Predicate, class value_type >
concept Predicat_valid = requires(Predicate predicate, value_type value)
{
    {predicate.operator()(value)} -> std::same_as<bool>;
};