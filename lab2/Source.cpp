#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include <vector>

// ������� ��� ��������, �������� �� ������ �������
bool isVowel(char c)
{
    std::string vowels = "����������Ũ�������";
    return vowels.find(c) != std::string::npos;
}

// ������� ��� ��������, �������� �� ������ ������
bool isLetter(char c)
{
    return ((c >= '�' && c <= '�') || (c >= '�' && c <= '�'));
}

// ������� ��� ��������� ����� �� �����
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

// ������� ��� �������� ����
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

        // ���������, �������� �� ��������� ������ ������
        if (!isLetter(result.back()))
        {
            sign = *(result.end() - 1);
            // ���� ���, ������� ����� ����� ����������� ��������
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
        std::cerr << "�� ������� ������� ����" << std::endl;
        return 1;
    }

    // ������� ������ ofstream ��� ������ � ����
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
                outfile << hw << " "; // ���������� ��������� � ����
        }

        outfile << "\n"; // ��������� ����� ������ � ���� ����� ������ ������ �������� �����
    }

    file.close();

    // ��������� ���� ��� ������
    outfile.close();

    return 0;
}




//������� ���� � ������� �� ������� �����. ���� �������� �������� ���� ����.������� �������� �� ��������� �������� :
//����������� ���� �������� � ����� ������ �� ����� ���� ��������;
//���������� ������� ����� ������� '�' � '�';
//����� ������ ����� �� ����� ���� ������;
//� ���������� � ����������� ������ ����� ������ ���� ������� �����.
//������� ����������� ���� �� ����� ���� ���� (������� ���)