#define BOOST_TEST_MODULE ip_pool_test_module

#include "ip_pool.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( ip_pool_test_suite )


BOOST_AUTO_TEST_CASE( ip_pool_test )
{
    std::ifstream file("ip_filter.tsv");
    std::ifstream testFile("ip_filter.tst");

    ip_pool pool(file);

    BOOST_CHECK( pool.size() != 0 );

    pool.sort();

    for( auto& item : pool)
    {
        BOOST_CHECK( testFile );

        std::string line;
        testFile >> line;

        std::stringstream record;
        record << item;

        BOOST_CHECK(  record.str() == line);
    }

    auto filteredPool = pool.getFilteredIP([]( const ip_pool::PoolRecordType& record) {return (record[0] == 1) ? true : false; });

    for( auto& item : filteredPool)
    {
        BOOST_CHECK( testFile );

        std::string line;
        testFile >> line;

        std::stringstream record;
        record << item;

        BOOST_CHECK(  record.str() == line);
    }

    filteredPool = pool.getFilteredIP([](const ip_pool::PoolRecordType& record) {return  (record[0] == 46 && record[1] == 70) ? true : false; });

    for( auto& item : filteredPool)
    {
        BOOST_CHECK( testFile );

        std::string line;
        testFile >> line;

        std::stringstream record;
        record << item;

        BOOST_CHECK(  record.str() == line);
    }

    filteredPool = pool.getFilteredIP([](const ip_pool::PoolRecordType& record) {return  std::any_of(record.begin(), record.end(), []( const auto v ){ return v == 46; }); });

    for( auto& item : filteredPool)
    {
        BOOST_CHECK( testFile );

        std::string line;
        testFile >> line;

        std::stringstream record;
        record << item;

        BOOST_CHECK(  record.str() == line);
    }
}

BOOST_AUTO_TEST_SUITE_END()