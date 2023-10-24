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
class is_even_user_number
{
public:
	bool operator()(user_class<value_type> value) const
	{
		return value.get_value() % 2 == 0;
	}
};

template<class value_type>
class is_even_number
{
public:
	bool operator()(value_type value) const
	{
		return value % 2 == 0;
	}
};

template<class type>
class is_positive_number {
public:
	bool operator()(const type& x) const { return 0 < x; }
};
