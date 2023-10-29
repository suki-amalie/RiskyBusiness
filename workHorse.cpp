//
// Created by ADMIN on 29-Oct-23.
//

#include "workhorse.h"
/***************************************************************************
 *                      WORKHORSE FUNCTIONS
 **************************************************************************/

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
/**************************** DISPLAY FUNCTIONS ********************************/

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
    while (response.empty()) {
        cout << question;
        getline(cin, response);
    }
    return response;
}

string center(const string s, const int w) {

    stringstream ss, spaces;
    int padding = w - s.size();                 // count excess room to pad
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if(padding>0 && padding%2!=0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();

}