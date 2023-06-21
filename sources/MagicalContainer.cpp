#include "MagicalContainer.hpp"
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

namespace ariel{
    void MagicalContainer::addElement(int newElement) {
        // Create a new node for the new element
        Node* newNode = new Node(newElement);

        // Check if the element already exists in the container
        Node* curr = elements.head;
        while (curr != nullptr) {
            if (curr->value == newElement) {
                delete newNode; // Element already exists, so delete the newly created node
                return;
            }
            curr = curr->next;
        }

        // Insert in the sorted place in the container for ascending iterator

        // If the container is empty
        if (elements.head == nullptr) {
            elements.head = newNode;
            elements.tail = newNode;
        }
            // If the new element should be inserted at the beginning
        else if (newNode->value <= elements.head->value) {
            newNode->next = elements.head;
            elements.head->prev = newNode;
            elements.head = newNode;
        }
            // If the new element should be inserted at the end
        else if (newNode->value >= elements.tail->value) {
            elements.tail->next = newNode;
            newNode->prev = elements.tail;
            elements.tail = newNode;
        }
            // If the new element should be inserted in the middle
        else {
            Node* current = elements.head->next;
            while (current != nullptr && newNode->value > current->value) {
                current = current->next;
            }
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }

        ++contSize;

        // Insert if prime number for prime iterator
        if (isPrime(newElement)) {
            addPrime(newNode);
        }

        // Building the crossOrder by taking one from the beginning and one from the end.
        updateSideCross();
    }


    void MagicalContainer::removeElement(int toDelete) {
        bool flag = false;
        Node* curr = elements.head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;  // Store the next node
            if (curr->value == toDelete) {
                if (curr == elements.head) {
                    elements.head = curr->next; // delete the first - pass the head to the second
                }
                if (curr == elements.tail) {
                    elements.tail = curr->prev; // delete the last - pass the tail to one before
                }
                if (curr->prev != nullptr) { // before delete curr set the prev to jump over curr
                    curr->prev->next = curr->next;
                }
                if (curr->next != nullptr) { // before delete curr set the next to jump over curr
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
        if (num == 2)
            return true;
        for (int i = 2; i < num; ++i) {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    void MagicalContainer::addPrime(Node* newNode) {
        // Find the correct position to insert the prime node in ascending order
        if (primeElements.empty()) {
            primeElements.push_back(newNode);
            return;
        }
        size_t i = 0;
        while (i < primeElements.size() - 1 && primeElements[i]->value < newNode->value) {
            if (primeElements[i]) {
                ++i;
            } else {
                primeElements.push_back(newNode);
                return;
            }
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
        if (index >= this->container.size()) {
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
        if (index >= this->container->size())
        {
            throw std::runtime_error("Exceeded container's size");
//            return *this;
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
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::operator++() {
        if (index >= this->container->primeElements.size()) {
            throw std::runtime_error("Iterator reached the end of the container");
//            return *this;
        }
        ++index;
        return *this;
    }
    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const{
        MagicalContainer::PrimeIterator pri =PrimeIterator(*container,0);
        return pri;
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
