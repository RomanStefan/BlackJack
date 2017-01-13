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


void StartBlackjack(bool vsComputer, int p1, int p2 = -1) {
	Mana jucator, dealer;
	Carte splitcard;
	int i, j, splitchk = 0, ture;

	srand(time(NULL));

	system("cls");
	int pariu = -1;

	do
    {
		jucator.dimensiune = jucator.blackjack = dealer.blackjack = dealer.dimensiune = jucator.puncte = dealer.puncte = ture = 0;

		CreiazaPachet();

		if (splitchk == 1)
        {
			jucator.carte[jucator.dimensiune++] = splitcard;

			for (i = 0; i < 52; i++)
            {
				if (aceiasi_carte(pachet.carte[i], splitcard) == 1)
				{
					for (j = i; j < --pachet.total; j++)
                    {
						pachet.carte[j] = pachet.carte[j + 1];
					}
				}
			}
		}

		for (i = 0; i < 2; i++)
        {
			if ((splitchk != 1) || (i != 0))
                cartea21(jucator);

			numara21(jucator);

			cartea21(dealer);
			numara21(dealer);
		}
		cout<<"Aveti "<<player[p1].bani<<"$. Cat doriti sa pariati?\n\n";
		cin>>pariu;

		while(player[p1].bani - pariu < 0)
        {
            cout<<"\nNu aveti destui bani. Introduceti o noua suma: ";
            cin>>pariu;
        }
        player[p1].bani -= pariu;

        cout<<"Dealer: \n# ??? #\n";
        cout<<"# "<<dealer.carte[1].nume<<" #\n";

		cout<<"\nPlayer: \n";
		for (i = 0; i < 2; i++)
		{
            cout<<"# "<<jucator.carte[i].nume<<" #\n";
			if ((i == 0) && (splitchk == 1))
			{
				cout<<" split";
				splitchk = 0;
			}
		}

		if (jucator.puncte == 21) jucator.blackjack = 1;
		if (dealer.puncte == 21) dealer.blackjack = 1;


		if (jucator.blackjack == 0) {
            do
            {
                cout<<"\n\n[ "<<player[p1].bani<<" $]\n";
                cout<<"Ai "<<jucator.puncte<<" puncte. Ce vrei sa faci?";
                cout<<"\n1) Hit";
                cout<<"\n2) Hand";
                cout<<"\n3) Split";
                cout<<"\n4) Stay";
                cout<<"\n5) Iesi\n";
                char c;
                cin.get();
                c = cin.get();
				if (c == '1')
                {
					cartea21(jucator);
					numara21(jucator);

                    cout<<"\nAi "<<jucator.carte[jucator.dimensiune - 1].uno;
                    cout<<' '<<jucator.carte[jucator.dimensiune - 1].nume;

					if (jucator.puncte > 21)
                    {
						cout<<'\n'<<player[p1].nume<<" a pierdut!\n";
						break;
					}

					ture = 1;
				}
				else if (c == '2')
                {
                    for (i = 0; i < jucator.dimensiune; i++)
                    {
                        cout<<"# "<<jucator.carte[i].nume<<" #\n";
                    }

                    amestecaPachet();

                    if (splitchk == 1)
                    {
                        cout<<"# "<<splitcard.nume<<" #";
                    }
                }
                else if (c == '3')
                {
                    if ((ture == 0)
                    && ((jucator.carte[0].valoare == jucator.carte[1].valoare)
                    || ((jucator.carte[0].valoare == 1) && (jucator.carte[1].valoare == 11))
                    || ((jucator.carte[0].valoare == 11) && (jucator.carte[1].valoare == 1)))
                    && (splitchk == 0))
                    {
                        splitcard = jucator.carte[--jucator.dimensiune];
                        cout<<"\nAi decis sa-ti salvezi "<<jucator.carte[jucator.dimensiune].nume;

                        jucator.puncte -= jucator.carte[jucator.dimensiune].valoare;

                        cartea21(jucator);
                        numara21(jucator);

                        cout<<"\nAi primit "<<jucator.carte[jucator.dimensiune - 1].uno<<' '<<jucator.carte[jucator.dimensiune - 1].nume;

                        splitchk = 1;
                    }
                    else cout<<"\nNu poti face split.";
                }
                else if (c == '4')
                {
                    cout<<"\n"<<player[p1].nume<<": \n";
                    for (i = 0; i < jucator.dimensiune; i++)
                    {
                        cout<<"# "<<jucator.carte[i].nume<<" #\n";
                    }

                    cout<<"\n\nDealer: \n";
                    for (i = 0; i < dealer.dimensiune; i++)
                    {
                        cout<<"# "<<dealer.carte[i].nume<<" #\n";
                    }
                    cout<<"\n";

                    if (dealer.blackjack == 1)
                        break;

                    ture = 1;

                    while ((dealer.puncte <= 16) && (dealer.puncte <= jucator.puncte) && (jucator.puncte != 21))
                    {
                        cartea21(dealer);
                        numara21(dealer);

                        cout<<"\nDealerul a primit "<<dealer.carte[dealer.dimensiune - 1].uno<<' '<<dealer.carte[dealer.dimensiune - 1].nume<<'\n';

                    }

                    if (dealer.puncte > 21)
                    {
                        cout<<"Dealerul a pierdut!!";
                    }
                    else if (jucator.puncte != 21)
                    {
                        cout<<"\n\nDealerul ramane cu "<<dealer.puncte<<" puncte";
                    }

                    break;
                }
                else if (c == '5')
                {
                    jucator.blackjack = 2;
                    cout<<player[p1].nume<<" crede ca dealerul are blackjack.";

                    break;
                }
                else if (c == '6') {
                    jucator.blackjack = 15;
                    break;
                }
                else cout<<"Comanda necunoscuta\n";
            } while(1);
		}
//5 comit/
		if (jucator.blackjack == 1) {
			cout<<player[p1].nume<<" are blackjack!";
		}

		if (jucator.blackjack == 15)
            break;
		else if (jucator.blackjack == 2)
		{
            if (dealer.puncte == 21) {
                cout<<"Ai dreptate !";
            }
            else cout<<" Nu ai dreptate >.< !";
        }
        else
        {
            if (((jucator.puncte >= dealer.puncte) && (jucator.puncte <= 21)) || (dealer.puncte > 21))
            {
                cout<<"\n\nAi castigaaat !";
                player[p1].bani += pariu * 3 / 2;
            }
            else
                cout<<"\n\nAi pierdut >.< !";
        }

		cout<<"\n\n"<<player[p1].nume<<":";
		for (i = 0; i < jucator.dimensiune; i++)
		{
            cout<<"# "<<jucator.carte[i].nume<<" #\n";
		}

        cout<<"\n\nDoriti sa mai jucati?\n";
        cout<<"1)Da\n";
        cout<<"2)Nu\n";


        char p;
        bool cont = false, oka = false;
        while(!oka)
        {
            p = cin.get();
            if(p == '2')
            {
                oka = true;
            }
            else if(p == '1')
            {
                oka = true;
                cont = true;
            }
        }
        if(!cont)
            break;
		//system("cls");
	} while(1);
}




