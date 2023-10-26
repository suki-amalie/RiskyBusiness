/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen
 Purpose: Application file
**************************************************/

#include <iostream>
#include "main.h"

/*PUT IN HEADER COMMENT FOR HEADER FILES*/
int main() {
    //set up new seed
    srand(unsigned (time(nullptr)));
    //setUpRisks("riskDefault.txt");
    //setUpCompanies(3, "companies.txt");
    setUpGame();
    //display intro to game
    //displayTextFile("RBintro.txt");
    //displayCompanies();
    //displayRisks();
    loadGame("gameData.txt");
    return 0;
}

/************** SETUP FUNCTIONS ***********************/

void setUpGame() {
    bool won = false;
    bool end = false;
    int mode = askForNumber("Enter game mode", 4, 6);
    int playersNumber = askForNumber("Enter number of players", 1, 3);
    int maxCompanies = getMaxCompanies(mode);
    int minCompanies = getMinCompanies(mode);
    int minMoney = getMinMoney(mode);
    int maxDays = getMaxDays(mode);
    int dayCounter = 1;
    setUpCompanies(maxCompanies, "companies.txt");
    setUpShares();
    // default risks
    //setUpRisks("riskDefault.txt");
    // Extra functionality: Advanced risks
    setUpRisks("risksAdvanced.txt");
    setUpPlayers(mode, playersNumber);
    char userChoice = ' ';
    do {
        for (auto &player:players){
            displayGameInterface(player, minCompanies, minMoney, dayCounter);
            userChoice = askForLetter("What will you do now? ");
            // Default menu
            checkMenuSelection(userChoice, player);
            // Advanced menu
            if (player.getTotalCompaniesOwned() >= minCompanies && player.getMoney() >= minMoney) {
                won = true;
                cout << "Congratulations, " << player.getPlayerName() << "! You won :)\n";
            }
            if (dayCounter >= maxDays || won || players.size() <= 0) {
                end = true;
            }
            waitForPlayer();
            clearScreen();
        }
        /* Increase day counter by one and reset market shares */
        dayCounter ++;
        resetSharesPrice();
    } while (not end);


    for (auto ptr:companies) {
        delete ptr;
        ptr = nullptr;
    }

    if (not won) {
        cout << "\t\t\tEND GAME ~~~\n";
    }
    cout << "\tThank you for testing this program :)\n";
    waitForPlayer();
    clearScreen();
}

void setUpPlayers(int mode, int playersNumber) {
    for (int i=0; i<playersNumber; i++) {
        stringstream question;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        question << "Enter player " <<  i+1 << "'s name: ";
        string name = askForString(question.str());
        Player newPlayer(name, mode);
        cout << newPlayer.getDetails();
        players.push_back(newPlayer);
    }
    waitForPlayer();
    clearScreen();
}

void setUpCompanies(int maxCompanies, string fileName) {
    // instantiate company object from data read from text file and store
    // them into companies global vector
    ifstream fileToRead(fileName);
    int counter = 0;
    if (fileToRead.is_open()) {
        while (! fileToRead.eof() && counter < maxCompanies) {
            string level, companyName, rest;
            getline(fileToRead, level, ';');
            getline(fileToRead, companyName, ';');
            getline(fileToRead, rest);
            int companyLevel = stoi(level);
            switch (companyLevel) {
                case 1: {
                    companies.push_back(new Bronze(companyName));
                    break;
                };
                case 2: {
                    companies.push_back(new Silver(companyName));
                    break;
                };
                case 3: {
                    companies.push_back(new Gold(companyName));
                    break;
                }

            }
            counter ++;
        }
    }
    fileToRead.close();
}

void setUpShares() {
    /* Set up the amount of shares and share price in each company */
    for (auto ptr:companies) {
        ptr ->setTotalShares(numberOfPlayers);
        ptr ->setSharePrice(ptr -> getLevel());
    }
}

void resetSharesPrice() {
    /* Set the share price of each company to a new random value*/
    for (auto ptr: companies) {
        ptr ->setSharePrice(ptr -> getLevel());
    }
}

