#include <iostream>
using namespace std;

const int MAX_SIZE = 100;
int arr[MAX_SIZE];
int size = 0;

// Search operation
int search(int key) {
    int left = 0;
    int right = ::size - 1; // Use ::size to refer to the global variable size

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid; // Return the index if key is found
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // Return -1 if key is not found
}

// Insert operation
void insert(int key) {
    if (::size >= MAX_SIZE) { // Use ::size to refer to the global variable size
        cout << "Array is full. Cannot insert element." << endl;
        return;
    }

    int i = ::size - 1; // Use ::size to refer to the global variable size
    while (i >= 0 && arr[i] > key) {
        arr[i + 1] = arr[i];
        i--;
    }

    arr[i + 1] = key;
    ::size++; // Use ::size to refer to the global variable size
    cout << "Element inserted successfully." << endl;
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

