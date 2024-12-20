#pragma once
#include <iostream>
#include <string>
#include <vector>

class Term{
public:
	virtual ~Term(){}
};
class End : public Term {
};
class Variable : public Term{
	std::string name;
	double data=3;
public:
	Variable(std::string& str) : name(str) { }
	void setData(double& data_) {
		data = data_;
	}
	double getData() {
		return data;
	}
	std::string getName() {
		return name;
	}
};
class Const: public Term {

};
class Bracket : public Term {
	bool flag; // 0 - открывающаяся, 1 - закрывающаяся 
public:
	Bracket(bool flag_) : flag(flag_) {
	}
	bool getFlag() {
		return flag;
	}
};

class Number : public Term {
	double data;
public:
	Number(double data_) : data(data_) {
	}	
	double getData() {
		return data;
	}
};
typedef double(*BinFunc)(double, double);
typedef double(*UnFunc)(double);
class Function : public Term {
protected:
	virtual ~Function() {}
};

class BinaryFunction : public Function {
	BinFunc F;
public:
	BinaryFunction(double(*F_)(double, double)) : F(F_){
	}
	BinFunc getFunc() {
		return F;
	}
};
class UnaryFunction : public Function {
	UnFunc F;
public:
	UnaryFunction(double(*F_)(double)) : F(F_) {
	}
	UnFunc getFunc() {
		return F;
	}
};
//функции в cpp или inline
double SIN(double num) {
	return sinf(num);
}
double EXP(double num) {
	return expf(num);
}
double ADD(double num1, double num2) {
	return num1 + num2;
}
double SUB(double num1, double num2) {
	return num1 - num2;
}
double DIV(double num1, double num2) {
	if (num2 != 0) {
		return num1 / num2;
	}
	else throw "division by 0\n";
}
double MUL(double num1, double num2) {
	return num1*num2;
}