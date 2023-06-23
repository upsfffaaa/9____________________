#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>


using namespace std;

string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

int main() {
    setlocale(LC_ALL, "ru");
    setlocale(LC_ALL, "Russian");
    string filename = "D://9.txt";
    ifstream file(filename);
    map<string, int> wordCounts;
    string word;
    while (file >> word) {
        word.erase(remove_if(word.begin(), word.end(), ispunct), word.end());
        word = toLowercase(word);
        wordCounts[word]++;
    }
    for (const auto& pair : wordCounts) {
        cout << pair.first << ": " << pair.second << endl;
    }
    return 0;
}
