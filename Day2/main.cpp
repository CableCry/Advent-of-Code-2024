#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

class FileProcessor {
private:
    vector<int> parseLine(const string& line) {
        vector<int> numbers;
        stringstream ss(line);
        int number;
        while (ss >> number) {
            numbers.push_back(number);
        }
        return numbers;
    }

    bool isValidReport(const vector<int>& report) {
        if (report.size() < 2) {
            return false; 
        }

        for (size_t removal_index = 0; removal_index < report.size(); ++removal_index) {
            vector<int> modified_report = report;
            modified_report.erase(modified_report.begin() + removal_index);

            if (checkReportValidity(modified_report)) {
                return true;
            }
        }

        return checkReportValidity(report);
    }

    bool checkReportValidity(const vector<int>& report) {
        if (report.size() < 2) {
            return false; 
        }

        bool increasing = report[1] > report[0];

        for (size_t i = 1; i < report.size(); ++i) {
            int diff = report[i] - report[i-1];
            
            if (abs(diff) < 1 || abs(diff) > 3) {
                return false;
            }

            if ((increasing && diff <= 0) || (!increasing && diff >= 0)) {
                return false;
            }
        }

        return true;
    }

public:
    void readFileAndParse(const string& filename) {
        ifstream file(filename);
        string line;
        int validRowCount = 0;
        int totalRowCount = 0;

        if (!file.is_open()) {
            cerr << "Error: Could not open the file." << endl;
            return;
        }

        while (getline(file, line)) {
            if (line.empty()) continue;

            vector<int> row = parseLine(line);
            totalRowCount++;

            if (isValidReport(row)) {
                ++validRowCount;
            } else {
                // Optional: Debug print for problematic rows
                // cout << "Invalid row: ";
                // for (int num : row) {
                //     cout << num << " ";
                // }
                // cout << endl;
            }
        }

        file.close();

        cout << "Total reports: " << totalRowCount << endl;
        cout << "Safe reports: " << validRowCount << endl;
    }
};

int main() {
    FileProcessor processor;
    processor.readFileAndParse("input.txt");
    return 0;
}