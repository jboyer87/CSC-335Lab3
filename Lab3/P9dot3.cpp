#include "P9dot3.h"
#include <string>
#include <exception>
#include <iostream>

namespace P9dot3 {
	NotFound::NotFound(const std::string& message)
	{
		m_message = message;
	}

	NotFound::~NotFound() {}

	std::string NotFound::getMessage() const
	{
		return m_message;
	}

	MapElement::MapElement(int key, int value)
	{
		m_key = key;
		m_value = value;
	}

	MapElement::~MapElement()
	{
		// nothing to do here...
	}

	const int MapElement::getKey()
	{
		return m_key;
	}

	const int MapElement::getValue()
	{
		return m_value;
	}

	void MapElement::setValue(const int &value)
	{
		m_value = value;
	}

	MyMap::MyMap()
	{
		// Map initializes a new empty list when instantiated
		m_list = new std::vector<MapElement>;
	}

	MyMap::~MyMap()
	{
		// Delete the list
		delete m_list;
	}

	const int MyMap::size()
	{
		return m_list->size();
	}

	const bool MyMap::empty()
	{
		return m_list->empty();
	}

	const MyMap::Iterator MyMap::find(int key)
	{
		Iterator iterator = m_list->begin();

		// Walk the list from beginning to end
		while (iterator != m_list->end())
		{
			// If the value is found, return the iterator
			if ((*iterator).getKey() == key)
			{
				return iterator;
			}

			// Advance the iterator each time
			iterator++;
		}

		// Throw an exception if we get this far, means it was not found
		throw NotFound("The item was not found in the map.");
	}

	MyMap::Iterator MyMap::put(int key, int value)
	{
		// Initialize a bool to track whether the value is found
		bool found = false;

		// Iterate through the list
		for (MyMap::Iterator iterator = this->begin(); iterator != this->end(); iterator++)
		{
			// If this is the key we were looking for, update it and break
			if ((*iterator).getKey() == key)
			{
				// Set found to true
				found = true;

				(*iterator).setValue(value);

				// Return here if we found and set the value successfully
				return iterator;
			}
		}

		// If the key wasn't found just insert it
		if (found == false)
		{
			this->m_list->emplace_back(MapElement(key, value));

			// Set up a new iterator to return, pointed at the end which will be the new element
			Iterator newElement = this->end();

			return newElement;
		}
	}

	void MyMap::erase(int key)
	{
		Iterator iterator = m_list->begin();

		for (Iterator iterator = m_list->begin(); iterator != m_list->end(); iterator++)
		{
			// If the value is found, erase the element that the iterator points to
			if ((*iterator).getKey() == key)
			{
				m_list->erase(iterator);
				break;
			}
		}

		// If we get this far, we did not find the matching element, throw exception
		throw NotFound("The element matching that key was not found.");
	}

	void MyMap::erase(Iterator atPosition)
	{
		// Erase the item at the position of the iterator provided
		m_list->erase(atPosition);
	}

	const MyMap::Iterator MyMap::begin()
	{
		return m_list->begin();
	}

	const MyMap::Iterator MyMap::end()
	{
		if (m_list->empty())
		{
			Iterator lastElement = m_list->begin();
			return lastElement;
		}
		else
		{
			Iterator lastElement = --m_list->end();
			return lastElement;
		}
	}

	const bool MyMap::contains(int key)
	{
		for (Iterator iterator = m_list->begin(); iterator != m_list->end(); iterator++)
		{
			if ((*iterator).getKey() == key)
			{
				// Return true if the list contains the key somewhere
				return true;
			}
		}
		// Return false if we get this far
		return false;
	}

	void run()
	{
		std::cout << "Testing all of the map functions..." << std::endl;

		// Create a new map
		MyMap myMap;

		// Check empty
		if (myMap.empty())
		{
			std::cout << "It's empty!" << std::endl;
		}

		// Check size (0)
		std::cout << "Current size: " << myMap.size() << std::endl;

		// Put an element
		myMap.put(1, 1);

		// Check empty (false)
		if (!myMap.empty())
		{
			std::cout << "There are some items." << std::endl;
		}

		// Check size (1)
		std::cout << "Current size: " << myMap.size() << std::endl;

		// Do a check to make sure that the put returns a proper iterator
		std::vector<MapElement>::iterator testPut = myMap.put(2, 2);

		// Put the rest of the elements
		myMap.put(3, 3);
		myMap.put(4, 4);
		myMap.put(5, 5);

		// Try inserting a duplicate key - this should update the value
		myMap.put(3, 13);

		// Test begin
		std::vector<MapElement>::iterator begin = myMap.begin();

		std::cout << "Key for element at beginning: " << (*begin).getKey() << std::endl;
		std::cout << "Value for element at beginning: " << (*begin).getValue() << std::endl;

		// Test end
		std::vector<MapElement>::iterator end = myMap.end();

		std::cout << "Key for element at end: " << (*end).getKey() << std::endl;
		std::cout << "Value for element at end: " << (*end).getValue() << std::endl;

		// Test finding something with key = 1
		try
		{
			std::vector<MapElement>::iterator findSomething = myMap.find(1);

			// If it's found, show the key/value pair
			std::cout << "Found it, here's the key/value pair: " << (*findSomething).getKey() << "/" << (*findSomething).getValue() << std::endl;
		}
		catch (NotFound exception)
		{
			// Catch the notfound exception and output the error message if it isn't found
			std::cout << exception.getMessage() << std::endl;
		}
	}
}