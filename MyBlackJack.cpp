#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
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


void anora (int i) {
	if(pachet.carte[i].valoare == 12) strcpy(pachet.carte[i].uno, "o");
	else strcpy(pachet.carte[i].uno, "un");
}

void amestecaPachet() {
	int i, rand1, rand2, total;

	total = pachet.total*pachet.total*2;

	for (i = 0; i < total; i++) {
		rand1 = rand()%(pachet.total + 1);
		rand2 = rand()%(pachet.total + 1);

		pachet.carte[56] = pachet.carte[rand1];
		pachet.carte[rand1] = pachet.carte[rand2];
		pachet.carte[rand2] = pachet.carte[56];
	}
}



void CreiazaPachet() {
	unsigned short int i, j;

	pachet.total = 0;

	for (i = 0; i < 4; i++) {
		pachet.carte[pachet.total].valoare = 11;

		strcpy(pachet.carte[pachet.total].nume, "As de ");
		strcat(pachet.carte[pachet.total].nume, simbol[i]);

		anora(pachet.total);

		pachet.carte[pachet.total].simbol = i;

		for (j = 2; j < 11; j++) {
			pachet.carte[++pachet.total].valoare = j;

			itoa(j, pachet.carte[52].nume, 10);

			strcpy(pachet.carte[pachet.total].nume, pachet.carte[52].nume);
			strcat(pachet.carte[pachet.total].nume, " de ");
			strcat(pachet.carte[pachet.total].nume, simbol[i]);

			anora(pachet.total);

			pachet.carte[pachet.total].simbol = i;
		}

		for (j = 0; j < 3; j++) {
			pachet.carte[++pachet.total].valoare = 12;

			strcpy(pachet.carte[pachet.total].nume, definitii_carti[j]);
			strcat(pachet.carte[pachet.total].nume, " de ");
			strcat(pachet.carte[pachet.total].nume, simbol[i]);

			anora(pachet.total);

			pachet.carte[pachet.total].simbol = i;
		}

		pachet.total++;
	}

	pachet.total++;

	amestecaPachet();
}

void afiseaza_pachet() {
	int i;

	for (i = 0; i < 52; i++) {
		cout<<pachet.carte[i].nume<<' '<<pachet.carte[i].valoare<<'\n';
	}
}


int main()
{
    srand(time(0));
    CreiazaPachet();
    afiseaza_pachet();
}
