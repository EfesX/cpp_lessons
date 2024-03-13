#define BOOST_TEST_MODULE allocator_test

#include <boost/test/unit_test.hpp>

#include <map>
#include <algorithm>

#include "allocator.h"

BOOST_AUTO_TEST_SUITE(allocator_test)

BOOST_AUTO_TEST_CASE(allocator_test)
{
    const std::size_t SIZE_BLOCK = 5;
    std::map<int, int, std::less<int>, efes::allocator<std::pair<const int, int>, SIZE_BLOCK > > map;

    // при заполнении 10-ю элементами аллокатор должен выделить 2 блока памяти,
    // т.к. SIZE_BLOCK == 5
    for (int i = 0; i < 10; i++){
        map.emplace(i, i);    
    }
    // проверка на правильность заполнения
    for (int i = 0; i < 10; i++){
        BOOST_ASSERT(map[i] == i);
    }
    // получаем расстояние между участками памяти хранения элементов,
    // т.к. аллокатор, на самом деле, хранит в памяти свою служебную структуру,
    // размер заведомо неизвестен
    auto diff = (&map[1] - &map[0]);
    // проверка того что часть элементов распределилась 
    // по блоку выделенной памяти равномерно...
    BOOST_ASSERT(&map[2] == (&map[1] + diff));
    BOOST_ASSERT(&map[3] == (&map[2] + diff));
    BOOST_ASSERT(&map[4] == (&map[3] + diff));
    // ... а для второй части элементов, аллокатор выделил другой блок памяти
    BOOST_ASSERT(&map[5] != (&map[4] + diff));
    BOOST_ASSERT(&map[6] == (&map[5] + diff));
    BOOST_ASSERT(&map[7] == (&map[6] + diff));
    BOOST_ASSERT(&map[8] == (&map[7] + diff));
    BOOST_ASSERT(&map[9] == (&map[8] + diff));

    //получаем конкретные адреса двух элементов из разных блоков памяти
    auto addr2 = &map[2];
    auto addr5 = &map[5];
    // удаляем эти элементы
    map.erase(2);
    map.erase(5);
    // вставляем новые елементы, которые должны попасть на ранее освобожденные адреса
    map.emplace(22, 222);
    BOOST_ASSERT(&map[22] == addr2);
    map.emplace(55, 555);
    BOOST_ASSERT(&map[55] == addr5);
}


template<typename List>
void _tests_lcontainer(List& list)
{
    BOOST_ASSERT(list.empty());
    BOOST_ASSERT(list.size() == 0);
    
    for(int i = 0; i < 100; i++){
        list.push_back(i);
    }

    BOOST_ASSERT(!list.empty());
    BOOST_ASSERT(list.size() == 100);

    int i = 0;
    std::for_each(list.begin(), list.end(), [&](const int& val){
        BOOST_ASSERT(val == i);
        i++;
    });

    std::transform(list.begin(), list.end(), list.begin(), [](int& val){
        return (val + 1);
    });

    i = 1;
    std::for_each(list.begin(), list.end(), [&](const int& val){
        BOOST_ASSERT(val == i);
        i++;
    });
}


BOOST_AUTO_TEST_CASE(lcontainer_test_1)
{
    efes::lcontainer<int, efes::allocator<int, 5> > list;
    _tests_lcontainer(list);
}

BOOST_AUTO_TEST_CASE(lcontainer_test_2)
{
    efes::lcontainer<int, std::allocator<int> > list;
    _tests_lcontainer(list);
}

BOOST_AUTO_TEST_SUITE_END()
