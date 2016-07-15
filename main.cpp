#include <algorithm>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <cctype>

using namespace std;
int    global_prize;
int    g=1,t_end=0;
int    c = 0;
int    allready_got=0;            /**< pomocnicza do sprawdzania powtazalnosci */  //   zmienne
const int    pot=30, q=8,r=3;      /** nagrody, pytania, rundy */                  //   stale**
int    k,l,m;                       /**< pomocnicze zmienne: k do wailów l token tury  */                      //   zmienne
int    active_t=0;                 /**< ktora tura  */                             //   zmienne
string checkpassword;                                                              //   zmienne
int    how_meny=0;           /**<jak wielu graczy podawane 2 pkt 2 menu  */        //   zmienne
void   player_one_turn (string, string&, int, string);                             //funkcje
void   player_two_turn (string, string&, int, string);                             //funkcje
int    prize_weel();                                                           //funkcje
void   rulles ();                                                          //funkcje
void   w_wintable();                                                         //funkcje
void   make_players();                                                     //funkcje
void   abut();                                             //tablica ile gracy
int    chek_questions();
void   two_players_game(string, string, string, string);                                                   //funkcje

struct player {
string   name;
int    money;
char   color;
}player_one,player_two;

int main()
{
    string passowrd;
    string codedpassword;
    string random;
    string kategory;
    int    nr_password[r+1]={0};
    int    password_length=0;
    do
    {
        srand (time (NULL));
        system ("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tWitaj w Kole Fortuny\n\n";
        cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tLoading ";
        Sleep(250);
        cout << " R";
        Sleep(250);
        cout << "E";
        Sleep(250);
        cout << "A";
        Sleep(250);
        cout << "D";
        Sleep(250);
        cout << "Y";
        Sleep (500);
        system ("cls");
        cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl
             << "\t\t\t\t**\t\t      MENU\t\t\t**"<<endl
             << "\t\t\t\t**==============================================**"<<endl
             << "\t\t\t\t**\t1. Zalozenia projektu\t\t\t**"<<endl
             << "\t\t\t\t**\t2. Rozpocznij gre na 2-ch graczy   \t**"<<endl
             << "\t\t\t\t**\t3. Ranking\t\t\t\t**"<<endl
             << "\t\t\t\t**\t4. Poznaj zasady\t\t\t**"<<endl
             << "\t\t\t\t**\t5. WYJSCIE\t\t\t\t**"<<endl
             << "\t\t\t\t**************************************************"<<endl
             << "\t\t\t\t>>";
        int menu=0;
            while(!(cin>>menu)||menu>5)
            {
                cin.clear();
                cin.ignore();
                cout <<endl<< "\n\t\tLipa podales zla wartosc";
                cout <<endl<< "\n\t\tPodaj jeszcze raz:";
            }
        switch(menu)
        {
        case 1:
            {
                abut();
                break;
            }


        case 2:
            {
            make_players();
            system("cls");

            for (int i=1; i<=r; i++)
             {  ifstream file ("questions.txt");
                nr_password[i] = (rand() % q+1);
                nr_password[0] = nr_password[i];

                if (i>1)
                for(k=1;k<i;k++)    //sprawdzenie powtarzalnosci hasla (poprzed przeniesienie nowo wylosowangeo hasla do zmiennej j w petli i wielokrotne porównywanie z poprzednimi pytaniami.
                    {
                     if  (nr_password[i]==nr_password[k])
                          {
                            do
                            {
                             nr_password[i] = (rand() % q )+ 1;
                             nr_password[0] = nr_password[i];
                            }while(nr_password[k]==nr_password[0]);
                            k=0;
                          }
                         k++;
                    }


				for (int j = 1; j < nr_password[i]; j++)
				{
					getline(file, random);
				}

				kategory.clear();
				passowrd.clear();
				file >> kategory;																					//wczytanie	hasla i kategori do osobnych zmiennych
				getline(file, passowrd);
				passowrd.erase(0, 1);
				file.close();
				codedpassword.clear();
				codedpassword = passowrd;
				password_length =passowrd.size();


                for (int j=0;j <= password_length;j++)																	//podmiana hasla na kropki <<<<<tutaj skoñczy³em
                {

                    if (codedpassword[j] == '-')
                        codedpassword[j] =  ' ';
                    else
                        codedpassword[j] =  '_';
                }
                for (int j = 0; j <=password_length; j++)
				{

					if (passowrd[j] == '-')
						passowrd[j] =  ' ';
				}
				system("cls");

                do
                {   if (g == i)
                    {cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\t\t==================================="
                         <<"\n\t\t\t\t\t|Rozpoczynamy  "<< i <<"  runde !!        |\t\t\t\t"
                         <<"\n\t\t\t\t\t===================================";
                    Sleep(3000);
                    g++; /**a to wskazuje która mamy runde  */
                    }
                    if (l == 0)
                    {
                        player_one_turn(passowrd, codedpassword, password_length, kategory);

                        if (passowrd == codedpassword)
                            {//t_end=1;
                            break;}
                    }
                    if (l == 1)
                    {
                        player_two_turn(passowrd, codedpassword, password_length, kategory);

                        if (passowrd == codedpassword)
                            {//t_end=1;
                            break;}
                    }

                } while (passowrd != codedpassword);
                t_end=0;
                }
            system("cls");
            if (player_one.money > player_two.money)
            {
                system("cls");
                cout <<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tKoniec gry!!!" << endl;
                Sleep(2000);
                system("cls");
                cout <<"\n\n\n\n\n\n\n\n\n\t\t\t\t\tWygrana nalezy do " << player_one.name
                     << "\n\t\t\t\t\tWygrales: " << player_one.money<< " zl "
                     << "\n\t\t\t\t\tGratulacje!";
            }
            else
                if (player_one.money < player_two.money)
                {
                    system("cls");
                    cout <<"\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tKoniec gry!!!" << endl;
                    Sleep(2000);
                    system("cls");
                    cout <<"\n\n\n\n\n\n\n\n\n\t\t\t\t\tWygrywa nalezy do " << player_two.name
                         <<"\n\t\t\t\t\tWygrales: "<< player_two.money << "zl"
                         <<"\n\t\t\t\t\tGratulacje!";
                }
                else
                    if (player_one.money == player_two.money)
                        cout <<"\n\n\n\n\n\n\n\n\n\t\t\t\t\tNiewiarygodne !!! To przeciez"
                             <<"\n\t\t\t\t\t>>>>>REMIS!!!<<<<<"
                             <<"\n\t\t\t\t\tWasz wynik to : "<< player_one.money<< endl;
            cout << "\n\n\n\t\t\t\t\t\t\t\tWczytuje ranking ogolny...";
            Sleep(5000);

            fstream  wintable;
            wintable.open("wintable.txt",ios::out | ios::app);
            wintable << player_one.money << " "<< player_one.name  << endl;
            wintable << player_two.money << " "<< player_two.name <<  endl;
            wintable.close();

            w_wintable();
            getchar();
            getchar();
            g=1;
                break;}
        case 3:
                {w_wintable();
                break;}
        case 4:
                {rulles();
                break;}
        case 5:
                exit(0);
        }
      }while (true);


 return 0;
}           /**< tu skonczylem */


int prize_weel()
	{
	    system("cls");
		int prize_nr = 0;
		int prize = 0;
		cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tNacisnij ENTER aby zakrecic kolem...";
		cin.get();
		ifstream fprize("prize.txt");
		prize_nr = (rand() % pot) + 1;
		for (int i = 1; i < prize_nr; i++)
		{
			fprize >> prize;
		}
		fprize.close();
		if (prize == 0)
            {
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tBANKRUT! Utrata kolejki" << endl;
                getchar();
            }
		global_prize=prize;
		system("cls");
		return prize;
    }
void make_players()
{
	system("cls");
    cin.get();
    for (int i=1;i<=2;i++)
    {
        if (i==1)
        {
         system("cls");
         cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl
             << "\t\t\t\t\tPodaj imie gracz nr "<<i<< " : ";																//wczytywanie graczy
         getline(cin,player_one.name);
        }
        else if (i==2)
        {
         system("cls");
         cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl
             << "\t\t\t\t\tpodaj imie " << i << " gracza : ";
         getline(cin,player_two.name);
        }
    }
    cout <<endl<<endl<<endl<< "\t\t\tGracz nr 1 : "<<player_one.name
         << "\t\t\t\tGracz nr 2 : "<<player_two.name<<endl;
	Sleep(2200);
	system("cls");
}
void rulles()
{
 	system("cls");
 	cout << "______________________________________________________________________________________________________"<<endl<<
            " \t\t|* Jest to konsolowa adaptacja znanego programu kolo fortuny "<<endl<<
            " \t\t|* Aby rozpoczac gre na jednego gracza w MENU wcisnij 1 "<<endl<<
            " \t\t|* W przypadku gry na 2 graczy w MENU wcisnij 2 "<<endl<<
            " \t\t|* Skrot gry ~~ Krecisz kolem>>losujac narogde>>dostajesz pytanie>>zarabiasz zl :)"<<endl<<
            " \t\t|* Gracz z wieksza iloscia zl wygrywa rozgrywke"<<endl<<
            " \t\t|* Jesli zdobędziesz wystarczajaca ilosc zl zostaniesz zapisany w tabeli zwyciezcow"<<endl<<
            " \t\t|* Aby podac haslo w calosci nalezy zamiast litery wpisac 0 (zero)."<<endl<<
            " \t\t|* Spolgloski zgadujesz , a samogloski mozesz kupic."<<endl<<
	        " \t\t|* Samogloski kosztuja 50."<<endl<<
	        " \t\t|* W przypadku gdy zarzadasz kupno samogloski a nie masz wystaraczajaco duzo zl "<<endl<<
	        " \t\t|* utracisz kolejke!."<<endl<<
	        " \t\t|* Bonus przy podawania hasla w calosci to 10 za kazdy odgadniety znak"<<endl<<
	        " \t\t|* nagroda wylosowana na kole przyznawana jest za karzda odgadnieta literke."<<endl<<
	        " \t\t|* Miłego bicia rekordow !!! :) " <<endl<<
	        "_______________________________________________________________________________________________________"<<endl<<endl<<endl<<endl<<
	        " \t\t\t\tAby wrocic do MENU nacisnij Jakis klawisz"<<endl;


	cin.get();
	cin.get();
}
void w_wintable()
{
    struct player
    {
      string name;
      int money;
    }p;
	string test;
	int s = 0;

	fstream ran;
	ran.open("wintable.txt",ios::in);
	if(ran.good()==false)
    {
        system("cls");
        cout << "\n\n\n\n\t\tplik wintable.txt nie istnieje, zamknięcie z błedem krytycznym";
        Sleep(2500);
        exit(0);
    }
	while (!ran.eof())
	{
		getline(ran, test);
		s++;
	}
	ran.close();
//
	player* tab = new player[s+1];

	ifstream ranking("wintable.txt");
	for (int i = 0; i < s; i++)             //
	{
		ranking >> tab[i].money;
		getline(ranking, tab[i].name);
	}
    ranking.close();
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s -2; j++)
		{
			if (tab[j].money < tab[j + 1].money)
				{ p=tab[j];
                  tab[j]= tab[j + 1];
                  tab[j+1] = p;}
		}
	}
	system("cls");
	cout <<endl<<endl<<endl<<endl<<endl
         << "\t\t\t\tW pierwszej 10 sklasyfikowali sie !!!"<<endl
         << "\t\t\t________________________________________________________"<<endl;
    s=10;
	for (int i = 0; i < s; i++)
		cout <<"\t\t\t\t\t"<< i + 1 << "." << tab[i].name << " " << tab[i].money << endl;
    cout << "\t\t\t________________________________________________________"<<endl;
    cout << "\t\t\t\t\tGratulacje!!! "<<endl;
	delete [] tab;
	cout <<endl<<endl<< "\t\t\t\tAby powrocic do meny nacisnij ENTER... ";
	cin.sync();
	cin.clear();
	cin.get();
}
void player_one_turn(string pass, string& cpass,int p_l,string kat)
	{
	    string samo="aeiouy";
	    int samo1=5;
		char letter;
		int  to_win, sam=0;
		bool w = 1;

		while (w!=0)
		{
			to_win = prize_weel();
			if (to_win == 0)
				{
					player_one.money = 0;
					l = 1;
					break;
				}
			w = 0;
			system("cls");
			cout<<endl<<endl
                <<      "\t+|========================================================================================="
                <<endl<<"\t+|"<<" Gracz 1 :"<< player_one.name<<"\t||\t stan konta : "<<player_one.money
			    <<endl<<"\t+|========================================================================================="
                <<endl<<"\t+|"<<" runda: >> "<<g-1  << " << "
                <<endl<<"\t+|"<<" Wykreciles sznse na zobycie " << global_prize << "."
                <<endl<<"\t+|-----------------------------------------------------------------------------------------"
                <<endl<<"\t+|"<<"\t\t\t\t"<< kat<<"\t\t " << cpass << "\t\t\t"
                <<endl<<"\t+|"
                <<endl<<"\t+|"<<" podaj co typujesz ?. jesli chcesz wprowadzic cale haslo wpisz '0'<<zero."
                <<endl<<"\t==========================================================================================="
                <<endl<<"\t___________"
                <<endl<<"\t Twoj typ |: ";
            cin.sync();
			cin.clear();
			cin >>  letter;
			cout << endl;
			cin.sync();
			cin.clear();
		//	cin.get();
			if (letter == 'a' || letter == 'e' || letter == 'y' || letter == 'u' || letter == 'i' || letter == 'o')
			{
				if (player_one.money < 50)
				{
					cout <<endl<< "\t\tZbyt malo zl by podac samogloske. Tracisz kolejke." << endl<<"\t\t\t\t\tNacisnij ENTER by kontynulowac...";
                    cin.sync();
                    getchar();
					l = 1;
					break;
				}
				cout <<endl<< "\t\tKupujesz samogloske "<<letter << " . Koszt 50 zl" << endl<<endl<<"\t\t\t\t\tNacisnij ENTER by kontynulowac" ;
				player_one.money -= 50;
				cin.sync();
				getchar();
			}
			else if (letter == '0')
			{
				cout <<endl<< "\t\tPróba odgadniecia calego hasla!! : ";
				Sleep(2000);
				getline(cin, checkpassword);
				c=0;
				if (checkpassword == pass)
				{
					cout <<endl<< "\t\tNiewiarygodne !? Poprawnie !!";
					cpass = pass;
                        for (int i = 0; i <= p_l; i++)         // sprawdzanie który zpodanych znakow jest literka by podliczyć zl
                        {
						if (isalpha(pass[i]))
							c++;
                        }
					player_one.money += (c * 100)+to_win;
					cout <<endl<< "\t\tHurra !! do twojego konta zostaje dodane "<<c*100+to_win<<" zl"<<endl;
					cout <<endl<< "\t\t\t\t\tNacisnij klawisz by kontynulowac";
					cin.sync();
					getchar();
                    w=1;
                    m=w;
					break;
				}
				else
				{
					cout <<endl<< "\t\tNiestety bledne haslo :( tracisz kolejke" <<endl<<endl<<"\t\t\t\t\tNaciśnij ENTER by kontynulowac" << endl;
					cin.sync();
					getchar();
					l = 1;
					break;
				}
			}
		for(int j=0;j<samo1;j++)
        {if (letter ==samo[j])
            {for(int i = 0 ; i <= p_l ; i++)
               {if (cpass[i]==letter)
                {
                    cout <<endl<< "\t\tKtos tu sie stara oszukiwac! za kare tracisz kolejke !!!";
                    Sleep(2000);
                    system("cls");
                    cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<< "\t\t\t\t\tKara!!"<<endl;
                    Sleep(1000);
                    cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<< "\t\t\t\t\tNacisnij ENTER by kontynulowac ";
                    getchar();
                    l=1;
                    w=0;
                    break;
                }

                else if (pass[i] == letter)
                {
                    cpass[i] = letter;
                    sam=1;
                    if(pass==cpass)
                    {
                      cout<<endl<<"\t\tHaslo odgadniete! :) " <<endl <<"\t\tCzas na ture przeciwnika";
                      l=1;
                      w=0;
                      cin.sync();
                      getchar();
                      break;
                    }
                }
               }
            }}
            if (sam==1)
                {
                    player_one.money += to_win;
                    cout <<endl<< "\t\tBRAWO! samogloska trafiona. Do twojego konta zostanie dodane: "<< to_win << "\n\n\t\t\t\t\tNacisnij ENTER aby kontynulowac";
                    cin.sync();
                    sam=0;
                    getchar();
                    w=1;
                    m=w;
                }

        else{
			for (int i = 0; i <= p_l; i++)
				{
                    if (cpass[i]==letter)
                    {
                        cout <<endl<< "\t\tKtos tu sie stara oszukiwac! za kare tracisz kolejke !!!";
                        Sleep(2000);
                        system("cls");
                        cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<< "\t\t\t\t\tKara!!"<<endl;
                        Sleep(1000);
                        cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<< "\t\t\t\t\tNacisnij ENTER by kontynulowac ";
                        getchar();
                        l=1;
                        w=0;
                        m=w;
                        break;
                    }
                    else if (pass[i] == letter)
					{
						cpass[i] = letter;
						w = 1;
						player_one.money += to_win;
						cout <<endl<< "\t\tBRAWO! "<<i+1<< " litera trafiona. Do twojego konta zostanie dodane: "<< to_win << "\n"
                             <<endl<< "\t\t\t\t\tNacisnij ENTER by kontynulowac ";
						if(pass==cpass)
                        {
                            cout<<endl<<"\t\tHaslo odgadniete! :) " <<endl <<"\t\tCzas na ture przeciwnika";
                            l=1;
                            w=0;
                            m=w;
                            break;
                        }
                        cin.sync();
                        getchar();
					}
				}
            }
	//		cout << "\t\t\t" << kat<<"  " << cpass << "\n\n";
            if(pass==cpass)
            {
                cout<<endl<<"\t\tHaslo odgadniete! :) " <<endl <<"\t\tczas na ture przeciwnika...  Naciśnij ENTER by kontynulowac... ";
                cin.sync();
                getchar();
                l=1;
                w=1;
                m=w;
                break;
            }
			if (w == 0)
			{
				cout <<endl<< "\t\tNiestety :( proba nie udana tracisz kolejke, nacisnij ENTER by kontynulowac " << endl;
				cin.sync();
				getchar();
				system("cls");
				l = 1;
				break;
			}
			else if (cpass == pass)
                    {w = 1;
                        break;}

		}
	}
