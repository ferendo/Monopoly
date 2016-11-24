//
// Created by dylan on 16/11/2016.
//

#include "UpgradableProperty.h"

GameBoard::UpgradableProperty::UpgradableProperty(const string &name, double propertyPrice, double rentCost,
                                                  const string &colour, GameBoard::HousesPrice housesPrice) :
        Property(name, propertyPrice, rentCost, colour), housesPrice(housesPrice) {}

bool GameBoard::UpgradableProperty::checkIfOwnerHasAllSameColour(Player::Participant *player, GameMechanics::Game *game) {
    return player->getSameGroupColourProperties(getColour()) == game->getGroupColoursSize(getColour());
}

const GameBoard::HousesPrice &GameBoard::UpgradableProperty::getHousesPrice() const {
    return housesPrice;
}

void GameBoard::UpgradableProperty::action(Player::Participant *player, GameMechanics::Game * game) {
    if (getOwner() == nullptr) {
        noOwner(player, game);
    } else if (getOwner()->isEqual(player)) {
        // Upgrade hotel
        if (checkIfOwnerHasAllSameColour(player, game)) {
            upgradeProperty(player, game);
        } else {
            cout << "Upgrading house is currently not available." << endl;
        }
    } else {
        payRent(player, game);
    }
}

void GameBoard::UpgradableProperty::payRent(Player::Participant *player, GameMechanics::Game * game) {
    double amount;
    // If no hotel and does not own same colour properties
    if (currentHousesBuild == 0 && !checkIfOwnerHasAllSameColour(getOwner(), game)) {
        amount = getRentCost();
    } else if (currentHousesBuild == 0) {
        // Owner has same colour properties but no house, thus pay double rent
        cout << "Owner has all " << getColour() << " properties. Pay double rent!!" << endl;
        amount = getRentCost() * 2;
    } else {
        amount = getHousesPrice().getHousePrice(currentHousesBuild);
    }
    player->getMoney().subtractBalance(amount);
    getOwner()->getMoney().addBalance(amount);
}

void GameBoard::UpgradableProperty::upgradeProperty(Player::Participant *player, GameMechanics::Game *game) {
    string input;

    operator<<(cout, housesPrice);
    cout << "Want to upgrade house?(y/n)" << endl;
    getline(cin, input);
    if (input[0] == 'y') {
        // TODO Build evenly
        if (currentHousesBuild < MAX_HOUSES) {
            currentHousesBuild += 1;
            player->getMoney().subtractBalance(getHousesPrice().getPriceToUpgrade());
        } else {
            cout << "Maximum house limit." << endl;
        }
    }
}

string GameBoard::UpgradableProperty::getName() {
    string houseUpgrade;
    for (int i = 0; i < currentHousesBuild; i++) {
        houseUpgrade += "*";
    }
    return Tile::getName() + houseUpgrade;
}



