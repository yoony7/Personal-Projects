#include "deck.h"

namespace EXC {

Deck::~Deck() {
  del_deck();
}

void Deck::init() {
  srand((unsigned) time(nullptr));; // seed rand
  rand(); // throwaway rand
  create_deck();
  shuffle_deck();
  return;
}

void Deck::del_deck() {
  if(_deck) delete [] _deck;
  _deck = nullptr;
  rem_count = 0;
}

// move constructor
Deck::Deck(Deck && old) noexcept {
  cards_per_deck = old.cards_per_deck;
  num_decks = old.num_decks;

  // move the deck
  _deck = old._deck;
  rem_count = old.rem_count;

  // reset old deck
  old._deck = nullptr;
  old.del_deck();
}

// Deck Functions

void Deck::init_deck() {
  del_deck();
  if (num_decks > max_decks) throw E("\nDeck: too many decks (max 10)\n");
  rem_count = num_decks * cards_per_deck;
  _deck = new Card[rem_count];
}

/* create deck
suit is cdhs or 0-3; rank is 23456789TJQKA or 0-12
*/

void Deck::create_deck() {
  init_deck();
  uint16 cardnum = 0; // index init
  for (uint8 n_deck = 0; n_deck < num_decks; ++n_deck) {
    uint8 n_suit = 0;
    for (; n_suit < suit_count; ++n_suit) {
      uint8 n_rank = 0;
      for (; n_rank < rank_count; ++n_rank) {
        _deck[cardnum].suit = n_suit;
        _deck[cardnum].rank = n_rank;
        ++cardnum;
      }
    }
  }
}

void Deck::new_deck() {
  create_deck();
  shuffle_deck();
}

void Deck::new_deck(uint8 n) {
  num_decks = n;
  create_deck();
  shuffle_deck();
}

void Deck::shuffle_deck() {
  uint16 ncards = remaining();

  for (uint16 i = 0; i < ncards; ++i) {
    uint16 r = i + (rand() % (ncards - i));
    if (r != i) std::swap(_deck[r], _deck[i]);
  }
}

const Card & Deck::get_card(uint16 index) const {
  if (index >= rem_count) throw E("\nDeck: card out of range\n");
  return _deck[index];
}

const Card & Deck::deal_card() {
  if (rem_count == 0) throw E("\nDeck: cannot deal from empty deck\n");

  return _deck[--rem_count];
}

// Deck Info

uint16 Deck::deck_size() const {
  return cards_per_deck * num_decks;
}

uint16 Deck::remaining() const {
  return rem_count;
}

const Card * Deck::deck() const {
  return _deck;
}

// Non-member functions

const char * card_str(const Card & c) {
  static char outstr[3] = { 'x', 'x', 0};
  char & outstr_rank = outstr[0];
  char & outstr_suit = outstr[1];

  if (c.rank > 7) outstr_rank = facecards[c.rank - 7]; // T J Q K A
  else outstr_rank = c.rank + '2'; // numeric cards

  outstr_suit = suitstr[c.suit];
  return (const char *) outstr;
} 

}
