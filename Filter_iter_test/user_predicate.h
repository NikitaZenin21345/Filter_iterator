#pragma once
template<class type>
struct is_positive_number {
    bool operator()(type x) { return 0 < x; }
};