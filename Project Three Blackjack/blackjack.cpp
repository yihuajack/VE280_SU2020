#include <iostream>
#include <string>
#include "deck.h"
#include "player.h"
#include "rand.h"

using namespace std;

void Shuffle(Deck& deck) {
    // EFFECT: Shuffle the deck
    int i, cut_point;
    cout << "Shuffling the deck\n";
    for (i = 0; i < 7; i++) {
        cut_point = get_cut();
        deck.shuffle(cut_point);
        cout << "cut at " << cut_point << endl;
    }
}

void Deal(Deck& deck, Player *player, Hand& hand) {
    // REQUIRE: an initialized player
    // EFFECT: deal the player's hands
    Card dealcard = deck.deal();
    hand.addCard(dealcard);
    player->expose(dealcard);
    cout << "Player dealt " << SpotNames[dealcard.spot] << " of " << SuitNames[dealcard.suit] << endl;
}

Card Deal(Deck& deck, Hand& hand, bool hole) {
    // EFFECTS: deal the dealer's hands and return the card that is dealt
    Card dealcard = deck.deal();
    hand.addCard(dealcard);
    if (!hole)
        cout << "Dealer dealt " << SpotNames[dealcard.spot] << " of " << SuitNames[dealcard.suit] << endl;
    return dealcard;
}

void FinalStateJudge(const int dealercount, const int playercount, int& bankroll, const int wager) {
    // REQUIRE: the count of the player's hands is less than or equal to 21
    // EFFECT: calculate the bankroll according to the conditions
    cout << "Dealer's total is " << dealercount << endl;
    if (dealercount > 21) {
        cout << "Dealer busts\n";
        bankroll += wager;
    }
    else if (dealercount > playercount) {
        bankroll -= wager;
        cout << "Dealer wins\n";
    }
    else if (dealercount < playercount) {
        bankroll += wager;
        cout << "Player wins\n";
    }
    else
        cout << "Push\n";
}

void Blackjack(Deck& deck, Player *player, int& bankroll) {
    // REQUIRES: thishand is less than hands
    //           bankroll is larger than or equal to MIN_BET
    // EFFECT: deal cards for the player and the dealer
    //         calculate bankroll
    int wager;
    const int MIN_BET = 5;
    Hand hand_dealer, hand_player;
    if (deck.cardsLeft() < 20) {
        Shuffle(deck);
        player->shuffled();
    }
    wager = player->bet(bankroll, MIN_BET);
    cout << "Player bets " << wager << endl;
    Deal(deck, player, hand_player);
    Card dealerfaceup = Deal(deck, hand_dealer, false);
    player->expose(dealerfaceup);
    Deal(deck, player, hand_player);
    Card dealerfacedown = Deal(deck, hand_dealer, true);
    if (hand_player.handValue().count == 21) {
        bankroll += wager * 3 / 2;
        cout << "Player dealt natural 21\n";
        return;
    }
    while (player->draw(dealerfaceup, hand_player)) {
        Deal(deck, player, hand_player);
    }
    cout << "Player's total is " << hand_player.handValue().count << endl;
    if (hand_player.handValue().count > 21) {
        bankroll -= wager;
        cout << "Player busts\n";
    }
    else {
        player->expose(dealerfacedown);
        cout << "Dealer's hole card is " << SpotNames[dealerfacedown.spot] << " of " << SuitNames[dealerfacedown.suit] << endl;
        while (hand_dealer.handValue().count < 17) {
            player->expose(Deal(deck, hand_dealer, false));
        }
        FinalStateJudge(hand_dealer.handValue().count, hand_player.handValue().count, bankroll, wager);
    }
}

void Play(int bankroll, int hands, const string& playertype) {
    // REQUIRE: playertype is one of the two strings "simple" or "counting"
    // EFFECT: initialize deck and player
    //         deal with the situation the limit of bankroll is reached or there is no hands left
    int thishand = 1;
    const int MIN_BET = 5;
    Deck deck;
    Player *player = nullptr;
    player = (playertype == "simple") ? get_Simple() : get_Counting();
    Shuffle(deck);
    player->shuffled();
    if (bankroll < MIN_BET) {
        cout << "Player has " << bankroll << " after " << 0 << " hands\n";
        return;
    }
    while (bankroll >= MIN_BET && thishand <= hands) {
        cout << "Hand " << thishand << " bankroll " << bankroll << endl;
        Blackjack(deck, player, bankroll);
        thishand++;
    }
    cout << "Player has " << bankroll << " after " << --thishand << " hands\n";
}

int main(int argc, char *argv[]) {
    // REQUIRES: argv[1] and argv[2] are positive (>=1) integers input by the user and within an upper limit of 10000
    //           argv[3] is a string that is one of the two strings "simple" or "counting"
    // EFFECTS: process the program arguments
    int bankroll = stoi(argv[1]), hands = stoi(argv[2]);
    string playertype = argv[3];
    Play(bankroll, hands, playertype);
}