#pragma once
#include <concepts>

template <class Predicate, class value_type >
concept Predicat_valid = requires(Predicate predicate,const Predicate const_predicate, value_type value)
{
    {predicate.operator()(value)} -> std::same_as<bool>;
    {const_predicate.operator()(value)} -> std::same_as<bool>;
};