
#include "ip_pool.h"
#include  <sstream>
#include <limits>
#include <range/v3/all.hpp>


ip_pool::ip_pool(const std::istream& input)
{
    for (std::string line; std::getline(std::cin, line) && line.size() > 0;)
    {
        m_Pool.push_back(split(line.substr( 0,line.find("\t"))));
    }
}

ip_pool::ip_pool( std::ifstream& input)
{
    for (char a[17]; input.getline(a, 17,'\t');)
    {
        std::string line(a);
        m_Pool.push_back(split(line));

        input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

ip_pool::PoolRecordType ip_pool::split(const std::string& str)
{
    PoolRecordType element{};
    auto i = 0;
    auto startPos = 0;
    auto pos = 0;

    while( i < getPoolRecordCount() - 1)
    {
        pos = str.find(".", startPos);
        element[i] = std::stoul(str.substr(startPos,pos - startPos));
        startPos = pos+1;
        ++i;
    }

    element[i] = std::stoul(str.substr(startPos));

    return element;
}

void ip_pool::sort()
{
    ranges::sort(m_Pool, ranges::greater() );
}

ip_pool::PoolType ip_pool::getFilteredIP(ip_pool::FilterType filter) const
{
    auto ret = m_Pool | ranges::view::filter(filter);
    return ret;
}

std::ostream& operator<< (std::ostream& out, const ip_pool::PoolRecordType& point)
{
    for (auto ip_part = point.cbegin(); ip_part != point.cend(); ++ip_part)
    {
        if (ip_part != point.cbegin())
        {
            out << ".";
        }

        out << *ip_part;
    }

    return out;
}
