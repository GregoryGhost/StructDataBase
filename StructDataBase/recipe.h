#pragma once
#include <string>
#include <vector>
using namespace std;;
#pragma pack (push, 1)
struct timed {
	uint16_t day;
	uint16_t mon;
	uint16_t year;
	string ToString() {
		string str;;
		str = to_string(day) + "." + to_string(mon) + "." + to_string(year);;
		return str;;
	}
	void ToTimed(string str) {
		int i = 0;;
		string::size_type startpos, endpos;;
		startpos = 0;;
		endpos = startpos;;
		while (endpos != string::npos) {
			endpos = str.find(".", startpos);;
			string sub(str.substr(startpos, endpos - startpos));;
			startpos = endpos + 1;;
			istringstream ist(sub);;
			switch (i) {
			case 0:
				ist >> day;;
				break;;
			case 1:
				ist >> mon;;
				break;;
			case 2:
				ist >> year;;
				break;;
			}
			i++;
			ist.clear();;
		}
	}
};
#pragma pack(pop)
#pragma pack (push, 1)
struct formula {
	string ingredient;
	float required_quantity;
	float having_amount;
	float cost;
	timed storage_time;
	timed date_buying;
};
#pragma pack(pop)
#define LIMIT 3
/*
Рецепт: (ингредиент, требуемое
количество, имеющееся количество,
стоимость, время хранения, дата
покупки).
*/
//DB-DataBase (База Данных)
bool DetermineHavingAmount(vector<formula>& vecDB);;
int CalcFreshFood(timed& date, vector<formula>& vecDB);;
float CalcCostAllExpiredProduct(timed date, vector<formula>& vecDB);
formula* StrToFormula(string& str);;
void SaveInDB(string nameDBFile, vector<formula>& dataBase);
void LoadFromDB(string nameDBFile, vector<formula>& arrayDB);;
formula& ReadRecipeFromConsole();
void PrintDB(vector<formula>& arrayDB);
bool ValidateDate(string& sourceDate, timed& outDate);;
void ClearBanSymbol(string& str, char ch);;

bool operator <(timed const & a, timed const & b);;
double DateToDay(int year, int month, int day);;
bool is_leap_year(int year);;