#include <cstdio>
#include "deck.h"

void deal_hand(EXC::Deck & deck, int num_cards) {
    while(num_cards--) {
        EXC::Card card = deck.deal_card();
        printf("%s ", EXC::card_str(card));
    }
    puts("");
}

int main()
{
    try {
        EXC::Deck deck;
        printf("there are %d cards remaining\n", deck.remaining());

        deal_hand(deck, 9);
        deal_hand(deck, 5);
        deal_hand(deck, 13);
        deal_hand(deck, 10);

        printf("there are %d cards remaining\n", deck.remaining());
    } catch (EXC::E & e) {
        puts(e.what());
        return 1;
    }

    return 0;
}
