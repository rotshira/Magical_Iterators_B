#include "MagicalContainer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <math.h>
namespace ariel 
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MagicalContainer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

MagicalContainer::MagicalContainer()
{
    // Default constructor 
}
// Copy constructor - copy the elements and prime numbers from the other container
MagicalContainer::MagicalContainer(MagicalContainer& other)
{
    this->elements = other.elements;
    this->numbers_prime = other.numbers_prime;
}

MagicalContainer::~MagicalContainer()
{
    // Destructor
}

// Function to add an element to the container
void MagicalContainer::addElement(int element)
{
    elements.push_back(element); // Add the element to the elements vector

    if (isPrime(element)) // Check if the element is prime
    {
        numbers_prime.push_back(element); // If it is prime, add it to the prime numbers vector
    }
}

// Function to remove an element from the container
void MagicalContainer::removeElement(int element)
{
    bool found = false; // Flag to indicate if the element is found

    for (auto it = elements.begin(); it != elements.end(); ++it)
    {
        if (*it == element) // If the element is found
        {
            elements.erase(it); // Erase the element from the elements vector
            found = true;
            delete_(numbers_prime, element); // Remove the element from the prime numbers vector
            break; // Exit the loop after the first occurrence is removed
        }
    }

    if (!found) // If the element is not found
    {
        throw std::runtime_error("Element not found");
    }
}

// Function to get a constant reference to the elements vector
const std::vector<int>& MagicalContainer::getElements() const
{
    return elements;
}

// Function to get a constant reference to the prime numbers vector
const std::vector<int>& MagicalContainer::get_primes() const
{
    return numbers_prime;
}

// Function to check if a number is prime
bool MagicalContainer::isPrime(int number)
{
    if (number < 2)
        return false;

    for (int i = 2; i <= sqrt(number); ++i)
    {
        if (number % i == 0)
            return false;
    }

    return true;
}

// Function to delete an element from a vector
void MagicalContainer::delete_(std::vector<int>& vector_, int n)
{
    vector_.erase(std::remove(vector_.begin(), vector_.end(), n), vector_.end());
}

// Function to get the size of the container
int MagicalContainer::size() const
{
    int size_ = elements.size();
    return size_;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//AscendingIterator
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // Constructor for AscendingIterator
MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& container)
    : container(container), currentIndex(0)
{
    // Initialize the iterator with the provided container and set the current index to 0
}

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer& other, int index)
    : container(other), currentIndex(index)
{
    // Initialize the iterator with the provided container and set the current index to the provided value
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : container(other.container), currentIndex(other.currentIndex)
{
    // Copy constructor for AscendingIterator - copy the container and current index from the other iterator
}

MagicalContainer::AscendingIterator::~AscendingIterator()
{
    // Destructor for AscendingIterator - no explicit cleanup is needed
}

// Assignment operator for AscendingIterator
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
{
    if (this != &other)
    {
        if (&container != &(other.container))
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        currentIndex = other.currentIndex;
    }
    return *this;
}

// Equality operator for AscendingIterator
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const
{
    return currentIndex == other.currentIndex;
}

// Inequality operator for AscendingIterator
bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const
{
    return !(*this == other);
}

// Greater than operator for AscendingIterator
bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const
{
    return currentIndex > other.currentIndex;
}

// Less than operator for AscendingIterator
bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const
{
    return currentIndex < other.currentIndex;
}

// Dereference operator for AscendingIterator
int MagicalContainer::AscendingIterator::operator*()
{
    if (currentIndex >= container.size())
    {
        throw std::runtime_error("Iterator out of range");
    }
    std::vector<int> sortedElements = container.getElements();
    std::sort(sortedElements.begin(), sortedElements.end());
    // Sort the elements in ascending order
    return sortedElements[static_cast<std::vector<int>::size_type>(currentIndex)];
    // Return the element at the current index
}

// Pre-increment operator for AscendingIterator
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
{
    if (currentIndex < container.size())
    {
        ++currentIndex;
    }
    else
    {
        throw std::runtime_error("Iterator increment beyond end");
    }
    // Increment the current index to move to the next element
    return *this;
}

// Begin function for AscendingIterator
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    return AscendingIterator(container, 0);
    // Return an iterator pointing to the beginning of the container (index 0)
}

