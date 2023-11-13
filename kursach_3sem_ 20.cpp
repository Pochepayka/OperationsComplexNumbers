/********************************************************************
*                КАФЕДРА № 304 2 КУРС                               *
* Задание       : программа для реализации алгебраических операций  *
* со структурированными переменными - комплексными числами          *
* Project Type  : Win32 Console Application                         *
* Project Name  : kursach_3sem_20                                   *
* File Name     : kursach_3sem_20.cpp                               *
* Language      : C/C++                                             *
* Programmer(s) : Поцепай В.Н.                                      *
* Groups        : M30-209Б-21                                       *
* Created       : 18/11/2022                                        *
* Last Revision : 28/01/2023                                        *
* Comment(s)    : калькулятор комплексных чисел                     *
*********************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

struct complex;//структура для переменных комплексного типа
void zeroingElls(complex* com);//обнуление всех значений элемента структуры
void formingAlgOfTrig(complex* com);//перевод и формирование алг.ф. по триг.ф.
void formingTrigOfAlg(complex* com);//перевод и формирование триг.ф. по алг.ф.
void menuInfo();//вывод меню
void inputCom1Com2Com3(complex* com1, complex* com2, complex* com3, char sign);//вывод операции с трямя элементами
void readCom(complex* com);//чтение из консоли
/*-void readAllConsol(int& count, complex* com1, complex* com2, complex* com3, int& n);//чтение данных из консоли*/
void readAllFile(int& count, complex* com1, complex* com2, complex* com3, int& n, char* FNAME);//чтение данных из файла
void menu(int& count, complex* com1, complex* com2, complex* com3, int& n);//реализация вызов операций
void summa(complex* com1, complex* com2, complex* com3);
void difference(complex* com1, complex* com2, complex* com3);
void proizvedenie(complex* com1, complex* com2, complex* com3);
void division(complex* com1, complex* com2, complex* com3);
void degree(complex* com1, complex* com3, int N);
void degreeRoot(complex* com1, complex* com3, int N);
void logarifm(complex* com1, complex* com3, int N);
void eof();
void eofOff();
using namespace std;
ofstream fout;
ifstream fin;
//НЕКОРРЕКТНЫЕ ДАННЫЕ
//const char* FNAME = "Test_01.txt";//нет файла
//const char* FNAME = "Test_02.txt";//пустой файл
//const char* FNAME = "Test_03.txt";//8 0 -5 -3 2
//const char* FNAME = "Test_04.txt";//1 0 -5 -3 _
//const char* FNAME = "Test_05.txt";//1 0 -5 -3 2 | 5
//const char* FNAME = "Test_06.txt";//4 3 -5 0 0 (znam==0)
//const char* FNAME = "Test_07.txt";//7 -4 1 -5 (n<=0;n=1)
//const char* FNAME = "Test_08.txt";//7 0 0 4 (z=0)
//const char* FNAME = "Test_09.txt";//5 -3 4 0 (Nroot=0)
//const char* FNAME = "Test_10.txt";//5 0 0 -6 (z=0)
//const char* FNAME = "Test_11.txt";//6 0 0 -3 (z=0;n<0)
//const char* FNAME = "Test_12.txt";//
// //*/+-AnderRoot!=0z?log,root,degreeN?log,root,degree
//КОРРЕКТНЫЕ ФАЙЛЫ 
//const char* FNAME = "Test_20.txt";//1 -3 5 6 0
//const char* FNAME = "Test_21.txt";//2 -4 5 -6 -2
//const char* FNAME = "Test_22.txt";//3 9 3 0 -5
//const char* FNAME = "Test_23.txt";//4 4 0 5 -3
//const char* FNAME = "Test_24.txt";//5 1 -6 -6
//const char* FNAME = "Test_25.txt";//6 4 6 7
const char* FNAME = "Test_26.txt";//7 2 4 4
//const char* FNAME = "Test_27.txt";// 

const char* FNAMEOUT = "RESULT_1.txt";//выходной файл

int countOperation;//знак операции
int N;//степень операции
const float pi = 3.14159236;//константа число пи 

