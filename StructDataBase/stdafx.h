// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
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



// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
