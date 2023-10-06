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
	std::vector<int> numbers_ = { -1, 0, 4, -3, 5, 8, 2 };
	std::vector<int> test_vector = { 4 , 5, 8, 2 };
	std::vector<int> result = {};
	const int N = 6;
	is_positive_number<int> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), std::begin(numbers_) + N + 1);
	iterators::filter_iterator filter_iter_last(predicate, std::begin(numbers_) + N + 1, std::begin(numbers_) + N + 1);

	std::copy(filter_iter_first, filter_iter_last, std::back_inserter(result));
	EXPECT_TRUE(result == test_vector);
}

TEST(FilterIterTest, VectorDouble) {
	std::vector<double> numbers_ = { 1.2, 0, 4.9, -3, 5.9, 8.6, -2.4 };
	std::vector<double> test_vector = { 1.2 , 4.9, 5.9, 8.6 };
	std::vector<double> result = {};
	const int N = 6;
	is_positive_number<double> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), std::begin(numbers_) + N);
	iterators::filter_iterator filter_iter_last(predicate, std::begin(numbers_) + N, std::begin(numbers_) + N);

	std::copy(filter_iter_first, filter_iter_last, std::back_inserter(result));
	EXPECT_TRUE(result == test_vector);
}

TEST(FilterIterTest, VectorUserClass) {
	std::vector<user_class<int>> numbers_ = { user_class(5),user_class(2) , user_class(-3),user_class(4) };
	std::vector<user_class<int>> test_vector = { user_class(5) , user_class(-3) };
	std::vector<user_class<int>> result = {};
	const int N = 4;
	is_even_number<int> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), std::begin(numbers_) + N);
	iterators::filter_iterator filter_iter_last(predicate, std::begin(numbers_) + N, std::begin(numbers_) + N);

	std::copy(filter_iter_first, filter_iter_last, std::back_inserter(result));
	EXPECT_TRUE(result == test_vector);
}



TEST(FilterIterTest, ArrayUserClass) {
	user_class<int> numbers_[] = { user_class(5), user_class(2), user_class(-3),user_class(4) };
	user_class<int> test_numbers_[] = { user_class(5) , user_class(0) };
	user_class<int> result[] = { user_class(0) , user_class(0) };
	const int N = 3;
	is_even_number<int> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), std::begin(numbers_) + 2);
	iterators::filter_iterator filter_iter_last(predicate, std::begin(numbers_) + 2, std::begin(numbers_) + 2);

	std::copy(filter_iter_first, filter_iter_last, std::begin(result));
	EXPECT_TRUE(result[0] == test_numbers_[0] &&
		result[1] == test_numbers_[1]);
}

//TEST(FilterIterTest, ArrayInt) {//!!
//	int numbers_[] = { 0, -1, 4, -3, 5, 8, -2 };
//	int test_numbers_[] = { 4 , 5, 8 };
//	int result[] = { 0, 0, 0 };
//	const int N = 6;
//	is_positive_number<int> predicate;
//	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_));
//	iterators::filter_iterator filter_iter_last(predicate, std::begin(numbers_) + N, std::begin(numbers_) + N);
//
//	std::copy(filter_iter_first, filter_iter_last, std::begin(result));
//	EXPECT_TRUE(result[0] == test_numbers_[0] &&
//		result[1] == test_numbers_[1] &&
//		result[2] == test_numbers_[2]);
//}

TEST(FilterIterTest, ForwardListint) {
	std::forward_list<int> numbers_ = { -1, 0, 4, -3, 5, 8, 2 };
	std::forward_list<int> test_vector = { 5, 4 };
	auto end_list = std::begin(numbers_);
	for (auto counter = 0; counter != 5; ++counter) { ++end_list; }
	std::forward_list<int> result = {};
	is_positive_number<int> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), end_list);
	iterators::filter_iterator filter_iter_last(predicate, end_list, end_list);

	for (; filter_iter_first.base() != filter_iter_first.end(); ++filter_iter_first)
	{
		result.push_front(*filter_iter_first.base());
	}
	EXPECT_TRUE(result == test_vector);

}

TEST(FilterIterTest, ForwardListUserClass) {
	std::forward_list<user_class<int>> numbers_ = { user_class(5),user_class(2) , user_class(-3),user_class(4) };
	std::forward_list<user_class<int>> test_vector = { user_class(-3) , user_class(5) };
	std::forward_list<user_class<int>> result = {};
	is_even_number<int> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), std::end(numbers_));

	for (; filter_iter_first.base() != filter_iter_first.end(); ++filter_iter_first)
	{
		result.push_front(*filter_iter_first.base());
	}
	EXPECT_TRUE(result == test_vector);
}


TEST(FilterIterTest, SetInt) {
	std::set<int> numbers_ = { -1, 0, 4, -3, 5, 8, 2 };
	std::set<int> test_vector = { 5, 4 ,8,2};
	std::set<int> result = {};
	is_positive_number<int> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), std::end(numbers_));

	for (; filter_iter_first.base() != filter_iter_first.end(); ++filter_iter_first)
	{
		result.insert(*filter_iter_first.base());
	}
	EXPECT_TRUE(result == test_vector);
}

TEST(FilterIterTest, SetUserClass) {
	std::set<user_class<int>> numbers_ = { user_class(5),user_class(2) , user_class(-3),user_class(4) };
	std::set<user_class<int>> test_vector = { user_class(-3) , user_class(5) };
	std::set<user_class<int>> result = {};
	is_even_number<int> predicate;
	iterators::filter_iterator filter_iter_first(predicate, std::begin(numbers_), std::end(numbers_));

	for (; filter_iter_first.base() != filter_iter_first.end(); ++filter_iter_first)
	{
		result.insert(*filter_iter_first.base());
	}
	EXPECT_TRUE(result == test_vector);
}