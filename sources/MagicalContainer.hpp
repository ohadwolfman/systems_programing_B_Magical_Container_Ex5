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
        int size() const { return elements.size() };
        vector<int> getElements();
        MagicalContainer& operator=(const MagicalContainer& otherContainer);

        class AscendingIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
            AscendingIterator(MagicalContainer& container, size_t index): container(container),index(index){}

        };

        class SideCrossIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
                SideCrossIterator(MagicalContainer& container, size_t index): container(container),index(index){}
                bool operator==(const MagicalContainer& other)
        };

        class PrimeIterator{
            private:
                MagicalContainer& container;
                size_t index;

            public:
            PrimeIterator(MagicalContainer& container, size_t index): container(container),index(index){}
        };

    };
}

#endif
