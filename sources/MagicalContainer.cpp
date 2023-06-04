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

    MagicalContainer& MagicalContainer::operator=(const MagicalContainer& otherContainer){
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const{
        return this->index==other.index; }
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const{}
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const{}
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const{}
    int MagicalContainer::AscendingIterator::operator*() const{}
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(int num) const{}
    int* MagicalContainer::AscendingIterator::begin() const{ return &container.elements.at(0); }
    int* MagicalContainer::AscendingIterator::end() const{ return &container.elements.at(container.size()); }


    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const{
        return this->index==other.index; }
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const{}
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const{}
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const{}
    int MagicalContainer::SideCrossIterator::operator*() const{}
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(int num) const{}
    int* MagicalContainer::SideCrossIterator::begin() const{ return &container.elements.at(0); }
    int* MagicalContainer::SideCrossIterator::end() const{ return &container.elements.at(container.size()); }

    bool MagicalContainer::PrimeIterator::operator==(const MagicalContainer::PrimeIterator &other) const {
        return false; }
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const{}
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const{}
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const{}
    int MagicalContainer::PrimeIterator::operator*() const{}
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(int num) const{}
    int* MagicalContainer::PrimeIterator::begin() const{ return &container.elements.at(0); }
    int* MagicalContainer::PrimeIterator::end() const{ return &container.elements.at(container.size()); }




}