void player_two_turn(string pass, string& cpass,int p_l,string kat)
	{
		char letter;
		int  to_win,sam=0;
		bool w = 1;

        while (w!=0)
		{
			to_win = prize_weel();
			if (to_win == 0)
				{
					player_one.money = 0;
					l = 0;
					break;
				}
			w = 0;
			cout<<endl<<endl
			    <<      "\t+|========================================================================================="
                <<endl<<"\t+|"<<" Gracz 2 :"<< player_two.name<<"\t||\t stan konta : "<<player_two.money
                <<endl<<"\t+|========================================================================================="
                <<endl<<"\t+|"<<" runda: >> "<<g-1 << " << "
                <<endl<<"\t+|"<<" Wykreciles sznse na zobycie " << global_prize << "."
                <<endl<<"\t+|-----------------------------------------------------------------------------------------"
                <<endl<<"\t+|"<<"\t\t\t\t"<< kat<<"\t\t " << cpass
                <<endl<<"\t+|"
                <<endl<<"\t+|"<<" podaj co typujesz ?. jesli chcesz wprowadzic cale haslo wpisz '0'<<zero."
                <<endl<<"\t==========================================================================================="
                <<endl<<"\t___________"
                <<endl<<"\t Twoj typ |: ";
            cin.sync();
			cin.clear();
			cin  >>  letter;
			cout << endl;
			cin.sync();
			cin.clear();
		//	cin.get();
			if (letter == 'a'||letter == 'A' || letter == 'e'||letter == 'E' || letter == 'y'||letter == 'Y'|| letter == 'u'||letter == 'U' || letter == 'i'||letter == 'I' || letter == 'o'||letter == 'O')
			{
				if (player_two.money < 50)
				{
					cout << "\t\tZbyt malo zl by podac samogloske. Tracisz kolejke." << endl<<"\t\t\t\t\tNacisnij ENTER by kontynulowac...";
                    cin.sync();
                    getchar();
					l = 0;
					break;
				}
				cout <<endl<< "\t\tkupujesz samogloske "<<letter << " . Koszt 50 zl" << endl<<endl<<"\t\t\t\t\tnacisnij ENTER by kontynulowac" ;
				player_two.money -= 50;
				cin.sync();
				getchar();

			}
			else if (letter == '0')
			{
				cout <<endl<< "\t\tPróba odgadniecia calego hasla!! : " << endl;
				Sleep(2000);
				getline(cin, checkpassword);
				c=0;
				if (checkpassword == pass)
				{
					cout <<endl<< "\t\tNiewiarygodne !? Poprawnie !!" << endl;
					cpass = pass;
                        for (int i = 0; i <= p_l; i++)         // sprawdzanie który zpodanych znakow jest literka by podliczyć zl
                        {
						if (isalpha(pass[i]))
							c++;
                        }
					player_two.money += (c * 100)+to_win;
					cout <<endl<< "\t\tHurra !! do twojego konta zostaje dodane "<<c*100+to_win<<" zl"<<endl<<endl;
					cout <<       "\t\tNacisnij ENTER by kontynulowac";
					cin.sync();
					getchar();
                    w=1;
					break;
				}
				else
				{
					cout <<endl<< "\t\tNiestety bledne haslo :( tracisz kolejke" <<endl<<endl<<"\t\t\t\t\tnaciśnij ENTER by kontynulowac" << endl;
					cin.sync();
					getchar();
					l = 0;
					break;
				}
			}
        if(letter == 'a'||letter == 'A' || letter == 'e'||letter == 'E' || letter == 'y'||letter == 'Y'|| letter == 'u'||letter == 'U' || letter == 'i'||letter == 'I' || letter == 'o'||letter == 'O')
            {for(int i = 0 ; i <= p_l ; i++)
               {if (cpass[i]==letter)
                {
                    cout <<endl<< "\t\tKtos tu sie stara oszukiwac! za kare tracisz kolejke !!!";
                    Sleep(2000);
                    system("cls");
                    cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<< "\t\t\t\t\tKara!!";
                    Sleep(1000);
                    cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"\t\t\t\tnacisnij ENTER by kontynulowac ";
                    getchar();
                    l=0;
                    w=0;
                    break;
                }

                else if (pass[i] == letter)
                {
                    cpass[i] = letter;
                    sam=1;
                    if(pass==cpass)
                       {
                         cout<<endl<<"\t\tHaslo odgadniete! :) " <<endl <<"\t\tCzas na ture przeciwnika";
                         l=1;
                         w=0;
                         cin.sync();
                         getchar();
                         break;
                       }
                }
               }
            }
            if (sam==1)
                {
                    player_two.money += to_win;
                    cout <<endl<< "\t\tBRAWO! samogloska trafiona. Do twojego konta zostanie dodane: "<< to_win << "\n\n";
                    cin.sync();
                    sam=0;
                    getchar();
                    w=1;
                }
        else
            {
            for (int i = 0; i <= p_l; i++)
                {
                    if (cpass[i]==letter)
                    {
                        cout <<endl<< "\t\tKtos tu sie stara oszukiwac! za kare tracisz kolejke !!!";
                        Sleep(2000);
                        system("cls");
                        cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<< "\t\t\t\t\tKara!!";
                        Sleep(1000);
                        cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<< "\t\t\t\t\tNacisnij ENTER by kontynulowac ";
                        cin.sync();
                        cin.ignore();
                        getchar();
                        l=0;
                        w=0;
                        break;
                    }

					else if (pass[i] == letter)
					{
						cpass[i] = letter;
						w = 1;
						player_two.money += to_win;
						cout <<endl<< "\t\tBRAWO! "<<i<< " litera trafiona. Do twojego konta zostanie dodane: "<< to_win << "\n"
						     <<endl<< "\t\t\t\t\tNacisnij ENTER by kontynulowac ";
                        if(pass==cpass)
                            {
                                cout<<endl<<"\t\tHaslo odgadniete! :) " <<endl <<"\t\tczas na ture przeciwnika";
                                l=1;
                                w=0;
                                break;
                            }
                        cin.sync();
                        getchar();
					}
				}
            }
    //        cout << "\t\t\t" << kat<<"  " << cpass << "\n\n";
            if(pass==cpass)
            {
                cout<<endl<<"\t\tHaslo odgadniete! :) " <<endl <<"\t\tCzas na ture przeciwnika... Nacisnij ENTER by kontynulowac...";
                l=0;
                w=1;
                break;
            }
			if (w == 0)
			{
				cout <<endl<< "\t\tNiestety :( proba nie udana tracisz kolejke"<<endl<<endl<< "\t\t\t\t\tnacisnij ENTER by kontynulowac " << endl;
				cin.sync();
				getchar();
				system("cls");
				l = 0;
				w = 0;
				break;
			}
			if (cpass == pass)
				{w=1;
				break;}

		}
	}
void abut ()
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\t\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n"
             << "\t\t\t<>\t1. Gramy w kolo fortuny\t\t\t\t<>\n"
             << "\t\t\t<>\t2. Samogloski kupujemy\t\t\t\t<>\n"
             << "\t\t\t<>\t3. Spolgloski odgadujemy\t\t\t<>\n"
             << "\t\t\t<>\t4. Gracz podaje jedynie male litery\t\t<>\n"
             << "\t\t\t<>\t5. Program powinien byc 'ludzioodporny' \t<>\n"
             << "\t\t\t<>\t6. Gramy na 2-ch graczy\t\t\t\t<>\n"
             << "\t\t\t<>\t7. Wykorzystaj zapis i odczyt z pliku txt\t<>\n"
             << "\t\t\t<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>";
             cin.get();
             cin.get();
    }