void setUpRisks(string fileName) {
    // instantiate risk object from data read from text file and store
    // them into risks global vector
    ifstream fileToRead(fileName);
    if (fileToRead.is_open()) {
        while (! fileToRead.eof()) {
            string riskName, effect, min, max;
            getline(fileToRead, riskName, ';');
            getline(fileToRead, effect, ';');
            getline(fileToRead, min, ';');
            getline(fileToRead, max);
            Risk newRisk(riskName, effect, stoi(min), stoi(max));
            risks.push_back(newRisk);
        }
    }
    fileToRead.close();
}

/******************** GAME FUNCTIONS *********************/

void checkMenuSelection(char userChoice, Player& player) {
    switch (userChoice) {
        case 'B': {
            buyShares(player);
            break;
        }
        case 'S': {
            sellShares(player);
            break;
        }
        case 'A': {
            acquireCompany(player);
            break;
        }
        case 'P': {
            usePower(player);
            break;
        }
        case 'R': {
            takeARisk(player);
            break;
        }
        case 'Q': {
            quitPlayer(player);
            break;
        }
        default:
            cout << "Invalid key\n";
            break;
    }
}

void checkMenuSelectionAdvanced(char userChoice, Player& player) {
    switch (userChoice) {
        case 'B': {
            buyShares(player);
            break;
        }
        case 'S': {
            sellShares(player);
            break;
        }
        case 'A': {
            acquireCompany(player);
            break;
        }
        case 'P': {
            usePower(player);
            break;
        }
        case 'R': {
            takeARisk(player);
            break;
        }
        case 'Q': {
            quitPlayer(player);
            break;
        }
        case 'V': {
            saveGame("gameData.txt");
            break;
        }
        default:
            cout << "Invalid key\n";
            break;
    }
}

void buyShares(Player & player) {
    char companyKey = askForCompanyKey("Buy shares in which company");
    int companyIndex = getCompanyIndex(companyKey);
    Company* ptr = companies[companyIndex];

    /*maxShares is the maximum number of shares that the user is able to buy from the given company
     *based on player's money and company's available shares*/
    if (ptr->getTotalShares() <= 0) {
        cout << "This company doesnt have any available shares to buy.\n";
    } else {
        /* Player cannot buy more shares than the company's available shares*/
        int maxShares = min(player.getMoney()/ptr->getSharePrice(), ptr->getTotalShares());
        if (maxShares > 0) {
            int numberOfShares = askForNumber("How many shares to buy: ", 1, maxShares);
            player.buyShares(ptr, numberOfShares);
        } else {
            cout << "You dont have enough money to buy shares.\n";
        }
    }
}

void sellShares(Player& player) {
    char companyKey = askForCompanyKey("Sell shares in which company");
    int companyIndex = getCompanyIndex(companyKey);
    // player can only sell the amount of shares they have in that company
    int maxShares = player.getCompanyShares(companyKey);
    if (maxShares > 0) {
        int numberOfShares = askForNumber("How many shares to sell: ", 1, maxShares);
        player.sellShares(companies[companyIndex], numberOfShares);
    } else {
        cout << "You dont have any shares to sell\n";
    }
}


void acquireCompany(Player & player) {
    /* Default acquire company option*/
    char companyKey = askForCompanyKey("You want to acquire which company");
    int companyIndex = getCompanyIndex(companyKey);
    //check if company is already owned
    if (companies[companyIndex] -> getOwnerName() == noOwner) {
        //check if player has enough shares in company
        int playerShares = player.getCompanyShares(companyKey);
        if (playerShares >= companies[companyIndex]->getCompanyCost()) {
            companies[companyIndex]->setOwner(player.getPlayerName());
            player.updateTotalCompaniesOwned(1);
        } else {
            cout << "You dont have enough shares to acquire this company.\n";
        }
    } else {
        cout << "This company is already owned.\n";
    }
}

