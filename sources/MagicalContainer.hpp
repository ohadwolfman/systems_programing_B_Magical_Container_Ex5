#ifndef CPP_EX5_MAGICALCONTAINER_HPP
#define CPP_EX5_MAGICALCONTAINER_HPP
#include <vector>
using namespace std;

namespace ariel {
    class MagicalContainer {
    private:
        vector<int>elements;

    public:
        MagicalContainer();
        MagicalContainer(const MagicalContainer& other);
        ~MagicalContainer();
        void addElement(int newElement);
        void removeElement(int toDelete);
        int size() const { return elements.size(); }
        vector<int> getElements();

        class AscendingIterator{
            private:
                MagicalContainer& container;  // Pointer to the MagicalContainer object
                size_t index;  // The Current position in the container

            public:
            // Constructors
            AscendingIterator(MagicalContainer& container, size_t index = 0): container(container),index(index){}
            AscendingIterator(const AscendingIterator& other); // Copy constructor
            ~AscendingIterator() = default;

            // --------------operators----------------
            MagicalContainer::AscendingIterator& operator=(const AscendingIterator& other);
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            int operator*() const;
            AscendingIterator& operator++();
            MagicalContainer::AscendingIterator begin() const;
            MagicalContainer::AscendingIterator end() const;
        };

        class SideCrossIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
                // Constructors
                SideCrossIterator(MagicalContainer& container, size_t index = 0): container(container),index(index){}
                SideCrossIterator(const SideCrossIterator& other); // Copy constructor
                ~SideCrossIterator() = default;

                // --------------operators----------------
                MagicalContainer::SideCrossIterator& operator=(const SideCrossIterator& other);
                bool operator==(const SideCrossIterator &other) const;
                bool operator!=(const SideCrossIterator& other) const;
                bool operator>(const SideCrossIterator& other) const;
                bool operator<(const SideCrossIterator& other) const;
                int operator*() const;
                SideCrossIterator& operator++();
                MagicalContainer::SideCrossIterator begin() const;
                MagicalContainer::SideCrossIterator end() const;
        };

        class PrimeIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
                // Constructors
                PrimeIterator(MagicalContainer& container, size_t index = 0): container(container),index(index){}
                PrimeIterator(const PrimeIterator& other); // Copy constructor
                ~PrimeIterator() = default;

                // --------------operators----------------
                PrimeIterator& operator=(const PrimeIterator& other);
                bool operator==(const PrimeIterator &other) const;
                bool operator!=(const PrimeIterator& other) const;
                bool operator>(const PrimeIterator& other) const;
                bool operator<(const PrimeIterator& other) const;
                int operator*() const;
                PrimeIterator& operator++();
                MagicalContainer::PrimeIterator begin() const;
                MagicalContainer::PrimeIterator end() const;
        };
    };
}

#endif
