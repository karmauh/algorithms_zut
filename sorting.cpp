#include <iostream>
using namespace std;

void mieszaj(int* tab, int size, int index)
{
	if (index == 0)
	{
		return;
	}

	if (tab[(index - 1) / 2] < tab[index])
	{
		int cos = tab[index];
		tab[index] = tab[(index - 1) / 2];
		tab[(index - 1) / 2] = cos;
	}
	mieszaj(tab, size, (index - 1) / 2);
}

void dodaj(int* tablica, int value, int* size)
{
	*size = (*size) + 1;
	tablica[*size - 1] = value;
	mieszaj(tablica, *size, *size - 1);
}

void wyswietl(int* tab, int size)
{
	for (int i = 0, j = 1; i < size; i++)
	{
		cout << tab[i] << "  ";
		if (i == j - 1)
		{
			cout << endl;
			j = 2 * j + 1;
		}
	}
}

void napraw(int* tab, int wielkosc, int index)
{
	if (index > wielkosc - 1)
	{
		return;
	}

	if (2 * index + 2 > wielkosc - 1)
	{
		if (2 * index + 1 > wielkosc - 1)
		{
			return;
		}
		else
		{
			if (tab[2 * index + 1] >= tab[2 * index + 2]) {
				swap(tab[index], tab[2 * index + 1]);
				napraw(tab, wielkosc, 2 * index + 1);
			}
			return;
		}
	}

	if (tab[2 * index + 1] <= tab[2 * index + 2])
	{
		swap(tab[index], tab[2 * index + 2]);
		napraw(tab, wielkosc, 2 * index + 2);
	}
	else
	{
		swap(tab[index], tab[2 * index + 1]);
		napraw(tab, wielkosc, 2 * index + 1);
	}
}

void usunMax(int* tab, int* size)
{
	tab[0] = 0;
	napraw(tab, *size, 0);
	*size = (*size) - 1;
}

void czyszczenie(int* tab, int* size)
{
	for (int i = 0; i < *size; i++)
	{
		tab[i] = NULL;
	}
	*size = 0;
}

void sortPrzezKopcowanie(int* tab, int size)
{
	int psize = size;
	for (int i = size - 1; i >= 0; i--)
	{
		swap(tab[0], tab[size - 1]);
		size--;
		napraw(tab, size, 0);
	}
	size = psize;
	for (int i = 0; i < size; i++)
	{
		cout << ' ' << tab[i];
	}
}

void sortPrzezZliczanie(int* tab, int size, int tmp)
{
	int* counts = new int[tmp];
	for (int i = 0; i < tmp; i++)
	{
		counts[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		counts[tab[i]]++;
	}
	int k = 0;
	for (int i = 0; i < tmp; i++)
	{
		for (int j = 0; j < counts[i]; j++)
		{
			tab[k++] = i;
		}
	}
	int j = 0;
	delete[] counts;
	for (int i = 0; i < tmp; i++)
	{
		cout << ' ' << tab[i];
	}
}

void kopcowanieGora(int* tab, int index)
{
	cout << tab[index];
	if (index == 0)
	{
		return;
	}
	kopcowanieGora(tab, (index - 1) / 2);
}

void kopcowanieDol(int* tab, int size, int index)
{
	cout << tab[index];
	if (2 * index + 2 > size - 1)
	{
		if (2 * index + 1 > size - 1)
		{
			return;
		}
		kopcowanieDol(tab, size, 2 * index + 1);
		return;
	}
	kopcowanieDol(tab, size, 2 * index + 1);
	kopcowanieDol(tab, size, 2 * index + 2);
}

int main()
{
	int tablica[100];
	int size = 0;
	int* psize = &size;
	dodaj(tablica, 1, psize);
	dodaj(tablica, 2, psize);
	dodaj(tablica, 3, psize);
	dodaj(tablica, 4, psize);
	czyszczenie(tablica, psize);
	dodaj(tablica, 1, psize);
	dodaj(tablica, 2, psize);
	dodaj(tablica, 3, psize);
	dodaj(tablica, 4, psize);
	dodaj(tablica, 5, psize);
	dodaj(tablica, 6, psize);
	dodaj(tablica, 7, psize);
	dodaj(tablica, 8, psize);
	dodaj(tablica, 9, psize);
	//usunMax(tablica, psize);
	wyswietl(tablica, size);
	cout << endl << endl;
	sortPrzezZliczanie(tablica, 0, size);
	cout << endl << endl;
	sortPrzezKopcowanie(tablica, size);
	cout << endl << endl;
	//kopcowanieGora(tablica, 2);
	cout << endl << endl;
	//kopcowanieDol(tablica, size, 0);
}
