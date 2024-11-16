#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <array>
#include <chrono>
#include "SearchTree.h"

using namespace std;
using namespace std::chrono;

// Problem 2
//TPos finder(const K& k, const TPos& v) {
//    TPos current = v;
//    while (!current.isExternal()) {
//        if (k < current->key()) {
//            current = current.left();
//        }
//        else if (current->key() < k) {
//            current = current.right()
//        }
//        else {
//            return current;
//        }
//    }
//    return current;
//}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void mergeDescending(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] > R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSortDescending(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortDescending(arr, left, mid);        
        mergeSortDescending(arr, mid + 1, right); 

        mergeDescending(arr, left, mid, right);
    }
}

void quickSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    int p = arr[right];

    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] < p) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[right]);

    quickSort(arr, left, i);
    quickSort(arr, i + 2, right);
}

void quickSortDescending(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }

    int p = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] > p) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);

    quickSortDescending(arr, left, i);
    quickSortDescending(arr, i + 2, right);
}


void heapify(int arr[], int size, int i)
{
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2; 

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);

    for (int i = size - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

void heapifyDescending(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapifyDescending(arr, n, smallest);
    }
}

void heapSortDescending(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDescending(arr, n, i);
    }

    for (int i = n - 1; i >= 1; i--) {
        swap(arr[0], arr[i]);
        heapifyDescending(arr, i, 0);
    }
}


void copyArray(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) {
        arr2[i] = arr1[i];
    }
}

bool sameArray(int* arr1, int* arr2, int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

void printSpaces() {
    for (int i = 0; i < 1000; i++) {
        cout << endl;
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << endl;
    }
}

void randomizeArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}
void quickSortAscending(int* arr, int size) {
    quickSort(arr, 0, 4999);
}

void quickSortReverse(int* arr, int size) {
    quickSortDescending(arr, 0, 4999);
}


void mergeSortAscending(int* arr, int size) {
    mergeSort(arr, 0, 4999);
}

void mergeSortReverse(int* arr, int size) {
    mergeSortDescending(arr, 0, 4999);
}

void heapSortAscending(int* arr, int size) {
    heapSort(arr, 5000);
}

void heapSortReverse(int* arr, int size) {
    heapSortDescending(arr, 5000);
}

int main()
{
    //int arr1[5000] = {};
    //int arr2[5000] = {};
    //int arr3[5000] = {};
    //randomizeArray(arr1, 5000);
    //copyArray(arr1, arr2, 5000);
    //copyArray(arr1, arr3, 5000);
    //auto start = high_resolution_clock::now();
    //quickSortAscending(arr2, 5000);
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //auto start2 = high_resolution_clock::now();
    //quickSortReverse(arr3, 5000);
    //auto stop2 = high_resolution_clock::now();
    //auto duration2 = duration_cast<microseconds>(stop2 - start2);
    //cout << duration.count() << endl;
    //cout << duration2.count() << endl;
    SearchTree<int> tree;
    tree.insert(5, 2);
    tree.insert(7, 3);
    tree.insert(15, 5);
    tree.insert(20, 7);
    tree.insert(25, 4);
    tree.insert(17, 7);
    tree.insert(32, 10);
    tree.insert(44, 10);
    tree.insert(48, 3);
    tree.insert(50, 5);
    tree.insert(62, 21);
    tree.insert(78, 29);
    tree.insert(88, 6);
    tree.insert(62, 40);
    tree.insert(90, 7);
    cout << endl << endl;
    cout << "Removals occuring next..." << endl << endl;
    tree.remove(32);
    tree.remove(88);
    tree.remove(90);
}