#pragma once
#include "lexicalAnalyzer.h"
#include "syntaxAnalyzer.h"
#include "translator.h"
#include "calculator.h"

class workWithExpression {
public:
	void printVectorOfTerm(std::vector<Term*> v) {
		for (int i = 0; i < v.size(); i++) {
			Term* curr = v[i];
			if (dynamic_cast<Number*>(curr)) {
				std::cout << dynamic_cast<Number*>(curr)->getData();
			}
			if (dynamic_cast<Variable*>(curr)) {
				std::cout << dynamic_cast<Variable*>(curr)->getName();
			}
			if (dynamic_cast<Bracket*>(curr) && dynamic_cast<Bracket*>(curr)->getFlag() == 0) std::cout << "(";
			if (dynamic_cast<Bracket*>(curr) && dynamic_cast<Bracket*>(curr)->getFlag() == 1) std::cout << ")";
			if (dynamic_cast<BinaryFunction*>(curr)) {
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == ADD) std::cout << "+";
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == SUB) std::cout << "-";
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == DIV) std::cout << "/";
				if (dynamic_cast<BinaryFunction*>(curr)->getFunc() == MUL) std::cout << "*";
			}
			if (dynamic_cast<UnaryFunction*>(curr)) {
				if (dynamic_cast<UnaryFunction*>(curr)->getFunc() == SIN) std::cout << "SIN";
				if (dynamic_cast<UnaryFunction*>(curr)->getFunc() == EXP) std::cout << "EXP";
			}
		}
		std::cout << std::endl;
	}
	double forTests(std::string str) {
		syntaxAnalyzer S;
		lexicalAnalyzer L;
		std::vector<Term*> v = L.getVectorOfTerms(str);
		if (S.correctly(v)) {
			translator T;
			std::vector<Term*> t = T.getPostfix(v);
			return calculator().calculate(t);
		}
		else throw "Expression is not correctly\n";
	}
	void Expression() {
			std::string str;
			std::cout << "You can keep your expression.\n";
			std::cout << "1. If you entered an incorrect expression(you will be told about this later), \nyou need to correct the error and enter it again.\nThe program will query the expression until it gets the correct one.\n";
			std::cout << "2. If you want to stop typing expressions, write stop.\n";
			std::cout << "3. If the expression is correct and contains variables, then enter their values.\n";
			std::cout << "4. Get the result.\n";
			std::cout << "\nInput new expression\n";
			std::cin >> str;
			while (str != "stop") {
				syntaxAnalyzer S;
				lexicalAnalyzer L;
				std::vector<Term*> v = L.getVectorOfTerms(str);
				while (S.correctly(v) == 0) {
					std::cout << "Expression is not correctly, input a new expression\n";
					std::cin >> str;
					v = L.getVectorOfTerms(str);
					if (str == "stop") {
						break;
					}
				}
				std::cout << "You entered the correct expression\n";
				translator T;
				std::vector<Term*> t = T.getPostfix(v);
				for (int i = 0; i < t.size(); i++) {
					if (dynamic_cast<Variable*>(t[i])) {
						double x;
						std::cout << dynamic_cast<Variable*>(t[i])->getName() << "=";
						std::cin >> x;
						dynamic_cast<Variable*>(t[i])->setData(x);
					}
				}
				calculator C;
				double res = C.calculate(t);
				std::cout << "Result: "<<res << std::endl;
				std::cout << "Input new expression\n";
				std::cin >> str;
			}
	}
};