// End function for AscendingIterator
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    return AscendingIterator(container, container.size());
    // Return an iterator pointing to the end of the container (index equal to container size)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SideCrossIterator
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Constructor for SideCrossIterator
MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& container)
    : container(container), leftIndex(0), rightIndex(container.size()), use(true)
{
    
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer& container, int left, int right)
    : container(container), leftIndex(left), rightIndex(right), use(true)
{
    
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : container(other.container), leftIndex(other.leftIndex), rightIndex(other.rightIndex), use(other.use)
{
    // Copy constructor for SideCrossIterator - copy the container, left index, right index, and 'use' flag from the other iterator
}

MagicalContainer::SideCrossIterator::~SideCrossIterator()
{
    // Destructor for SideCrossIterator - no explicit cleanup is needed
}

// Assignment operator for SideCrossIterator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
{
    if (this != &other)
    {
        if (&container != &(other.container))
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        leftIndex = other.leftIndex;
        rightIndex = other.rightIndex;
        use = other.use;
    }
    return *this;
}

// Equality operator for SideCrossIterator
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const
{
    return (leftIndex == other.leftIndex && rightIndex == other.rightIndex);
}

// Inequality operator for SideCrossIterator
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const
{
    return !(*this == other);
}

// Greater than operator for SideCrossIterator
bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const
{
    return (leftIndex > other.leftIndex || rightIndex < other.rightIndex);
}

// Less than operator for SideCrossIterator
bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const
{
    return (leftIndex < other.leftIndex || rightIndex > other.rightIndex);
}

// Dereference operator for SideCrossIterator
int MagicalContainer::SideCrossIterator::operator*()
{
    if (leftIndex > rightIndex)
    {
        throw std::runtime_error("Iterator out of range");
    }
    std::vector<int> sortedElements = container.getElements();
    std::sort(sortedElements.begin(), sortedElements.end());
    if (use)
    {
        return sortedElements[static_cast<std::vector<int>::size_type>(leftIndex)];
    }
    else
    {
        return sortedElements[static_cast<std::vector<int>::size_type>(rightIndex)];
    }
    // Sort the elements in ascending order
    // If the 'use' flag is true, return the element at the left index
    // Otherwise, return the element at the right index
}

// Pre-increment operator for SideCrossIterator
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
{
    if (leftIndex >= rightIndex)
    {
        throw std::runtime_error("Iterator out of range");
    }
    // If the left index is greater than or equal to the right index, the iterator is out of range

    if (use)
    {
        rightIndex--;
        use = false;
    }
    else
    {
        leftIndex++;
        use = true;
    }
    

    return *this;
}

// Begin function for SideCrossIterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    return SideCrossIterator(container, 0, container.size());
    // Return an iterator pointing to the beginning of the container
    // Set the left index to 0 and the right index to the container size
}

// End function for SideCrossIterator
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    if (container.size() % 2 == 0)
    {
        return SideCrossIterator(container, container.size() / 2, container.size() / 2);
    }
    else
    {
        return SideCrossIterator(container, container.size() / 2, container.size() / 2);
    }
   
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PrimeIterator
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Constructor for PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& other)
    : container(other), currentIndex(0)
{
    // Initialize the iterator with the provided container
    // Set the current index to 0 (beginning of container)
}

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer& other, int index)
    : container(other), currentIndex(index)
{
    // Initialize the iterator with the provided container
    // Set the current index to the provided value
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : container(other.container), currentIndex(other.currentIndex)
{
    // Copy constructor for PrimeIterator - copy the container and current index from the other iterator
}

MagicalContainer::PrimeIterator::~PrimeIterator()
{
    // Destructor for PrimeIterator - no explicit cleanup is needed
}

// Assignment operator for PrimeIterator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
{
    if (this != &other)
    {
        if (&container != &(other.container))
        {
            throw std::runtime_error("Iterators are pointing to different containers");
        }
        currentIndex = other.currentIndex;
    }
    return *this;
}

// Equality operator for PrimeIterator
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const
{
    return currentIndex == other.currentIndex;
}

// Inequality operator for PrimeIterator
bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const
{
    return !(*this == other);
}

// Greater than operator for PrimeIterator
bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const
{
    return currentIndex > other.currentIndex;
}

// Less than operator for PrimeIterator
bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const
{
    return currentIndex < other.currentIndex;
}

// Dereference operator for PrimeIterator
int MagicalContainer::PrimeIterator::operator*()
{
    if (currentIndex >= this->container.get_primes().size())
    {
        throw std::runtime_error("Iterator out of range");
    }
    
    std::vector<int> sortedElements = container.get_primes();
    std::sort(sortedElements.begin(), sortedElements.end());
    // Sort the prime elements in ascending order

    return sortedElements[static_cast<std::vector<int>::size_type>(currentIndex)];
    // Return the prime element at the current index
}

// Pre-increment operator for PrimeIterator
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
{
    if (currentIndex + 1 > this->container.get_primes().size())
    {
        throw std::runtime_error("Iterator out of range");
    }
    // If incrementing the current index by 1 exceeds the size of the prime elements, the iterator is out of range

    currentIndex++;
    // Increment the current index by 1

    return *this;
}

// Begin function for PrimeIterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    currentIndex = 0;
    // Set the current index to 0 (beginning of prime elements)

    return *this;
    // Return an iterator pointing to the beginning of the prime elements
}

// End function for PrimeIterator
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    currentIndex = container.get_primes().size();
    // Set the current index to the size of the prime elements

    return *this;
    // Return an iterator pointing to the end of the prime elements
}


} // namespace ariel