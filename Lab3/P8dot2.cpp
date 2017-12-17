#include "P8dot2.h"
#include <string>
#include <exception>
#include <iostream>

namespace P8dot2 {
	PriorityQueueElement::PriorityQueueElement(int key, int value)
	{
		m_key = key;
		m_value = value;
	}

	PriorityQueueElement::~PriorityQueueElement()
	{
		// nothing to do here...
	}

	const int PriorityQueueElement::getKey()
	{
		return m_key;
	}

	const int PriorityQueueElement::getValue()
	{
		return m_value;
	}


	const int MyPriorityQueue::size()
	{
		return m_elements.size();
	}

	const bool MyPriorityQueue::empty()
	{
		return m_elements.empty();
	}

	void MyPriorityQueue::insert(PriorityQueueElement& element)
	{

		// Grab an iterator at the start of the list
		Iterator iterator = this->m_elements.begin();

		// Walk through until we reach the end
		while (iterator != this->m_elements.end() && !(element.getKey() < (*iterator).getKey()))
		{
			++iterator;
		}

		// The iterator should be at the correct spot now
		m_elements.insert(iterator, element);
	}

	PriorityQueueElement& MyPriorityQueue::min()
	{
		// Element in the front is always going to be the minimum element
		return this->m_elements.front();
	}

	void MyPriorityQueue::removeMin()
	{
		// Element in the front is always going to be the minimum element, remove it
		this->m_elements.pop_front();
	}

	void MyPriorityQueue::displayElements()
	{
		std::cout << "[ ";

		std::list<PriorityQueueElement>::iterator iterator = m_elements.begin();
		if (this->empty())
		{
			std::cout << "empty";
		}
		else
		{
			while (iterator != m_elements.end())
			{
				std::cout << (*iterator).getKey() << "/" << (*iterator).getValue();

				iterator++;

				if(iterator != m_elements.end())
				{
					std::cout << ", ";
				}
			}
		}

		std::cout << " ]" << std::endl;
	}
	
	void run()
	{
		std::cout << "Testing all of the priority queue functions..." << std::endl;

		// Create some elements
		PriorityQueueElement element4 = PriorityQueueElement(4, 4);
		PriorityQueueElement element2 = PriorityQueueElement(2, 2);
		PriorityQueueElement element10 = PriorityQueueElement(44, 3);
		PriorityQueueElement element1 = PriorityQueueElement(1, 1);
		PriorityQueueElement element8 = PriorityQueueElement(93, 3);
		PriorityQueueElement element9 = PriorityQueueElement(2, 3);
		PriorityQueueElement element3 = PriorityQueueElement(3, 3);
		PriorityQueueElement element5 = PriorityQueueElement(5, 5);
		PriorityQueueElement element6 = PriorityQueueElement(10, 3);
		PriorityQueueElement element7 = PriorityQueueElement(2, 4);


		// Create a new priority queue
		MyPriorityQueue myPriorityQueue;

		// Check empty
		if (myPriorityQueue.empty())
		{
			std::cout << "It's empty!" << std::endl;
		}

		// Check size (0)
		std::cout << "Current size: " << myPriorityQueue.size() << std::endl;

		// Insert an element
		myPriorityQueue.insert(element1);

		// Check empty (false)
		if (!myPriorityQueue.empty())
		{
			std::cout << "There are some items." << std::endl;
		}

		// Check size (1)
		std::cout << "Current size: " << myPriorityQueue.size() << std::endl;

		// Insert the rest of the elements
		myPriorityQueue.insert(element4);
		myPriorityQueue.insert(element3);
		myPriorityQueue.insert(element5);
		myPriorityQueue.insert(element10);
		myPriorityQueue.insert(element8);
		myPriorityQueue.insert(element9);
		myPriorityQueue.insert(element7);
		myPriorityQueue.insert(element6);

		// All of the values have been inserted, print it out in order
		myPriorityQueue.displayElements();

		// Test min
		std::cout << "The minimum element key/value pair is: " << myPriorityQueue.min().getKey() << "/" << myPriorityQueue.min().getValue() << std::endl;

		// Test remove min
		myPriorityQueue.removeMin();

		// Test min again to show that it has been updated
		std::cout << "The minimum element key/value pair is now: " << myPriorityQueue.min().getKey() << "/" << myPriorityQueue.min().getValue() << std::endl;

		myPriorityQueue.displayElements();
	}
}