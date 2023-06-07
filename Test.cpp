#include <stdexcept>
#include <iostream>
#include <sstream>
#include "doctest.h"
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>
#include "sources/MagicalContainer.hpp"
using namespace std;
using namespace ariel;


/////////////////////////////MagicalContainer///////////////////////////////////////////////////////
TEST_CASE("MagicalContainer")
{
    MagicalContainer container;
    container.addElement(17);
    container.removeElement(17);
    CHECK(container.size() == 0);
    
    // Add a large number of elements
    const int numElements = 1000;
    for (int i = 0; i < numElements; ++i) {
        container.addElement(i);
    }
    CHECK(container.size() == numElements);

    // Add and remove elements alternately
    for (int i = 0; i < numElements/2; ++i) 
        {
            container.removeElement(i);
        }
    CHECK(container.size() == numElements / 2);
    
}

//////////////////////////////////AscendingIterator//////////////////////////////////////////////////
TEST_CASE("AscendingIterator")
{
    // *the iterator*
    MagicalContainer container;

    //*empty container*
    MagicalContainer::AscendingIterator iter1(container);
    CHECK(iter1 == iter1.begin());
    CHECK(iter1 == iter1.end());
    CHECK_EQ(container.size(), 0);

    // add elements
    container.addElement(3);
    container.addElement(1);
    container.addElement(2);
    CHECK_EQ(container.size(), 3);

    // Iteration order
    CHECK(*iter1 == 1);
    ++iter1;
    CHECK(*iter1 == 2);
    ++iter1;
    CHECK(*iter1 == 3);
    ++iter1;
    CHECK(iter1 == iter1.end());

    // remove element
    container.removeElement(1);
    CHECK_EQ(container.size(), 2);

    // function
    MagicalContainer::AscendingIterator iter2(container);
    CHECK(iter1 == iter2);
    CHECK_FALSE(iter1 != iter2);

    ++iter2;
    CHECK(iter1 != iter2);
    CHECK(iter1 < iter2);
}

//////////////////////////////////SideCrossIterator//////////////////////////////////////////////////
TEST_CASE("SideCrossIterator")
{
    // *the iterator*
    MagicalContainer container;

    MagicalContainer::SideCrossIterator iter1(container);
    CHECK(iter1 == iter1.end());

    // add elements
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);
    container.removeElement(2);
    container.removeElement(4);

    // Iteration order
    CHECK(*iter1 == 1);
    ++iter1;
    CHECK(*iter1 == 5);
    ++iter1;
    CHECK(*iter1 == 3);
    ++iter1;
    CHECK(iter1 == iter1.end());


    // remove element
    container.removeElement(1);
    CHECK_EQ(container.size(), 2);

    // function
    MagicalContainer::SideCrossIterator iter2(container);
    CHECK(iter1 == iter2);
    CHECK_FALSE(iter1 != iter2);

    ++iter2;
    CHECK(iter1 != iter2);
    CHECK(iter1 < iter2);
    CHECK_FALSE(iter1 > iter2);
}

//////////////////////////////////PrimeIterator//////////////////////////////////////////////////
TEST_CASE("PrimeIterator")
{
    // *the iterator*
    MagicalContainer container;

    //*empty container*
    MagicalContainer::PrimeIterator iter1(container);
    CHECK(iter1.begin() == iter1.end());

    //*Non-empty container*
    // add prime numbers
    container.addElement(2);
    container.addElement(3);
    container.addElement(5);
    container.addElement(4);
    CHECK_EQ(container.size(), 3);

    // Iteration order
    CHECK(*iter1 == 2);
    ++iter1;
    CHECK(*iter1 == 3);
    ++iter1;
    CHECK(*iter1 == 5);
    ++iter1;
    CHECK(iter1 == iter1.end());

    // remove element
    container.removeElement(2);
    CHECK_EQ(container.size(), 2);

    
    // function
    MagicalContainer::PrimeIterator iter2(container);
    CHECK(iter1 == iter2);
    CHECK_FALSE(iter1 != iter2);

    ++iter2;
    CHECK(iter1 != iter2);
    CHECK(iter1 < iter2);
    CHECK_FALSE(iter1 > iter2);
}
TEST_CASE("PrimeIterator - Only Non-Prime Numbers") 
{
    MagicalContainer container;
    container.addElement(4);
    container.addElement(8);
    container.addElement(15);
    container.addElement(20);

    MagicalContainer::PrimeIterator primeIter(container);
    CHECK(primeIter == primeIter.begin());
    CHECK(primeIter == primeIter.end());
}
