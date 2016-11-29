//
// Created by dylan on 19/11/2016.
//

#include <cmath>
#include "RailRoad.h"
#include "../Exception/NoMoneyException.h"
#include "../GameMechanics/Bankruptcy.h"

GameBoard::RailRoad::RailRoad(const string &name, double propertyPrice,
                              double rentCost, const string &colour, double mortgage)
        : Property(name, propertyPrice, rentCost, colour, mortgage) {}


void GameBoard::RailRoad::action(Player::Participant *player, GameMechanics::Game *game) {
    // Nobody owns the property
    if (getOwner() == nullptr) {
        noOwner(player, game);
    } else if (!getOwner()->isEqual(player)) {
        // Pay rent
        payRent(player, game);
    }
}

void GameBoard::RailRoad::payRent(Player::Participant *player, GameMechanics::Game * game) {
    int numberOfRailRoad = getOwner()->getSameGroupColourPropertiesAmount("BLACK");
    cout << "The owner has in total " << numberOfRailRoad << " railroads" << endl;
    // Charge 25 if one owned, 50 if two owned, 100 if three owned, 200 if all owned by the same owner
    int amountToBePaid = pow(2, numberOfRailRoad - 1) * 25;
    try {
        player->getMoney().subtractBalance(amountToBePaid);
        getOwner()->getMoney().addBalance(amountToBePaid);
    } catch (NoMoneyException & exception) {
        cout << exception.message << endl;
        // If player cannot pay debt, he will be declared bankrupt
        bool isPlayerNotBankrupt = exception.payAmountDue(game, exception.amountDue, player, getOwner());
        if (!isPlayerNotBankrupt) {
            Bankruptcy::transferProperties(game, player, getOwner());
        }
    }
}