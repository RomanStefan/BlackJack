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

int aceiasi_carte(Carte a, Carte b) {
	if (strcmp(a.nume, b.nume) == 0) return 1;
	else return 0;
}

void cartea21 (Mana &p) {
	do{
		p.carte[p.dimensiune] = pachet.carte[--pachet.total];

		if ((p.carte[p.dimensiune].valoare != 0) && (p.carte[p.dimensiune].valoare != 10))
            break;
	}while(1);

	if (p.carte[p.dimensiune].valoare == 12)
        p.carte[p.dimensiune].valoare = 10;

	p.dimensiune++;
}

void numara21 (Mana &p) {
	unsigned short int i;

	p.puncte += p.carte[p.dimensiune - 1].valoare;

	if (p.puncte > 21) {
		for (i = 0; i < p.dimensiune; i++) {
			if (p.carte[i].valoare == 11) {
				p.carte[i].valoare = 1;
				p.puncte -= 10;
			}
		}
	}
}


void jucatorNou(int i)
{
    system("cls");

    cout<<"Doriti sa adaugati un jucator nou.\n\n";
    cout<<"Numele: ";

    cin.getline(player[i].nume, 60);

    while(strlen(player[i].nume) == 0)
    {
        cout<<"Numele: ";
        cin.getline(player[i].nume, 60);
    }

    cout<<"Suma de bani: ";
    cin>>player[i].bani;
}

void editeazaJucator(int i)
{
    system("cls");

    cout<<"Doriti sa editati un jucator.\n\n";

    char a;
    while(1)
    {
        cout<<"Ce doriti sa editati?\n\n";
        cout<<"1)Numele\n";
        cout<<"2)Suma de bani\n";

        cin>>a;

        if(a == '1' || a == '2')
            break;
    }

    if(a == '1')
    {
        cout<<"\nIntroduceti noul nume: ";
        cin.getline(player[i].nume, 60);

        while(strlen(player[i].nume))
        {
            cout<<"\nIntroduceti noul nume: ";
            cin.getline(player[i].nume, 60);
        }
    }
    if(a == '2')
    {
        cout<<"\nIntroduceti noua suma de bani: ";
        cin>>player[i].bani;
    }

}

void afiseaza_despre_jucator(int i)
{
    cout<<"\n\nNume: "<<player[i].nume;
    cout<<"\nSuma de bani: "<<player[i].bani;
    cout<<"\nJocuri castigate: "<<player[i].jocuri_castigate;
    cout<<"\nJocuri pierdute: "<<player[i].jocuri_pierdute;
}


int main()
{
    srand(time(0));
    CreiazaPachet();
    afiseaza_pachet();
    jucatorNou(1);
    editeazaJucator(1);
    afiseaza_despre_jucator(1);
}
