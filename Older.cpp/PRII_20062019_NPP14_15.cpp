#include<iostream>
using namespace std;
/*
1. BROJ I VRSTA PARAMETARA MORAJU BITI IDENTICNI KAO U PRIMJERIMA. U SUPROTNOM SE RAD NECE BODOVATI
2. STAVITE KOMENTAR NA DIJELOVE CODE-A KOJE NE BUDETE IMPLEMENTIRALI
3. KREIRAJTE .DOC FAJL SA VAŠIM BROJEM INDEKSA ( NPR. IB180081.DOC BEZ IMENA I PREZIMENA), TE NA KRAJU ISPITA U NJEGA KOPIRAJTE RJEŠENJA VAŠIH ZADATAKA. NE PREDAVATI .TXT ILI .CPP FAJLOVE
4. TOKOM IZRADE ISPITA NIJE DOZVOLJENO KORIŠTENJE HELP-A
5. TOKOM IZRADE ISPITA MOGU BITI POKRENUTA SAMO TRI PROGRAMA: PDF READER (ISPITNI ZADACI), MS VISUAL STUDIO, MS WORD (U KOJI CETE KOPIRATI VAŠA RJEŠENJA)
6. BEZ OBZIRA NA TO DA LI SU ISPITNI ZADACI URAĐENI, SVI STUDENTI KOJI SU PRISTUPILI ISPITU MORAJU PREDATI SVOJ RAD
*/

enum VrstaAktivnosti { Tehnike, Kata, Borba };
enum Pojas { Zuti, Narandzasti, Zeleni, Plavi, Smedji, Crni };
const int MAX_POKUSAJA = 10;

char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr) return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}
struct Datum {
	int * _dan, *_mjesec, *_godina;
	void Unos(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}
	void Ispis() { cout << *_dan << "/" << *_mjesec << "/" << *_godina << endl; }
	void Dealociraj() { delete  _dan; delete  _mjesec; delete _godina; }
};
struct Aktivnost {
	shared_ptr<VrstaAktivnosti> _vrsta;
	Datum _datumIzvrsenja;
	char * _nazivOpis;
	int _ocjena; // 1 - 10 
	void Unos(VrstaAktivnosti vrsta, Datum * datum, int ocjena, const char * nazivOpis) {
		_vrsta = make_shared<VrstaAktivnosti>(vrsta);
		_datumIzvrsenja.Unos(*datum->_dan, *datum->_mjesec, *datum->_godina);
		_ocjena = ocjena;
		_nazivOpis = AlocirajNizKaraktera(nazivOpis);
	}
	void Ispis() {
		cout << *_vrsta << " " << _ocjena << " " << _nazivOpis;
		_datumIzvrsenja.Ispis();
		cout << endl;
	}
	void Dealociraj() {
		_datumIzvrsenja.Dealociraj();
		delete[] _nazivOpis; _nazivOpis = nullptr;
	}
};
struct KaratePojas {
	Datum * _datumPolaganja;//datum koji ce se evidentirati kao datum polaganja pojasa tj. kada su ispunjene sve aktivnosti/obaveze
	Pojas * _pojas;
	//u slucaju da kandidat uspjesno polozi aktivnosti zahtijevane odredjenim pojas, vrijednost atributa _polozen ce se postaviti na true
	bool _polozen;
	Aktivnost * _listaIzvrsenihAktivnosti;
	int _trenutnoIzvrsenihAktivnosti;
	void Unos(Pojas pojas) {
		_listaIzvrsenihAktivnosti = nullptr;
		_trenutnoIzvrsenihAktivnosti = 0;
		_datumPolaganja = nullptr;
		_pojas = new Pojas(pojas);
		_polozen = false;
	}
	void Dealociraj() {
		_datumPolaganja->Dealociraj();
		for (size_t i = 0; i < _trenutnoIzvrsenihAktivnosti; i++)
			_listaIzvrsenihAktivnosti[i].Dealociraj();
		delete[] _listaIzvrsenihAktivnosti; _listaIzvrsenihAktivnosti = nullptr;
		delete _pojas; _pojas = nullptr;
	}
};

