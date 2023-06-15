#ifndef CPP_EX5_MAGICALCONTAINER_HPP
#define CPP_EX5_MAGICALCONTAINER_HPP
#include <vector>
using namespace std;

namespace ariel {
    class Node {
    public:
        int value;
        Node* next;
        Node* prev;

        explicit Node(int val) : value(val), next(nullptr), prev(nullptr) {}
        ~Node() = default;
    };
    class LinkedList {
    public:
        Node* head;
        Node* tail;
        explicit LinkedList(Node* n) : head(n), tail(nullptr) {}
        ~LinkedList() = default;
        Node* operator[](size_t ind) const;
    };

    class MagicalContainer {
    private:
        LinkedList elements; // The elements will be inserted sorted s.t the ascending iterator will iterate directly
        std::vector<Node*> primeElements;
        std::vector<Node*> sideCrossElements;
        int contSize;

    public:
        explicit MagicalContainer() : elements(nullptr), contSize(0) {}
        MagicalContainer(const MagicalContainer& other):
            elements(other.elements), primeElements(other.primeElements),
            sideCrossElements(other.sideCrossElements), contSize(other.contSize) {}
        // Destructor
        ~MagicalContainer() {
            for (Node* node : primeElements) {
                delete node;
            }
            primeElements.clear();
            sideCrossElements.clear();
        }
        void addElement(int newElement);
        void removeElement(int toDelete);
        static bool isPrime(int num);
        void addPrime(Node* newNode);
        void updateSideCross();
        int size() const{ return this->contSize; }

        // ---------------------- Class: AscendingIterator ----------------------
        class AscendingIterator{
            private:
                MagicalContainer& container;  // Pointer to the MagicalContainer object
                size_t index;  // The Current position in the container

            public:
            // Constructors
            explicit AscendingIterator(MagicalContainer& container, size_t index = 0): container(container),index(index){}
            AscendingIterator (const AscendingIterator& other) = default;
            ~AscendingIterator() = default;

            // --------------operators----------------
            AscendingIterator& operator=(const AscendingIterator& other);
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            int operator*() const;
            AscendingIterator& operator++();
            AscendingIterator begin() const;
            AscendingIterator end() const;
        };


        // ---------------------- Class: SideCrossIterator ----------------------
        class SideCrossIterator{
            private:
                MagicalContainer* container;
                size_t index;

            public:
                // Constructors
                explicit SideCrossIterator(MagicalContainer& container, size_t index = 0): container(&container),index(index){}
                SideCrossIterator(const SideCrossIterator& other) = default;
                ~SideCrossIterator() = default;

                // --------------operators----------------
                MagicalContainer::SideCrossIterator& operator=(const SideCrossIterator& other);
                bool operator==(const SideCrossIterator &other) const;
                bool operator!=(const SideCrossIterator& other) const;
                bool operator>(const SideCrossIterator& other) const;
                bool operator<(const SideCrossIterator& other) const;
                int operator*() const;
                Node* operator[](size_t index) const;
                SideCrossIterator operator++();
                SideCrossIterator begin() const;
                SideCrossIterator end() const;
        };


        // ---------------------- Class: PrimeIterator ----------------------
        class PrimeIterator{
            private:
                MagicalContainer* container;
                size_t index;

            public:
                // Constructors
                PrimeIterator(MagicalContainer& container, size_t index = 0): container(&container),index(index){}
                PrimeIterator(const PrimeIterator& other) = default;
                ~PrimeIterator() = default;

                // --------------operators----------------
                PrimeIterator& operator=(const PrimeIterator& other);
                bool operator==(const PrimeIterator &other) const;
                bool operator!=(const PrimeIterator& other) const;
                bool operator>(const PrimeIterator& other) const;
                bool operator<(const PrimeIterator& other) const;
                int operator*() const;
                Node* operator[](size_t index) const;
                PrimeIterator operator++();
                PrimeIterator begin() const;
                PrimeIterator end() const;
        };
    };
}

#endif
