#include <iostream>
#include <fstream>
#include <windows.h>

#define COUNT_LETTERS 33

using namespace std;

int main() 
{
    // Русский язык
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");
    string text;
    char symbol;

    // Считывание текста из файла
    while (inputFile.get(symbol))
        text += symbol;

    // Поиск количества слов в тексте
    int countWords = 1;
    for (size_t i = 0; text[i] != '\0'; ++i)
        if (text[i] == ' ')
            countWords++;

    // Заполнение массива слов
    string* words = new string[countWords];
    for (size_t i = 0, j = 0; i < countWords; ++i, ++j)
    {
        words[i] = "";
        for (; text[j] != ' ' && text[j] != '\0'; ++j)
            words[i] += text[j];
    }

    int countLetters[COUNT_LETTERS] {0};

    // Проходим по каждому слову и считаем кол-во каждой буквы
    for (size_t i = 0; i < countWords; ++i)
    {
        for (size_t j = 0; j < words[i].length(); ++j)
        {
            char letter = words[i][j];

            if (letter >= 'А' && letter <= 'Я')
                letter += COUNT_LETTERS - 1;

            if (letter >= 'а' && letter <= 'я')
                countLetters[letter - 'а'] += 1;
        }
    }

    // Поиск 4 наиболее встречающихся букв текста
    int indexesMax[4]{ 0 };
    for (size_t count = 0; count < 4; ++count)
    {
        int iMax = 0;
        int max = countLetters[0];
        for (size_t i = 1; i < COUNT_LETTERS; ++i)
            if (max < countLetters[i])
            {
                max = countLetters[i];
                iMax = i;
            }
        indexesMax[count] = iMax;
        countLetters[iMax] = 0;
    }

    string maxLetters;
    for (size_t i = 0; i < 4; ++i) {
        maxLetters += indexesMax[i] + 'а';
    }

    // Вставка к словам с 2-мя такими буквами кол-во букв в скобках
    for (size_t i = 0; i < countWords; ++i)
    {
        string word = words[i];
        words[i] = "";

        char first = 0;
        char second = 0;
        int countExist = 0;
        size_t index;
        bool onlyTwo = false;
        int indexLetter1 = -1;
        int indexLetter2 = -1;

        for (size_t j = 0; j < word.length(); ++j)
        {
            index = maxLetters.find(word[j]);
            if (index != string::npos)
            {
                if (index != string::npos)
                {
                    if (indexLetter1 == -1)
                    {
                        indexLetter1 = j;
                        countExist += 1;
                        first = word[j];
                    }
                    //else if (word[j] == first && j == indexLetter1 + 1) // пропускаем, если одна буква идет подряд
                    //{
                    //    continue;
                    //}
                    else if (indexLetter2 == -1 && indexLetter1 == j + 1 || indexLetter1 == j - 1)
                    {
                        indexLetter2 = j;
                        countExist += 1;
                        second = word[j];
                        onlyTwo = true;
                    }
                }
            }
        }

        if (onlyTwo == true)
        {
            words[i] = word;

            words[i][indexLetter1] = word[indexLetter1] - COUNT_LETTERS + 1;
            words[i][indexLetter2] = word[indexLetter2] - COUNT_LETTERS + 1;

            words[i] += "(";
            words[i] += first;
            words[i] += second;
            words[i] += ")";
        }
        else
            words[i] = word;

        if (i == countWords - 1)
            outputFile << words[i];
        else
            outputFile << words[i] + ' ';
    }

    cout << maxLetters << endl;

    inputFile.close();
    outputFile.close();

    delete[] words;

    system("pause");
    return 0;
}