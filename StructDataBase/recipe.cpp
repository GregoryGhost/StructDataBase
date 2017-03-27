#include "stdafx.h"
#include "recipe.h"

void SaveInDB(string nameDBFile, vector<formula>& dataBase)
{
	ofstream fout(nameDBFile, ios_base::trunc);;
	if (!fout.is_open()) {
		cout << "Файл не может быть открыт!\n";;
	}
	for (formula i : dataBase) {
		fout << i.ingredient << "," << i.cost << "," << i.having_amount << "," << i.required_quantity << ","
			<< i.storage_time.ToString() << ","
			<< i.date_buying.ToString()
			<< endl;;
	}
	fout.close();;
}

void LoadFromDB(string nameDBFile, vector<formula>& arrayDB)
{
	ifstream fin(nameDBFile, ios_base::in);;
	if (!fin.is_open()) {
		cout << "Файл не может быть открыт!\n";;
	}
	string str;;
	while (fin >> str) {
		if (!fin.eof()) {
			arrayDB.push_back(*StrToFormula(str));;
		}
	}
	fin.close();;
}

bool DetermineHavingAmount(vector<formula>& vecDB)
{
	bool result = false;;
	for (formula f : vecDB) {
		if (f.having_amount < f.required_quantity) {
			cout << f.ingredient << " " << " НЕ достаточное количество" << endl;;
		}
		else {
			cout << f.ingredient << " " << " достаточное количество" << endl;;
		}
	}
	system("pause");;
	return result;
}

int CalcFreshFood(timed& date, vector<formula>& vecDB)
{
	int result = 0;;
	string str;;
	bool isCorrect = false;;
	do {
		cout << "Введите дату:" << endl;;
		cin >> str;;
		isCorrect = ValidateDate(str, date);;
		if (!isCorrect) {
			cout << "Invalid date!" << endl;
		}
	} while (!isCorrect);;
	for (formula f : vecDB) {
		if (!(f.storage_time < date)) {
			result++;;
		}
	}
	cout << "Для введенной даты " << date.ToString() << "посчитаны свежие продукты " << result << endl;;
	system("pause");;
	return result;
}

float CalcCostAllExpiredProduct(timed date, vector<formula>& vecDB)
{
	float result = 0.0f;;

	string str;;
	bool isCorrect = false;;
	do {
		cout << "Введите дату:" << endl;;
		cin >> str;;
		isCorrect = ValidateDate(str, date);;
		if (!isCorrect) {
			cout << "Invalid date!" << endl;
		}
	} while (!isCorrect);;

	for (formula f : vecDB) {
		if (f.storage_time < date) {
			result += f.cost;;
		}
	}
	cout << "Для введенной даты " << date.ToString() << " посчитана сумма всех просроченных продуктов " << result << endl;;
	system("pause");;
	return result;
}

formula* StrToFormula(string & str)
{
	formula* f = new formula[sizeof(formula)];;
	string::size_type startpos, endpos;;
	startpos = 0;;
	endpos = startpos;;
	int i = 0;;
	while (endpos != string::npos) {
		endpos = str.find(",", startpos);;
		string substr(str.substr(startpos, endpos - startpos));;
		startpos = endpos + 1;;
		switch (i) {
		case 0:
			f->ingredient = substr;;
			break;;
		case 1:
			f->cost = stof(substr);;
			break;;
		case 2:
			f->having_amount = stof(substr);;
			break;
		case 3:
			f->required_quantity = stof(substr);;
			break;;
		case 4:
			f->storage_time.ToTimed(substr);;
			break;;
		case 5:
			f->date_buying.ToTimed(substr);;
			break;;
		}
		i++;;
	}
	return f;
}

