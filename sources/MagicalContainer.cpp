#include "MagicalContainer.hpp"
#include <iterator>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

namespace ariel{
//    MagicalContainer::MagicalContainer(const MagicalContainer& other){
//        size=other.size;
//        elements = other.elements;
//        primeElements = other.primeElements;
//        sideCrossElements = other.sideCrossElements;
//    }
    MagicalContainer::~MagicalContainer() {
//        for (int* ptr : primeElements) {
//            delete ptr;
//        }
//        primeElements.clear(); // Clear the vector after deleting the pointers
//
//        // There is no need to delete elements in sideCrossElements since they are not dynamically allocated
//        sideCrossElements.clear(); // Clear the vector
    }

    void MagicalContainer::addElement(int newElement) {
        // Insert in the sorted place in the vector for ascending iterator
        Node* curr = elements.head;
        while(curr != nullptr){
            if(curr->value == newElement)
                return;
            curr = curr->next;
        }

        // Create a new node for the new element
        Node* newNode = new Node(newElement);

        // Insert the new node in ascending order
        curr = elements.head;
        while(curr != nullptr && (curr->value < curr->next->value)){
            curr = curr->next;
        }
        curr->next->prev=newNode;
        newNode->next = curr->next;
        curr->next = newNode;
        newNode->prev=curr;
        ++size;


        // Insert if prime number for prime iterator
        if (isPrime(*newNode)) {
            addPrime((Node &) newNode);
        }

        // Insert to cross order pointers vector for crossOrder iterator
        // building the crossOrder by taking one from the beginning and one from the end.
        updateSideCross();

//        std::cout<<elements.size()<<endl;
//        std::cout<<primeElements.size()<<endl;
//        std::cout<<sideCrossElements.size()<<endl;
    }

    void MagicalContainer::removeElement(int toDelete) const{
        bool flag = false;
        Node* curr = elements.head;
        for(int i = 0; i<this->size; ++i){
            if(toDelete == curr->value){
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                flag = true;
                delete curr;
                break;
            }
        }
        if(!flag)
            throw runtime_error("The element isn't exist in the container");
    }

    bool MagicalContainer::isPrime(Node newNode) {
        if (newNode.value < 2)
            return false;
        for (int i = 2; i * i <= newNode.value; ++i) {
            if (newNode.value % i == 0)
                return false;
        }
        return true;
    }

    void MagicalContainer::addPrime(Node& newNode){
        // Find the correct position to insert the prime node in ascending order
        if(primeElements.empty()){
            primeElements.push_back(&newNode);
            return;
        }
        int i = 0;
        while(primeElements[static_cast<unsigned long>(i)]->value < newNode.value){
            ++i;
        }
        primeElements.insert(primeElements.begin() + i,&newNode);
    }

    void MagicalContainer::updateSideCross(){
        // clear the vector because every addition the container changes.
        sideCrossElements.clear();
        Node* start = this->elements.head;
        Node* end = this->elements.tail;

        // If it's odd size - we will add the first, and then we will run even number of nodes
        if(this->size % 2 == 1) {
            sideCrossElements.insert(sideCrossElements.begin(), this->elements.head);
            start = start->next;
        }
        for (int i = 0; i < floor(this->size / 2); ++i) {
            sideCrossElements.insert(sideCrossElements.begin()+i, start);
            sideCrossElements.insert(sideCrossElements.end()-i, end);
            start = start->next;
            end = end->prev;
        }
    }

    bool MagicalContainer::pointersCompare(const Node* a, const Node* b) {
        return a->value < b->value;
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
        if (index == this->container.size) {
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
        MagicalContainer::AscendingIterator asc(container, static_cast<size_t>(this->container.size));
        return asc;
    }

    Node* MagicalContainer::AscendingIterator::operator[](size_t ind) const{
        if(ind > this->container.size)
            throw runtime_error("Invalid index");

        Node* curr = container.elements.head;
        size_t count = 0;

        while (curr != nullptr && count < ind) {
            curr = curr->next;
            count++;
        }
        return curr;
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
        return this->container.elements[index];
    }
    Node* MagicalContainer::SideCrossIterator::operator[](size_t ind) const{
        if(ind > this->container.size)
            throw runtime_error("Invalid index");

        Node* curr = container.sideCrossElements.at(ind);
        return curr;
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
    Node* MagicalContainer::PrimeIterator::operator[](size_t ind) const{
        if(ind > this->container.size)
            throw runtime_error("Invalid index");

        Node* curr = container.primeElements.at(ind);
        return curr;
    }
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
        if (index == this->container.size) {
            return *this;
//            throw runtime_error ("Exceeded container's size");
        }
        ++index;
        return *this;

    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{
        MagicalContainer::PrimeIterator pri(container);
        pri.index = reinterpret_cast<size_t>(pri.container.primeElements[0]);
        return pri;
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const{
        MagicalContainer::PrimeIterator pri(container);
        pri.index = reinterpret_cast<size_t>(pri.container.primeElements[static_cast<size_t>(this->container.size())-1]);
        return pri;
    }
}
