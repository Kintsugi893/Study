#include <iostream>
#include <fstream>
#include <windows.h>

//есть баг, если присутствует новые строки, то код не видит, что находится после них

int main()
{
    // Русский язык
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    std::string text;
    char symbol;

    while (inputFile.get(symbol)) {
        text += symbol;
    }

    // Поиск количества слов в тексте
    int countWords = 1;
    for (size_t i = 0; text[i] != '\0'; ++i)
        if (text[i] == ' ')
            countWords++;

    std::string word;
    std::string result;
    std::string vowels = "аеёиоуыэюяАЕЁИОУЫЭЮЯ";

    // Заполнение массива слов
    std::string* words = new std::string[countWords];
    int* countVowels = new int[countWords] {0};
    for (size_t i = 0, j = 0; i < countWords; ++i, ++j)
    {
        words[i] = "";
        for (; text[j] != ' ' && text[j] != '\0' && text[j] != '\n';  ++j)
        {
            if (text[j] >= 'А' && text[j] <= 'Я')
                text[j] += ('а' - 'А');

            // Обработка буквы ё
            if (text[j] == -88)
                text[j] += 16;

            if (text[j] >= 'а' && text[j] <= 'я' || text[j] <= 'ё' ||  text[j] == '-')
                words[i] += text[j];
        }
    }

    int maxVowelCount = 0;
    bool hasPalindrome = false;

    // Проходим по каждому слову
    for (size_t i = 0; i < countWords; ++i)
    {
        bool isPalindrom = true;
        if (words[i].length() > 1)
        {
            // Проверка на палиндром
            size_t left = 0;
            size_t right = words[i].length() - 1;
            while (left < right)
            {
                if (words[i][left] != words[i][right])
                {
                    isPalindrom = false;
                    break;
                }
                left++;
                right--;
            }
        }
        else
            isPalindrom = false;

        if (isPalindrom == true)
            hasPalindrome = true;

        for (size_t j = 0; j < words[i].length(); ++j)
        {
            if (vowels.find(words[i][j]) != std::string::npos)
                countVowels[i] += 1;
        }
    }

    // Вывод результата
    if (hasPalindrome)
    {
        // Сортировка слов по убыванию количества гласных
        for (size_t i = 0; i < countWords - 1; ++i)
            for (size_t j = 0; j < countWords - i - 1; ++j)
                if (countVowels[j] < countVowels[j + 1])
                {
                    std::string temp = words[j];
                    words[j] = words[j + 1];
                    words[j + 1] = temp;

                    int temp2 = countVowels[j];
                    countVowels[j] = countVowels[j + 1];
                    countVowels[j + 1] = temp2;
                }

        for (size_t i = 0; i < countWords; ++i) {
            outputFile << words[i] << std::endl;
            std::cout << words[i] << std::endl;
        }
    }
    else
    {
        // Сортировка в алфавитном порядке
        for (int i = 0; i < countWords - 1; ++i)
        {
            for (int j = 0; j < countWords - i - 1; ++j)
            {
                std::string one = words[j];
                std::string two = words[j + 1];

                if (one > two)
                {
                    std::string temp = words[j];
                    words[j] = words[j + 1];
                    words[j + 1] = temp;
                }
            }
        }

        for (size_t i = 0; i < countWords; ++i)
        {
            std::string temp = "";

            for (size_t j = 0; j < words[i].length(); ++j)
            {
                temp += words[i][j];

                if (vowels.find(words[i][j]) != std::string::npos)
                    temp += words[i][j];
            }
            outputFile << temp << std::endl;
            std::cout << temp << std::endl;
        }
    }


    inputFile.close();
    outputFile.close();

    delete[] countVowels;
    delete[] words;

    system("pause");
    return 0;
}
