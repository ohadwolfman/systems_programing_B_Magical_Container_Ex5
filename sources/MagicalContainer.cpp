#include "MagicalContainer.hpp"
#include <iterator>
#include <math.h>

using namespace std;

namespace ariel{
    MagicalContainer::MagicalContainer(){

    }
    MagicalContainer::MagicalContainer(const MagicalContainer& other){
        this->elements=other.elements;
    }
    MagicalContainer::~MagicalContainer() {

    }


    void MagicalContainer::addElement(int newElement){
        for(int element: elements){
            if(newElement == element)
                return;
        }
        elements.push_back(newElement);
        if (isPrime(newElement))
            prime_container.push_back(&newElement);
    }

    void MagicalContainer::removeElement(int toDelete){
        auto itr = elements.begin();
        for(int element: elements){
            if(toDelete == element){
                elements.erase(itr);
            }
            ++itr;
        }
    }

    int MagicalContainer::AT(size_t index){
        return this->elements.at(index);
    }

    vector<int> MagicalContainer::getElements(){
        return this->elements;
    }

    bool MagicalContainer::isPrime(int num){
        if(num<2)
            return false;
        for(int i=2; i<= sqrt(num); ++i){
            if(num % i == 0)
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
        if (index == container.size() || *this == end()) {
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
        if (index == container.size() || *this == end()) {
            return *this;
//            throw runtime_error ("Exceeded container's size");
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
