#include "sources/MagicalContainer.hpp"
#include <stdexcept>
#include <iostream>
#include "doctest.h"

using namespace ariel;

TEST_CASE("MagicalContainer Test") {
    MagicalContainer container;

    CHECK_NOTHROW(container.addElement(9));
    CHECK_NOTHROW(container.addElement(9));
    CHECK_EQ(container.size(), 1);

    container.addElement(3);
    container.addElement(15);
    container.addElement(8);
    container.addElement(34);
    container.addElement(21);
    container.addElement(11);

    CHECK(container.size() == 6);
    container.removeElement(15);
    CHECK(container.size() == 5);
    container.removeElement(2);
    CHECK(container.size() == 5);
    container.addElement(34);
    CHECK(container.size() == 5);

    MagicalContainer otherContainer = container;
    CHECK(otherContainer.size() == 5);

    container.removeElement(10);  // 10 isn't in the container
    CHECK(otherContainer.size() == 5);
    container.addElement(10);
    CHECK(otherContainer.size() == 6);
    container.removeElement(10);
    CHECK(otherContainer.size() == 5);
    CHECK_THROWS(container.removeElement(150));


    SUBCASE("AscendingIterator Test") {
        MagicalContainer::AscendingIterator asc(container);
        CHECK(*asc.begin() == 3);
        CHECK(*asc.end() == 34);
        ++asc;
        CHECK_EQ(*asc, 8);
    }

    SUBCASE("SideCrossIterator Test") {
        MagicalContainer::SideCrossIterator sci(container);
        CHECK(*sci.begin() == 3);
        CHECK(*sci.end() == 15);
        ++sci;
        CHECK_EQ(*sci, 21);
    }

    SUBCASE("PrimeIterator Test") {
        MagicalContainer::PrimeIterator pri(container);
        CHECK(*pri.begin() == 3);
        CHECK(*pri.end() == 11);
        ++pri;
        CHECK_EQ(*pri, 11);
    }
}