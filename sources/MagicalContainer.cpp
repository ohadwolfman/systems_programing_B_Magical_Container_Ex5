#include "MagicalContainer.hpp"
#include <iterator>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

namespace ariel{
    void MagicalContainer::addElement(int newElement) {
        // Create a new node for the new element
        Node* newNode = new Node(newElement);
        // Insert in the sorted place in the vector for ascending iterator

        // if elements size is 0
        if (elements.head == nullptr) {
            elements.head = newNode;
            elements.tail=newNode;
            ++contSize;
        }
        // if elements size is 1
        else if (elements.head->next == nullptr) {
            if (elements.head->value < newNode->value) {
                elements.head->next = newNode;
                newNode->prev = elements.head;
                elements.tail=newNode;
            } else {
                newNode->next = elements.head;
                elements.tail=elements.head;
                elements.head = newNode;
                elements.tail->prev=newNode;
            }
            ++contSize;
        }
        else{ // if the container's size is 2 or more
            // if the element is already in the container - it won't be inserted
            Node* curr = elements.head;
            while(curr->next != nullptr && curr->next->value <= newNode->value){
                if(curr->next->value == newNode->value)
                    return;
                curr = curr->next;
            }
            if(curr->value < newNode->value){
                if(curr->next == nullptr){
                    curr->next=newNode;
                    elements.tail=newNode;
                    newNode->prev=curr;
                    this->elements.tail=newNode;
                }
                else{
                    newNode->next=curr->next;
                    curr->next->prev=newNode;
                    newNode->prev=curr;
                    curr->next=newNode;
                }
            }
            ++contSize;
        }

        // Insert if prime number for prime iterator
        if (isPrime(newElement)) {
            addPrime(newNode);
        }

        // Insert to cross order pointers vector for crossOrder iterator
        // building the crossOrder by taking one from the beginning and one from the end.
        updateSideCross();

//        std::cout<<this->elements.tail->value<<","<<this->contSize<<endl;
//        std::cout<<(*primeElements.begin())->value<<","<<this->primeElements.size()<<endl;
//        std::cout<<(*sideCrossElements.begin())->value<<","<<this->sideCrossElements.size()<<endl;
    }

    void MagicalContainer::removeElement(int toDelete) {
        bool flag = false;
        Node* curr = elements.head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;  // Store the next node
            if (curr->value == toDelete) {
                if (curr == elements.head) {
                    elements.head = curr->next;
                }
                if (curr == elements.tail) {
                    elements.tail = curr->prev;
                }
                if (curr->prev != nullptr) {
                    curr->prev->next = curr->next;
                }
                if (curr->next != nullptr) {
                    curr->next->prev = curr->prev;
                }
                delete curr;
                --contSize;
                flag = true;
            }
            curr = nextNode;  // Move to the next node
        }
        if (!flag) {
            throw std::runtime_error("The element does not exist in the container");
        }
    }

    bool MagicalContainer::isPrime(int num) {
        if (num < 2)
            return false;
//        if (num == 2)
//            return true;
        for (int i = 2; i < num; ++i) {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    void MagicalContainer::addPrime(Node* newNode){
        // Find the correct position to insert the prime node in ascending order
        if(primeElements.empty()){
            primeElements.push_back(newNode);
            return;
        }
        size_t i = 0;
        while(primeElements[i]->value < newNode->value){
            ++i;
        }
        primeElements.insert(primeElements.begin() + static_cast<long>(i), newNode);
    }

    void MagicalContainer::updateSideCross(){
        // clear the vector because every addition the container changes.
        sideCrossElements.clear();
        Node* start = this->elements.head;
        Node* end = this->elements.tail;
        if(this->contSize == 0)
            return;
        int count = 0;
        while (count < this->size()){
            if(count%2 == 0){
                sideCrossElements.push_back(start);
                start = start->next;
//                cout << "number " << sideCrossElements[static_cast<unsigned long>(count - 1)]->value << endl;
            }
            else{
                sideCrossElements.push_back(end);
                end = end->prev;
//                cout << "number " << sideCrossElements[static_cast<unsigned long>(count - 1)]->value << endl;
            }
            ++count;
        }

//        // If it's odd size - we will add the first, and then we will run even number of nodes
//        if(this->size() % 2 == 1) {
//            sideCrossElements.insert(sideCrossElements.begin(), this->elements.head);
//            start = start->next;
//        }
//        for (int i = 0; i < floor(this->size() / 2); ++i) {
//            sideCrossElements.push_back(start);
//            sideCrossElements.push_back(end);
//            start = start->next;
//            end = end->prev;
//        }
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
        return this->container.elements[this->index]->value;
    }
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
        if (index == this->container.size()) {
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
        int val = this->container->sideCrossElements[this->index]->value;
        return val;
    }
    Node* MagicalContainer::SideCrossIterator::operator[](size_t ind) const{
        if(ind > this->container->size())
            throw runtime_error("Invalid index");

        Node* curr = container->sideCrossElements.at(ind);
        return curr;
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::operator++(){
        if (*this == end())
        {
            throw std::runtime_error("Exceeded container's size");
        }
        ++this->index;
        return *this;
    }
    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const{
        MagicalContainer::SideCrossIterator sci(*container);
        return sci;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const{
        MagicalContainer::SideCrossIterator sic =
                SideCrossIterator(*container, static_cast<size_t>(this->container->size()));
        return sic;

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
        int val = this->container->primeElements[this->index]->value;
        return val;
    }
    Node* MagicalContainer::PrimeIterator::operator[](size_t ind) const{
        if(ind > this->container->size())
            throw runtime_error("Invalid index");

        Node* curr = container->primeElements.at(ind);
        return curr;
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::operator++(){
        if (index == this->container->size()) {
            return *this;
//            throw runtime_error ("Exceeded container's size");
        }
        ++index;
        return *this;

    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{
        return PrimeIterator(*container);
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const{
        MagicalContainer::PrimeIterator pri =
                PrimeIterator(*container,this->container->primeElements.size());
        return pri;

    }

    Node* LinkedList::operator[](size_t ind) const {
        Node* curr = this->head;
        size_t count = 0;
        while (curr != nullptr && count < ind) {
            curr = curr->next;
            count++;
        }
        if(count<ind) // the index is too big
            throw runtime_error("Invalid index");
        else
            return curr;
    }
}
