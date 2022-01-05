#include "player.h"

class Simple_player : public Player {
    // the implementation of the Simple player derived from the base class Player
 public:
    int bet(unsigned int bankroll, unsigned int minimum);
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive

    bool draw(Card dealer, const Hand &player);
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.

    void expose(Card c);
        // EFFECTS: allows the player to "see" the newly-exposed card c.
        // For example, each card that is dealt "face up" is expose()d.
        // Likewise, if the dealer must show his "hole card", it is also
        // expose()d.  Note: not all cards dealt are expose()d---if the
        // player goes over 21 or is dealt a natural 21, the dealer need
        // not expose his hole card.

    void shuffled();
        // EFFECTS: tells the player that the deck has been re-shuffled.
    
    ~Simple_player();
        // Note: this is here only to suppress a compiler warning.
        //       Destructors are not needed for this project.
};

int Simple_player::bet(unsigned int bankroll, unsigned int minimum) {
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive
    return (int)minimum;
}

bool Simple_player::draw(Card dealer,             // Dealer's "up card"
                              const Hand &player) // Player's current hand
{
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
    if (player.handValue().soft)
        return (player.handValue().count <= 17 || (player.handValue().count == 18 && dealer.spot != TWO && dealer.spot != SEVEN && dealer.spot != EIGHT)) ? true : false;
    else
        return (player.handValue().count <= 11 || (player.handValue().count == 12 && !(dealer.spot >= FOUR && dealer.spot <= SIX)) || (player.handValue().count >=13 && player.handValue().count <= 16 && !(dealer.spot >= TWO && dealer.spot <= SIX))) ? true : false;
}

void Simple_player::expose(Card c) {
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.
}

void Simple_player::shuffled() {
    // EFFECTS: tells the player that the deck has been re-shuffled.
}

Simple_player::~Simple_player() {
    // Note: this is here only to suppress a compiler warning.
    //       Destructors are not needed for this project.
}

class Counting_player : public Player {
    // the implementation of the Counting player derived from the base class Player
 private:
    // the cards that the Counting player seen from the deck
    int count;
 public:
    int bet(unsigned int bankroll, unsigned int minimum);
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive

    bool draw(Card dealer, const Hand &player);
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.

    void expose(Card c);
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.

    void shuffled();
    // EFFECTS: tells the player that the deck has been re-shuffled.
    
    ~Counting_player();
    // Note: this is here only to suppress a compiler warning.
    //       Destructors are not needed for this project.
};

int Counting_player::bet(unsigned int bankroll, unsigned int minimum) {
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll 
    // inclusive
    return (count >= 2 && bankroll >= minimum * 2) ? (int)minimum * 2 : (int)minimum;
}

bool Counting_player::draw(Card dealer,             // Dealer's "up card"
                                const Hand &player) // Player's current hand
{
    // EFFECTS: returns true if the player wishes to be dealt another
    // card, false otherwise.
    Simple_player simple_player;
    return simple_player.draw(dealer, player);
}

void Counting_player::expose(Card c) {
    // EFFECTS: allows the player to "see" the newly-exposed card c.
    // For example, each card that is dealt "face up" is expose()d.
    // Likewise, if the dealer must show his "hole card", it is also
    // expose()d.  Note: not all cards dealt are expose()d---if the
    // player goes over 21 or is dealt a natural 21, the dealer need
    // not expose his hole card.
    if (c.spot >= TEN)
        count--;
    else if (c.spot >= TWO && c.spot <= SIX)
        count++;
}

void Counting_player::shuffled() {
    // EFFECTS: tells the player that the deck has been re-shuffled.
    count = 0;
}

Counting_player::~Counting_player() {
    // Note: this is here only to suppress a compiler warning.
    //       Destructors are not needed for this project.
}

Player *get_Simple() {
    // EFFECTS: returns a pointer to a "simple player", as defined by the
    // project specification
    Player *simple_player = new Simple_player();
    return simple_player;
}

Player *get_Counting() {
    // EFFECTS: returns a pointer to a "counting player", as defined by
    // the project specification.
    Player *counting_player = new Counting_player();
    return counting_player;
}