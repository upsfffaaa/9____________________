int main() {
    setlocale(LC_ALL, "ru");
    setlocale(LC_ALL, "Russian");
    std::string filename = "D://9.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return 1;
    }

    std::map<std::string, int> words;
    std::string word;
    while (file >> word) {
        // удаляем знаки препинания с начала и конца слова
        while (!word.empty() && ispunct(word.front())) {
            word.erase(0, 1);
        }
        while (!word.empty() && ispunct(word.back())) {
            word.pop_back();
        }
        // приводим слово к нижнему регистру
        for (auto& c : word) {
            c = tolower(c);
        }
        // добавляем слово в map
        if (!word.empty()) {
            words[word]++;
        }
    }

    // выводим список слов и количество их вхождений
    for (const auto& pair : words) {
        std::cout << pair.first << " - " << pair.second << std::endl;
    }

    return 0;
}
