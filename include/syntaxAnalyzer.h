#pragma once
#include "term.h"

class syntaxAnalyzer {
public:
	bool correctly(std::vector<Term*> v) {
		int flag = 0;
		int k = 0; //число аквтивных скобок
		for (int i = 0; i < v.size(); i++) {
			switch (flag) {
			case 0: 
				if (dynamic_cast<Bracket*>(v[i])&&dynamic_cast<Bracket*>(v[i])->getFlag() == 0) {
					k++;
					break;
				}
				if (dynamic_cast<Number*>(v[i])||dynamic_cast<Variable*>(v[i])) {
					flag = 1;
					break;
				}
				if (dynamic_cast<UnaryFunction*>(v[i])) {
					flag = 4;
					break;
				}
				else {
					flag = 3;
					break;
				}
			case 1: 
				if (dynamic_cast<Bracket*>(v[i]) && dynamic_cast<Bracket*>(v[i])->getFlag() == 1) {
					k--;
					if (k < 0) flag = 3;
					break;
				}
				if (dynamic_cast<BinaryFunction*>(v[i])) {
					flag = 0;
					break;
				}
				if (dynamic_cast<End*>(v[i])) {
					flag = 2;
				}
				else {
					flag = 3;
					break;
			}
			case 2:
				if (k != 0) {
					flag = 3;
				}
				break;
			case 4:
				if (dynamic_cast<Bracket*>(v[i]) && dynamic_cast<Bracket*>(v[i])->getFlag() == 0) {
					flag = 5;
					break;
				}
				else {
					flag = 3;
					break;
				}
			case 5:
				if (dynamic_cast<Number*>(v[i])|| dynamic_cast<Variable*>(v[i])) {
					flag = 6;
					break;
				}
				else {
					flag = 3;
					break;
				}
			case 6:
				if (dynamic_cast<Bracket*>(v[i]) && dynamic_cast<Bracket*>(v[i])->getFlag() == 1) {
					flag = 1;
					break;
				}
				else {
					flag = 3;
					break;
				}
			}

			if (flag == 3) return 0;
		}
		return 1;
}
};
//класс, в котором есть метод, принимающий массив терм, проверяющий на корректность их расстановки