struct complex
{
	float real;
	float imaginary;
	string input;
	double modul;
	double fi;
};
void inputCom1Com2Com3(complex* com1, complex* com2, complex* com3, char sign)
{
	cout <<"\n"<< com1->input << " " << sign << " " << com2->input << " = " << com3->input << " = " << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" ;
	fout << com1->input << " " << sign << " " << com2->input << " = " << com3->input << " = " << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" ;
}
void readCom(complex* com)
{
	eof();
	fin >> com->real;
	//cout << "read x:" << com->real;
	eof();
	fin >> com->imaginary;
	//cout << "read y:" << com->imaginary;
}
void menuInfo()
{
	cout << "\nВозможные операции с комплексными числами:";
	cout << "\n\t1 - сложение двух чисел";
	cout << "\n\t2 - вычитание двух чисел";
	cout << "\n\t3 - умножение двух чисел";
	cout << "\n\t4 - деление двух чисел";
	cout << "\n\t5 - корень N-й степени от числа ";
	cout << "\n\t6 - возведение числа в степень N";
	cout << "\n\t7 - логарифм числа по основанию N";
	cout << "\nКакую операцию вы хотите совершить?\n";
}
void readAllFile(int& count, complex* com1, complex* com2, complex* com3, int& n,const char* FNAME)
{
	fin.open(FNAME);
	if (!fin)// Если файл не найден
	{
		cout << "\nОшибка! Файл не найден!";//вывод сообщения об ошибки
		fout << "Ошибка! Файл не найден!";//вывод сообщения об ошибки
		exit(0);
	}
	//проверка вход знач:
	if (fin.peek() == EOF) //если найденный файл пуст
	{
		cout << "\nОшибка! файл пустой!";// вывод сообщения об ошибке
		fout << "Ошибка! файл пустой!";// вывод сообщения об ошибке
		fin.close();//закрыть файл
		exit(0);
	}
	fin >> count;
	if (count < 1)
	{
		cout << "\nДанного номера операции не существует. Завершение программы..";
		fout << "Данного номера операции не существует. Завершение программы..";
		fin.close();
		exit(0);
	}
	else if (count < 5)
	{
		cout << "\nОперация с двумя числами..";
		readCom(com1);//чтение комплексного числа
		formingTrigOfAlg(com1);//формирование значений
		readCom(com2);//чтение комплексного числа
		formingTrigOfAlg(com2);//формирование 
		eofOff();

	}
	else if (count < 8)
	{
		cout << "\nОперация с одним числом и значением N..";
		readCom(com1);//чтение комплексного числа
		formingTrigOfAlg(com1);//формирование значений
		eof();
		fin >> n;
		//cout << "read n:" << n;
		eofOff();
	}
	else
	{
		cout << "\nДанного номера операции не существует. Завершение программы..";
		fout << "Данного номера операции не существует. Завершение программы..";
		fin.close();
		exit(0);
	}
	fin.close();
}
void eofOff()
{
	if (!fin.eof())
	{
		cout << "\nПереизбыток данных!";
		fout << "Переизбыток данных!";
		fin.close();
		exit(0);
	}
}
void eof()
{
	if (fin.eof())
	{
		cout << "\nНедостаточно данных!";
		fout << "Недостаточно данных!";
		fin.close();
		exit(0);
	}
}
void summa(complex* com1, complex* com2, complex* com3)
{
	com3->real = com1->real + com2->real;
	com3->imaginary = com1->imaginary + com2->imaginary;
	formingTrigOfAlg(com3);
	inputCom1Com2Com3(com1, com2, com3, '+');
}
void difference(complex* com1, complex* com2, complex* com3) 
{
	com3->real = com1->real - com2->real;
	com3->imaginary = com1->imaginary - com2->imaginary;
	formingTrigOfAlg(com3);
	inputCom1Com2Com3(com1, com2, com3, '-');
}
void proizvedenie(complex* com1, complex* com2, complex* com3) {
	com3->real = (com1->real) * (com2->real) - (com1->imaginary) * (com2->imaginary);
	com3->imaginary = (com1->imaginary) * (com2->real) + (com2->imaginary) * (com1->real);
	formingTrigOfAlg(com3);
	inputCom1Com2Com3(com1, com2, com3, '*');
}
void division(complex* com1, complex* com2, complex* com3) {
	float znam = (com2->imaginary) * (com2->imaginary) + (com2->real) * (com2->real);
	if (znam == 0)
	{
		cout << "\nДеление на ноль.." << " Завершение программы..";
		fout << "Деление на ноль.." << " Завершение программы..";
		exit(0);
	}
	com3->real = ((com1->real) * (com2->real)
		- (com1->imaginary) * (-(com2->imaginary))) / znam;
	com3->imaginary = ((com1->imaginary) * (com2->real)
		+ (-(com2->imaginary)) * (com1->real)) / znam;
	formingTrigOfAlg(com3);
	inputCom1Com2Com3(com1, com2, com3, '/');
}
void degree(complex* com1, complex* com3, int N) {
	if (com1->modul == 0 && N<0)
	{
		cout << "\nДеление на ноль при возведении в степень!";
		fout << "Деление на ноль при возведении в степень!";
		exit(0);
	}
	com3->modul = pow(com1->modul, N);
	com3->fi = (N * com1->fi);
	formingAlgOfTrig(com3);
	cout << "\n" << com1->input << " ^ " << N << " = " << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" <<
		" = " << com3->input;
	fout << com1->input << " ^ " << N << " =" << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" <<
		" = " << com3->input;
}
void degreeRoot(complex* com1, complex* com3, int N) {
	if (N == 0)
	{
		cout << "\nНекорректное значение степени корня!";
		fout << "Некорректное значение степени корня!";
		exit(0);
	}
	if (com1->modul <= 0)
	{
		cout << "\nНекорректное значение аргумента корня!";
		fout << "Некорректное значение аргумента корня!";
		exit(0);
	}
	com3->modul = pow(com1->modul, 1.0000 / N);
	com3->fi = (1.0000 / N * com1->fi);
	formingAlgOfTrig(com3);
	cout << "\n" << com1->input << " ^ (1/" << N << ") = " << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" <<
		" = " << com3->input;
	fout << com1->input << " ^ (1/" << N << ") =" << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" <<
		" = " << com3->input;
}
void logarifm(complex* com1, complex* com3, int N) {
	if ((N <= 0)||(N==1)) {
		cout << "\nНекорректное значение степени логарифма!";
		fout << "Некорректное значение степени логарифма!";
		exit(0);
	}
	if (com1->modul <= 0) {
		cout << "\nНекорректное значение аргумента логарифма!";
		fout << "Некорректное значение аргумента логарифма!";
		exit(0);
	}

	com3->real = log(com1->modul) / log(N);//logn(modul)
	com3->imaginary = (com1->fi) / log(N);
	formingTrigOfAlg(com3);
	cout << "\nlog" << N << " " << com1->input << " = " << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" << " = " << com3->input;
	fout << "log" << N << " " << com1->input << " =" << com3->modul <<
		"*(cos(" << com3->fi / pi << "pi) + i*sin(" << com3->fi / pi << "pi))" << " = " << com3->input;
}
void menu(int& count, complex* com1, complex* com2, complex* com3, int& n)
{
	switch (countOperation)
	{
	case 1:
		summa(com1, com2, com3);
		break;
	case 2:
		difference(com1, com2, com3);
		break;
	case 3:
		proizvedenie(com1, com2, com3);
		break;
	case 4:
		division(com1, com2, com3);
		break;
	case 5:
		degreeRoot(com1, com3, n);
		break;
	case 6:
		degree(com1, com3,n);
		break;
	case 7:
		logarifm(com1, com3, n);
		break;
	default:
		cout << "\nДанной операции не существует..";
		fout << "Данной операции не существует..";
	}
	exit(0);
}
void formingTrigOfAlg(complex* com)
{
		com->input = "(" + to_string(com->real) + " + " + "(" + to_string(com->imaginary) + "i))";
		if (com->real == 0 && com->imaginary == 0) com->modul = 0;
		else
		com->modul = pow((pow(com->real, 2) + pow(com->imaginary, 2)), 0.5);
		if ((com->real > 0) && (com->imaginary > 0)) com->fi = atan(abs(com->imaginary / com->real));
		else if ((com->real > 0) && (com->imaginary == 0)) com->fi = 0;
		else if ((com->real == 0) && (com->imaginary > 0)) com->fi = pi / 2;
		else if ((com->real < 0) && (com->imaginary > 0)) com->fi = pi - atan(abs(com->imaginary / com->real));
		else if ((com->real <= 0) && (com->imaginary == 0)) com->fi = pi;
		else if ((com->real < 0) && (com->imaginary < 0)) com->fi = -pi + atan(abs(com->imaginary / com->real));
		else if ((com->real == 0) && (com->imaginary < 0)) com->fi = -pi / 2;
		else if ((com->real > 0) && (com->imaginary < 0)) com->fi = -atan(abs(com->imaginary / com->real));
		else {
			cout << "\nОшибка значения fi";
			exit(0);
		}
}
void formingAlgOfTrig(complex* com)
{
		com->real = com->modul * cos(com->fi);
		com->imaginary = com->modul * sin(com->fi);
		com->input = "(" + to_string(com->real) + " + " + "(" + to_string(com->imaginary) + "i))";
}
void zeroingElls(complex* com)
{
	com->fi = NULL;
	com->real = NULL;
	com->imaginary = NULL;
	com->modul = NULL;
}
int main()
{
	setlocale(LC_ALL, "RUSSIAN"); // подключение русского языка 
	fout.open(FNAMEOUT);    // файл вывода
	complex* complex1 = new complex;//первое комплексное число
	zeroingElls(complex1);
	complex* complex2 = new complex;//второе комплексное число
	zeroingElls(complex2);
	complex* complex3 = new complex;//результат комплексное число
	zeroingElls(complex3);
	menuInfo();
	readAllFile(countOperation, complex1, complex2, complex3, N, FNAME);
	menu(countOperation, complex1, complex2, complex3, N);
}
/*-void readAllConsol(int& count, complex* com1, complex* com2, complex* com3, int& n)
{

	cin >> count;
	if (count < 1)
	{
		cout << "\nДанного номера операции не существует. Завершение программы..";
		exit(0);
	}
	else if (count < 5)
	{
		cout << "\nОперация с двумя числами..";
		cout << "\nЧтение первого..";
		readCom(com1);
		formingTrigOfAlg(com1);
		cout << "\nЧтение второго..";
		readCom(com2);
		formingTrigOfAlg(com2);
	}
	else if (count < 8)
	{
		cout << "\nОперация с одним числом и значением N..";
		cout << "\nЧтение..";
		readCom(com1);
		formingTrigOfAlg(com1);
		cout << "\nВведите N:";
		eof();
		cin >> n;
	}
	else
	{
		cout << "\nДанного номера операции не существует. Завершение программы..";
		exit(0);
	}
}*/
