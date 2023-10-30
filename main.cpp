/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: Application file
**************************************************/

#include "main.h"
#include "GameDefault.h"
#include "GameAdvanced.h"

int main() {
    //set up new seed
    GameDefault* bPtr = nullptr;
    GameAdvanced gameAdvanced;
    srand(unsigned (time(nullptr)));

    // default intro
    //displayTextFile("RBintro.txt");

    // advanced intro
    displayTextFile("RBintroAdvanced.txt");

    int gameMode = askForNumber("Enter game difficulty level: ", 4, 6);
    int numberOfPlayers = askForNumber("Enter number of players", 1, 3);

    // Default game play
    //bPtr = new GameDefault(gameMode, numberOfPlayers);

    // Advanced game play
    bPtr = new GameAdvanced(gameMode, numberOfPlayers);

    bPtr->playGame();

    // clean up memory
    delete bPtr;
    return 0;
}

/********* DISPLAY FUNCTIONS *****************/

void waitForPlayer() {
    // adjust new line and indents as required
    // Windows
    system("pause");
    // Mac & Linux
    //system("read -n 1 -s -r -p \"Press any key to continue\"");
}

void clearScreen() {
    // Windows
    system("cls");
    // Mac & Linux
    //system("clear");
}


void displayTextFile(string myFile) {
    // local vars
    ifstream blurbData(myFile);
    string line = "";

    // read in file data
    if (blurbData.is_open()) {
        while (getline(blurbData, line)) {
            cout << line << "\n" ;
        }
    }
    blurbData.close();
    waitForPlayer();
    clearScreen();
}

/****************** INPUT FUNCTIONS **********************/
int askForNumber(string question, int min, int max) {
    // ask for a numeric response from the user
    bool valid = false;
    string userInput = "";
    int number = min;
    while (!valid) {
        cout << question << "(" << min << "-" << max << "): ";
        cin >> userInput;
        //check if userInput is a digit
        if (all_of(userInput.begin(), userInput.end(), ::isdigit)) {
            //convert userInput into integer
            number = stoi(userInput);
            //check if userInput is within the given range
            if  (number >= min && number <= max) {
                valid = true;
            } else {
                cout << "Input must be between " << min << " and " << max << endl;
            }
        } else {
            cout <<"Input must be a positive integer\n";
        }
    }
    cin.ignore();
    return number;
}

char askForLetter(string question) {
    // ask a single letter response question
    string userInput = "";
    bool valid = false;
    while (!valid) {
        cout << "\n " + question;
        cin >> userInput;
        if (userInput.length() == 1 && isalpha(userInput[0])) {
            valid = true;
        } else {
            cout << "Input must be a character!\n";
        }
    }
    cin.ignore();
    return toupper(userInput[0]);
}

string askForString(string question) {
    string response = "";
    while (response == "") {
        cout << question;
        getline(cin, response);
    }
    return response;

}






