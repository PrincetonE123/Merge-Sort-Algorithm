/*
Programming-Assignment-2-Source.cpp

Princeton Epeagba J00701287
*/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>  // For rand() and srand()
#include <chrono>   // Time 
#include <fstream>  // Imported library that allows for reading and writting files
#include <cmath>    // Imported math for log function

void printSepLine(const char& delimiter, const int LEN = 25);
void randomizeArray(int* a, int size);
void mergeSort(int* numbers, int i, int k);
void merge(int* numbers, int i, int j, int k);
void printCSV(int size, int logN[], int time[], double nLogN_Time[], const char* filename);

using namespace std;

int main() {
    const int NUM_ARRAYS = 9;
    const int BASE_ARRAY_SIZE = 1000;
    const int MAX_ARRAY_SIZE = 9000;
    int sortTime[NUM_ARRAYS];
    int nLogN[NUM_ARRAYS];
    double nLogN_Time[NUM_ARRAYS];
    int arrays[NUM_ARRAYS][MAX_ARRAY_SIZE];

    srand(time(NULL));  // Seed random number generator

    for (int i = 0; i < NUM_ARRAYS; ++i) {  // Populates all 9 arrays with random numbers based on size
        int currentArraySize = BASE_ARRAY_SIZE * (i + 1);
        randomizeArray(arrays[i], currentArraySize);
    }

    while (true) {  // While loop for user input. Program must be ran again as all arrays are sorted after 1st iteration
        cout << "Select an array from 1 to 9 to display results or 0 to exit and generate results." << endl;
        int userChoice;
        cin >> userChoice;

        if (userChoice < 0 || userChoice > 9) {
            cout << "Invalid choice. Please select a number from 1 to 9 or 0 to exit and generate results." << endl;
            continue;
        }

        if (userChoice == 0) {
            cout << "Exiting program." << endl;
            break;
        }

        cout << "Original Array " << userChoice << ": ";  // Prints orginal array before sort

        for (int i = 0; i < BASE_ARRAY_SIZE * userChoice; ++i) {
            cout << arrays[userChoice - 1][i] << " ";
        }
        cout << endl;

        for (int i = 0; i < NUM_ARRAYS; ++i) {
            auto start = chrono::high_resolution_clock::now();

            mergeSort(arrays[i], 0, BASE_ARRAY_SIZE * (i + 1) - 1);  // Sorting occurs for all arrays

            auto stop = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            sortTime[i] = duration.count();

            nLogN[i] = BASE_ARRAY_SIZE * (i + 1) * log(BASE_ARRAY_SIZE * (i + 1));
            nLogN_Time[i] = static_cast<double>(nLogN[i]) / sortTime[i];
        }
        cout << "\n\nSorted Array " << userChoice << ": ";  // Prints sorted array

        for (int i = 0; i < BASE_ARRAY_SIZE * userChoice; ++i) {
            cout << arrays[userChoice - 1][i] << " ";
        }

        cout << endl;
    }

    // Creates Excel .csv file
    printCSV(NUM_ARRAYS, nLogN, sortTime, nLogN_Time, "C:\\Users\\droug\\Downloads\\Mergesort_Time.csv "); // Must manually change to your computer's path

    return 0;
}

// Merge Sort Functions
void mergeSort(int* numbers, int left, int right) {
    int mid = 0;
    // i == left, j == mid, k == right

    if (left < right) {
        mid = (left + right) / 2;  // Find the midpoint in the partition

        // Recursively sort left and right partitions
        mergeSort(numbers, left, mid);
        mergeSort(numbers, mid + 1, right);

        // Merge left and right partition in sorted order
        merge(numbers, left, mid, right);
    }

    return;
}

void merge(int* numbers, int left, int mid, int right) {
    int mergedSize = right - left + 1;           // Size of merged partition 
    int mergePos = 0;                            // Position to insert merged number
    int leftPos = 0;                             // Position of elements in left partition
    int rightPos = 0;                            // Position of elements in right partition
    int* mergedNumbers = new int[mergedSize];    // Dynamically allocates temporary array for merged numbers

    leftPos = left;                              // Initialize left partition position
    rightPos = mid + 1;                          // Initialize right partition position

    // Add the smallest element from left or right partition to merged numbers
    while (leftPos <= mid && rightPos <= right) {
        if (numbers[leftPos] <= numbers[rightPos]) {
            mergedNumbers[mergePos] = numbers[leftPos];
            ++leftPos;
        }
        else {
            mergedNumbers[mergePos] = numbers[rightPos];
            ++rightPos;
        }
        ++mergePos;
    }

    // If the left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= mid) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }

    // If the right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= right) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }

    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[left + mergePos] = mergedNumbers[mergePos];
    }

    delete[] mergedNumbers;  // Frees memory
    mergedNumbers = nullptr;

    return;
}

// Utility functions
void printSepLine(const char& delimiter, const int LEN) {  // Prints a separation line
    for (int i = 0; i < LEN; ++i) {
        cout << delimiter;
    }
    cout << std::endl;

    return;
}


void randomizeArray(int* a, int size) {  // Populates array with random numbers
    for (int i = 0; i < size; i++) {
        a[i] = rand() % (size * 4) + 1;  // 1 to twice array size (up to RAND_MAX)
    }
}

void printCSV(int size, int nLogN[], int time[], double nLogN_Time[], const char* filename) {
    ofstream csvFile(filename);
    if (!csvFile.is_open()) {
        cerr << "Error opening output file." << filename << endl;  // Checks for errors 

        return;
    }

    // Excel headers
    csvFile << "Input size n,Value of n·logn,Time Spent (Microseconds), Value of (n·logn)/time\n";

    // Written data
    for (int i = 0; i < size; i++) {
        csvFile << (i + 1) * 1000 << "," << nLogN[i] << "," << time[i] << "," << scientific << nLogN_Time[i] << "\n";
    }

    cout << "CSV file created: " << filename << endl;
    csvFile.close();
}

