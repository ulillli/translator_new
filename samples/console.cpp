#include "console.h"

int main() {
	try {
		workWithExpression W;
		W.Expression();
	}
	catch (const char* str) {
		std::cout << str;
	}
	return 0;
}