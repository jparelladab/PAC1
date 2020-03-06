#include "chess.h"

int main (void) {
    tChessTournament c;

    /* section a */
    init_chess_tournament (&c);

    /* section b */
    new_player (&c, 12345, "Magnus Carlsen", 29, "Norway", 2862);
    new_player (&c, 23456, "Fabiano Caruana", 27, "USA", 2354);
    new_player (&c, 34567, "Ding Liren", 25, "China", 2551);
    new_player (&c, 45678, "Sabrina Vega", 37, "Spain", 2350);
    new_player (&c, 56789, "Francisco Vallejo", 38, "Spain", 2701);
    new_player (&c, 67890, "Vladimir Kramnik", 44, "Russia", 2152);
    new_player (&c, 78901, "Vishy Anand", 48, "India", 2425);
    new_player (&c, 89012, "Judit Polgar", 29, "Hungary", 2605);
    new_player (&c, 90123, "David Anton", 22, "Spain", 2664);
    new_player (&c, 01234, "Wesley So", 18, "Philippines", 1650);
    new_player (&c, 123456, "Ian Nepo", 26, "Russia", 2120);
    new_player (&c, 234567, "Hikaru Nakamura", 18, "Japan", 2785);
    new_player (&c, 12345, "Magnus Carlsen", 29, "Norway", 2862); //Already in the list 

    /* section c */
    new_round (&c, 1);
    new_round (&c, 2);
    new_round (&c, 3);
    new_round (&c, 4);
    new_round (&c, 5);
    new_round (&c, 6);
    new_round (&c, 7);
    new_round (&c, 8);
    new_round (&c, 9);

    /* section d */
    add_pairing (&c, 1, 12345, 98765, 1); //Player 98765 does not exist
    add_pairing (&c, 1, 12345, 23456, 1);
    add_pairing (&c, 2, 34567, 45678, 1);
    add_pairing (&c, 3, 56789, 67890, 1);
    add_pairing (&c, 4, 78901, 89012, 1);
    add_pairing (&c, 5, 90123, 01234, 1);  
    add_pairing (&c, 6, 90123, 123456, 1); //90123 already paired in round 1
    add_pairing (&c, 7, 123456, 234567, 1); //Pairings are full in round 1
    add_pairing (&c, 1, 56789, 78901, 2);
    add_pairing (&c, 2, 67890, 89012, 2);
    add_pairing (&c, 3, 90123, 23456, 2);

    /* section e*/
    print_round_pairings (c, 1);
    print_round_pairings (c, 2);

    return 0;
}