struct Kandidat {
	char * _imePrezime;
	//od ukupno 6 karate pojaseva, kandidat ima pravo na 10 pologanja. ukoliko u okviru pomenutog broja polaganja kandidat ne stekne crni pojas, ostaje na posljednje uspjesno osvojenom pojasu
	KaratePojas * _pojasevi[MAX_POKUSAJA] = { nullptr };
	char * _napomena[MAX_POKUSAJA] = { nullptr };//za svaki (ne)polozeni pojas se mora napraviti odgovarajuca napomena

	void Unos(const char * imePrezime) {
		_imePrezime = AlocirajNizKaraktera(imePrezime);
	}
	void Dealociraj() {
		delete[] _imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < MAX_POKUSAJA; i++)
			if (_pojasevi[i] != nullptr) {
				_pojasevi[i]->Dealociraj();
				delete _pojasevi[i];
				delete[] _napomena[i];
			}
	}
	void Ispis() {
		cout << _imePrezime << endl;
		for (size_t i = 0; i < MAX_POKUSAJA; i++)
			if (_pojasevi[i] != nullptr) {
				_pojasevi[i]->Ispis();
				cout << _napomena[i] << endl;
			}
	}
};

int main() {

	//BROJ I VRSTA PARAMETARA MORAJU BITI IDENTICNI KAO U PRIMJERIMA. ZA TESTIRANJE MOZETE POVECATI BROJ POZIVA POJEDINIH FUNKCIJA, TE KORISTITI DRUGE VRIJEDNOSTI PARAMETARA
	//STAVITE KOMENTAR NA DIJELOVE CODE-A KOJE NE BUDETE IMPLEMENTIRALI
	Datum datumPolaganja1, datumPolaganja2, datumPolaganja3, datumPolaganja4;
	datumPolaganja1.Unos(10, 6, 2019);
	datumPolaganja2.Unos(18, 6, 2019);
	datumPolaganja3.Unos(22, 3, 2019);
	datumPolaganja4.Unos(22, 7, 2019);

	Aktivnost aktivnost1, aktivnost2, aktivnost3, aktivnost4, aktivnost5;
	aktivnost1.Unos(Tehnike, &datumPolaganja1, 6, "Tehnike za zuti pojas");
	aktivnost2.Unos(Kata, &datumPolaganja1, 8, "Taiki joko shodan - zuti pojas");
	aktivnost3.Unos(Borba, &datumPolaganja1, 2, "Jednostavne borbene tehnike sa partnerom");
	aktivnost4.Unos(Borba, &datumPolaganja1, 6, "Jednostavne borbene tehnike sa partnerom");
	aktivnost5.Unos(Borba, &datumPolaganja4, 6, "Jednostavne borbene tehnike sa partnerom");

	KaratePojas pojasZuti, pojasNarandzasti, pojasZeleni;
	pojasZuti.Unos(Zuti);
	pojasNarandzasti.Unos(Narandzasti);
	pojasZeleni.Unos(Zeleni);


	/*Na osnovu vrijednosti primljenog parametra osigurati dodavanje novoizvrsene aktivnosti za potrebe stjecanja odredjenog pojasa.
	Identicna aktivnost se moze dodati jedino u slucaju kada je prethodna (identivna aktivnost po vrsti) imala ocjenu manju od 6.
	Uspjesnom aktivnoscu se smatraju one aktivnosti koje imaju ocjenu vecu od 5, a svaka naredna identicna aktivnost, bez obzira da li je uspjesna ili ne,
	moze biti dodana jedino ako je proslo najmanje 10 dana od izvrsenja prethodne. Onemoguciti dodavanje aktivnosti uspjesno polozenom pojasu.*/
	if (pojasZuti.DodajIzvrsenuAktivnost(&aktivnost1))
		cout << "Aktivnost uspjesno dodana!" << endl;
	if (pojasZuti.DodajIzvrsenuAktivnost(&aktivnost2))
		cout << "Aktivnost uspjesno dodana!" << endl;
	if (pojasZuti.DodajIzvrsenuAktivnost(&aktivnost3))
		cout << "Aktivnost uspjesno dodana!" << endl;
	if (pojasZuti.DodajIzvrsenuAktivnost(&aktivnost4))//10 dana...
		cout << "Aktivnost uspjesno dodana!" << endl;
	if (pojasZuti.DodajIzvrsenuAktivnost(&aktivnost5))
		cout << "Aktivnost uspjesno dodana!" << endl;

	//koristeci neki od obradjenih algoritama, po ocjeni sortirati aktivnosti u okviru odredjenog pojasa
	pojasZuti.Sortiraj();

	/* Karate pojas zahtijeva uspjesnu realizaciju svih planiranih aktivnosti, a one se za jedan povecavaju sa svakim novim pojasom, npr.
	zuti pojas: 1 x tehnika, 1 x kata, 1 x borba;	narandzasti pojas: 2 x tehnika, 2 x kata, 2 x borba; i td...
	Funkcija vraca false u slucaju da nedostaje bilo koja od aktivnosti zahtijevanih u okviru tog pojasa.
	Ukoliko je kandidat uspjesno realizovao sve aktivnost, datum polaganja se postavlja na datum posljednje uspjesno
	realizovane aktivnosti i vrijednost*/
	if (pojasZuti.DaLiJePolozen())
		pojasZuti.Ispis();

	//ispisuje sve dostupne podatke o pojasu
	pojasZuti.Ispis();

	Kandidat jasmin;
	jasmin.Unos("Jasmin Azemovic");

	/*
	Karate pojasevi se moraju dodavati po redoslijedu tj. ne smije se dozvoliti dodavanje zelenog pojasa
	ukoliko prethodno nije dodan zuti i narandzasti. Za provjeru lokacije na koju ce se dodati novi karate pojas,
	te da li su nizi pojasevi prethodno dodani, koristiti lambda funkciju.
	*/
	if (jasmin.DodajPojas(pojasZuti, "izrazito dobra tehnika"))
		cout << "Pojas uspjesno dodan!" << endl;
	if (jasmin.DodajPojas(pojasZeleni, "poraditi na stavu prilikom izvodjena kate"))//prethodno je trebao biti dodan narandzasti pojas
		cout << "Pojas uspjesno dodan!" << endl;
	if (jasmin.DodajPojas(pojasNarandzasti, "kandidat pokazuje zrelost i znacajan napredak u odnosu na proslo polaganje. potrebno poraditi na kondiciji"))
		cout << "Pojas uspjesno dodan!" << endl;

	/*U fajl sa nazivom brojIndeksa.txt (npr.IB180081.txt) upisati podatke o kandidatu i svim njegovim aktivnostima prilikom stjecanja  pojasa (podatke upisati kao obicni tekst)
	koji je proslijedjen kao parametar. Nakon upisa, potrebno je ispisati sadrzaj fajla*/
	if (jasmin.SpasiUFajl("IB180081.txt", Zuti))
		cout << "Pojas uspjesno spase u fajl!" << endl;
	if (!jasmin.SpasiUFajl("IB180081.txt", Crni))//ukoliko pojas prethodno nije dodan kandidatu ili se javio problem pri radu sa fajlom, funkcija vraca false
		cout << "Pojas nije polozen ili se javio problem pri rad sa fajlom!" << endl;
	//Funkcija GetNajbolji vraca par koji sadrzi oznaku i prosjecnu ocjenu (uspjesno okoncanih aktivnosti) pojasa sa najvecim prosjekom
	pair<Pojas, float> par = jasmin.GetNajbolji();
	cout << "Najbolji rezultat od " << par.second << " je ostvaren tokom stjecanja pojasa " << par.first << endl;

	datumPolaganja1.Dealociraj(), datumPolaganja2.Dealociraj(), datumPolaganja3.Dealociraj(), datumPolaganja4.Dealociraj();
	aktivnost1.Dealociraj(), aktivnost2.Dealociraj(), aktivnost3.Dealociraj(), aktivnost4.Dealociraj(), aktivnost5.Dealociraj();
	pojasZuti.Dealociraj(), pojasNarandzasti.Dealociraj(), pojasZeleni.Dealociraj();
	jasmin.Dealociraj();

	system("pause>0");
	cin.get();
	return 0;
}

