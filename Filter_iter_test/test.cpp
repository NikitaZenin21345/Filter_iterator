#include "pch.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <forward_list>
#include <set>
#include "filter_iterator.h"
#include "tested_user_class.h"
#include <iterator>

constexpr is_positive_number<int> predicate_positive_int;
constexpr is_positive_number<double> predicate_positive_double;
constexpr is_even_number<int> predicate_even_int;
constexpr is_even_user_number<int> user_predicate_int;

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(FilterIterTest, VectorInt) {
	std::vector numbers = { -1, 0, 4, -3, 5, 8, 2 };
	const std::vector filtered_numbers = { 4 , 5, 8, 2 };
	std::vector<int> result = {};

	const iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	static_assert(std::is_same<decltype(*filter_range.cbegin()), const int&>::value);
	for (auto iter = filter_range.cbegin(); iter != filter_range.cend(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, VectorDouble) {
	const std::vector<double> numbers = { 1.2, 0, 4.9, -3, 5.9, 8.6, -2.4 };
	const std::vector<double> filtered_numbers = { 1.2 , 4.9, 5.9, 8.6 };
	std::vector<double> result = {};

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_double);
	static_assert(std::is_same<decltype(*filter_range.cbegin()), const double&>::value);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, VectorUserClass) {
	std::vector<user_class<int>> numbers = { {5}, {2}, {-3}, {4} };
	const std::vector<user_class<int>> filtered_numbers = { {2} , {4} };
	std::vector<user_class<int>> result = {};
	
	iterators::filter_range filter_range(numbers.begin(), numbers.end(), user_predicate_int);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, ArrayUserClass) {
	std::vector<user_class<int>> numbers = { {5}, {2}, {-3}, {4} };
	const std::vector<user_class<int>> filtered_numbers = { {2} , {4} };
	std::vector<user_class<int>> result = {};

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), user_predicate_int);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	for (auto i = 0; i != 2; ++i)
	{
		EXPECT_TRUE(result[i] == filtered_numbers[i]);
	}
}

TEST(FilterIterTest, ForwardListint) {
	std::forward_list numbers = { -1, 0, 4, -3, 5, 8, 2 };
	const std::forward_list filtered_numbers = { 2, 8, 5, 4 };
	std::forward_list<int> result = {};

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_front(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, ForwardListUserClass) {
	std::forward_list<user_class<int>> numbers = { {5}, {2}, {-3}, {4} };
	std::forward_list<user_class<int>> filtered_numbers = { {4}, {2} };
	std::forward_list<user_class<int>> result = {};

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), user_predicate_int);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_front(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, CopyVector) {
	std::vector numbers = { -1, 0, 4, -3, 5, 8, 2 };
	const std::vector filtered_numbers = { 4, 5 ,8,2 };
	std::vector<int> result = { };
	auto finded_element = std::find(numbers.begin(), numbers.end(), 5);
	EXPECT_TRUE(*finded_element == 5);
	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	std::copy(filter_range.begin(), filter_range.end(), std::back_inserter(result));
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, FindVectorIterator) {
	std::vector numbers = { -1, 0, 4, -3, 5, 8, 2 };
	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	auto finded_element = std::find(filter_range.begin(), filter_range.end(), 5);
	EXPECT_TRUE(*finded_element == 5);
}

TEST(FilterIterTest, ConstVectorIterator) {
	const std::vector numbers = { -1, 0, 4, -3, 5, 8, 2 };
	const std::vector filtered_numbers = { 4, 5 ,8,2 };
	std::vector<int> result = { };
	
	const iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	static_assert(std::is_same<decltype(*filter_range.cbegin()), const int&>::value);

	for (auto iter = filter_range.cbegin(); iter != filter_range.cend(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, CopyForwardList) {
	std::forward_list numbers = { -1, 0, 4, -3, 5, 8, 2 };
	const std::forward_list filtered_numbers = {2, 8, 5, 4 };
	std::forward_list<int> result = { };

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	std::copy(filter_range.begin(), filter_range.end(), std::front_inserter(result));
	EXPECT_TRUE(result == (filtered_numbers));
}

TEST(FilterIterTest, TransformVector) {
	std::vector numbers = { -1, 0, 4, -3, 5, 8, 2 };
	const std::vector filtered_numbers = { 16, 25 ,64, 4 };
	std::vector<int> result = { };

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	std::transform(filter_range.begin(), filter_range.end(),
		std::back_inserter(result), [](int x) { return x * x; });
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, SetUserClass) {
	std::set<user_class<int>> numbers = {{5}, {2}, {-3}, {4}};
	const std::set filtered_numbers = { user_class(2) , user_class(4) };
	std::set<user_class<int>> result = {};

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), user_predicate_int);

	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.insert(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, FilterIterFilterIter) {
	std::vector  numbers = { -1, 0, 4, -3, 5, 8, 11, 2 };
	std::vector filtered_numbers = { 4, 8, 2 };
	std::vector<int> result = {};

	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	iterators::filter_range iter_filter_range(filter_range.begin(), filter_range.end(), predicate_even_int);

	for (auto iter = iter_filter_range.begin(); iter != iter_filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterConceptTest, PredicatValid) {
	EXPECT_TRUE((iter_condition::is_predicate<is_even_number<int>, int>));
	EXPECT_FALSE((iter_condition::is_predicate<is_even_number<int>, user_class<int>>));
	EXPECT_TRUE((iter_condition::is_predicate<is_positive_number<user_class<int>>, user_class<int>>));
}

TEST(FilterIterTest, ExceptionCatch) {
	std::vector numbers = { -1, 0, 4, -3, 5, 8, 11, 2 };
	
	iterators::filter_range filter_range(numbers.begin(), numbers.end(), predicate_positive_int);
	auto iter = filter_range.begin();
	while ( iter != filter_range.end() )
	{
		++iter;
	}
	try
	{
		++iter;
	}
	catch ([[maybe_unused]] std::out_of_range& first_error)
	{
		try
		{
			*iter;
		}
		catch ([[maybe_unused]] error_dereferencing_end& second_error)
		{
			SUCCEED();
			return;
		}
		FAIL();
	}
	FAIL();
}