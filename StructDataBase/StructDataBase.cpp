// StructDataBase.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "StructDataBase.h"

const string _nameDB = "db.dat";;
enum ChooseFuncStr
{
	Exit = 0,
	SaveDB = 2,
	LoadDB = 6,
	InsertRecordInDB = 1,
	GetCountFreshFood = 3,
	GetCalcCostAllExpiredProduct = 4,
	PrintDataBase = 5,
	DetHavingAmount = 7
};

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

int main();

void PrintMenuAction(vector<formula>& vecRecipeDB);
void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

int main()
{
	setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
	vector<formula> vecRecipes;;
	formula* f1 = new formula[1];
	formula& f = *f1;;
	formula* f3 = new formula[1];
	formula& f2 = *f3;;

	f.ingredient = "pro";;
	f.required_quantity = 200;;
	f.having_amount = 2000;;
	f.cost = 2287;;
	f.storage_time;;
	f.storage_time.day = 18;;
	f.storage_time.mon = 12;
	f.storage_time.year = 2012;;
	f.date_buying;;
	f.date_buying.day = 28;;
	f.date_buying.mon = 1;
	f.date_buying.year = 2010;;

	f2.ingredient = "pro2222";;
	f2.required_quantity = 20022;;
	f2.having_amount = 2220;;
	f2.cost = 22227;;
	f2.storage_time;;
	f2.storage_time.day = 18;;
	f2.storage_time.mon = 12;
	f2.storage_time.year = 2012;;
	f2.date_buying;;
	f2.date_buying.day = 21;;
	f2.date_buying.mon = 1;
	f2.date_buying.year = 2012;;

	vecRecipes.push_back(f);;
	vecRecipes.push_back(f2);;

	PrintMenuAction(vecRecipes);;
	return 0;
}

void PrintMenuAction(vector<formula>& vecRecipeDB)
{
	int num_action = 0;
	do {
		system("cls");
		SetColor(White, Black);
		cout << "<--- Program Menu --->" << endl;
		SetColor(Yellow, Black);
		cout
			<< "1. Вставить запись в базу данных" << endl
			<< "2. Сохранить базу данных в файл" << endl
			<< "3. Получить количество свежих продуктов" << endl
			<< "4. Вычислить стоимость всех просроченных продуктов" << endl
			<< "5. Вывести все записи базы данных" << endl
			<< "6. Загрузить базу данных из файла" << endl
			<< "7. Определить достаточно ли имеющихся продуктов"
			<< endl;;
		SetColor(LightBlue, Black);
		cout
			<< "Выберите пункт (1-7) [Выход - 0]:"
			<< std::endl;
		IGNORECIN;
	} while (!(std::cin >> num_action));

	switch (num_action) {
	case SaveDB:
		SaveInDB(_nameDB, vecRecipeDB);;
		break;
	case LoadDB:
		LoadFromDB(_nameDB, vecRecipeDB);;
		break;
	case InsertRecordInDB:
		SetColor(White, Black);
		vecRecipeDB.push_back(ReadRecipeFromConsole());;
		//PrintDB(vecRecipeDB);;
		break;
	case GetCountFreshFood:
		timed tm;;
		CalcFreshFood(tm, vecRecipeDB);;
		break;
	case GetCalcCostAllExpiredProduct:
		timed tm1;;
		CalcCostAllExpiredProduct(tm1, vecRecipeDB);;
		break;
	case PrintDataBase:
		SetColor(Yellow, Black);
		PrintDB(vecRecipeDB);;
		break;
	case DetHavingAmount:
		DetermineHavingAmount(vecRecipeDB);;
		break;
	case Exit:
		cout << "Выход из программы" << endl;;
		return;
		break;
	default:
		SetColor(Red, Black);
		printf("Enter Correct number action!!!\n");
		system("pause");
		break;
	}
	PrintMenuAction(vecRecipeDB);
}