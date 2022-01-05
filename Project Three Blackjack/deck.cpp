#include "deck.h"

Deck::Deck() {
    // EFFECTS: constructs a "newly opened" deck of cards.  first the
    // spades from 2-A, then the hearts, then the clubs, then the
    // diamonds.  The first card dealt should be the 2 of Spades.
    reset();
}

void Deck::reset() {
    // EFFECTS: resets the deck to the state of a "newly opened" deck
    // of cards:
    for (unsigned int suit = 0; suit < 4; suit++) {
        for (unsigned int spot = 0; spot < 13; spot++) {
            deck[suit * 13 + spot].suit = (Suit) suit;
            deck[suit * 13 + spot].spot = (Spot) spot;
        }
    }
    next = 0;
}

void Deck::shuffle (int n) {
    // REQUIRES: n is between 0 and 52, inclusive.

    // MODIFIES: this

    // EFFECTS: cut the deck into two segments: the first n cards,
    // called the "left", and the rest called the "right".  Note that
    // either right or left might be empty.  Then, rearrange the deck
    // to be the first card of the right, then the first card of the
    // left, the 2nd of right, the 2nd of left, and so on.  Once one
    // side is exhausted, fill in the remainder of the deck with the
    // cards remaining in the other side.  Finally, make the first
    // card in this shuffled deck the next card to deal.  For example,
    // shuffle(26) on a newly-reset() deck results in: 2-clubs,
    // 2-spades, 3-clubs, 3-spades ... A-diamonds, A-hearts.
    //
    // Note: if shuffle is called on a deck that has already had some
    // cards dealt, those cards should first be restored to the deck
    // in the order in which they were dealt, preserving the most
    // recent post-shuffled/post-reset state.
    int i, num_left = 0, num_right = 0;
    Card left[n], right[DeckSize - n];
    for (i = 0; i < n; i++) {
        left[i] = deck[i];
    }
    for (i = 0; i < DeckSize - n; i++) {
        right[i] = deck[i + n];
    }
    while (num_left < n || num_right < DeckSize - n) {
        if (num_right < DeckSize - n) {
            deck[num_left + num_right] = right[num_right];
            num_right++;
        }
        if (num_left < n) {
            deck[num_left + num_right] = left[num_left];
            num_left++;
        }
    }
    next = 0;
}

Card Deck::deal() {
    // MODIFIES: this

    // EFFECTS: returns the next card to be dealt.  If no cards
    // remain, throws an instance of DeckEmpty.
    if (next < DeckSize)
        return deck[next++];
    else
        throw DeckEmpty();
}

int Deck::cardsLeft() {
    // EFFECTS: returns the number of cards in the deck that have not
    // been dealt since the last reset/shuffle.
    return DeckSize - next;
}