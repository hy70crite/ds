#include <iostream>
using namespace std;

// Node class to represent each node in the linked list
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Linked List class to manage the linked list operations
class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    // Search operation
    bool search(int key) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == key) {
                return true; // Key found
            }
            current = current->next;
        }
        return false; // Key not found
    }

    // Insert operation at the beginning of the linked list
    void insert(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        cout << "Element inserted successfully." << endl;
    }

    // Delete operation
    void remove(int key) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr && current->data != key) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Element not found in the linked list." << endl;
            return;
        }

        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "Element deleted successfully." << endl;
    }
};

int main() {
    LinkedList list;

    list.insert(5);
    list.insert(10);
    list.insert(15);

    if (list.search(10)) {
        cout << "Element 10 found in the linked list." << endl;
    } else {
        cout << "Element 10 not found in the linked list." << endl;
    }

    list.remove(10);

    if (list.search(10)) {
        cout << "Element 10 found in the linked list." << endl;
    } else {
        cout << "Element 10 not found in the linked list." << endl;
    }

    return 0;
}

