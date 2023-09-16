#include <iostream>
#include "main.h"


int mode = 4;
int companiesToWin = 1;
int maximumCompanies = 1;
int minWinMoney = 0;
int maxDays = 1;

int main() {
    //set up new seed
    srand(unsigned (time(nullptr)));
    //display intro to game
    //displayTextFile("RBintro.txt");
    //testPlayer();
    //testCompany();
    //testRisk();
    //setUpPlayer();
    setUpGame();
    return 0;
}

int getIndexFromPlayer(Player player) {
    for (int i=0; i<players.size(); i++) {
        if (players[i].getPlayerName() == player.getPlayerName()) {
            return i;
        }
    }
}

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

Company getCompanyByKey(char key) {
    for(auto company:companies) {
        if (company.getKey() == key) {
            return company;
        }
    }
}

void resetMarketShares() {
    for (auto &company:companies) {
        company.setSharePrice();
    }
}
int getIndexFromCompanyKey(char key) {
    for(int i=0; i < companies.size(); i++) {
        if (companies[i].getKey() == key) {
            return i;
        }
    }
    return -1;
}

string listCompanyKeys() {
    stringstream ss;
    ss << "company [" << companies[0].getKey()<< "-" << companies[maximumCompanies-1].getKey() << "]: ";
    return ss.str();
}

int askForCompanyKey(string question) {
    /* ask for company key until a valid company key is input, return the company key*/
    char companyKey = ' ';
    bool validKey = false;
    while (!validKey) {
        companyKey = askForLetter(question);
        int companyIndex = getIndexFromCompanyKey(companyKey);
        if (companyIndex != -1) {
            validKey = true;
        } else {
            cout << "Invalid company key!\n";
        }
    }
    return companyKey;
}

void buyShares(Player & player) {
    stringstream question;
    question << "Buy shares in which " << listCompanyKeys();
    char companyKey = askForCompanyKey(question.str());
    int companyIndex = getIndexFromCompanyKey(companyKey);
    Company company = companies[companyIndex];

    //maxShares is the maximum number of shares that the user is able to buy
    int maxShares = player.getMoney()/company.getSharePrice();
    if (maxShares > 0) {
        int numberOfShares = askForNumber("How many shares to buy: ", 1, maxShares);
        player.buyShares(companies[companyIndex], numberOfShares);
    } else {
        cout << "You dont have enough money to buy shares.\n";
    }
}

void sellShares(Player & player) {
    stringstream question;
    question << "Sell shares in which " << listCompanyKeys();
    char companyKey = askForCompanyKey(question.str());
    int companyIndex = getIndexFromCompanyKey(companyKey);
    // player can only sell the amount of shares they have in that company
    int maxShares = player.getSharesinCompany(companyKey);
    if (maxShares > 0) {
        int numberOfShares = askForNumber("How many shares to sell: ", 1, maxShares);
        player.sellShares(companies[companyIndex], numberOfShares);
    } else {
        cout << "You dont have any shares to sell\n";
    }
}


void acquireCompany(Player & player) {
    stringstream question;
    question << "You want to acquire which " << listCompanyKeys();
    char companyKey = askForCompanyKey(question.str());
    int companyIndex = getIndexFromCompanyKey(companyKey);
    //check if company is already owned
    if (companies[companyIndex].getOwnerName() == noOwner) {
        //check if player has enough shares in company
        int playerShares = player.getSharesinCompany(companyKey);
        if (playerShares >= companies[companyIndex].getCompanyWorth()) {
            companies[companyIndex].setOwner(player.getPlayerName());
            player.updateTotalCompaniesOwned(1);
        } else {
            cout << "You dont have enough shares to acquire this company.\n";
        }
    } else {
        cout << "This company is already owned.\n";
    }
}


void usePower(Player & player) {
    stringstream question;
    question << "Use the cooperate power of which company" << listCompanyKeys();
    if (player.getPowerUsageLeft() > 0) {
        char companyKey = askForCompanyKey(question.str());
        int companyIndex = getIndexFromCompanyKey(companyKey);
        Company company = companies[companyIndex];
        if (companies[companyIndex].getOwnerName() == player.getPlayerName()) {
            player.updatePowerUsage(-1);
            int multiplier = rand() % mode + 2;
            int level = company.getCompanyLevel();
            switch (level) {
                case 1: {
                    cout << "Added $" << 10 * mode * multiplier << " to " << player.getPlayerName()
                         << "'s account\n";
                    player.updateMoney(10 * mode * multiplier);
                    break;
                }
                case 2: {
                    cout << "Added " << mode * multiplier << " shares of " << company.getCompanyName()
                         << "to " << player.getPlayerName() << "'s portfolio\n";
                    player.buyShares(company, mode * multiplier);
                    break;
                }
                case 3: {
                    player.updateMoney(10 * mode * multiplier);
                    player.buyShares(company, mode * multiplier);
                    cout << "Added " << 10 * mode * multiplier << " to " << player.getPlayerName()
                         << "'s account\n";
                    cout << "Added " << mode * multiplier << " shares of " << company.getCompanyName()
                         << "to " << player.getPlayerName() << "'s portfolio\n";
                    break;
                }
            }
        } else {
            cout << "You must own this company to use power!\n";
        }
    }
}

