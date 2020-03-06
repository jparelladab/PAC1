#include "chess.h"

void init_chess_tournament (tChessTournament *c) {
  assert(c != NULL);
  
  strcpy(c->name,"OPEN CHESS 2020");
  strcpy(c->loc, "BARCELONA");
  c->date.day = 30;
  c->date.month = 1;
  c->date.year = 2020;
  c->numPlayers = 0;
  c->numRounds = 0;
}

tLevel get_level(int elo) {
    assert(elo >= 0);
    
    if (elo > 0 && elo <= 1800) {
        return NOVICE;
    } else if (elo > 1800 && elo <= 2000){
        return MEDIUM;
    } else if (elo > 2000 && elo <= 2400){
        return ADVANCED;
    } else if (elo > 2400){
        return MASTER;
    } else {
        return -1;
    }
}

tPlayer *find_player (tChessTournament c, int id) {
    assert(c != NULL);
    assert(id > 0);
    
    tPlayer *res;
    int i;
    i = 0;
    res = NULL;
    while ((i < c.numPlayers) && (res == NULL)) {
        if (c.players[i].id == id)
           res = &(c.players[i]);
        else
           i++;
    }
    return res;
}

void new_player (tChessTournament *c, int id, string name, int age, string country, int elo) {
    assert(c != NULL);
    assert(id > 0);
    
    if (find_player (*c, id) != NULL)
        printf("ERROR: Player with code %i already stored\n", id);
    else {
        if (c->numPlayers == 0)
            c->players = (tPlayer *) malloc(sizeof(tPlayer));
        else 
            c->players = (tPlayer *) realloc(c->players, (c->numPlayers+1)*sizeof(tPlayer));
        if (c->players == NULL)
            printf("ERROR: Memory error\n");
        else {
            c->players[c->numPlayers].id = id;
            c->players[c->numPlayers].age = age;
            c->players[c->numPlayers].elo = elo;
            strcpy(c->players[c->numPlayers].name, name);
            strcpy(c->players[c->numPlayers].country, country);
            c->players[c->numPlayers].level = get_level(elo);
            c->numPlayers++;
        }
    }
}

void new_round (tChessTournament *c, int num) {
    assert(c != NULL);
    assert(num > 0);
    
    if (c->numRounds >= num) {
        printf("ERROR: Round %i already stored\n", num);
    } else if (num > MAX_ROUNDS) {
        printf("ERROR: Round number out of bounds. Maximum round number: %i\n", MAX_ROUNDS);
    } else {
        c->rounds[num-1].num = num;
        c->rounds[num-1].numBVictories = 0;
        c->rounds[num-1].numDraws = 0;
        c->rounds[num-1].numWVictories = 0;
        c->rounds[num-1].numPairings = 0;
        c->numRounds += 1;
    }
}

bool find_player_in_round (tChessTournament *c ,int idPlayer, int numRound){
    assert(c != NULL);
    assert(idPlayer > 0);
    assert(numRound > 0);
    
    for (int i=0; i < c->rounds[numRound-1].numPairings; i++){
        if(c->rounds[numRound -1].pairs[i].idPlayerBlack == idPlayer)
            return true;
        else if(c->rounds[numRound -1].pairs[i].idPlayerWhite == idPlayer)
            return true;
    }
    return false;
}

void add_pairing (tChessTournament *c, int idPairing, int idWPlayer, int idBPlayer, int numRound) {
    assert(c != NULL);
    assert(idPairing > 0);
    assert(idWPlayer > 0);
    assert(idBPlayer > 0);
    assert(numRound > 0);
    
    if (find_player (*c, idWPlayer) == NULL) {
        printf("ERROR: Player with id %i does not exist\n", idWPlayer);
    } else if (find_player (*c, idBPlayer) == NULL) {
        printf("ERROR: Player with id %i not found\n", idBPlayer);
    } else if (find_player_in_round(c, idWPlayer, numRound) == true) {
        printf("ERROR: Player with id %i already paired in round %i\n", idWPlayer, numRound);
    } else if (find_player_in_round(c, idBPlayer, numRound) == true) {
        printf("ERROR: Player with id %i already paired in round %i\n", idBPlayer, numRound);
    } else if (c->rounds[numRound-1].numPairings >= MAX_PAIRS) {
        printf("ERROR: Pairings are full in round %i\n", numRound);
    } else if (c->numRounds > MAX_ROUNDS) {
        printf("ERROR: MAX number of rounds (%i) already reached\n", MAX_ROUNDS);
    } else {
        c->rounds[numRound-1].pairs[c->rounds[numRound-1].numPairings].idPairing = idPairing;
        c->rounds[numRound-1].pairs[c->rounds[numRound-1].numPairings].idPlayerWhite = idWPlayer;
        c->rounds[numRound-1].pairs[c->rounds[numRound-1].numPairings].idPlayerBlack = idBPlayer;
        c->rounds[numRound-1].numPairings ++;
        if(rand()%3+1 == 1) {
            c->rounds[numRound-1].pairs[c->rounds[numRound-1].numPairings].result = whiteWins;
            c->rounds[numRound-1].numWVictories ++;
        } else if(rand()%3+1 == 2) {
            c->rounds[numRound-1].pairs[c->rounds[numRound-1].numPairings].result = blackWins;
            c->rounds[numRound-1].numBVictories ++;
        } else if(rand()%3+1 == 3) {
            c->rounds[numRound-1].pairs[c->rounds[numRound-1].numPairings].result = draw;
            c->rounds[numRound-1].numDraws ++;
        }
    }
}

void print_round_pairings (tChessTournament c, int numRound) {
    assert(c != NULL);
    assert(numRound > 0);
    
    tRound round = c.rounds[numRound-1];
    printf("\n");
    printf("******************************************************************\n");
    printf("%s %s %i/%i/%i (%i players in the tournament)\n", c.name, c.loc, c.date.day, c.date.month, c.date.year, c.numPlayers);
    printf("******************************************************************\n");
    printf("ROUND %i\n", numRound);
    printf("------------------------------------------------------------------\n");
    printf("Number of pairings: %i\n", round.numPairings);
    printf("Number of wins with white pieces: %i\n", round.numWVictories);
    printf("Number of wins with black pieces: %i\n", round.numBVictories);
    printf("Number of draws: %i\n", round.numDraws);
    for(int i=0; i<round.numPairings; i++){
        tPairing pair = round.pairs[i];
        tPlayer *white = find_player(c, pair.idPlayerWhite);
        tPlayer *black = find_player(c, pair.idPlayerBlack);
        string winner;
        if (pair.result == 0){
            strcpy(winner,"White wins");
        } else if (pair.result == 1){
            strcpy(winner, "Black wins");
        } else {
            strcpy(winner,"Draw");
        }
        printf("\n");
        printf("Pairing id: %i\n", pair.idPairing);
        printf("White: %s, %i years old, from %s, %i elo\n", white->name, white->age, white->country, white->elo);
        printf("Black: %s, %i years old, from %s, %i elo\n", black->name, black->age, black->country, black->elo);
        printf("Result: %s\n", winner);
    }
}