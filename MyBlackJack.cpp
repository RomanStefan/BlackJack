#include <iostream>
using namespace std;

struct Carte
{
	int valoare;
	char simbol;
	char nume[18], uno[3];
};

struct Mana
{
	Carte carte[22];
	int puncte, blackjack, dimensiune;
}Player[12];

struct Player
{
    char nume[64];
	double bani;
	Mana mana;
	bool eDealer;
	int jocuri_castigate, jocuri_pierdute;
}player[12];

struct Pachet{
	Carte carte[57];
	int total;
} pachet;

char simbol[4][9] =
{
    "Inima",
    "Romb",
    "Trefla",
    "Frunza"
};

char definitii_carti[3][9] =
{
    "Valet",
    "Dama",
    "Popa"
};
