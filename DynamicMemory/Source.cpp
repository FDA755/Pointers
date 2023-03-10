//DynamicMemory
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
  
#define tab "\t"
#define delimiter "\n--------------------------------------------------------------------------------------\n"

template<typename T>T** allocate(const int rows, const int cols);
template<typename T>void clear(T** arr, const int rows);
void FillRand(int arr[], const int n, int MinRand, int MaxRand);
void FillRand(double arr[], const int n, int MinRand, int MaxRand);
void FillRand(double** arr, const int rows, const int cols);
void FillRand(int** arr, const int rows, const int cols);

template<typename T>void Print(T arr[], const int n);
template<typename T>void Print(T** arr, const int rows, const int cols);

template<typename T>T* push_back(T* arr, int& n, T value);
template<typename T>T* push_front(T* arr, int& n, T value);
template<typename T>T* insert(T* arr, int& n, T value, int ElementNum);

template<typename T>T* pop_back(T* arr, int& n);
template<typename T>T* pop_front(T* arr, int& n);
template<typename T>T* erase(T* arr, int& n, int ElementNum);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** push_row_front(T** arr, int& rows, const int cols);
template<typename T>T** insert_row(T** arr, int& rows, const int cols, int RowIndex);
template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);
template<typename T>T** pop_row_front(T** arr, int& rows, const int cols);
template<typename T>T** erase_row(T** arr, int& rows, const int cols, int RowIndex);

template<typename T>void push_col_back(T** arr, const int rows, int& cols);

//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");
#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Type amount of elements: "; cin >> n;
	int* arr = new int[n];
	FillRand(arr, n);
	Print(arr, n);

	int value;
	int ElementNum;
	cout << "Введите добавляемое значение добавить в конец: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);
	cout << "Введите добавляемое значение добавить в начало: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);
	cout << "Введите добавляемое значение, куда добавить "; cin >> value >> ElementNum;
	arr = insert(arr, n, value, ElementNum);
	Print(arr, n);
	cout << "Удаляем последний элемент массива: " << endl;
	arr =pop_back(arr, n);
	Print(arr, n);
	cout << "Удаляем первый элемент массива: " << endl;
	arr =pop_front(arr, n);
	Print(arr, n);
	cout << "Удаляем выбранный элемент массива: "; cin >> ElementNum;
	arr = erase(arr, n,	ElementNum);
	Print(arr, n);

	delete[] arr;
	//Memory leak
	/*while (true)new int[n];
	cout << "DONE" << endl;*/
#endif;
#ifdef DYNAMIC_MEMORY_2
	int rows; //количество строк
	int cols; //количество столбцов (количество элементов строки)
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество столбцов: "; cin >> cols;

	double** arr = allocate<double>(rows, cols);
	FillRand(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 900, 1000);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	arr = push_row_front(arr, rows, cols);
	FillRand(arr[0], cols, 100, 200);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	int RowIndex;
	cout << "Введите индекс новой строки: "; cin >> RowIndex;
	arr = insert_row(arr, rows, cols, RowIndex);
	FillRand(arr[RowIndex], cols, 100, 200);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	cout << "Удаляем последнюю строку: " << endl;
	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	cout << "Удаляем первую строку: " << endl;
	arr = pop_row_front(arr, rows, cols);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	cout << "Введите индекс удаляемой строки: "; cin >> RowIndex;
	arr = erase_row(arr, rows, cols, RowIndex);
	Print(arr, rows, cols);
	cout << delimiter << endl;
	push_col_back(arr, rows, cols);
	Print(arr, rows, cols);;

	clear(arr, rows);