void usePower(Player & player) {
    int mode = player.getMode();
    if (player.getPowerUsageLeft() > 0) {
        char companyKey = askForCompanyKey("Use the cooperate power of which company");
        int companyIndex = getCompanyIndex(companyKey);
        Company* ptr = companies[companyIndex];
        if (ptr->getOwnerName() == player.getPlayerName()) {
            int multiplier = rand() % mode + 2;
            int level = ptr -> getLevel();
            switch (level) {
                case 3: {
                    moneyPower(player, mode*multiplier*10);
                    break;
                }
                case 4: {
                    sharePower(player, mode*multiplier);
                    break;
                }
                case 5: {
                    sharePower(player, mode*multiplier);
                    moneyPower(player, mode*multiplier*10);
                    break;
                }
            }
            player.updatePowerUsage(-1);
    } else {
        cout << "You must own this company to use power!\n";
        }
    } else {
        cout << "You dont have any power usage left!\n";
    }
}

void moneyPower(Player &player, int amount) {
    player.updateMoney(amount);
    string action = (amount > 0)? "Added" : "Minus";
    cout << action << " $" << amount << " to " << player.getPlayerName()
         << "'s account\n";
}

void sharePower(Player &player, int amount) {
    string action = (amount > 0) ? "Added " : "Minus ";
    char companyKey = askForCompanyKey("Select which company to " + action + " shares");
    int companyIndex = getCompanyIndex(companyKey);
    Company* ptr = companies[companyIndex];
    player.addCompanyShares(ptr, amount);
    cout << action << amount << " " << ptr -> getCompanyName() + "'s shares to" + player.getPlayerName() + "'s portfolio\n";
}

void takeARisk(Player &player) {
    Risk chosenRisk = risks[getRandomNum(0, risks.size()-1)];
    string effect = chosenRisk.getEffect();
    string name = chosenRisk.getName();
    int max = chosenRisk.getMax();
    int min = chosenRisk.getMin();
    cout << chosenRisk.getDetails();
    if (effect == "money") {
        // check if effect name starts with global
        if (name.rfind("Global", 0) == 0) {
            // if True then, implement this effect on every player
            for (auto &globalPlayer: players) {
                moneyEffect(globalPlayer, min, max);
            }
        } else {
            moneyEffect(player, min, max);
        }

    } else
    {
        if (effect == "shares") {
            shareEffect(player, min, max);
        } else
        {
            if (effect == "assets") {
                shareEffect(player, min, max);
                moneyEffect(player, min, max);
            }
        }
    }
}

void moneyEffect(Player &player, int min, int max) {
    int money = 0;
    int mode = player.getMode();
    int randomValue = mode*getRandomNum(abs(min), abs(max));
    if (max < 0) {
        randomValue *= -1;
        if (min < 0) {
            money += max*mode;
        }
    }
    money += mode*randomValue;
    moneyPower(player, money);
}

void shareEffect(Player & player, int min, int max) {
    stringstream question;
    int randomValue = getRandomNum(min, max);
    int signedChange = (max > 0) ? randomValue : -1*randomValue;
    sharePower(player, signedChange);
}

