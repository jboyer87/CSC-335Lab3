#pragma once
#include <list>

// Write an implementation of the dictionary ADT using a linked list.

namespace P9dot2 {
	class DictionaryElement
	{
	public:
		DictionaryElement(int key, int value);
		~DictionaryElement();
		const int getKey();
		const int getValue();

	private:
		int m_key;
		int m_value;

		// Dictionary is a friend so that it can access the key/value pair
		friend class MyDictionary;
	};

	// Custom exception to be usesd below in the dictionary class
	class DuplicateKey : std::exception
	{
	public:
		DuplicateKey(const std::string& message);

		~DuplicateKey();

		std::string getMessage() const;

	private:
		std::string m_message;
	};

	// Custom exception to be used below in the dictionary class
	class NotFound : std::exception
	{
	public:
		NotFound(const std::string& message);

		~NotFound();

		std::string getMessage() const;

	private:
		std::string m_message;
	};

	class MyDictionary
	{
		typedef std::list<DictionaryElement>::iterator Iterator;
	public:
		MyDictionary();
		~MyDictionary();

		// Basic dictionary functions
		const int size(); // Returns the size (number of items) in the m_list
		const bool empty(); // Returns true if the size of m_list is 0, or false if not
		const Iterator find(int key); // Returns an iterator pointing to the node with key present, or exception if not found
		Iterator insert(DictionaryElement element); // Inserts a new key/value pair and returns an iterator to the location
		void erase(int key); // Removes an element from the list matching the key
		void erase(Iterator atPosition); // Removes an element from the list at the position referenced by the iterator
		const Iterator begin(); // Returns an iterator pointing to the first item in the list
		const Iterator end(); // Returns an iterator pointing to the last item in the list

		// Additional methods I included for utility
		const bool contains(int key); // Returns true if the list contains an element with the matching key

	private:
		std::list<DictionaryElement> *m_list;
	};

	void run();
}