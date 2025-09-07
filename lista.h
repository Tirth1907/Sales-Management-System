#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

// Forward declaration of the LinkedList class
template <class T>
class LinkedList;

// --- Node Class ---
// The Node class is an inner helper class for the LinkedList.
// It holds a data value and a pointer to the next node.
template <class T>
class Node {
private:
    T data;
    Node<T>* next;

public:
    Node(T value) : data(value), next(nullptr) {}
    ~Node() {}

    T getData() const { return data; }
    Node<T>* getNext() const { return next; }
    void setNext(Node<T>* newNext) { next = newNext; }
};

// --- LinkedList Class ---
// This is the main class for the linked list.
template <class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    // Constructors and Destructor
    LinkedList();
    LinkedList(const LinkedList<T>& other);
    ~LinkedList();

    // Operator Overloading
    LinkedList<T>& operator=(const LinkedList<T>& other);

    // Core Functionality
    bool isEmpty() const;
    void append(T value);
    void prepend(T value);
    void insert(T value, int pos);
    void erase(int pos);
    void clear();
    void reverse();

    // Accessors
    int size() const;
    T at(int pos) const;
    void display() const;
};

// --- Method Definitions ---

// Default Constructor
template <class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

// Copy Constructor
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), count(0) {
    Node<T>* current = other.head;
    while (current != nullptr) {
        append(current->getData());
        current = current->getNext();
    }
}

// Destructor
template <class T>
LinkedList<T>::~LinkedList() {
    clear();
}

// Copy Assignment Operator
template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        clear();
        Node<T>* current = other.head;
        while (current != nullptr) {
            append(current->getData());
            current = current->getNext();
        }
    }
    return *this;
}

// Check if the list is empty
template <class T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}

// Get the size of the list
template <class T>
int LinkedList<T>::size() const {
    return count;
}

// Add an element to the end of the list
template <class T>
void LinkedList<T>::append(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->setNext(newNode);
        tail = newNode;
    }
    count++;
}

// Add an element to the beginning of the list
template <class T>
void LinkedList<T>::prepend(T value) {
    Node<T>* newNode = new Node<T>(value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->setNext(head);
        head = newNode;
    }
    count++;
}

// Insert an element at a specific position
template <class T>
void LinkedList<T>::insert(T value, int pos) {
    if (pos < 0 || pos > count) {
        std::cerr << "Error: Position out of bounds." << std::endl;
        return;
    }
    if (pos == 0) {
        prepend(value);
    } else if (pos == count) {
        append(value);
    } else {
        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        count++;
    }
}

// Erase an element at a specific position
template <class T>
void LinkedList<T>::erase(int pos) {
    if (isEmpty() || pos < 0 || pos >= count) {
        std::cerr << "Error: Position out of bounds or list is empty." << std::endl;
        return;
    }

    Node<T>* toDelete;
    if (pos == 0) {
        toDelete = head;
        head = head->getNext();
        if (head == nullptr) {
            tail = nullptr;
        }
    } else {
        Node<T>* current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->getNext();
        }
        toDelete = current->getNext();
        current->setNext(toDelete->getNext());
        if (pos == count - 1) {
            tail = current;
        }
    }
    delete toDelete;
    count--;
}

// Get the value at a specific position
template <class T>
T LinkedList<T>::at(int pos) const {
    if (pos < 0 || pos >= count) {
        throw std::out_of_range("Error: Position out of bounds.");
    }

    Node<T>* current = head;
    for (int i = 0; i < pos; ++i) {
        current = current->getNext();
    }
    return current->getData();
}

// Clear the entire list (deallocate all nodes)
template <class T>
void LinkedList<T>::clear() {
    while (head != nullptr) {
        Node<T>* toDelete = head;
        head = head->getNext();
        delete toDelete;
    }
    tail = nullptr;
    count = 0;
}

// Display all elements in the list
template <class T>
void LinkedList<T>::display() const {
    if (isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->getData() << " -> ";
        current = current->getNext();
    }
    std::cout << "NULL" << std::endl;
}

// Reverse the list
template <class T>
void LinkedList<T>::reverse() {
    if (count <= 1) {
        return;
    }

    Node<T>* prev = nullptr;
    Node<T>* current = head;
    Node<T>* next = nullptr;
    tail = head; // The old head becomes the new tail

    while (current != nullptr) {
        next = current->getNext();
        current->setNext(prev);
        prev = current;
        current = next;
    }
    head = prev; // The old tail becomes the new head
}

#endif