#include "pch.h"
#include <algorithm>
#include <iterator>
#include <vector>
#include <forward_list>
#include <set>
#include "filter_iterator.h"
#include "user_predicates.h"
#include "test_user_class.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(FilterIterTest, VectorInt) {
	std::vector<int> numbers = { -1, 0, 4, -3, 5, 8, 2 };
	std::vector<int> filtered_numbers = { 4 , 5, 8, 2 };
	std::vector<int> result = {};
	is_positive_number<int> predicate;
	iterators::range range(numbers.begin(), numbers.end());
	iterators::filter_range filter_range( range, predicate);
	for (auto iter = filter_range.begin() ;iter != filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, VectorDouble) {
	std::vector<double> numbers = { 1.2, 0, 4.9, -3, 5.9, 8.6, -2.4 };
	std::vector<double> filtered_numbers = { 1.2 , 4.9, 5.9, 8.6 };
	std::vector<double> result = {};
	is_positive_number<double> predicate;
	iterators::range range(numbers.begin(), numbers.end());
	iterators::filter_range filter_range(range, predicate);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, VectorUserClass) {
	std::vector<user_class<int>> numbers = { user_class(5),user_class(2) , user_class(-3),user_class(4) };
	std::vector<user_class<int>> filtered_numbers = { user_class(2) , user_class(4) };
	std::vector<user_class<int>> result = {};
	is_even_number<int> predicate;
	iterators::range range(numbers.begin(), numbers.end());
	iterators::filter_range filter_range(range, predicate);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}



TEST(FilterIterTest, ArrayUserClass) {
	user_class<int> numbers[] = { user_class(5), user_class(2), user_class(-3),user_class(4) };
	user_class<int> filtered_numbers[] = { user_class(2) , user_class(4) };
	std::vector<user_class<int>> result = {};
	is_even_number<int> predicate;
	iterators::range range(std::begin(numbers), std::end(numbers));
	iterators::filter_range filter_range(range, predicate);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_back(*iter);
	}
	for (auto i = 0; i != 2; ++i)
	{
		result[i] == filtered_numbers[i];
	}
}


TEST(FilterIterTest, ForwardListint) {
	std::forward_list<int> numbers = { -1, 0, 4, -3, 5, 8, 2 };
	std::forward_list<int> filtered_numbers = { 2, 8, 5, 4};
	std::forward_list<int> result = {};
	is_positive_number<int> predicate;
	iterators::range range(numbers.begin(), numbers.end());
	iterators::filter_range filter_range(range, predicate);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_front(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);

}

TEST(FilterIterTest, ForwardListUserClass) {
	std::forward_list<user_class<int>> numbers = { user_class(5),user_class(2) , user_class(-3),user_class(4) };
	std::forward_list<user_class<int>> filtered_numbers = { user_class(4) , user_class(2) };
	std::forward_list<user_class<int>> result = {};
	is_even_number<int> predicate;
	iterators::range range(numbers.begin(), numbers.end());
	iterators::filter_range filter_range(range, predicate);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.push_front(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}


TEST(FilterIterTest, SetInt) {
	std::set<int> numbers = { -1, 0, 4, -3, 5, 8, 2 };
	std::set<int> filtered_numbers = { 5, 4 ,8,2};
	std::set<int> result = {};
	is_positive_number<int> predicate;
	iterators::range range(numbers.begin(), numbers.end());
	iterators::filter_range filter_range(range, predicate);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.insert(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}

TEST(FilterIterTest, SetUserClass) {
	std::set<user_class<int>> numbers = { user_class(5),user_class(2) , user_class(-3),user_class(4) };
	std::set<user_class<int>> filtered_numbers = { user_class(2) , user_class(4) };
	std::set<user_class<int>> result = {};
	is_even_number<int> predicate;
	iterators::range range(numbers.begin(), numbers.end());
	iterators::filter_range filter_range(range, predicate);
	for (auto iter = filter_range.begin(); iter != filter_range.end(); ++iter)
	{
		result.insert(*iter);
	}
	EXPECT_TRUE(result == filtered_numbers);
}