#pragma once
#include <list>

// Give a C++ implementation of a priority queue based on an unsorted list.

namespace P8dot2 {
	class PriorityQueueElement {
	public:
		PriorityQueueElement(int key, int value);
		~PriorityQueueElement();
		const int getKey();
		const int getValue();

	private:
		int m_key;
		int m_value;
	};

	class MyPriorityQueue {
		typedef std::list<PriorityQueueElement> ElementList;
		typedef int Comparator;
		typedef std::list<PriorityQueueElement>::iterator Iterator;
	public:
		const int size(); // Returns the size (number of items) in the m_list
		const bool empty(); // Returns true if the size of m_list is 0, or false if not
		void insert(PriorityQueueElement& element); // Keeps the list sorted as elements are inserted
		PriorityQueueElement& min(); // Returns a reference to the minimum value
		void removeMin(); // Removes the minimum value from the list

		void displayElements();
	private:
		ElementList m_elements;
	};

	void run();
}