#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

class FileProcessor {
private:
    // Parse numbers from a line
    vector<int> parseLine(const string& line) {
        vector<int> numbers;
        stringstream ss(line);
        int number;
        while (ss >> number) {
            numbers.push_back(number);
        }
        return numbers;
    }

    // Check if a sequence follows the rule set (all increasing or all decreasing)
    bool isValidSequence(const vector<int>& row) {
        if (row.size() < 2) {
            return true; // A row with fewer than 2 numbers is safe by definition
        }

        bool increasing = row[1] > row[0];
        for (size_t i = 1; i < row.size(); ++i) {
            int diff = row[i] - row[i - 1];
            if ((increasing && diff <= 0) || (!increasing && diff >= 0)) {
                return false;
            }
        }
        return true;
    }

    // Check if the row is safe with or without the Problem Dampener
    bool followsRuleSet(const vector<int>& row) {
        if (isValidSequence(row)) {
            return true; // The row is already safe
        }

        // Try removing one element and check if the sequence becomes valid
        for (size_t i = 0; i < row.size(); ++i) {
            vector<int> modifiedRow = row;
            modifiedRow.erase(modifiedRow.begin() + i); // Remove one element
            if (isValidSequence(modifiedRow)) {
                return true; // Safe with the Problem Dampener
            }
        }

        return false; // Not safe even with the Problem Dampener
    }

public:
    // Read file and process each line
    void readFileAndParse(const string& filename) {
        ifstream file(filename);
        string line;
        int validRowCount = 0;

        if (!file.is_open()) {
            cerr << "Error: Could not open the file." << endl;
            return;
        }

        while (getline(file, line)) {
            vector<int> row = parseLine(line);

            if (followsRuleSet(row)) {
                ++validRowCount;
            }
        }

        file.close();

        cout << "Number of safe reports: " << validRowCount << endl;
    }
};

int main() {
    FileProcessor processor;
    processor.readFileAndParse("input.txt"); // Replace "input.txt" with your file path
    return 0;
}