formula& ReadRecipeFromConsole()
{
	formula& recipeTemp = *(new formula[1]);;
	bool isCorrect = false;

	cout << "Введите название рецепта:" << endl;;
	cin >> recipeTemp.ingredient;;
	ClearBanSymbol(recipeTemp.ingredient, ',');;

	do {
		cout << "Введите требуемое количество:" << endl;;
		IGNORECIN;;
		cin >> recipeTemp.having_amount;;
		if (recipeTemp.having_amount < 0) {
			cout << "Введенное количество меньше нуля!!!" << endl;;
			recipeTemp.having_amount = 0;;
			isCorrect = false;;
		}
		else {
			isCorrect = true;;
		}
	} while (!isCorrect);;

	do {
		cout << "Введите имеющееся количество:" << endl;;
		IGNORECIN;;
		cin >> recipeTemp.required_quantity;;
		if (recipeTemp.required_quantity < 0) {
			cout << "Введенное количество меньше нуля!!!" << endl;;
			recipeTemp.required_quantity = 0;;
			isCorrect = false;;
		}
		else {
			isCorrect = true;;
		}
	} while (!isCorrect);;

	do {
		cout << "Введите стоимость:" << endl;;
		IGNORECIN;;
		cin >> recipeTemp.cost;;
		if (recipeTemp.cost < 0) {
			cout << "Введенная стоимость меньше нуля!!!" << endl;;
			recipeTemp.cost = 0;;
			isCorrect = false;;
		}
		else {
			isCorrect = true;;
		}
	} while (!isCorrect);;

	string dateTime;;
	do {
		cout << "Введите срок хранения(формат:день.месяц.год):" << endl;;
		cin >> dateTime;;
		isCorrect = ValidateDate(dateTime, recipeTemp.storage_time);;
		if (!isCorrect) {
			cout << "Invalid date!" << endl;
		}
	} while (!isCorrect);;
	dateTime = "";;

	do {
		cout << "Введите дату покупки(формат:день.месяц.год):" << endl;;
		cin >> dateTime;;
		isCorrect = ValidateDate(dateTime, recipeTemp.date_buying);;
		if (!isCorrect) {
			cout << "Invalid date!" << endl;
		}
		cout << dateTime;;
	} while (!isCorrect);;

	return recipeTemp;;
}

bool ValidateDate(string& sourceDate, timed& outDate) {
	string date[LIMIT];
	size_t position = 0;
	int index = 0;
	bool isLeap = false;
	bool isValidDate = true;
	int day, month, year;

	for (int i = 0; i < sourceDate.length(); i++) {
		if (!(sourceDate[i] >= '0' && sourceDate[i] <= '9' || sourceDate[i] == '.')) {
			sourceDate.erase(sourceDate.begin() + i);;
		}
	}
	while ((position = sourceDate.find('.')) != std::string::npos) {
		string token = sourceDate.substr(0, position);
		date[index] = token;
		sourceDate.erase(0, position + 1);
		index += 1;
	}
	date[index] = sourceDate;

	day = atoi(date[0].c_str());
	month = atoi(date[1].c_str());
	year = atoi(date[2].c_str());

	if (year % 4 == 0) {
		isLeap = true;
	}
	if (day < 1 || day > 31) {
		isValidDate = false;
	}
	if (month < 1 || month > 12) {
		isValidDate = false;
	}
	if (month == 2 && day > 29 && isLeap == true) {
		isValidDate = false;
	}
	if (month == 2 && day > 28 && isLeap == false) {
		isValidDate = false;
	}
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day > 30) {
			isValidDate = false;
		}
	}
	if (isValidDate) {
		outDate.day = day;;
		outDate.mon = month;;
		outDate.year = year;;
	}
	return isValidDate;
}

void ClearBanSymbol(string & str, char ch)
{
	size_t  pos = 0;;
	while ((pos = str.find(ch)) != string::npos) {
		str.erase(str.begin() + pos);;
	}
}

void PrintDB(vector<formula>& arrayDB)
{
	cout << "<===Вывод базы данных===>)))" << endl;;
	//cout << "размер:" << arrayDB.size() << endl;;
	for (formula f : arrayDB) {
		cout << "Ингредиент:" << f.ingredient << endl
			<< "Требуемое количество:" << f.required_quantity << endl
			<< "Имеющееся количество:" << f.having_amount << endl
			<< "Стоимость:" << f.cost << endl
			<< "Время хранения:" << f.storage_time.ToString() << endl
			<< "Дата покупки:" << f.date_buying.ToString()
			<< endl << endl
			;;
	}
	system("pause");;
}

bool operator <(timed const & a, timed const & b)
{
	int dayA = DateToDay(a.year, a.mon, a.day);;
	int dayB = DateToDay(b.year, b.mon, b.day);;
	bool result = false;;
	
	result = (dayB - dayA) > 0 ? true : false;;
	return result;;
}

double DateToDay(int year, int month, int day)
{
	// count day in month
	int cdm[] = { 0,31,59,90,120,151,181,212,243,273,304,334 };

	if (month < 1)
		month = 1;
	else if (month > 12)
	{
		year += (month - 1) / 12;
		month = ((month - 1) % 12) + 1;
	}

	// convert [y, mo, d] -> num
	const double d_year = year;
	double num = 365 * year + ceil(d_year / 4) - ceil(d_year / 100) +
		ceil(d_year / 400) + cdm[month - 1] + day;

	if (month > 2 && is_leap_year(year))
		++num;

	return num;
}

bool is_leap_year(int year)
{
	return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
}