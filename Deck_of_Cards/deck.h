#ifndef deck_h
#define deck_h

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "exception.h"

namespace EXC {

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

constexpr const char * suitstr = "cdhs"; // set ranking of suits
constexpr const char * facecards = "TJQKA"; // set ranking of facecards
constexpr uint8 default_deck = 52;
constexpr uint8 max_decks = 10;
constexpr uint8 suit_count = 4;
constexpr uint8 rank_count = 13;

typedef struct {
uint8 suit : 4;
uint8 rank : 4;
} Card;

class Deck {
uint8 cards_per_deck = 0;
uint8 num_decks = 0;
uint16 rem_count = 0;
Card * _deck = nullptr;

void init_deck();
void del_deck();
void create_deck();
void init();

Deck(const Deck &); // prevent copy constructor
Deck & operator = (Deck); //prevent assignment operator

public:
Deck() : cards_per_deck(default_deck), num_decks(1) {init();}
Deck(uint8 n) : cards_per_deck(default_deck), num_decks(n) { init();}
Deck(Deck &&) noexcept; //move constructor
~Deck();

// deck functions
void new_deck();
void new_deck(uint8 n);
void shuffle_deck();
const Card & get_card(uint16) const;
const Card & deal_card();

// deck info
uint16 remaining() const;
uint16 deck_size() const;
const Card * deck() const;
};

const char * card_str(const Card &);

}

#endif // deck_h
