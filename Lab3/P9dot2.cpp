#include "P9dot2.h"
#include <string>
#include <exception>
#include <iostream>

namespace P9dot2 {
	NotFound::NotFound(const std::string& message)
	{
		m_message = message;
	}

	NotFound::~NotFound() {}

	std::string NotFound::getMessage() const
	{
		return m_message;
	}

	DuplicateKey::DuplicateKey(const std::string& message)
	{
		m_message = message;
	}

	DuplicateKey::~DuplicateKey() {}

	std::string DuplicateKey::getMessage() const
	{
		return m_message;
	}

	DictionaryElement::DictionaryElement(int key, int value)
	{
		m_key = key;
		m_value = value;
	}

	DictionaryElement::~DictionaryElement()
	{
		// nothing to do here...
	}

	const int DictionaryElement::getKey()
	{
		return m_key;
	}

	const int DictionaryElement::getValue()
	{
		return m_value;
	}

	MyDictionary::MyDictionary()
	{
		// Dictionary initializes a new empty list when instantiated
		m_list = new std::list<DictionaryElement>;
	}

	MyDictionary::~MyDictionary()
	{
		// Delete the list
		delete m_list;
	}

	// Basic dictionary functions
	const int MyDictionary::size()
	{
		return m_list->size();
	}

	const bool MyDictionary::empty()
	{
		return m_list->empty();
	}

	const MyDictionary::Iterator MyDictionary::find(int key)
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
		throw NotFound("The item was not found in the dictionary.");
	}

	MyDictionary::Iterator MyDictionary::insert(DictionaryElement element)
	{
		// Make sure this isn't a duplicate key before inserting
		if (this->contains(element.getKey()))
		{
			throw DuplicateKey("An element with that key already exists.");
		}

		// Place the element at the end of the list
		m_list->emplace_back(element);

		// Grab an iterator at the end of the list
		Iterator position = m_list->end();

		// Decrement it, now it will be pointing to the new element we just inserted
		position--;

		// Return this iterator
		return position;
	}

	void MyDictionary::erase(int key)
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

	void MyDictionary::erase(Iterator atPosition)
	{
		// Erase the item at the position of the iterator provided
		m_list->erase(atPosition);
	}
	
	const MyDictionary::Iterator MyDictionary::begin()
	{
		return m_list->begin();
	}

	const MyDictionary::Iterator MyDictionary::end()
	{
		Iterator lastElement = m_list->end()--;

		lastElement--;

		return lastElement;
	}

	const bool MyDictionary::contains(int key)
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
		std::cout << "Testing all of the dictionary functions..." << std::endl;

		// Create some elements
		DictionaryElement element1 = DictionaryElement(1, 1);
		DictionaryElement element2 = DictionaryElement(2, 2);
		DictionaryElement element3 = DictionaryElement(3, 3);
		DictionaryElement element4 = DictionaryElement(4, 4);
		DictionaryElement element5 = DictionaryElement(5, 5);
		
		// Create a new dictionary
		MyDictionary myDictionary;

		// Check empty
		if (myDictionary.empty())
		{
			std::cout << "It's empty!" << std::endl;
		}

		// Check size (0)
		std::cout << "Current size: " << myDictionary.size() << std::endl;

		// Insert an element
		myDictionary.insert(element1);

		// Check empty (false)
		if (!myDictionary.empty())
		{
			std::cout << "There are some items." << std::endl;
		}

		// Check size (1)
		std::cout << "Current size: " << myDictionary.size() << std::endl;
		
		// Do a check to make sure that the insert returns a proper iterator
		std::list<DictionaryElement>::iterator testInsert = myDictionary.insert(element2);

		// Insert the rest of the elements
		myDictionary.insert(element3);
		myDictionary.insert(element4);
		myDictionary.insert(element5);

		// Try inserting a duplicate key
		DictionaryElement elementSameAsElement3 = DictionaryElement(3, 3);

		try 
		{
			myDictionary.insert(elementSameAsElement3);
		}
		catch(DuplicateKey exception)
		{
			std::cout << exception.getMessage() << std::endl;
		}

		// Test begin
		std::list<DictionaryElement>::iterator begin = myDictionary.begin();

		std::cout << "Key for element at beginning: " << (*begin).getKey() << std::endl;
		std::cout << "Value for element at beginning: " << (*begin).getValue() << std::endl;

		// Test end
		std::list<DictionaryElement>::iterator end = myDictionary.end();

		std::cout << "Key for element at end: " << (*end).getKey() << std::endl;
		std::cout << "Value for element at end: " << (*end).getValue() << std::endl;

		// Test finding something with key = 1
		try
		{
			std::list<DictionaryElement>::iterator findSomething = myDictionary.find(1);

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