#include <iostream>
using namespace std;

const int MAX_SIZE = 100;
int arr[MAX_SIZE];
int size = 0;

// Search operation
int search(int key) {
    for (int i = 0; i < ::size; i++) { // Use ::size to refer to the global variable size
        if (arr[i] == key) {
            return i; // Return the index if key is found
        }
    }
    return -1; // Return -1 if key is not found
}

// Insert operation
void insert(int key) {
    if (::size < MAX_SIZE) { // Use ::size to refer to the global variable size
        arr[::size] = key; // Use ::size to refer to the global variable size
        ::size++; // Use ::size to refer to the global variable size
        cout << "Element inserted successfully." << endl;
    } else {
        cout << "Array is full. Cannot insert element." << endl;
    }
}

// Delete operation
void remove(int key) {
    int index = search(key);
    if (index != -1) {
        for (int i = index; i < ::size - 1; i++) { // Use ::size to refer to the global variable size
            arr[i] = arr[i + 1];
        }
        ::size--; // Use ::size to refer to the global variable size
        cout << "Element deleted successfully." << endl;
    } else {
        cout << "Element not found in the array." << endl;
    }
}

int main() {
    insert(5);
    insert(10);
    insert(15);

    int key = 10;
    int index = search(key);
    if (index != -1) {
        cout << "Element found at index: " << index << endl;
    } else {
        cout << "Element not found in the array." << endl;
    }

    remove(10);

    key = 10;
    index = search(key);
    if (index != -1) {
        cout << "Element found at index: " << index << endl;
    } else {
        cout << "Element not found in the array." << endl;
    }

    return 0;
}

