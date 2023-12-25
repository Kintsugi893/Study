#include <iostream>
#include <fstream>

// Функция для проверки, содержит ли слово не менее трех раз какую-либо букву
bool containsLetterThreeTimes(const std::string& word) {
    for (size_t i = 0; i < word.length(); ++i) {
        char c = word[i];
        int count = 0;
        for (size_t j = 0; j < word.length(); ++j) {
            if (word[j] == c) {
                count++;
                if (count >= 3) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isRussianLetter(char c) {
    return ((c >= 'А' && c <= 'я') || c == 'Ё' || c == 'ё');
}

void toLower(std::string& word) {
    // Удаление символов, не являющихся русскими буквами в начале
    size_t start = 0;
    while (start < word.length() && !isRussianLetter(word[start])) {
        ++start;
    }

    if (start > 0) {
        word = word.substr(start);
    }

    // Приведение к нижнему регистру и удаление знаков припинания
    for (size_t i = 0; i < word.length(); ++i) {
        char& c = word[i];

        if (isRussianLetter(c)) {
            if (c >= 'А' && c <= 'Я') {
                c = c - 'А' + 'а'; // Приведение к нижнему регистру для заглавных букв
            }
            else if (c == 'Ё') {
                c = 'ё'; // Обработка буквы "Ё"
            }
        }
        else if (!isalnum(c) && c != '-') {
            // Удаление символов припинания, но оставляем дефис
            c = '\0';
        }
    }

    // Удаление символов припинания в конце слова
    size_t end = word.length();
    while (end > 0 && !isRussianLetter(word[end - 1])) {
        --end;
    }

    if (end < word.length()) {
        word.resize(end);
    }
}

// Функция для сортировки массива строк по длине
void sortWordsByLength(std::string* words, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (words[i].length() > words[j].length()) {
                std::string temp = words[j];
                words[j] = words[i];
                words[i] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    const int N = 2000;

    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Unable to open input.txt or output.txt\n";
        return 1;
    }

    const int MAX_WORD_COUNT = 10000;
    std::string* shortestWords = new std::string[MAX_WORD_COUNT];
    int wordCount = 0;

    // Чтение слов из файла и добавление подходящих в массив
    std::string word;
    while (inputFile >> word) {
        toLower(word);
        if (containsLetterThreeTimes(word)) {
            shortestWords[wordCount++] = word;
        }
    }

    // Сортировка по длине слова
    sortWordsByLength(shortestWords, wordCount);

    // Удаление дубликатов
    for (int i = 0; i < wordCount - 1; ++i) {
        for (int j = i + 1; j < wordCount; ++j) {
            if (shortestWords[i] == shortestWords[j]) {
                shortestWords[j] = "";
            }
        }
    }

    // Запись в файл
    int writtenCount = 0;
    for (int i = 0; i < wordCount && writtenCount < N; ++i) {
        if (!shortestWords[i].empty()) {
            outputFile << shortestWords[i] << std::endl;
            ++writtenCount;
            std::cout << shortestWords[i] << std::endl;
        }
    }

    delete[] shortestWords;

    std::cout << "\nDone\n";

    return 0;
}
