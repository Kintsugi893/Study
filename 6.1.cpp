#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int main()
{
    // Русский язык
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Открываем файлы
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open())
    {
        cout << "Ошибка открытия файла input.txt" << endl;
        return 1;
    }

    if (!outputFile.is_open())
    {
        cout << "Ошибка открытия файла output.txt" << endl;
        return 1;
    }

    // Читаем текст из файла
    string text = "";
    char symbol;
    while (inputFile.get(symbol))
        text += symbol;

    // Закрываем файлы
    inputFile.close();
    outputFile.close();

    int N = 2000;
    int count = 0;
    string* shortestWords = new string[N];

    string word = "";

    // Проходим по каждому символу в тексте и меняем регистр
    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];

        if (c >= 'А' && c <= 'Я')
            c += ('а' - 'А');

        // Обработка буквы ё
        if (c == -88)
            c += 16;

        if (c >= 'а' && c <= 'я' || c == 'ё' || c == '-')
            word += c;


        if (c == ' ' || c == '\n')
        {
            for (char letter = 'а'; letter <= 'я'; letter++)
            {
                int occurrences = 0;
                for (int j = 0; j < word.length(); j++)
                    if (word[j] == letter || word[j] == 'ё')
                        occurrences++;

                // Если текущее слово удовлетворяет условию, добавляем его в массив
                if (occurrences >= 3) {
                    shortestWords[count] = word;
                    count++;
                }
            }

            // Если достигнуто максимальное количество слов, завершаем цикл
            if (count == N)
                break;

            // Сбрасываем текущее слово
            word = "";
        }
    }

    // Удаляем повторяющиеся слова
    for (int i = 0; i < count; ++i)
        for (int j = i + 1; j < count; ++j)
            if (shortestWords[i] == shortestWords[j])
                shortestWords[j] = "";

    // Сортируем массив самых коротких слов по возрастанию длины
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (shortestWords[j].length() > shortestWords[j + 1].length())
            {
                string temp = shortestWords[j];
                shortestWords[j] = shortestWords[j + 1];
                shortestWords[j + 1] = temp;
            }

    for (int i = 0; i < count; i++)
        if (shortestWords[i] != "")
            cout << shortestWords[i] << endl;

    // Записываем найденные слова в текстовый файл
    outputFile.open("output.txt");
    for (int i = 0; i < count; i++)
        if (shortestWords[i] != "")
            outputFile << shortestWords[i] << endl;
    outputFile.close();

    delete[] shortestWords;

    system("pause");
    return 0;
}