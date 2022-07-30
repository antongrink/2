#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <array>
#include <Windows.h>

using std::cout;
using std::cin;

static unsigned short getRandomNumber(unsigned short min, unsigned short max)
{
    static double foration = 1 / (1.0 + RAND_MAX);
    return static_cast<unsigned short>(rand() * foration * (max - min + 1) + min);
}

char corrInput()
{
    char letter;
    cin >> letter;
    while (true)
    {
        if (cin.rdbuf()->in_avail() > 1 || cin.fail() /*|| isdigit(std::stoi(cin.peek()))*/)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Неверное введенные данные, повторите ввод: ";

        }
        else
            break;

    }
    cin.ignore(1000, '\n');
    return letter;
}



class Gallows
{
    const std::string unknown_word;
    std::string guessed_word;
    static std::array< std::string, 40> words;
    enum Condition {START = 0,HAS_LETTER,NO_LETTER};
    unsigned short attempts{ 5 };
public:

   

    Gallows() : unknown_word(words[getRandomNumber(0, words.size() - 1)])
    {
        for (int i{ 0 }; i < unknown_word.size(); i++)
            guessed_word += "_";
        startOfGame();
    }

    void startOfGame();
   

    void showWord(const std::string& guessed_word) const
    {
       
            for (const auto& letter : guessed_word)
                cout << letter << " ";
            cout << "\n";
        
        
    }

    bool hasgWord(char letter)
    {
        
        bool has_letter{ false };
        for (int i{ 0 }; i < unknown_word.size(); i++)
            if (letter == unknown_word[i] || std::toupper(letter) == unknown_word[i])
            {
                guessed_word[i] = letter;
                has_letter = true;
            }
        return has_letter;
    }

    
};

std::array<std::string, 40> Gallows::words
{
    "обучение" , "адвокат" , "тень" , "температура" , "актер" , "переход" , "минимум"
     , "член" , "приказ" , "золото" , "кровь" , "помощь" , "понятие" , "книжка"
     , "дыхание" , "орган" , "слой" , "кулак" , "выполнение" , "американец" , "опыт"
     , "контракт" , "публика" , "плечо" , "последствие" , "род" , "государство" , "бок"
     , "кабинет" , "обработка" , "позиция" , "форма" , "кухня" , "конференция" , "вид"
    , "вина" , "причина" , "транспорт" , "принятие" , "герой"
};

int main()
{
    SetConsoleCP(1251);   SetConsoleOutputCP(1251);
    srand(static_cast<unsigned short>(time(0)));
    setlocale(LC_ALL, "RUS");
    Gallows();
}

void Gallows::startOfGame()
{
    cout << "Добро пожаловать в игру \"Виселица\"!\n";
    cout << "Слово - "; showWord(guessed_word);
    char letter;

    while (attempts!=0) {
   
        cout << "Угадайте букву: "; letter = corrInput();
        if (hasgWord(letter))
        {
            cout << "Верно - "; showWord(guessed_word);
        }
        else
        {
            attempts--;
            cout << "\nНеверно! Такой буквы нет, у вас осталось " << attempts << " попыток неверно указать букву!\n";
        }
    }

    cout << "Вы проиграли, у вас не осталось попыток!\n";
    cout << "Загаданное слово " << unknown_word << "\n";
}
