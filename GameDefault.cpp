

#include <iostream>
#include "GameDefault.h"

/********************** MAIN FUNCTION ********************/

void GameDefault::playGame() {
    bool won = false;
    char userChoice = ' ';
    do {
        for (auto &player:players){
            if (player.getState()) {
                displayGameInterface(player);
                displayMenu();
                userChoice = askForLetter("What will you do now? ");
                checkMenuSelection(userChoice, player);
                won = endGame(player, dayCounter);
                waitForPlayer();
                clearScreen();
            }
        }
        /* Increase day counter by one and reset market shares */
        dayCounter ++;
        resetSharesPrice();
    } while (not won && dayCounter < maxDays);
    cout << "\t\t\tEND GAME ~~~\n";
    cout << "\tThank you for testing this program :)\n";
    waitForPlayer();
    clearScreen();

}

/*********************** CONSTRUCTORS *********************/
GameDefault::GameDefault() {
    dayCounter = 1;
    gameMode = 4;
    playersNumber = 1;
    minCompanies = 1;
    minMoney = 100;
    maxDays = 1;
}

GameDefault::GameDefault(int newGameMode, int playerNum) {
    setGameMode(newGameMode);
    setPlayersNumber(playerNum);
    dayCounter = 1;

    minCompanies = newGameMode - 1;
    minMoney = (gameMode+1)*100;
    maxDays = gameMode*10;
    int maxCompanies = gameMode*3;

    setUpCompanies(maxCompanies, "companies.txt");\
    setUpShares();
    setUpPlayers(gameMode, playersNumber);
    setUpRisks("riskDefault.txt");
}

GameDefault::~GameDefault() {
    // clean up pointers
    for (auto ptr:companies) {
        delete ptr;
        ptr = nullptr;
    }
}

/*********************** SETTER FUNCTIONS ***********************/

void GameDefault::setGameMode(int val) {
    gameMode = (4 <= val <= 6) ? val : 4;
}

void GameDefault::setDay(int val) {
    dayCounter = (val > 0) ? val : 1;
}

void GameDefault::setPlayersNumber(int val) {
    playersNumber = (1 <= val <= 4)? val : 1;
}

void GameDefault::setUpPlayers(int mode, int playersNumb) {
    for (int i=0; i<playersNumb; i++) {
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

void GameDefault::setUpCompanies(int maxCompanies, string fileName) {
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
                }
                case 2: {
                    companies.push_back(new Silver(companyName));
                    break;
                }
                case 3: {
                    companies.push_back(new Gold(companyName));
                    break;
                }
                default: {cout << "Invalid company level.\n";}

            }
            counter ++;
        }
    }
    fileToRead.close();
}

void GameDefault::setUpShares() {
    /* Set up the amount of shares and share price in each company */
    for (auto ptr:companies) {
        ptr ->setTotalShares(playersNumber);
        ptr ->setSharePrice(ptr -> getLevel());
    }
}


