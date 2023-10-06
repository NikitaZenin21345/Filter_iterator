#pragma once

template<typename value_type>
class user_class
{
	value_type value;
public:
	user_class(value_type value_) :value(value_) {}
	bool operator<(const user_class other) const
	{
		return value < other.value;
	}
	bool operator==(user_class other) const
	{
		return value == other.value;
	}
	value_type get_value() const
	{
		return value;
	}
};

template<class value_type>
class is_even_number
{
public:
	bool operator()(user_class<value_type> value) const
	{
		return value.get_value() % 2;
	}
};

