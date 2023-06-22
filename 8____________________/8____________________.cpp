#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>


using namespace std;


class FileReader {
private:
    string filename;
    map<string, int> wordCounts;
public:
    FileReader(const string& filename) {
        this->filename = filename;
    }

    bool readFile() {
        ifstream file(filename);
        if (!file) {
            cerr << "Ошибка при открытии файла.\n";
            return false;
        }

        string word;
        while (file >> word) {
            // Удаляем знаки препинания и пробелы в начале и конце слова
            word.erase(remove_if(word.begin(), word.end(), [](char c) { return ispunct(c) || isspace(c); }), word.end());

            // Приводим слово к нижнему регистру
            word = toLowercase(word);

            // Увеличиваем счетчик вхождений слова
            wordCounts[word]++;
        }

        file.close();
        return true;
    }

    const map<string, int>& getWordCounts() const {
        return wordCounts;
    }
};


class WordCounter {
private:
    map<string, int> wordCounts;
public:
    WordCounter(const map<string, int>& wordCounts) {
        this->wordCounts = wordCounts;
    }

    void sortByFrequency() {
        vector<pair<string, int>> items(wordCounts.begin(), wordCounts.end());

        sort(items.begin(), items.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second > b.second;
            });

        for (const auto& item : items) {
            cout << item.first << ": " << item.second << endl;
        }
    }
};



class UserInput {
public:
    static string getFilename() {
        string filename;
        cout << "Введите имя файла: ";
        getline(cin, filename);

        if (filename.empty()) {
            filename = "default.txt";
        }

        return filename;
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    string filename = UserInput::getFilename();

    FileReader reader(filename);
    if (reader.readFile()) {
        WordCounter counter(reader.getWordCounts());
        counter.sortByFrequency();
    }

    return 0;
}
