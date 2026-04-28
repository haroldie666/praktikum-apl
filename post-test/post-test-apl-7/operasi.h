#ifndef OPERASI_H
#define OPERASI_H

#include <iostream>
#include <string>
#include <algorithm>
#include "auth.h" 

using namespace std;

struct kadaluarsa {
    int tanggal;
    int bulan;
    int tahun;
};

struct produk {
    int id;
    string namaBahan;          
    int jumlahStok;            
    int hargaBeli;              
    int hargaJual;              
    int jumlahTerjual;                    
    kadaluarsa kadaluarsa; 
};

void insertionSortId(produk arr[], int n) {
    for (int i = 1; i < n; i++) {
        produk key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].id > key.id) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertionSortByStok(produk arr[], int n) {
    for (int i = 1; i < n; i++) {
        produk key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].jumlahStok > key.jumlahStok) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void quickSort(produk arr[], int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    string pivot = arr[mid].namaBahan;
    int i = low, j = high;

    while (i <= j) {
        while (arr[i].namaBahan > pivot) i++;
        while (arr[j].namaBahan < pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++; j--;
        }
    }
    if (low < j) quickSort(arr, low, j);
    if (i < high) quickSort(arr, i, high);
}

void insertionSort(produk arr[], int n) {
    for (int i = 1; i < n; i++) {
        produk key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].hargaJual > key.hargaJual) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(produk arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int indeksMax = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].jumlahStok > arr[indeksMax].jumlahStok) {
                indeksMax = j;
            }
        }
        if (indeksMax != i) swap(arr[i], arr[indeksMax]);
    }
}

int binarySearchId(produk *arr, int size, int targetId) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (arr[mid].id == targetId) return mid;
        else if (arr[mid].id < targetId) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int binarySearchStok(produk *arr, int size, int targetStok) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2; 
        if (arr[mid].jumlahStok == targetStok) return mid;
        else if (arr[mid].jumlahStok < targetStok) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int linearSearchNama(produk *arr, int size, string targetNama) {
    string targetLower = toLowerCase(targetNama); 
    for (int i = 0; i < size; i++) {
        if (toLowerCase(arr[i].namaBahan) == targetLower) return i;
    }
    return -1;
}

#endif