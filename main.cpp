#include "ip_pool.h"
#include <iostream>
#include <algorithm>
#include <range/v3/all.hpp>

int
main()
{
    ip_pool pool(std::cin);
    auto print = [](auto element){std::cout << element << std::endl;};

    pool.sort();

    ranges::for_each(pool, print);

    auto filteredPool = pool.getFilteredIP([]( const ip_pool::PoolRecordType& record) {return (record[0] == 1) ? true : false; });

    ranges::for_each(filteredPool, print);

    filteredPool = pool.getFilteredIP([](const ip_pool::PoolRecordType& record) {return  (record[0] == 46 && record[1] == 70) ? true : false; });

    ranges::for_each(filteredPool, print);

    filteredPool = pool.getFilteredIP([](const ip_pool::PoolRecordType& record) {return  std::any_of(record.begin(), record.end(), []( const auto v ){ return v == 46; }); });

    ranges::for_each(filteredPool, print);

    return 0;
}