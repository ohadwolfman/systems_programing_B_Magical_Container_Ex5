#include "MagicalContainer.hpp"
#include <iterator>

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
    }

    void MagicalContainer::removeElement(int toDelete){
        for(int element: elements){
            if(toDelete == element){
                //elements.erase(elements.at(element));
                return;
            }
        }
    }

    vector<int> MagicalContainer::getElements(){
        return this->elements;
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
        return this->index==other.index; }
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const{
        return true;
    }
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const{
        return true;
    }
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const{
        return true;
    }
    int MagicalContainer::AscendingIterator::operator*() const{
        return 1;
    }
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
        ++(this->index);
        return *this;
    }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const{ return AscendingIterator(container,0); }
    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const{ return AscendingIterator(container,size_t(container.size())); }


// ---------------------- Class: SideCrossIterator ----------------------
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other){
        if (this != &other){
            container = other.container;
            index = other.index;
        }
        return *this;
    }
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const{
        return this->index==other.index; }
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const{
        return true;
    }
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const{
        return true;
    }
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const{
        return true;
    }
    int MagicalContainer::SideCrossIterator::operator*() const{
        return 1;
    }
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
        ++(this->index);
        return *this;
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const{ return SideCrossIterator(container,0); }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const{ return SideCrossIterator(container,size_t(container.size())); }


    // ---------------------- Class: PrimeIterator ----------------------
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other){
        if (this != &other){
            container = other.container;
            index = other.index;
        }
        return *this;
    }
    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &other) const {
        return false; }
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const{
        return true;
    }
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const{
        return true;
    }
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const{
        return true;
    }
    int MagicalContainer::PrimeIterator::operator*() const{
        return 0;
    }
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
        ++(this->index);
        return *this;

    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{ return PrimeIterator(container,0); }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const{ return PrimeIterator(container,size_t(container.size())); }
}
