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
        MagicalContainer& operator=(const MagicalContainer& otherContainer);

        class AscendingIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
            explicit AscendingIterator(MagicalContainer& container, size_t index = 0): container(container),index(index){}
            ~AscendingIterator() = default;
            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            int operator*() const;
            AscendingIterator& operator++() const;
            MagicalContainer::AscendingIterator begin() const;
            MagicalContainer::AscendingIterator end() const;
        };

        class SideCrossIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
                explicit SideCrossIterator(MagicalContainer& container, size_t index): container(container),index(index){}
                ~SideCrossIterator() = default;
                bool operator==(const SideCrossIterator &other) const;
                bool operator!=(const SideCrossIterator& other) const;
                bool operator>(const SideCrossIterator& other) const;
                bool operator<(const SideCrossIterator& other) const;
                int operator*() const;
                SideCrossIterator& operator++() const;
                MagicalContainer::SideCrossIterator begin() const;
                MagicalContainer::SideCrossIterator end() const;
        };

        class PrimeIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
                explicit PrimeIterator(MagicalContainer& container, size_t index): container(container),index(index){}
                ~PrimeIterator() = default;
                bool operator==(const PrimeIterator &other) const;
                bool operator!=(const PrimeIterator& other) const;
                bool operator>(const PrimeIterator& other) const;
                bool operator<(const PrimeIterator& other) const;
                int operator*() const;
                PrimeIterator& operator++() const;
                MagicalContainer::PrimeIterator begin() const;
                MagicalContainer::PrimeIterator end() const;
        };
    };
}

#endif
