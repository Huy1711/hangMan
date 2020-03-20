#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_BAD_GUESSES = 7;
const char DATA_FILE[] = "words.txt";
const string FIGURE[] = {
        "   ------------    \n"
        "   |               \n"
        "   |               \n"
        "   |               \n"
        "   |               \n"
        "   |     \n"
        " -----   \n",
        "   ------------    \n"
        "   |          |    \n"
        "   |               \n"
        "   |               \n"
        "   |               \n"
        "   |     \n"
        " -----   \n",
        "   ------------    \n"
        "   |          |    \n"
        "   |          O    \n"
        "   |               \n"
        "   |               \n"
        "   |     \n"
        " -----   \n",
        "   ------------    \n"
        "   |          |    \n"
        "   |          O    \n"
        "   |          |    \n"
        "   |               \n"
        "   |     \n"
        " -----   \n",
        "   ------------    \n"
        "   |          |    \n"
        "   |          O    \n"
        "   |         /|    \n"
        "   |               \n"
        "   |     \n"
        " -----   \n",
        "   ------------    \n"
        "   |          |    \n"
        "   |          O    \n"
        "   |         /|\\  \n"
        "   |               \n"
        "   |     \n"
        " -----   \n",
        "   ------------    \n"
        "   |          |    \n"
        "   |          O    \n"
        "   |         /|\\  \n"
        "   |         /     \n"
        "   |     \n"
        " -----   \n",
        "   ------------    \n"
        "   |          |    \n"
        "   |          O    \n"
        "   |         /|\\  \n"
        "   |         / \\  \n"
        "   |     \n"
        " -----   \n"
};

string toLowerCase(const string &s) {
    string temp = s;
    transform(s.begin(), s.end(), temp.begin(), ::tolower);
    return temp;
}

string getWord(const char* fileName) {
    vector<string> wordList;
    ifstream fcin(fileName);
    if (fcin.is_open()) {
        string word;
        while (fcin >> word) {
            wordList.push_back(word);
        }
        fcin.close();
    } else return "book";
    if (wordList.size()>0) {
        int randomIndex = rand() % wordList.size();
        return toLowerCase(wordList[randomIndex]);
    } else return "";
}

char readAGuess() {
    char c;
    cout << "Enter your guess:";
    cin >> c;
    return c;
}

bool contains(const string &secretWord, char guess) {
    char temp = tolower(guess);
    return (secretWord.find_first_of(temp) != string::npos);
}

void update(string &guessedWord, char guess, const string &secretWord) {
    for (int i=0; i<secretWord.size(); i++) {
        if (tolower(guess) == secretWord[i])
            guessedWord[i] = tolower(guess);
    }
}

void printResult(int badGuessCount, string guessedWord, string secretWord) {
    if (badGuessCount==MAX_BAD_GUESSES) {
        cout << FIGURE[badGuessCount] << endl;
        cout << "--------------------" << endl;
        cout << "You lost!!" << endl;
        cout << "The answer is: " << secretWord << endl;
        cout << "Number of wrong guesses: " << badGuessCount << endl;
    }
    else {
        cout << "--------------------" << endl;
        cout << "You won!!" << endl;
        cout << "The word is: " << guessedWord << endl;
        cout << "Number of wrong guesses: " << badGuessCount << endl;
    }
}

void printTypedWord(string typedWord) {
    if (typedWord.size()!=0) {
        cout << "Typed words: ";
        for (int i = 0; i < typedWord.size(); i++) {
            cout << typedWord[i] << " ";
        }
        cout << endl;
    }
}

void renderGame(string guessedWord, int badGuessCount, string typedWord) {
    cout << FIGURE[badGuessCount] << endl;
    cout << guessedWord << endl;
    cout << "Number of wrong guesses: " << badGuessCount << endl;
    printTypedWord(typedWord);
}

int playHangman() {
    srand(time(0));
    string secretWord, guessedWord, typedWord;
    secretWord = getWord(DATA_FILE);
    if (secretWord.length() < 1) {
        cout << "Error reading vocabulary life " << DATA_FILE;
        return -1;
    }
    int badGuessCount=0;
    guessedWord = string(secretWord.size(), '-');
    do {
        renderGame(guessedWord, badGuessCount, typedWord);
        char guess = readAGuess();
        typedWord.push_back(tolower(guess));
        if (contains(secretWord, guess)) {
            update(guessedWord, guess, secretWord);
        } else {
            badGuessCount++;
        }
    } while (badGuessCount < MAX_BAD_GUESSES && guessedWord != secretWord);
    printResult(badGuessCount, guessedWord, secretWord);
    return 0;
}

bool askIfPlayAgain() {
    string answer;
    cout << "Continue playing? (Y/N):";
    cin >> answer;
    if (answer == "Y" || answer == "y" || answer == "Yes" || answer == "YES")
        return true;
    else {
        cout << "Goodbye!" << endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    bool continuePlaying;
    do {
        playHangman();
        continuePlaying = askIfPlayAgain();
    } while (continuePlaying);
    return 0;
}