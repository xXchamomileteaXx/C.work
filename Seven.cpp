#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <string>
#include <cctype>

using namespace std;

//структура для данных о книге
struct book {
	string title;   //название
	long int isbn;  //ISBN
	string author;  //автор
	int lists;      //количество страниц
};
// структура для случайного бинарного дерева
struct Tree {
    book tbook;
	Tree* left = NULL;
	Tree* right = NULL;
};


void heapify(int arr[], int n, int i)
{
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

 // Если левый дочерний элемент больше корня
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// Если самый большой элемент не корень
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(arr, n, largest);
	}
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int arr[], int n)
{
	// Построение кучи (перегруппируем массив)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(arr[0], arr[i]);

		// вызываем процедуру heapify на уменьшенной куче
		heapify(arr, i, 0);
	}
}

/* Вспомогательная функция для вывода на экран массива размера n*/
void printArray(int arr[], int n,book *mass)
{
	int ch;
	for (int i = 0; i < n; ++i)
	{
		cout << i + 1 << ".Number of pages [" << arr[i] << "] " << "\n";
		for (int j = 0; j < 6; ++j)
			if (arr[i] == mass[j].lists) {
				cout << "---------------------------\n";
				cout << "Book [" << j + 1 << "] " << endl;
				cout << "ISBN:  " << mass[j].isbn << endl;
				cout << "Title: " << mass[j].title << endl;
				cout << "Author: " << mass[j].author << endl;
				cout << "Lists: " << mass[j].lists << endl;
				cout << "----------------------------\n";
			}
	}

	cout << "\n";
}


//Добавление элемента 
Tree* add(Tree* p, book tbook) {
	Tree* tree = p;
	
	if (tree == NULL) { //если корня нет,то ключ tbook и есть корень
		tree = new Tree;
		tree->tbook = tbook;
		return tree;
	}
	if (tree->tbook.isbn > tbook.isbn) {
		tree->left = add(tree->left, tbook);
		return tree;
	}
	else {
		tree->right = add(tree->right, tbook);
		return tree;
	}
}


void print(book tbook) {
	cout << "---------------------------\n";
	cout << "ISBN:  " << tbook.isbn << endl;
	cout << "Title: " << tbook.title << endl;
	cout << "Author: " << tbook.author << endl;
	cout << "Lists: " << tbook.lists << endl;
	cout << "----------------------------";
}

//Функция поиска
Tree* find(Tree* p, int k)
{
	Tree* tree = p;
	while (tree && tree->tbook.isbn != k)
	{
		if (tree->tbook.isbn > k)
			tree = tree->left;
		else
			tree = tree->right;
	}
	return tree;
}

int main() {
	//указатель на начало массива
	book* mass;
	ifstream fin;
	// выделяем память
	int size = 6;
	mass = new book[size];
	Tree* Tbook = NULL;
	int key, task;
	Tree* ISBN;
	// чтение из файла
	fin.open("seven.txt");
	if (!fin.is_open())
	{
		cout << "\nFile opening error";
	}
	else {
		for (int i = 0; i < size; i++) {
			fin >> mass[i].isbn;
			fin.ignore();
			getline(fin, mass[i].title);
			getline(fin, mass[i].author);
			fin >> mass[i].lists;
			Tbook = add(Tbook, mass[i]);
		}
		fin.close();

		int* arr = new int[size];





		do
		{
			cout << "Enter number \n\n";
			cout << "[1] Output information about all books\n\n";
			cout << "[2] Sort books by number of pages\n\n";
			cout << "[3] Book Search by ISBN\n\n";
	
			cout << "(0)exit";
			cout << "\n\nYou entered: ";

			cin >> task;
			cout << " ";

			system("cls");

			switch (task)
			{

			case 1:

				for (int i = 0; i < size; i++)
				{
					cout << "---------------------------\n";
					cout << "Book [" << i + 1 << "] " << endl;
					cout << "ISBN:  " << mass[i].isbn << endl;
					cout << "Title: " << mass[i].title << endl;
					cout << "Author: " << mass[i].author << endl;
					cout << "Lists: " << mass[i].lists << endl;
					cout << "----------------------------";
				}
				cout << "\n";

				cout << "\n\n";
				system("pause"); system("cls");
				break;

			case 2:


				heapSort(arr, size);
				cout << endl;
				for (int i = 0; i < size; i++)
					arr[i] = mass[i].lists;

				heapSort(arr, size);
				cout << "Sorted book\n";
				printArray(arr, size, mass);
				cout << "\n\n";
				system("pause"); system("cls");
				break;

			case 3:
				cout << "Book ISBN:";
				for (int i = 0; i < size; i++)
					 cout << " [" << mass[i].isbn <<"] ";
				cout << "\nEnter ISBN: ";
				cin >> key;
				cout << endl;
				ISBN = find(Tbook, key);
				if (!ISBN) cout << "Error\n\n";
				else {
					cout << "Information about book with isbn:" << key << endl;
					print(ISBN->tbook);
					cout << "\n\n";
					}
				system("pause"); system("cls");
				break;
			}

		} while (task != 0);
		return 0;

	}

}