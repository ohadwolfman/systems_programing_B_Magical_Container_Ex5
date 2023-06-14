#include "MagicalContainer.hpp"
#include <iterator>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

namespace ariel{
    MagicalContainer::MagicalContainer(){
        elements = vector<int>();
        primeElements = vector<int*>();
        sideCrossElements = vector<int*>();
    }
    MagicalContainer::MagicalContainer(const MagicalContainer& other){
        elements = other.elements;
        primeElements = other.primeElements;
        sideCrossElements = other.sideCrossElements;
    }
    MagicalContainer::~MagicalContainer() {
        for (int* ptr : primeElements) {
            delete ptr;
        }
        primeElements.clear(); // Clear the vector after deleting the pointers

        // There is no need to delete elements in sideCrossElements since they are not dynamically allocated
        sideCrossElements.clear(); // Clear the vector
    }

    void MagicalContainer::addElement(int newElement) {
        // Insert in the sorted place in the vector for ascending iterator
        for(int elem: elements){
            if(elem == newElement)
                return;
        }
        auto insertionPoint = std::upper_bound(elements.begin(), elements.end(), newElement);
        elements.insert(insertionPoint, newElement);

        // Insert if prime number for prime iterator
        if (isPrime(newElement)) {
            addPrime(newElement);
        }

        // Insert to cross order pointers vector for crossOrder iterator
        // building the crossOrder by taking one from the beginning and one from the end.
        updateSideCross(newElement);

        std::cout<<elements.size()<<endl;
        std::cout<<primeElements.size()<<endl;
        std::cout<<sideCrossElements.size()<<endl;
    }

    void MagicalContainer::removeElement(int toDelete){
        bool flag = false;
        auto itr = elements.begin();
        for(int element: elements){
            if(toDelete == element){
                elements.erase(itr);
                flag = true;
            }
            ++itr;
        }
        if(!flag)
            throw runtime_error("The element isn't exist in the container");
    }

    void MagicalContainer::addPrime(int newElement){
        size_t loc = std::binary_search(elements.begin(), elements.end(), newElement);
        int* newElementPtr  = &elements[loc];
        primeElements.push_back(newElementPtr);
        std::sort(primeElements.begin(), primeElements.end(), pointersCompare);
    }

    void MagicalContainer::updateSideCross(int newElement){
        // clear the vector because every addition the container changes.
        sideCrossElements.clear();
        int start = 0;
        int end = static_cast<int>(elements.size()) - 1;
        if(elements.size()%2 == 1) {
            sideCrossElements.push_back(&(elements.at(static_cast<unsigned long>(start))));
            ++start;
        }
        for (int i = 0; i < floor(elements.size() / 2); ++i) {
            sideCrossElements.push_back(&(elements.at(static_cast<unsigned long>(start))));
            sideCrossElements.push_back(&(elements.at(static_cast<unsigned long>(end))));
            ++start;
            --end;
        }
    }


    vector<int>& MagicalContainer::getElements(){
        return this->elements;
    }
    bool MagicalContainer::pointersCompare(const int* a, const int* b) {
        return *a < *b;
    }


    bool MagicalContainer::isPrime(int number) {
        if (number < 2)
            return false;
        for (int i = 2; i * i <= number; ++i) {
            if (number % i == 0)
                return false;
        }
        return true;
    }


// ---------------------- Class: AscendingIterator ----------------------
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other){
        if (this != &other){
            container = other.container;
            index = other.index;
        }
        return *this;
    }
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const{
        return this->index == other.index;
    }
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const{
        return this->index != other.index;
    }
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const{
        return this->index > other.index;
    }
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const{
        return this->index < other.index;
    }
    int MagicalContainer::AscendingIterator::operator*() const{
        return this->container.elements.at(index);
    }
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
        if (index == container.size()) {
            return *this;
//            throw runtime_error ("Exceeded container's size");
        }
        ++index;
        return *this;
    }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const{
        MagicalContainer::AscendingIterator asc(container);
        return asc;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const{
        MagicalContainer::AscendingIterator asc(container, static_cast<size_t>(this->container.size()));
        return asc;
    }


// ---------------------- Class: SideCrossIterator ----------------------
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other){
        if (this != &other){
            container = other.container;
            index = other.index;
        }
        return *this;
    }
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const{
        return this->index == other.index;
    }
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const{
        return this->index != other.index;
    }
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const{
        return this->index > other.index;
    }
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const{
        return this->index < other.index;
    }
    int MagicalContainer::SideCrossIterator::operator*() const{
        return this->container.elements.at(index);
    }
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
        if (*this == end())
        {
            throw std::runtime_error("Exceeded container's size");
        }
        ++index;
        return *this;
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const{
        MagicalContainer::SideCrossIterator sci(container);
        return sci;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const{
        MagicalContainer::SideCrossIterator sci(container, static_cast<size_t>(this->container.size()));
        return sci;
    }


    // ---------------------- Class: PrimeIterator ----------------------
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other){
        if (this != &other){
            container = other.container;
            index = other.index;
        }
        return *this;
    }
    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &other) const {
        return this->index == other.index;
    }
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const{
        return this->index != other.index;
    }
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const{
        return this->index > other.index;
    }
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const{
        return this->index < other.index;
    }
    int MagicalContainer::PrimeIterator::operator*() const{
        return this->container.elements.at(index);
    }
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
        if (index == container.size() || *this == end()) {
            return *this;
//            throw runtime_error ("Exceeded container's size");
        }
        ++index;
        return *this;

    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{
        MagicalContainer::PrimeIterator pri(container);
        return pri;
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const{
        MagicalContainer::PrimeIterator pri(container, static_cast<size_t>(this->container.size()));
        return pri;
    }
}