#endif; 
}
template<typename T>T** allocate(const int rows, const int cols)
{
	T** arr = new T* [rows]; //создаем массив указателей
	for (int i = 0; i < rows; i++)
	{
		//создаем строки двумерного массива
		arr[i] = new T[cols];
	}
	return arr;
}
template<typename T>void clear(T** arr, const int rows)
{
	//1)Удаляем строки двумерного массива:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	//2)Удаляем массив указателей:
	delete[] arr;
}

	void FillRand(int arr[], const int n, int MinRand, int MaxRand)
	{
		//cout << typeid(arr).name() << endl;
		for (int i = 0; i < n; i++)
		{
			//через арифметику массива указателей и оператор разыменования:
			//*(arr + i) = rand() % 100;
			*(arr + i) = rand() % (MaxRand - MinRand) + MinRand;
		}
	}
	void FillRand(double arr[], const int n, int MinRand, int MaxRand)
	{
		//cout << typeid(arr).name() << endl;
		MinRand *= 100;
		MaxRand *= 100;

		for (int i = 0; i < n; i++)
		{
			//через арифметику массива указателей и оператор разыменования:
			//*(arr + i) = rand() % 100;
			*(arr + i) = rand() % (MaxRand - MinRand) + MinRand;
			*(arr + i) /= 100;
		}
	}
	
	void FillRand(int** arr, const int rows, const int cols)
	{
		for (int i = 0; i < rows; i++)  //i - нумерует строки
		{
			for (int j = 0; j < cols; j++)  //j - нумерует элементы строк
			{
				arr[i][j] = rand() % 100;
			}
		}
	}
	void FillRand(double** arr, const int rows, const int cols)
	{
		for (int i = 0; i < rows; i++)  //i - нумерует строки
		{
			for (int j = 0; j < cols; j++)  //j - нумерует элементы строк
			{
				arr[i][j] = rand() % 10000;
				arr[i][j] /= 100;
			}
		}
	}
	template<typename T>void Print(T arr[], const int n)
	{
		//cout << typeid(arr).name() << endl;
		for (int i = 0; i < n; i++)
	{
		//через оператор индексирования 
		//[] - оператор индексирования (Subscript operator)
			cout << arr[i] << tab;
	}
		cout << endl;
	}
	template<typename T>void Print(T** arr, const int rows, const int cols)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << arr[i][j] << tab;
			}
			cout << endl;
		}
	}

	template<typename T>T* push_back(T* arr, int& n, T value)
	{
		//1)Создаем новый массив нужного размера:
		T* buffer = new T[n + 1];
		//2)Копируем все элементы массива в буферный:
		for (int i = 0; i < n; i++)
		{
			buffer[i] = arr[i];
		}
		//3)Удаляем исходный массив:
		delete[] arr;
		//4)Подменяем адресс в указателе 'arr' адресом нового массива:
		arr = buffer;
		//5)Только после всего этого в конец массива 'arr'можно добавить значение:
		arr[n] = value;
		//6)После добавления в массив 'arr' элемента, количество его элементов увеличивается на 1:
		n++;
		//7)Массив добавлен!
		return arr;
	}
	template<typename T>T* push_front(T* arr, int& n, T value)
	{
		T* buffer = new T[n + 1];
		for (int i = 0; i < n; i++)
		{
			buffer[i + 1] = arr[i];
		}
		delete[] arr;
		arr = buffer;
		arr[0] = value;
		n++;
		return arr;
	}
	template<typename T>T* insert(T* arr, int& n, T value, int ElementNum)
	{
		T* buffer = new T[n + 1];
		for (int i = 0; i < ElementNum; i++)
		{
			buffer[i] = arr[i];
		}
		for (int i = ElementNum; i < n; i++)
		{
			buffer[i + 1] = arr[i];
		}
		delete[] arr;
		arr = buffer;
		arr[ElementNum] = value;
		n++;
		return arr;
	}
	//int* pop_back(int* arr, int& n)
	//{
	//	int* buffer = new int[n-1];
	//	for (int i = 0; i < n; i++)
	//	{
	//		buffer[i] = arr[i];
	//	}
	//	delete[] arr;
	//	arr = buffer;
	//	n--;
	//	return arr;
	//}
	template<typename T>T* pop_back(T* arr, int& n)
	{
		T* buffer = new T[n--];
		for (int i = 0; i < n; i++) buffer[i] = arr[i];
		delete[] arr;
		arr = buffer;
		return arr;
	}
	template<typename T>T* pop_front(T* arr, int& n)
	{
		n--;
		T* buffer = new T[n];
		for (int i = 0; i <n ; i++)
		{
			buffer[i] = arr[i+1];
		}
		delete[] arr;
		arr = buffer;
		return arr;
	}
	template<typename T>T* erase(T* arr, int& n, int ElementNum)
	{
		n--;
		T* buffer = new T[n];
		for (int i = 0; i < ElementNum; i++)
		{
			buffer[i] = arr[i];
		}
		for (int i = ElementNum; i < n; i++)
		{
			buffer[i] = arr[i+1];
		}
		delete[] arr;
		arr = buffer;
		return arr;
	}

	template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
	{
		////1)Создаем буфферный массив указателей:
		//T** buffer = new T* [rows + 1];
		////2)Копируем адреса срок в новый массив указателей:
		//for (int i = 0; i < rows; i++)
		//{
		//	buffer[i] = arr[i];
		//}
		////3)Удаляем исходный массив указателей
		//delete[] arr;
		////4)Подменяем адресс в указаьеле 'arr' адресом нового массива:
		//arr = buffer;
		////5) Создаем новую строку:
		//arr[rows] = new T[cols] {};
		////6)После добавления строки ,количество трок увеличивается на 1
		//rows++;
		////7) Строка добавлена, Возвращаем массив:
		//return arr;
		return push_back(arr, rows, new T[cols]{});
	}
	template<typename T>T** push_row_front(T** arr, int& rows, const int cols)
	{
		/*T** buffer = new T* [rows + 1];
		for (int i = 0; i < rows; i++)
		{
			buffer[i+1] = arr[i];
		}
		delete[] arr;
		arr = buffer;
		arr[0] = new T[cols] {};
		rows++;
		return arr;*/
		return push_front(arr, rows, new T[cols]{});
	}
	template<typename T>T** insert_row(T** arr, int& rows, const int cols, int RowIndex)
	{
		/*T** buffer = new T* [rows + 1];
		for (int i = 0; i <RowIndex; i++)
		{
			buffer[i] = arr[i];
		}
		for (int i = RowIndex; i < rows; i++)
		{
			buffer[i+1] = arr[i];
		}
		delete[] arr;
		arr = buffer;
		arr[RowIndex] = new T[cols] {};
		rows++;
		return arr;*/
		return insert(arr, rows, new T[cols]{}, RowIndex);
	}
	template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
	{
		/*T** buffer = new T* [rows--];
		for (int i = 0; i < rows; i++)
		{
			buffer[i] = arr[i];
		}
		delete[] arr;
		arr = buffer;
		return arr;*/
		return pop_back(arr, rows);
	}
	template<typename T>T** pop_row_front(T** arr, int& rows, const int cols)
	{
	/*	rows--;
		T** buffer = new T* [rows];
		for (int i = 0; i < rows; i++)
		{
			buffer[i] = arr[i + 1];
		}
		delete arr;
		arr = buffer;
		return arr;*/
		return pop_front(arr, rows);
	}
	template<typename T>T** erase_row(T** arr, int& rows, const int cols, int RowIndex)
	{
	/*	rows--;
		T** buffer = new T* [rows];
		for (int i = 0; i < RowIndex; i++)
		{
			buffer[i] = arr[i];
		}
		for (int i = RowIndex; i < rows; i++)
		{
			buffer[i] = arr[i+1];
		}
		delete[] arr;
		arr = buffer;
		return arr;*/
		return erase(arr, rows, RowIndex);
	}
	template<typename T>void push_col_back(T** arr, const int rows, int& cols)
	{
		for (int i = 0; i < rows; i++)
		{
			T* buffer = new T[cols + 1] {};
			for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];
			delete[] arr[i];
			arr[i] = buffer;
		}
		cols++;
	}

