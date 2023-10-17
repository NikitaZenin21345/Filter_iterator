#pragma once
template<class type>
struct is_positive_number {
    bool operator()(type x) const{ return 0 < x; }
};