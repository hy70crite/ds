#include <iostream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Insert at the beginning
    void insertFront(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Insert at the end
    void insertBack(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Delete from the beginning
    void deleteFront() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    // Delete from the end
    void deleteBack() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

    // Insert after a given node
    void insertAfter(Node* prevNode, int value) {
        if (!prevNode) return;
        Node* newNode = new Node(value);
        newNode->next = prevNode->next;
        newNode->prev = prevNode;
        if (prevNode->next) prevNode->next->prev = newNode;
        prevNode->next = newNode;
        if (prevNode == tail) tail = newNode;
    }

    // Delete a given node
    void deleteNode(Node* nodeToDelete) {
        if (!nodeToDelete) return;
        if (nodeToDelete == head) head = nodeToDelete->next;
        if (nodeToDelete == tail) tail = nodeToDelete->prev;
        if (nodeToDelete->prev) nodeToDelete->prev->next = nodeToDelete->next;
        if (nodeToDelete->next) nodeToDelete->next->prev = nodeToDelete->prev;
        delete nodeToDelete;
    }

    // Search for a value
    Node* search(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) return current;
            current = current->next;
        }
        return nullptr;
    }

    // Print the list forward
    void printForward() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Print the list backward
    void printBackward() {
        Node* current = tail;
        while (current) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }

    // Destructor to free memory
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    DoublyLinkedList list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertFront(0);

    std::cout << "Forward: ";
    list.printForward();
    std::cout << "Backward: ";
    list.printBackward();

    Node* node = list.search(2);
    std::cout << "After inserting 4 after 2:\n";
    std::cout << "Forward: ";
    list.printForward();
    std::cout << "Backward: ";
    list.printBackward();

    list.deleteFront();
    list.deleteBack();

    std::cout << "After deleting front and back:\n";
    std::cout << "Forward: ";
    list.printForward();
    std::cout << "Backward: ";
    list.printBackward();

    Node* nodeToDelete = list.search(2);
    if (nodeToDelete) list.deleteNode(nodeToDelete);

    std::cout << "After deleting node with value 2:\n";
    std::cout << "Forward: ";
    list.printForward();
    std::cout << "Backward: ";
    list.printBackward();

    return 0;
}
