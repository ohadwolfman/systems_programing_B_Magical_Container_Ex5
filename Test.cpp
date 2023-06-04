#include "sources/MagicalContainer.hpp"
#include <stdexcept>
#include <iostream>
#include "doctest.h"

using namespace ariel;

TEST_CASE("MagicalContainer Test") {
    MagicalContainer container;
    container.addElement(3);
    container.addElement(15);
    container.addElement(8);
    container.addElement(34);
    container.addElement(21);
    container.addElement(11);

    CHECK(container.size() == 6);
    container.removeElement(15)
    CHECK(container.size() == 5);
    container.removeElement(2)
    CHECK(container.size() == 5);
    container.addElement(34)
    CHECK(container.size() == 5);

    MagicalContainer otherContainer = container;
    CHECK(otherContainer.size() == 5);
    CHECK_FALSE(container.getElements.begin() != otherContainer.getElements.begin());


    SUBCASE("AscendingIterator Test") {

    }

    TEST_CASE("SideCrossIterator Test") {

    }

    TEST_CASE("PrimeIterator Test") {

    }
}