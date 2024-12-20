#pragma once
#include "term.h"

class lexicalAnalyzer {
public:
	bool canBeCharOfVariable(char& s) {
		return ((('A' <= s) && (s <= 'Z')) || (('a' <= s) && (s <= 'z')) || (s == '_'));
	}
	bool canBeFunction(std::string str) {
		return str=="sin"||str=="exp";
	}
	std::vector<Term*> getVectorOfTerms(std::string str) {
		int i = 0;
		std::vector<Term*> result;
		while (i < str.size()) {
			if (str[i] == '+') { // "+"
				result.push_back(new BinaryFunction(ADD));
				i++;
				continue;
			}
			if (str[i] == '-') { // "-"
				result.push_back(new BinaryFunction(SUB));
				i++;
				continue;
			}
			if (str[i] == '*') { // "*"
				result.push_back(new BinaryFunction(MUL));
				i++;
				continue;
			}
			if (str[i] == '/') { // "/"
				result.push_back(new BinaryFunction(DIV));
				i++;
				continue;
			}
			if ((48 <= str[i]) && (str[i] <= 57)) { // "0123456789"
				int j = i + 1;
				std::string num = "";
				num += str[i];
				while (j < str.size() && ((str[j] >= 48) && (str[j] <= 57))) {
					num += str[j];
					j++;
				}
				if (str[j] == 46) {
					num += str[j];
					j++;
					while (j < str.size() && ((str[j] >= 48) && (str[j] <= 57))) {
						num += str[j];
						j++;
					}
				}
				else num += ".0";
				i = j;
				result.push_back(new Number(stod(num)));
				continue;
			}
			if (str[i] == 40) { // "("
				result.push_back(new Bracket(0));
				i++;
				continue;
			}
			if (str[i] == 41) { // ")"
				result.push_back(new Bracket(1));
				i++;
				continue;
			}
			if (canBeCharOfVariable(str[i])) {
				int j = i;
				std::string name;
				while (j < str.size() && (canBeCharOfVariable(str[j]) || (('0' <= str[j]) && (str[j] <= '9')))) {
					name += str[j];
					j++;
				}
				if (canBeFunction(name)) {
					if (name == "sin") {
						result.push_back(new UnaryFunction(SIN));
					}
					if (name == "exp") {
						result.push_back(new UnaryFunction(EXP));
					}
				}
				else result.push_back(new Variable(name));
				i = j;
				continue;
			}
			else throw "Not correct sybol\n";
		}
		result.push_back(new End);
		return result;
	}
};
// класс, в котором есть метод, разбивающий строку на термы и передаёт массив терм в синтаксический анализатор
