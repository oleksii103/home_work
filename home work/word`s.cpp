#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

int main() {
    ifstream inputFile("bober.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file input.txt!" << endl;
        return 1;
    }

    map<string, int> wordFrequency;
    string line, word;

    while (getline(inputFile, line)) {
        size_t start = 0, end;
        while ((end = line.find_first_of(" ", start)) != string::npos) {
            word = line.substr(start, end - start);
            start = end + 1;
            word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
            word = toLowerCase(word);
            if (!word.empty()) {
                wordFrequency[word]++;
            }
        }
        word = line.substr(start);
        word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
        word = toLowerCase(word);
        if (!word.empty()) {
            wordFrequency[word]++;
        }
    }

    inputFile.close();

    cout << "Word : Frequency" << endl;
    for (const auto& pair : wordFrequency) {
        cout << pair.first << " : " << pair.second << endl;
    }

    string mostFrequentWord;
    int maxFrequency = 0;
    for (const auto& pair : wordFrequency) {
        if (pair.second > maxFrequency) {
            mostFrequentWord = pair.first;
            maxFrequency = pair.second;
        }
    }

    cout << "\nMost frequent word: " << mostFrequentWord
        << " (" << maxFrequency << " times)" << endl;

    ofstream outputFile("homic.txt");
    if (!outputFile.is_open()) {
        cerr << "Error opening file output.txt!" << endl;
        return 1;
    }

    outputFile << "Word : Frequency\n";
    for (const auto& pair : wordFrequency) {
        outputFile << pair.first << " : " << pair.second << "\n";
    }

    outputFile << "\nMost frequent word: " << mostFrequentWord
        << " (" << maxFrequency << " times)\n";

    outputFile.close();

    return 0;
}