void quitPlayer(Player player) {
    for (auto companyDetails: player.getCompaniesDetails()) {
        Company* ptr = companyDetails.first;
        int companyShares = companyDetails.second;
        if (ptr->getOwnerName() == player.getPlayerName()) {
            ptr->setOwner(noOwner);
        }
        // Return back company's shares from player to company's available shares;
        ptr->updateShares(companyShares);
    }
    // erase player from global players vector
    int pos = getIndexFromPlayer(player);
    players.erase(players.begin() + pos);
    cout << "Exited " << player.getPlayerName() << " from game!\n";
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

void displayTitle() {
    // use this if NOT using the title as a constant
    cout << divider << endl;
    cout << "\t\tRisky Business :: Share Market Simulation\n";
    cout << divider << endl;

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
}

void displayRisks() {
    for (auto risk:risks) {
        cout << risk.getDetails() << endl;
    }
}

void displayCompanies() {
    for (auto c:companies) {
        cout << c -> getDetails() << endl;
    }
}

/*display company's total shares, share price, cost and owner*/
void displayMarket() {
    stringstream descriptions;
    descriptions << divider << endl;
    descriptions << setw(35) << "Available" << setw(10) << "Current" << setw(10) << "Company"<< setw(12) << "Current" << "\n";
    descriptions << setw(34) << "Shares" << setw(10) << "Value" << setw(10) << "Cost" << setw(12) << "Owner" << "\n";
    for (auto & ptr:companies) {
        descriptions << setw(25) << ptr->getCompanyName() << setw(7) << ptr->getTotalShares()<< setw(10)
        << ptr->getSharePrice() << setw(11) << ptr->getCompanyCost() << setw(14) << ptr->getOwnerName() << endl;
    }
    cout << descriptions.str();
}

void displayMenu() {
    cout << setw(15) << "[B]uy" << setw(10) << "[S]ell" << setw(10) << "[P]ower" << setw(10) << "[R]isk" << setw(10) << "[Q]uit" << setw(10) << "[A]quire" << endl;

}

void displayMenuAdvanced() {
    cout << setw(15) << "[B]uy" << setw(10) << "[S]ell" << setw(10) << "[P]ower" << setw(10) << "[R]isk" << setw(10) << "[Q]uit" << setw(12) << "[A]quire" << setw(10) << "Sa[V]e" << endl;

}

void displayGameInterface(Player &player, int minCompanies, int minMoney, int day) {
    cout << divider << endl;
    cout << "\t\tRisky Business :: Share Market Simulation\n";
    cout << divider << endl;
    cout << "\t#Companies to win: " << minCompanies << "\tMin Money: $" << minMoney << "\t\tDay: " << day << endl;
    displayMarket();
    cout << player.getPortfolio();
    cout << divider << endl;
    displayMenu();
    cout << divider << endl;
}

/***************** GET FUNCTIONS ****************************/

int getRandomNum(int min, int max) {
    return rand()%(max - min + 1) + min;
}

string getCompanyKeys(int mode) {
    stringstream ss;
    return ss.str();
}

int getMinCompanies(int mode) {
    return mode - 1; //minimum number of companies player must own to win
}

int getMinMoney(int mode) {
    return (mode+1)*100; //minimum amount of money player must own to win
}

int getMaxDays(int mode) {
    return mode*10; //maximum days player can play to win the game
}

int getMaxCompanies(int mode) {
    return mode*3; //maximum number of companies to read from file
}

int getCompanyIndex(char companyKey) {
    for (int i=0; i < companies.size(); i++) {
        Company* ptr = companies[i];
        if (ptr -> getKey() == companyKey) {
            return i;
        }
    }
    return -1;
}

int getIndexFromPlayer(Player player) {
    for (int i=0; i<players.size(); i++) {
        if (players[i].getPlayerName() == player.getPlayerName()) {
            return i;
        }
    }
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
        return response;
    }
}

char askForCompanyKey(string question) {
    /* ask for company key until a valid company key is input, return the company key*/
    char companyKey = ' ';
    bool validKey = false;
    while (!validKey) {
        companyKey = askForLetter(question + " [" + companies[0]->getKey() + "-" + companies[companies.size()-1]->getKey() + "]: ");
        int companyIndex = getCompanyIndex(companyKey);
        if (companyIndex != -1) {
            validKey = true;
        } else {
            cout << "Invalid company key!\n";
        }
    }
    return companyKey;
}

/********************** EXTRA FUNCTIONALITIES ***********************/

bool fileExist(string fileName) {
    ifstream infile(fileName);
    return infile.good();
}

void saveGame(string inputFile) {
    ofstream fileToWrite(inputFile);
    if (fileToWrite.is_open()) {
        for (auto player:players) {
            fileToWrite << player.getPlayerName();
        }
    }
    fileToWrite.close();
}

void loadGame(string outputFile) {
    string line;
    if (fileExist(outputFile)) {
        ifstream fileToRead(outputFile);
        if (fileToRead.is_open()) {
            while (not fileToRead.eof()) {
                getline(fileToRead, line);
                cout << line;
            }
        }
        fileToRead.close();
    }
}