int main()
{
    while(1)
    {
        cout<<"\n\nBLACKJACK\n\n";
        cout<<"1)Joaca cu Computer\n";
        cout<<"2)Joaca cu alt jucator\n";
        cout<<"3)Adauga Jucator\n";
     //   cout<<"4)Editeaza Jucator\n";
     //   cout<<"5)Date despre jucator\n";

        char c = cin.get();
        cin.get();

        if(c == '1')
        {
            char d;
            while(1)
            {
                system("cls");
                for(int i=0; i<10; i++)
                {
                    if(player[i].nume[0] == '\0')
                        cout<<i+1<<") <jucator nou>";
                    else
                        cout<<i+1<<") "<<player[i].nume;
                    cout<<'\n';
                }

                cout<<"\n\nAlege un jucator: ";
                cin>>d;
                cin.get();

                if(d >= '1' && d<= '10')
                    break;
            }

            if(player[d-'0'].nume[0] == '\0')
            {
                jucatorNou(d-'0');
            }

            StartBlackjack(true, d-'0');
        }
        else if(c == '2')
        {
            char d, e;
            while(1)
            {
                system("cls");
                for(int i=0; i<10; i++)
                {
                    if(player[i].nume[0] == '\0')
                        cout<<i+1<<") <jucator nou>";
                    else
                        cout<<i+1<<") "<<player[i].nume;
                    cout<<'\n';
                }

                cout<<"\n\nAlege un jucator: ";
                cin>>d;
                cin.get();

                if(d >= '1' && d<= '10')
                    break;
            }
            while(1)
            {
                system("cls");
                for(int i=0; i<10; i++)
                {
                    if(player[i].nume[0] == '\0')
                        cout<<i+1<<") <jucator nou>";
                    else
                        cout<<i+1<<") "<<player[i].nume;
                    cout<<'\n';
                }

                cout<<"\n\nAlege un jucator: ";
                cin>>e;
                cin.get();

                if(e >= '1' && e<= '10' && e != d)
                    break;
            }

            if(player[d-'0'].nume[0] == '\0')
            {
                jucatorNou(d-'0');
            }
            if(player[e-'0'].nume[0] == '\0')
            {
                jucatorNou(e-'0');
            }

            StartBlackjack(true, d-'0', e-'0');
        }
        else if(c == '3')
        {
            char d;
            while(1)
            {
                system("cls");
                for(int i=0; i<10; i++)
                {
                    if(player[i].nume[0] == '\0')
                        cout<<i+1<<") <jucator nou>";
                    else
                        cout<<i+1<<") "<<player[i].nume;
                    cout<<'\n';
                }

                cout<<"\n\nAlege un jucator: ";
                cin>>d;
                cin.get();

                if(d >= '1' && d<= '10')
                    break;
            }
            jucatorNou(d-'0');
        }
        else if(c == '4')
        {
            system("cls");
            char d;
            while(1)
            {
                for(int i=0; i<10; i++)
                {
                    if(player[i].nume[0] == '\0')
                        cout<<i+1<<") <jucator nou>";
                    else
                        cout<<i+1<<") "<<player[i].nume;
                    cout<<'\n';
                }

                cout<<"\n\nAlege un jucator: ";
                cin>>d;
                cin.get();

                if(d >= '1' && d<= '10')
                    break;
            }
            editeazaJucator(d-'0');
        }
        else if(c == '5')
        {
            char d;
            while(1)
            {
                system("cls");
                for(int i=0; i<10; i++)
                {
                    if(player[i].nume[0] == '\0')
                        cout<<i+1<<") <jucator nou>";
                    else
                        cout<<i+1<<") "<<player[i].nume;
                    cout<<'\n';
                }

                cout<<"\n\nAlege un jucator: ";
                cin>>d;
                cin.get();

                if(d >= '1' && d<= '10')
                    break;
            }

            afiseaza_despre_jucator(d-'0');
        }
    }
}
