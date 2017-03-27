// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "recipe.h"
using namespace std;;
#define IGNORECIN std::cin.clear(); std::cin.ignore(std::cin.rdbuf()->in_avail());
#define CLEARCIN std::cin.clear(); while(std::cin.get()!='\n');



// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