void quitPlayer(Player player) {
    for (auto companyDetails: player.getCompaniesDetails()) {
        char companyKey = companyDetails.first;
        int companyShares = companyDetails.second;
        int companyIndex = getIndexFromCompanyKey(companyKey);
        if (companies[companyIndex].getOwnerName() == player.getPlayerName()) {
            companies[companyIndex].setOwner(noOwner);
        }
        // Return back company's shares from player to company's available shares;
        companies[companyIndex].updateShares(companyShares);
    }
    // erase player from global players vector
    int pos = getIndexFromPlayer(player);
    players.erase(players.begin() + pos);
    cout << "Exited from game!\n";
}

void action(char userChoice, Player & player) {
    switch(userChoice) {
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
            cout << "Invalid input\n";
            break;
    }
}

void playGame(Player & player) {
    char userChoice = ' ';
    displayTitle();
    displayGameStatus();
    displayMarket();
    displayPlayerPortfolio(player);
    displayMenu();
    userChoice = askForLetter("What will you do now? ");
    action(userChoice, player);

}

void setUpGame() {
    bool end = false;
    int mode = 4; //Default game mode is 4 for easy
    int numberOfPlayers = 1;

    // asking for player's input
    mode = askForNumber("Select game mode:", 4, 6);
    numberOfPlayers = askForNumber("Enter number of players:", 1, 3);

    // set up winning criteria given game mode
    companiesToWin = mode - 1;
    maximumCompanies = mode*3;
    minWinMoney = (mode+1)*100;
    maxDays = mode*10;

    // set up companies
    parseCompanyData();
    // set up risks
    parseRiskData();

    for (int i=0; i < numberOfPlayers; i++) {
        setUpPlayer();
    }
    do {
        for (auto & player:players) {
            playGame(player);
            if (player.getTotalCompaniesOwned() >= companiesToWin && player.getMoney() >= minWinMoney) {
                won = true;
                cout << "Congratulations, " << player.getPlayerName() << "! You won :)\n";
            }
            if (dayCounter >= maxDays || won || players.size() <= 0) {
                end = true;
            }
            waitForPlayer();
            clearScreen();
            dayCounter += 1;
            resetMarketShares();
        }
    } while (not end);
    if (not won) {
        cout << "You lose :(\n";
        waitForPlayer();
        clearScreen();
    }
}

void displayGameStatus() {
    cout << "\t#Companies to win: " << companiesToWin << "\tMin Money: $"<<minWinMoney <<"\t\tDay: "<< dayCounter << endl;
    cout << divider << endl;
}

void displayMarket() {
    stringstream descriptions;
    descriptions << setw(35) << "Available" << setw(10) << "Current" << setw(10) << "Company"<< setw(12) << "Current" << "\n";
    descriptions << setw(34) << "Shares" << setw(10) << "Value" << setw(10) << "Cost" << setw(12) << "Owner" << "\n";
    for (auto & company:companies) {
        descriptions << setw(25) << company.getCompanyName() << setw(7) << company.getTotalShares()<< setw(10) << company.getSharePrice() << setw(11) << company.getCompanyWorth() << setw(14) << company.getOwnerName() << endl;
    }
    cout << descriptions.str();

}
int askForNumber(string question, int min, int max) {
    // ask for a numeric response from the user
    bool valid = false;
    string userInput = "";
    int number = 1;
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
        }
    }
    cin.ignore();
    return toupper(userInput[0]);
}

void testPlayer() {
    Player testPlayer("Jash", 3);
    cout << testPlayer.getDetails();
}

string askForString(string question) {
    string response;
    cout << question;
    cin >> response;
    return response;
}

void setUpPlayer() {
    Player newPlayer;
    string name = askForString("Enter player name: ");
    newPlayer = Player(name, mode);
    cout << newPlayer.getDetails();
    players.push_back(newPlayer);
    waitForPlayer();
    clearScreen();
}

