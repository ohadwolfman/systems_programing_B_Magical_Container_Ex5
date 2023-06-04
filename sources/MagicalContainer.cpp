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
                elements.erase(element);
                return;
            }
        }
    }

    vector<int> MagicalContainer::getElements(){
        return this->elements;
    }

    MagicalContainer& operator=(const MagicalContainer& otherContainer){
        return *otherContainer;
    }

}
