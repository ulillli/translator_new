#pragma once
#include "translator.h"
class calculator{
public:
	double calculate(std::vector<Term*> v) {
		std::stack<Number*> s;
		for (int i = 0; i < v.size(); i++) {
			Term* curr = v[i];
			if (dynamic_cast<Number*>(curr)) {
				s.push(dynamic_cast<Number*>(curr));
				continue;
			}
			if (dynamic_cast<Variable*>(curr)) {
				s.push(new Number(dynamic_cast<Variable*>(curr)->getData()));
				continue;
			}
			if (dynamic_cast<UnaryFunction*>(curr)) {
				double r;
				if(dynamic_cast<Number*>(v[i + 2])) r = dynamic_cast<UnaryFunction*>(curr)->getFunc()(dynamic_cast<Number*>(v[i+2])->getData());
				if (dynamic_cast<Variable*>(v[i + 2])) r = dynamic_cast<UnaryFunction*>(curr)->getFunc()(dynamic_cast<Variable*>(v[i + 2])->getData());
				s.push(new Number(r));
				i += 3;
				continue;
			}
			if (dynamic_cast<BinaryFunction*>(curr)) {
				double x1, x2;
				x2= s.top()->getData();
				s.pop();
				x1 = s.top()->getData();
				s.pop();
				double res = dynamic_cast<BinaryFunction*>(curr)->getFunc()(x1, x2);
				s.push(new Number(res));
			}
		}
		return s.top()->getData();
	}
};
//принимает постфиксную форму и вычисляет её

