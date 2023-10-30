/**************************************************
 Project: Risky Business - Assigment 2 part B
 Author: Jash Nguyen (34327681)
 Purpose: GAME ADVANCED CLASS file
**************************************************/

#include "GameAdvanced.h"

/********** CONSTRUCTORS ******/

GameAdvanced::GameAdvanced():GameDefault() {

}

GameAdvanced::GameAdvanced(int newGameMode, int playerNum) : GameDefault(newGameMode, playerNum) {

}
/************* GAME FUNCTIONS ******************/

void GameAdvanced::checkMenuSelection(char userChoice, Player &player) {

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
        case 'L': {
            loadGame("gameData.txt");
            break;
        }
        case 'M': {
            mergeCompany(player);
            break;
        }
        default:
            cout << "Invalid key\n";
            break;
    }

}

bool GameAdvanced::haveAnotherShareHolder(char companyKey, string playerName) {
    for (auto player: players) {
        if ((player.getCompanyShares(companyKey) > 0) && (player.getPlayerName() != playerName)) {
            return true;
        }
    }
    return false;
}

void GameAdvanced::acquireCompany(Player &player) {

    char companyKey = askForCompanyKey("You want to acquire which company");
    int companyIndex = getCompanyIndex(companyKey);
    //check if company is already owned
    if (companies[companyIndex] -> getOwnerName() == noOwner) {
        if (companies[companyIndex]->getTotalShares() <= 0 && (not haveAnotherShareHolder(companyKey, player.getPlayerName()))) {
            companies[companyIndex]->setOwner(player.getPlayerName());
            player.updateTotalCompaniesOwned(1);
            cout << "Successfully acquired " << companies[companyIndex]->getCompanyName() << endl;
            char userInput = askToContinue("Do you want to acquire more companies? (y/n) ");
            if (userInput == 'Y') {
                waitForPlayer();
                clearScreen();
                displayGameInterface(player);
                GameAdvanced::acquireCompany(player);
            }
        } else {
            cout << "You must own all the shares from this company to acquire it.\n";
        }
    } else {
        cout << "This company is already acquired.\n";
    }

}

void GameAdvanced::mergeCompany(Player & player) {
    char companyKey = askForCompanyKey("You want to merge which company");
    int companyIndex = getCompanyIndex(companyKey);
    bool validMerger = false;
    if (haveAnotherShareHolder(companyKey, player.getPlayerName())) {
        if (player.getCompanyShares(companyKey) > 0) {
            while (not validMerger) {
                string shareHolderName = askForString("Which opponent do you want to merge with? ");
                if (shareHolderName == player.getPlayerName()) {
                    cout << "You cannot merge with yourself!\n";
                } else {
                    for (auto &otherPlayer: players) {
                        if (otherPlayer.getPlayerName() == shareHolderName) {
                            int shares = otherPlayer.getCompanyShares(companyKey);
                            if ( shares > 0) {
                                validMerger = true;
                                int mergeCost = shares*(companies[companyIndex])->getSharePrice();
                                if (player.getMoney() >= mergeCost) {
                                    otherPlayer.sellShares(companies[companyIndex], shares);
                                    player.buyShares(companies[companyIndex], shares);
                                    cout << "\t\t Merge successfully.\n";
                                } else {
                                    cout << "You dont have enough money to merge.\n";
                                }
                            } else {
                                cout << "This player doesn't own share in this company to merge with.\n";
                            }
                        }
                    }
                }
            }
        } else {
            cout << "You dont own any company shares to merge with.\n";
        }
    } else {
        cout << "There's no other shareholders of this company to merge with.\n";
    }
}

bool GameAdvanced::fileExist(string fileName) {
    ifstream infile(fileName);
    return infile.good();
}

void GameAdvanced::saveGame(string inputFile) {
    ofstream fileToWrite(inputFile);
    if (fileToWrite.is_open()) {
        // risks are constant so there's no need to write and save risks
        fileToWrite << gameMode << " " << dayCounter << " " << companies.size() << " " << playersNumber << endl;
        // write companies
        for (auto company: companies) {
            fileToWrite << company->getCompanyName() << endl;
            fileToWrite << company->getOwnerName() << endl;
            fileToWrite << company->getLevel() << " " << company->getTotalShares() << " " << company->getSharePrice() << " " << company->getCompanyCost() << endl;
        }
        // write players
        for (auto player: players) {
            fileToWrite << player.getPlayerName() << endl;
            fileToWrite << player.getMoney() << " " << player.getTotalShares() << " " << player.getPowerUsageLeft() << " " << player.getTotalCompaniesOwned() << " " << player.getCompaniesDetails().size() << endl;
            for (auto companyDetail: player.getCompaniesDetails()) {
                fileToWrite << companyDetail.first->getKey() << ';' << companyDetail.second << endl;
            }
        }
        fileToWrite.close();
        cout << "\t\t Saved successfully.\n";
    } else {
        cout << "File unfound.\n";
    }
}

void GameAdvanced::loadGame(string outputFile) {
    string line;
    int mode, day, companiesNum, playersNum;
    // clear up companies pointer vector and players vector
    resetGame();
    ifstream fileToRead(outputFile);
    if (fileToRead.is_open()) {
        fileToRead >> mode >> day >> companiesNum >> playersNum;
        setGameMode(mode);
        setDay(day);
        for (int i = 0; i < companiesNum; i ++) {
            string companyName, owner;
            int level, shares, sharePrice, cost;
            getline(fileToRead, line);
            getline(fileToRead, companyName);
            getline(fileToRead, owner);
            fileToRead >> level >> shares >> sharePrice >> cost;
            switch (level) {
                case 3: {
                    companies[i] = new Bronze(companyName, owner, shares, sharePrice, cost);
                    break;
                }
                case 4: {
                    companies[i] = new Silver(companyName, owner, shares, sharePrice, cost);
                    break;
                }
                case 5: {
                    companies[i] = new Gold(companyName, owner, shares, sharePrice, cost);
                    break;
                    } default: {cout << "Invalid company level.\n";
                }
            }
        }
        getline(fileToRead, line);

        for (int i = 0; i < playersNum; i ++) {
            string playerName;
            int money, companyShares, powerLeft, companiesOwned, companyDetails;
            getline(fileToRead, playerName);
            fileToRead >> money >> companyShares >> powerLeft >> companiesOwned >> companyDetails;
            getline(fileToRead, line);
            Player player(playerName, mode);

            for (int j = 0; j < companyDetails; j ++) {
                string companyKey, shares;
                getline(fileToRead, companyKey, ';');
                getline(fileToRead, shares);
                player.updateCompanyShares(companies[getCompanyIndex(companyKey[0])], stoi(shares));
            }
            players.push_back(player);

        }
        fileToRead.close();
        cout << "\t\t Load previous saved game successfully.\n";

    } else {
        cout << "File unfound.\n";
    }
}

/*********** DISPLAY FUNCTIONS ***************/

void GameAdvanced::displayMenu() {
    cout << setw(15) << "[B]uy" << setw(10) << "[S]ell" << setw(10) << "[P]ower" << setw(10) << "[R]isk" << setw(10) << "[Q]uit" << setw(12) << "[A]quire" << setw(12) << "[M]erge" << setw(10) << "Sa[V]e" << setw(10) << "[L]oad" << endl;
    cout << divider << endl;
}



