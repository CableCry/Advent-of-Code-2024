#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

class FileProcessor {
private:
    int totalValue = 0;
    int validMulOperations = 0;
    int totalAllMuls = 0;
    int allMulOperations = 0;
    int doCount = 0;
    int dontCount = 0;
    regex fullPattern{R"(do\(\)|don't\(\)|mul\((\d+),(\d+)\))"}; // Matches do(), don't(), and mul(x, y)
    bool currentMode = true; // true = do(), false = don't()

    void parseLine(const string& line) {
        auto matches_begin = sregex_iterator(line.begin(), line.end(), fullPattern);
        auto matches_end = sregex_iterator();

        for (auto it = matches_begin; it != matches_end; ++it) {
            smatch match = *it;

            if (match[0] == "do()") {
                if (!currentMode) { // Switch to do() if not already in it
                    currentMode = true;
                    ++doCount;
                }
            } else if (match[0] == "don't()") {
                if (currentMode) { // Switch to don't() if not already in it
                    currentMode = false;
                    ++dontCount;
                }
            } else if (match[1].matched && match[2].matched) {
                // Extract the two numbers from the match
                int num1 = stoi(match[1].str());
                int num2 = stoi(match[2].str());
                int product = num1 * num2;

                totalAllMuls += product;
                ++allMulOperations;

                if (currentMode) {
                    totalValue += product;
                    ++validMulOperations;
                }
            }
        }
    }

public:
    void openFileAndParse(const string& filename) {
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            cerr << "Error: Could not open the file." << endl;
            return;
        }

        while (getline(file, line)) {
            if (line.empty()) continue;
            parseLine(line);
        }

        file.close();
    }

    int getTotalValue() const { return totalValue; }
    int getValidMulOperations() const { return validMulOperations; }
    int getTotalAllMuls() const { return totalAllMuls; }
    int getAllMulOperations() const { return allMulOperations; }
    int getDoCount() const { return doCount; }
    int getDontCount() const { return dontCount; }
};

int main() {
    FileProcessor processor;
    processor.openFileAndParse("input.txt");

    cout << "Total Value (all muls): " << processor.getTotalAllMuls() << endl;
    cout << "Total mul() Operations (all): " << processor.getAllMulOperations() << endl;
    cout << "Total Value (do/don't): " << processor.getTotalValue() << endl;
    cout << "Valid mul() Operations (do/don't): " << processor.getValidMulOperations() << endl;

    // These only account for state changing do()s and don't()
    //cout << "Total do() : " << processor.getDoCount() << endl;
    //cout << "Total don't() : " << processor.getDontCount() << endl;

    return 0;
}
