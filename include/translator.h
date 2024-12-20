#pragma once
#include "term.h"
#include <stack>
#include <map>

class translator {
public:
	std::vector<Term*> getPostfix(std::vector<Term*> v) {
		std::map<double (*)(double, double), int> priorities = { {ADD,1},{SUB,1},{MUL,2},{DIV,2}};

		std::vector<Term*> result;

		std::stack<Term*> stack;

		for (int i = 0; i < v.size(); i++) { 
			Term* curr = v[i];
			if (dynamic_cast<Number*>(curr)|| dynamic_cast<Variable*>(curr)) {
				result.push_back(curr);
			}
			if (dynamic_cast<UnaryFunction*>(curr)){
				result.push_back(curr);
				result.push_back(v[i + 1]);
				result.push_back(v[i + 2]);
				result.push_back(v[i + 3]);
				i += 3;
				continue;
			}
			if (dynamic_cast<Bracket*>(curr) && dynamic_cast<Bracket*>(curr)->getFlag() == 0) {
				stack.push(curr);
			}
			if (dynamic_cast<Bracket*>(curr) && dynamic_cast<Bracket*>(curr)->getFlag() == 1) {
					while (!(dynamic_cast<Bracket*>(stack.top()) && dynamic_cast<Bracket*>(stack.top())->getFlag() == 0)) {
						result.push_back(stack.top());
						stack.pop();
					}
					stack.pop();
			}
			if (dynamic_cast<BinaryFunction*>(curr)) {
				if ((stack.empty())||(dynamic_cast<Bracket*>(stack.top()) && dynamic_cast<Bracket*>(stack.top())->getFlag() == 0)) {
					stack.push(curr);
				}
				else {
					if (!stack.empty() && priorities[dynamic_cast<BinaryFunction*>(curr)->getFunc()] <= priorities[dynamic_cast<BinaryFunction*>(stack.top())->getFunc()]) {
						while (!stack.empty() && dynamic_cast<BinaryFunction*>(stack.top()) && priorities[dynamic_cast<BinaryFunction*>(curr)->getFunc()] <= priorities[dynamic_cast<BinaryFunction*>(stack.top())->getFunc()]) {
							result.push_back(stack.top());
							//result.push_back(curr);
							stack.pop();
						}
						stack.push(curr);
					}
					else stack.push(curr);
				}
			}
		}
		while(!stack.empty()){ 
			result.push_back(stack.top()); 
			stack.pop();
		}
		return result;
	}
};
//класс, в котором есть метод принимающий корректный массив терм и отдаёт постфиксную форму записи в термах

