#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

class FileProcessor {
private:
    vector<int> col1, col2;
    unordered_map<int, int> frequencyMap;
    int totalDistance = 0;
    int similarityScore = 0;

public:
    void readFileAndParse(const string& filename) {
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            cerr << "Error: Could not open the file." << endl;
            return;
        }

        while (getline(file, line)) {
            stringstream ss(line);
            int value1, value2;
            if (ss >> value1 >> value2) {
                col1.push_back(value1);
                col2.push_back(value2);
                frequencyMap[value2]++;
            }
        }

        file.close();
    }

    bool checkIfFileEmpty() const {
        if (col1.empty() || col2.empty()) {
            cerr << "No valid data found in the file." << endl;
            return true;
        }
        return false;
    }

    void calculateMetrics() {
        
        sort(col1.begin(), col1.end());
        sort(col2.begin(), col2.end());

        
        for (size_t i = 0; i < min(col1.size(), col2.size()); ++i) {
            totalDistance += abs(col1[i] - col2[i]);
        }

        for (int num : col1) {
            similarityScore += num * frequencyMap[num];
        }
    }

    int getTotalDistance() const { return totalDistance; }

    int getSimilarityScore() const { return similarityScore; }
};

int main() {
    string filename = "input.txt";
    FileProcessor processor;

    processor.readFileAndParse(filename);
    if (processor.checkIfFileEmpty()) {
        return 1;
    }

    processor.calculateMetrics();

    cout << "Similarity Score: " << processor.getSimilarityScore() << endl;
    cout << "Total Distance: " << processor.getTotalDistance() << endl;

    return 0;
}