void GameDefault::setUpRisks(string fileName) {
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

/***************** GET FUNCTIONS ****************************/

int GameDefault::getRandomNum(int min, int max) {
    return rand()%(max - min + 1) + min;
}

int GameDefault::getCompanyIndex(char companyKey) {
    for (int i=0; i < companies.size(); i++) {
        Company* ptr = companies[i];
        if (ptr -> getKey() == companyKey) {
            return i;
        }
    }
    return -1;
}

char GameDefault::askToContinue(string question) {
    char response = ' ';
    string options = "YN";
    bool end = false;
    while (not end) {
        response = askForLetter(question);
        if (options.find(response) != string::npos) {
            end = true;
            return response;
        } else {
            cout << "Invalid key.\n";
        }
    }
}

/******************** GAME FUNCTIONS *********************/

void GameDefault::resetSharesPrice() {
    /* Set the share price of each company to a new random value*/
    for (auto ptr: companies) {
        ptr ->setSharePrice(ptr -> getLevel());
    }
}

void  GameDefault::resetGame() {

    // clear company pointers
    for (auto company:companies) {
        delete company;
        company = nullptr;
    }

    players.clear();
}

/*check if game is ended based on winning conditions */
bool GameDefault::endGame(Player player, int day) {
    bool end = false;
    if (day >= maxDays) {
        cout << "Maximum days reached! Game over!\n";
        end = true;
    } else {
        if (player.getTotalCompaniesOwned() >= minCompanies and player.getMoney() >= minMoney) {
            cout << divider << endl;
            cout << setw(40) << "Congratulations, " << player.getPlayerName() << "! You won :)\n";
            cout << divider << endl;
            end = true;
        }
    }
    return end;
}


void GameDefault::checkMenuSelection(char userChoice, Player& player) {
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

void GameDefault::buyShares(Player & player) {
    char companyKey = askForCompanyKey("Buy shares in which company");
    int companyIndex = getCompanyIndex(companyKey);
    Company *ptr = companies[companyIndex];

    /*maxShares is the maximum number of shares that the user is able to buy from the given company
     *based on player's money and company's available shares*/
    if (ptr->getTotalShares() <= 0) {
        cout << "This company doesnt have any available shares to buy.\n";
    } else {
        /* Player cannot buy more shares than the company's available shares*/
        int maxShares = min(player.getMoney() / ptr->getSharePrice(), ptr->getTotalShares());
        if (maxShares > 0) {
            int numberOfShares = askForNumber("How many shares to buy: ", 1, maxShares);
            player.buyShares(ptr, numberOfShares);
            char userInput = askToContinue("Do you want to buy more shares? (y/n) ");
            if (userInput == 'Y') {
                waitForPlayer();
                clearScreen();
                displayGameInterface(player);
                buyShares(player);
            }
        } else {
            cout << "You dont have enough money to buy shares.\n";
        }
    }
}

void GameDefault::sellShares(Player& player) {
    char companyKey = askForCompanyKey("Sell shares in which company");
    int companyIndex = getCompanyIndex(companyKey);
    // player can only sell the amount of shares they have in that company
    int maxShares = player.getCompanyShares(companyKey);
    if (maxShares > 0) {
        int numberOfShares = askForNumber("How many shares to sell: ", 1, maxShares);
        player.sellShares(companies[companyIndex], numberOfShares);
        cout << "You earned $" << numberOfShares*(companies[companyIndex]->getSharePrice()) << " from selling shares!\n";
        char userInput = askToContinue("Do you want to buy more shares? (y/n) ");
        if (userInput == 'Y') {
            waitForPlayer();
            clearScreen();
            displayGameInterface(player);
            sellShares(player);
        }
    } else {
        cout << "You dont have any shares to sell\n";
    }
}

char GameDefault::askForCompanyKey(string question) {
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

void GameDefault::acquireCompany(Player & player) {
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
            char userInput = askToContinue("Do you want to acquire more companies? (y/n) ");
            if (userInput == 'Y') {
                waitForPlayer();
                clearScreen();
                displayGameInterface(player);
                acquireCompany(player);
            }

        } else {
            cout << "You dont have enough shares to acquire this company.\n";
        }
    } else {
        cout << "This company is already acquired.\n";
    }
}

void GameDefault::usePower(Player & player) {
    if (player.getPowerUsageLeft() > 0) {
        char companyKey = askForCompanyKey("Use the cooperate power of which company");
        int companyIndex = getCompanyIndex(companyKey);
        Company* ptr = companies[companyIndex];
        if (ptr->getOwnerName() == player.getPlayerName()) {
            int multiplier = (rand() % gameMode) + 2;
            int level = ptr -> getLevel();
            switch (level) {
                case 3: {
                    moneyPower(player, gameMode*multiplier*10);
                    break;
                }
                case 4: {
                    sharePower(player, gameMode*multiplier);
                    break;
                }
                case 5: {
                    sharePower(player, gameMode*multiplier);
                    moneyPower(player, gameMode*multiplier*10);
                    break;
                }
                default: {cout << "Invalid company level.\n";}
            }
            player.updatePowerUsage(-1);
        } else {
            cout << "You must own this company to use power!\n";
        }
    } else {
        cout << "You dont have any power usage left!\n";
    }
}

void GameDefault::moneyPower(Player &player, int amount) {
    player.updateMoney(amount);
    string action = (amount > 0)? "Added" : "Minus";
    cout << action << " $" << abs(amount) << " to " << player.getPlayerName()
         << "'s account\n";
}

void GameDefault::sharePower(Player &player, int amount) {
    int multiplier = rand() % gameMode + 2;
    string action = (amount > 0) ? "Added " : "Minus ";
    char companyKey = askForCompanyKey("Select which company to " + action + " shares");
    int companyIndex = getCompanyIndex(companyKey);
    Company* ptr = companies[companyIndex];
    // making sure that we don't take away more shares than the company's available shares
    amount = min(amount, ptr->getTotalShares());
    player.updateCompanyShares(ptr, amount);
    if (amount > 0) {
        ptr->updateShares(-1*amount);
    }
    cout << action << abs(amount) << " " << ptr -> getCompanyName() + "'s shares to " + player.getPlayerName() + "'s portfolio\n";
}

void GameDefault::takeARisk(Player &player) {
    random_device rd;
    mt19937 g(rd());
    shuffle(risks.begin(), risks.end(), g);
    Risk chosenRisk = risks[rand()%risks.size()];
    string effect = chosenRisk.getEffect();
    string name = chosenRisk.getName();
    int max = chosenRisk.getMax();
    int min = chosenRisk.getMin();
    //cout << chosenRisk.getDetails();
    if (effect == "money") {
        // check if riskEffect name starts with global
        if (name.rfind("Global", 0) == 0) {
            // if True then, implement this riskEffect on every player
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

void GameDefault::moneyEffect(Player &player, int min, int max) {
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

void GameDefault::shareEffect(Player & player, int min, int max) {
    stringstream question;
    int randomValue = getRandomNum(min, max);
    int signedChange = (max > 0) ? randomValue : -1*randomValue;
    sharePower(player, signedChange);
}

void GameDefault::quitPlayer(Player &player) {
    for (auto companyDetails: player.getCompaniesDetails()) {
        Company* ptr = companyDetails.first;
        int companyShares = companyDetails.second;
        if (ptr->getOwnerName() == player.getPlayerName()) {
            ptr->setOwner(noOwner);
        }
        // Return back company's shares from player to company's available shares;
        ptr->updateShares(companyShares);
    }
    player.setActiveState(false);
    cout << "Exited " << player.getPlayerName() << " from game!\n";

}


/********************* DISPLAY FUNCTIONS *****************/

void GameDefault::displayTitle() {
    cout << divider << endl;
    cout << "\t\t\t\tRisky Business :: Share Market Simulation\n";
    cout << divider << endl;

}

/*display company's total shares, share price, cost and owner*/
void GameDefault::displayMarket() {
    stringstream descriptions;
    descriptions << divider << endl;
    descriptions << setw(50) << "Available" << setw(10) << "Current" << setw(10) << "Company"<< setw(12) << "Current" << "\n";
    descriptions << setw(49) << "Shares" << setw(10) << "Value" << setw(10) << "Cost" << setw(12) << "Owner" << "\n";
    for (auto ptr:companies) {
        descriptions << setw(40) << ptr->getCompanyName() << setw(7) << ptr->getTotalShares()<< setw(10)
                     << ptr->getSharePrice() << setw(11) << ptr->getCompanyCost() << setw(14) << ptr->getOwnerName() << endl;
    }
    cout << descriptions.str();
}

void GameDefault::displayMenu() {
    cout << setw(30) << "[B]uy" << setw(10) << "[S]ell" << setw(10) << "[P]ower" << setw(10) << "[R]isk" << setw(10) << "[Q]uit" << setw(10) << "[A]quire" << endl;
    cout << divider << endl;

}

void GameDefault::displayGameInterface(Player player) {
    displayTitle();
    cout << setw(40) << "#Companies to win: " << minCompanies << "\tMin Money: $" << minMoney << "\t\tDay: " << dayCounter << endl;
    displayMarket();
    cout << player.getPortfolio();
    cout << divider << endl;
}

/**********************  TESTER FUNCTIONS *******************************/

void GameDefault::displayCompanies() {
    for (auto company:companies) {
        cout << company->getDetails();
    }
}

void GameDefault::displayRisks() {
    for (auto risk:risks) {
        cout << risk.getDetails();
    }
}

/*testing different scenarios where game can end */
void GameDefault::testEndGame() {
    Player testPlayer("Alice", gameMode);

    // case 1, player has played more than maximum number of days without winning
    endGame(testPlayer, maxDays+1);

    // case 2, player has minimum number of companies to win
    testPlayer.setTotalCompaniesOwned(minCompanies);
    endGame(testPlayer, maxDays);

    //case 3, player has minimum amount of money to win
    testPlayer.setMoney(minMoney);
    testPlayer.setTotalCompaniesOwned(minCompanies-1);
    endGame(testPlayer, maxDays);

    /* case 4, player has minimum number of companies and money to win
     * and day counter is equal to maximum days
    */
    testPlayer.setTotalCompaniesOwned(minCompanies);
    testPlayer.setMoney(minMoney);
    endGame(testPlayer, maxDays);

    /* case 5, player has minimum number of companies and money to win
    * and day counter is equal than maximum days + 1
   */
    endGame(testPlayer, maxDays+1);
}

void GameDefault::testPlayer() {
    //testing default constructor for player
    Player testPlayer;
    int testMode = 4;
    testPlayer = Player();
    testPlayer.setPlayerName("Bob");
    testPlayer.setGameMode(4);
    testPlayer.setPowerUsage(10 - testMode);
    testPlayer.setMoney(5 * 10 * testMode);
    cout << testPlayer.getDetails();

    //testing overloaded constructor for player
    testPlayer = Player("Jash", testMode);
    cout << testPlayer.getDetails();

    //testing update methods
    testPlayer.updateMoney(10);
    testPlayer.updatePowerUsage(-1);
    testPlayer.updateTotalCompaniesOwned(2);
    testPlayer.updateTotalShares(20);
    cout << testPlayer.getDetails();

}

void GameDefault::testRisk() {
    Risk testRisk;
    testRisk = Risk();
    // Testing default constructor for Risk class
    testRisk.setMinimum(10);
    testRisk.setMaximum(50);
    testRisk.setRiskEffect("money");
    testRisk.setRiskName("won a lottery");
    cout << testRisk.getDetails();

    //testing overloaded constructor for risk
    testRisk = Risk("enrolled to univeristy", "money", 10, -50);
    cout << testRisk.getDetails();
}












