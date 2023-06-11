#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

namespace ariel 
{
    class MagicalContainer 
    {
    private:
        std::vector<int> elements; // The container to store elements
        std::vector<int*> numbers_prime;//to store primes elements

        
    public:
        // Constructors
        MagicalContainer(); // Default 
        MagicalContainer(MagicalContainer &other); // Copy 
        MagicalContainer(MagicalContainer&&) = delete;
        MagicalContainer& operator=(MagicalContainer&&) = delete;
        MagicalContainer& operator=(const MagicalContainer&) = delete;
        ~MagicalContainer(); // Destructor
        
        // Member functions
        void addElement(int element); // Add an element to the container
        void removeElement(int element); // Remove an element from the container
        const std::vector<int>& getElements() const; // Get a const reference to the elements
        const std::vector<int*>& get_primes() const; // Get a const reference to the prime numbers
        bool isPrime(int number); // Check if a number is prime
        void delete_(std::vector<int*>& vector, int n); // Helper function to delete an element from a vector (to prime)
        int size() const; // Get the size of the container
        
        // Nested iterator classes
        class AscendingIterator; // Iterator for ascending order
        class SideCrossIterator; // Iterator for cross order
        class PrimeIterator; // Iterator for prime numbers
    };

    /* AscendingIterator class */
    class MagicalContainer::AscendingIterator
    {
    private:
        const MagicalContainer& container; // Reference to the container
        int currentIndex; // Current index of the iterator
        
    public:
        // Constructors
        AscendingIterator(const MagicalContainer& other, int index); // Default 
        AscendingIterator(const MagicalContainer& container); // with container reference
        AscendingIterator(const AscendingIterator& ascIter); // Copy 
        AscendingIterator(AscendingIterator&&) = delete;
        AscendingIterator& operator=(AscendingIterator&&) = delete;
        ~AscendingIterator(); // Destructor
        
        // Member functions
        AscendingIterator& operator=(const AscendingIterator& other); // Assignment operator
        bool operator==(const AscendingIterator& other) const; // Equality comparison operator
        bool operator!=(const AscendingIterator& other) const; // Inequality comparison operator
        bool operator>(const AscendingIterator& other) const; // Greater than comparison operator
        bool operator<(const AscendingIterator& other) const; // Less than comparison operator
        int operator*(); // Dereference operator
        AscendingIterator& operator++(); // Pre-increment operator
        AscendingIterator begin(); // Get the iterator pointing to the first element
        AscendingIterator end(); // Get the iterator pointing to the element after the last element
    };

    /* SideCrossIterator class */
    class MagicalContainer::SideCrossIterator
    {
    private:
        const MagicalContainer& container; // Reference to the container
        bool use; // Flag to indicate whether it is the left side or right side
        int leftIndex; // Current index of the left side
        int rightIndex; // Current index of the right side
        
    public:
        // Constructors
        SideCrossIterator(const MagicalContainer& container); // Default constructor
        SideCrossIterator(const MagicalContainer& other, int left, int right); // Constructor with container reference and indices
        SideCrossIterator(const SideCrossIterator& sideCrossIter); // Copy constructor
        SideCrossIterator(SideCrossIterator&&) = delete;
        SideCrossIterator& operator=(SideCrossIterator&&) = delete;
        ~SideCrossIterator(); // Destructor
        
        // Member functions
        SideCrossIterator& operator=(const SideCrossIterator& other); // Assignment operator
        bool operator==(const SideCrossIterator& other) const; // Equality comparison operator
        bool operator!=(const SideCrossIterator& other) const; // Inequality comparison operator
        bool operator>(const SideCrossIterator& other) const; // Greater than comparison operator
        bool operator<(const SideCrossIterator& other) const; // Less than comparison operator
        int operator*(); // Dereference operator
        SideCrossIterator& operator++(); // Pre-increment operator
        SideCrossIterator begin(); // Get the iterator pointing to the first element
        SideCrossIterator end(); // Get the iterator pointing to the element after the last element
    };

    /* PrimeIterator class */
    class MagicalContainer::PrimeIterator
    {
    private:
        const MagicalContainer& container; // Reference to the container
        int currentIndex; // Current index of the iterator
        
    public:
        // Constructors
        PrimeIterator(const MagicalContainer& container); // Default constructor
        PrimeIterator(const MagicalContainer& other, int index); // Constructor with container reference and index
        PrimeIterator(const PrimeIterator& primeIter); // Copy constructor
        PrimeIterator(PrimeIterator&&) = delete;
        PrimeIterator& operator=(PrimeIterator&&) = delete;
        ~PrimeIterator(); // Destructor
        
        // Member functions
        PrimeIterator& operator=(const PrimeIterator& other); // Assignment operator
        bool operator==(const PrimeIterator& other) const; // Equality comparison operator
        bool operator!=(const PrimeIterator& other) const; // Inequality comparison operator
        bool operator>(const PrimeIterator& other) const; // Greater than comparison operator
        bool operator<(const PrimeIterator& other) const; // Less than comparison operator
        int operator*(); // Dereference operator
        PrimeIterator& operator++(); // Pre-increment operator
        PrimeIterator begin(); // Get the iterator pointing to the first element
        PrimeIterator end(); // Get the iterator pointing to the element after the last element
    };
} // namespace ariel