void displayPlayerPortfolio(Player player) {
    stringstream portfolio;
    portfolio << divider << endl;
    portfolio << "\t\t" << player.getPlayerName() << "'s Share Portfolio and Assets\n";
    portfolio << divider << endl;
    portfolio << "Total Money: $" << player.getMoney() << "\tCompanies owned: " << player.getTotalCompaniesOwned() << "\tTotal Shares: " << player.getTotalShares() << "\t\tPower: " << player.getPowerUsageLeft() << endl;
    if (player.getCompaniesDetails().size() > 0) {
        portfolio << "\tCompany Names\t\tShares\t\tPower" << endl;
        for (auto companyShare: player.getCompaniesDetails()) {
            Company company = getCompanyByKey(companyShare.first);
            string power = (company.getOwnerName() == player.getPlayerName()) ? company.getPower() : "None";
            int sharesInCompany = companyShare.second;
            portfolio << "\t" << company.getCompanyName() << "\t" << sharesInCompany << "\t\t" << power << "\n";
        }
    } else
    {
        portfolio << "\n\t\tYour share portfolio is empty, " << player.getPlayerName();
    }
    cout << portfolio.str() << endl;
}

void displayMenu() {
    cout << divider << endl;
    cout << "\t[B]uy\t[S]ell\t[A]quire\t[P]ower\t[R]isk\t[Q]uit\n";
    cout << divider << endl;
}

void displayCompanies() {
    for (auto c:companies) {
        cout << c.getDetails() << endl;
    }
}

void testCompany() {
    parseCompanyData();
    displayCompanies();
}

void parseCompanyData() {
    // instantiate company object from data read from text file and store
    // them into companies global vector
    fstream fileToRead("companies.txt");
    int counter = 0;
    if (fileToRead.is_open()) {
        while (! fileToRead.eof() && counter < maximumCompanies) {
            string level, companyName, power;
            getline(fileToRead, level, ';');
            getline(fileToRead, companyName, ';');
            getline(fileToRead, power);
            int companyLevel = stoi(level);
            switch (companyLevel) {
                case 1: {
                    companies.push_back(Bronze(companyName));
                };

            }
            Company newCompany(companyName, stoi(level), power);
            newCompany.setTotalShares(newCompany.getCompanyWorth() + (rand()%11 + 10)*numberOfPlayers);
            companies.push_back(newCompany);
            counter ++;
        }
    }
    fileToRead.close();
}

void parseRiskData() {
    // instantiate risk object from data read from text file and store
    // them into risks global vector
    fstream fileToRead("risksAdvanced.txt");
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

void displayRisks() {
    for (auto risk:risks) {
        cout << risk.getDetails() << endl;
    }
}

void testRisk() {
    parseRiskData();
    displayRisks();

}

int generateRandomNum(int min, int max) {
    /* generate a random integer between min and max (inclusive)*/
    return rand()%(max - min + 1) + min;
}

void calculateMoneyEffect(Player & player, int min, int max) {
    int money = 0;
    int randomValue = mode*generateRandomNum(abs(min), abs(max));
    if (max < 0) {
        randomValue *= -1;
        if (min < 0) {
            money += max*mode;
        }
    }
    money += mode*randomValue;
    string action = (max > 0) ? "Added " : "Minus ";
    cout << action << "$" << money << " to " << player.getPlayerName() << "'s acccount\n";
    player.updateMoney(money);
}

void calculateShareEffect(Player & player, int min, int max) {
    char companyKey = ' ';
    stringstream question;
    int randomValue = generateRandomNum(min, max);
    int signedChange = (max > 0) ? randomValue : -1*randomValue;
    string action = (max > 0) ? "Added " : "Minus ";
    cout << action << randomValue << " shares" << " to " << player.getPlayerName() << "'s shares\n";
    question << action << "shares to which " << listCompanyKeys();
    companyKey = askForCompanyKey(question.str());
    int companyIndex = getIndexFromCompanyKey(companyKey);
    player.buyShares(companies[companyIndex], signedChange);
}

void takeARisk(Player & player) {
    Risk chosenRisk = risks[generateRandomNum(0, risks.size()-1)];
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
                calculateMoneyEffect(globalPlayer, min, max);
            }
        } else {
            calculateMoneyEffect(player, min, max);
        }

    } else
    {
        if (effect == "shares") {
            calculateShareEffect(player, min, max);
        } else
        {
            if (effect == "assets") {
                calculateMoneyEffect(player, min, max);
                calculateShareEffect(player, min, max);
            }
        }
    }
}
