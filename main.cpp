#include <vector>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class Tranzitie {
public:
	char c;
	int dest;
	friend istream& operator >>(istream&, Tranzitie&);
	friend ostream& operator <<(ostream&, Tranzitie&);
};

istream& operator>>(istream& in, Tranzitie& t)
{
	in >> t.c >> t.dest;
	return in;
}
ostream& operator<<(ostream& out, Tranzitie& t)
{
	out << "caracter: " << t.c << " destinatie: " << t.dest;
	return out;

}

class Stare {
public:
	int index;
	vector<Tranzitie> tranzitii;
	Stare(int id=0);
	friend istream& operator >>(istream&, Stare&);
	friend ostream& operator <<(ostream&, Stare&);

};
istream& operator>>(istream& in, Stare& s)
{
	int nr_tranz;
	cout << "introduceti nr de tranzitii: ";
	in >> nr_tranz;
	if(nr_tranz!=0)
		cout << "Introduceti caracter si starea destinatie" << endl;
	for (int i = 0; i < nr_tranz; i++)
	{
		Tranzitie t;
		in >> t;
		s.tranzitii.push_back(t);
	}
	return in;
}

ostream& operator<<(ostream& out, Stare& s)
{
	out << "q" << s.index << ":"<<endl;
	for (int i = 0; i < s.tranzitii.size(); i++)
		out << s.tranzitii[i] << endl;
	return out;
}


Stare::Stare(int id)
{
	index = id;
}

class Automat {
	int stare_init;
	vector<int> stari_fin;
	vector<Stare> stari;
	string alfabet;
public:
	Automat();
	int verificare(string);

	friend istream& operator >>(istream&, Automat&);
	friend ostream& operator <<(ostream&, Automat&);

};

Automat::Automat()
{
	stare_init = -1;
}

int Automat::verificare(string cuv)
{
	queue<pair<int, int>> coada;
	coada.push({ 0, stare_init });
	while (!coada.empty())
	{
		pair<int, int> poz_curenta;
		poz_curenta = coada.front();
		coada.pop();
		if (cuv.length() == poz_curenta.first && stari_fin[poz_curenta.second])
			return 1;
		for (Tranzitie t : stari[poz_curenta.second].tranzitii)
		{
			if (cuv[poz_curenta.first] == t.c)
			{
				coada.push({ poz_curenta.first+1, t.dest });
			}
		}
		
	}
	return 0;

}

istream& operator>>(istream& in, Automat& a)
{
	int nr_stari,k;
	in >> nr_stari; ///citesc nr de stari

	a.stari.resize(nr_stari);
	a.stari_fin.resize(nr_stari);
	for (int i = 0; i < nr_stari; i++)	//citere stari finale
	{	
		a.stari[i].index = i;
		in >> a.stari_fin[i];
	}

	in >> a.alfabet;

	in >> k;
	for (int i = 0; i < k; i++)
	{
		char c;
		int x, y;
		in >> c >> x >> y;
		Tranzitie t;
		t.c = c;
		t.dest = y;
		a.stari[x].tranzitii.push_back(t);
	}
	a.stare_init = 0;
	
	return in;
}



ostream& operator<<(ostream& out, Automat& a)
{
	if (a.stare_init == -1)
	{
		out << "Automatul nu e initializat.";
		return out;
	}
	out << "Stari: " << endl;
	for (Stare s : a.stari)
		out << s << endl;
	return out;
}






int main()
{
	int n;
	string cuvant;
	Automat a;
	ifstream in("afn.in");
	ofstream out("afn.out");
	in >> a;
	cout << a;
	in >> n;
	for (int i = 0; i < n; i++)
	{
		in >> cuvant;
		out << a.verificare(cuvant) << endl;
		
	}
	return 0;
}

