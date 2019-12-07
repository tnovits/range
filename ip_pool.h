
#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <fstream>


class ip_pool
{
public:
    using PoolRecordType = std::array<uint, 4>;
    using PoolType = std::vector<PoolRecordType>;
    using FilterType = bool(const PoolRecordType&);

public:
    ip_pool() = delete;
    ip_pool(const std::istream& input);
    ip_pool(std::ifstream& input);
    virtual ~ip_pool() = default;

public:
    auto begin() const
    {
        return m_Pool.begin();
    }

    auto end() const
    {
        return m_Pool.end();
    }

    void sort();
    PoolType getFilteredIP(FilterType filter) const;

    auto& operator[] (const int index) const
    {
        return m_Pool[index];
    }

    size_t size() const
    {
        return m_Pool.size();
    }

private:
    PoolType m_Pool;

private:
    const uint8_t getPoolRecordCount() const {return 4;}
    PoolRecordType split(const std::string& str);
};

std::ostream& operator<< (std::ostream& out, const ip_pool::PoolRecordType& point);