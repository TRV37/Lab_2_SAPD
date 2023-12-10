#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <vector>

// Функция для проверки, является ли символ гласным
bool isVowel(char c)
{
    std::string vowels = "аеёиоуыэюяАЕЁИОУЫЭЮЯ";
    return vowels.find(c) != std::string::npos;
}

// Функция для проверки, является ли символ буквой
bool isLetter(char c)
{
    return ((c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я'));
}

// Функция для разбиения слова на слоги
std::vector<std::string> splitIntoSyllables(const std::string& word)
{
    std::vector<std::string> syllables;
    std::string syllable;

    for (size_t i = 0; i < word.size(); ++i)
    {
        syllable += word[i];
        if (isVowel(word[i]) && i + 1 < word.size() && !isVowel(word[i + 1]))
        {
            syllables.push_back(syllable);
            syllable.clear();
        }
    }

    if (!syllable.empty())
        syllables.back() += syllable;

    return syllables;
}

// Функция для переноса слов
std::vector<std::string> hyphenate(const std::string& word)
{
    std::string sign;

    if (word.length() < 4)
        return { word };

    std::vector<std::string> syllables = splitIntoSyllables(word);

    if (syllables.size() < 2)
        return { word };

    std::vector<std::string> results;

    for (size_t i = 1; i < syllables.size(); ++i)
    {
        std::string result;

        for (size_t j = 0; j < i; ++j)
            result += syllables[j];

        result += "-";

        for (size_t j = i; j < syllables.size(); ++j)
            result += syllables[j];

        // Проверяем, является ли последний символ буквой
        if (!isLetter(result.back()))
        {
            sign = *(result.end() - 1);
            // Если нет, удаляем дефис перед небуквенным символом
            result.erase(result.end() - 1);

        }

        results.push_back(result);
    }
    results.back()+=sign;

    return results;
}

int main()
{
    system("chcp 1251");

    std::ifstream file("text.txt");

    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return 1;
    }

    // Создаем объект ofstream для записи в файл
    std::ofstream outfile("result.txt");

    std::string line;

    while (std::getline(file, line))
    {
        std::string word;

        std::istringstream iss(line);

        while (iss >> word)
        {
            std::vector<std::string> hyphenatedWords = hyphenate(word);
            for (const auto& hw : hyphenatedWords)
                outfile << hw << " "; // Записываем результат в файл
        }

        outfile << "\n"; // Добавляем новую строку в файл после каждой строки входного файла
    }

    file.close();

    // Закрываем файл для записи
    outfile.close();

    return 0;
}




//Имеется файл с текстом на русском языке. Дать варианты переноса всех слов.Перенос возможен по следующим правилам :
//Переносятся либо остаются в конце строки не менее двух символов;
//Невозможен перенос перед буквами 'ь' и 'ъ';
//Слово должно иметь не менее двух слогов;
//В оставшейся и переносимой частях слова должны быть гласные буквы.
//Перенос выполняется если на конце есть слог (изменил сам)