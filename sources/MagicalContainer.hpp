#ifndef CPP_EX5_MAGICALCONTAINER_HPP
#define CPP_EX5_MAGICALCONTAINER_HPP
#include <vector>
using namespace std;

namespace ariel {
    class MagicalContainer {
    private:
        vector<int>elements;  // The elements will be inserted sorted s.t the ascending iterator will iterate directly
        vector<int*> primeElements;
        vector<int*> sideCrossElements;

    public:
        MagicalContainer();
        MagicalContainer(const MagicalContainer& other);
        ~MagicalContainer();
        void addElement(int newElement);
        void removeElement(int toDelete);
        void addPrime(int newElement);
        void updateSideCross(int newElement);
        int size() const { return elements.size(); }
        vector<int>& getElements();
        static bool isPrime(int num);
        static bool pointersCompare(const int* a, const int* b);


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

        class SideCrossIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
                // Constructors
                explicit SideCrossIterator(MagicalContainer& container, size_t index = 0): container(container),index(index){}
                SideCrossIterator(const SideCrossIterator& other) = default;
                ~SideCrossIterator() = default;

                // --------------operators----------------
                MagicalContainer::SideCrossIterator& operator=(const SideCrossIterator& other);
                bool operator==(const SideCrossIterator &other) const;
                bool operator!=(const SideCrossIterator& other) const;
                bool operator>(const SideCrossIterator& other) const;
                bool operator<(const SideCrossIterator& other) const;
                int operator*() const;
                SideCrossIterator& operator++();
                SideCrossIterator begin() const;
                SideCrossIterator end() const;
        };

        class PrimeIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
                // Constructors
                explicit PrimeIterator(MagicalContainer& container, size_t index = 0): container(container),index(index){}
                PrimeIterator(const PrimeIterator& other) = default;
                ~PrimeIterator() = default;

                // --------------operators----------------
                PrimeIterator& operator=(const PrimeIterator& other);
                bool operator==(const PrimeIterator &other) const;
                bool operator!=(const PrimeIterator& other) const;
                bool operator>(const PrimeIterator& other) const;
                bool operator<(const PrimeIterator& other) const;
                int operator*() const;
                PrimeIterator& operator++();
                PrimeIterator begin() const;
                PrimeIterator end() const;
        };
    };
}

#endif
