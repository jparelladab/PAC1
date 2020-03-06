#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Constants *********************************************************/

#define MAX_PAIRS 5
#define MAX_ROUNDS 9
#define MAX_CHAR 100

/* Types *************************************************************/

typedef enum {false, true} bool;

typedef char string[MAX_CHAR+1];

typedef enum {NOVICE, MEDIUM, ADVANCED, MASTER} tLevel;
typedef enum {whiteWins, blackWins, draw} tResult;

typedef struct {
    int id;
    string name;
    int age;
    string country;
    int elo;
    tLevel level;
} tPlayer;

typedef struct {
    int idPairing;
    int idPlayerWhite;
    int idPlayerBlack;
    tResult result;
} tPairing;

typedef struct {
    int num;
    tPairing pairs[MAX_PAIRS];
    int numPairings;
    int numWVictories;
    int numBVictories;
    int numDraws;
} tRound;

typedef struct {
    int day;
    int month;
    int year; 
} tDate;

typedef struct {
    string name;
    string loc;
    tDate date;
    tPlayer *players;
    int numPlayers;
    tRound rounds[MAX_ROUNDS];
    int numRounds;
} tChessTournament;

/* Functions *********************************************************/

void init_chess_tournament (tChessTournament *c);
void new_player (tChessTournament *c, int id, string name, int age, string country, int elo);
tPlayer *find_player (tChessTournament c, int id);
tLevel get_level (int elo);
void new_round (tChessTournament *c, int num);
bool find_player_in_round(tChessTournament *c, int idPlayer, int numRound);
void add_pairing (tChessTournament *c, int idPairing, int idWPlayer, int idBPlayer, int numRound);
void print_round_pairings (tChessTournament c, int numRound);