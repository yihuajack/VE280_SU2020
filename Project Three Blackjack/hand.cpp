#include "hand.h"

Hand::Hand() {
    // EFFECTS: establishes an empty blackjack hand.
    discardAll();
}

void Hand::discardAll() {
    // MODIFIES: this
    // EFFECTS: discards any cards presently held, restoring the state
    // of the hand to that of an empty blackjack hand.
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::addCard(Card card) {
    // MODIFIES: this
    // EFFECTS: adds the card "c" to those presently held.
    if (card.spot == ACE) {
        if (curValue.count >= 11)
            curValue.count++;
        else {
            curValue.count += 11;
            curValue.soft = true;
        }
    }
    else if (card.spot == JACK || card.spot == QUEEN || card.spot == KING)
        curValue.count += 10;
    else
        curValue.count += card.spot + 2;
    if (curValue.count > 21 && curValue.soft) {
        curValue.count -= 10;
        curValue.soft = false;
    }
}

HandValue Hand::handValue() const {
    // EFFECTS: returns the present value of the blackjack hand.  The
    // count field is the highest blackjack total possible without
    // going over 21.  The soft field should be true if and only if at
    // least one ACE is present, and its value is counted as 11 rather
    // than 1.  If the hand is over 21, any value over 21 may be returned.
    //
    // Note: the const qualifier at the end of handValue means that
    // you are not allowed to change any member variables inside
    // handValue. Adding this prevents the accidental change by you.
    return curValue;
}