#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>

using namespace std;

const int totalNumbers = 10000;
const int chunkSize = 1000;
const int numChunks = totalNumbers / chunkSize;

void generateRandomNumbers(const string &filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    for (int i = 0; i < totalNumbers; ++i) {
        int randomNum = rand() % 100 + 1; // Generating random number between 1 and 100
        outFile << randomNum << endl;
    }

    outFile.close();
}

void createUnsortedFiles(const string &inputFile) {
    ifstream inFile(inputFile);

    if (!inFile.is_open()) {
        cerr << "Error opening initial numbers file for reading." << endl;
        return;
    }

    for (int i = 1; i <= numChunks; ++i) {
        vector<int> numbers;
        for (int j = 0; j < chunkSize; ++j) {
            int num;
            if (!(inFile >> num)) {
                cerr << "Error reading from initial numbers file." << endl;
                return;
            }
            numbers.push_back(num);
        }

        string unsortedFilename = "unsorted_" + to_string(i) + ".txt";
        ofstream unsortedFile(unsortedFilename);

        if (!unsortedFile.is_open()) {
            cerr << "Error opening file " << unsortedFilename << " for writing." << endl;
            return;
        }

        for (int num : numbers) {
            unsortedFile << num << endl;
        }

        unsortedFile.close();

        sort(numbers.begin(), numbers.end());

        string sortedFilename = "sorted_" + to_string(i) + ".txt";
        ofstream sortedFile(sortedFilename);

        if (!sortedFile.is_open()) {
            cerr << "Error opening file " << sortedFilename << " for writing." << endl;
            return;
        }

        for (int num : numbers) {
            sortedFile << num << endl;
        }

        sortedFile.close();
    }

    inFile.close();
}

void mergeSortFiles(const string &finalSortedFile) {
    ofstream finalFile(finalSortedFile);

    if (!finalFile.is_open()) {
        cerr << "Error opening final sorted file for writing." << endl;
        return;
    }

    vector<ifstream> sortedFiles;

    // Open all the sorted files
    for (int i = 1; i <= numChunks; ++i) {
        string sortedFilename = "sorted_" + to_string(i) + ".txt";
        ifstream sortedFile(sortedFilename);

        if (!sortedFile.is_open()) {
            cerr << "Error opening file " << sortedFilename << " for reading." << endl;
            return;
        }

        sortedFiles.push_back(move(sortedFile));
    }

    vector<int> currentValues(numChunks);
    vector<bool> fileEmpty(numChunks, false);

    // Read the initial values from each file
    for (int i = 0; i < numChunks; ++i) {
        if (!(sortedFiles[i] >> currentValues[i])) {
            fileEmpty[i] = true;
        }
    }

    while (true) {
        int minValue = INT_MAX;
        int minIndex = -1;

        // Find the minimum value among current values from different files
        for (int i = 0; i < numChunks; ++i) {
            if (!fileEmpty[i] && currentValues[i] < minValue) {
                minValue = currentValues[i];
                minIndex = i;
            }
        }

        // Break the loop if no minimum value is found
        if (minIndex == -1) {
            break;
        }

        // Write the minimum value to the final file
        finalFile << minValue << endl;

        // Read the next value from the file that contained the minimum value
        if (!(sortedFiles[minIndex] >> currentValues[minIndex])) {
            fileEmpty[minIndex] = true;
        }
    }

    // Close all the sorted files
    for (int i = 0; i < numChunks; ++i) {
        sortedFiles[i].close();
    }

    finalFile.close();
}


int main() {
    generateRandomNumbers("initial_numbers.txt");

    createUnsortedFiles("initial_numbers.txt");

    mergeSortFiles("sorted_final.txt");

    return 0;
}
