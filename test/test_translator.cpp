#include <gtest.h>
#include "console.h"

//by default, all variables are 3

TEST(translator, canNotCalculateEmptyString) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests(""));
}
TEST(translator, canCalculateExpressionWithOneNumber) {

	workWithExpression W;

	EXPECT_EQ(W.forTests("1"),1);
}
TEST(translator, canNotCalculateExpressionWithUndefinedSymbol) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("1+@9"));
}
TEST(translator, canNotCalculateExpressionWithTwoOperationsWhichAreRunningTogether) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("1+*9"));
}
TEST(translator, canNotDevidedByNull) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("1+6/0+7"));
}
TEST(translator, canCalculateExpressionWithVariableConsistingOfNumberAndLetter) {

	workWithExpression W;

	EXPECT_EQ(W.forTests("1+a7+7"),11);
}
TEST(translator, canNotCalculateExpressionWithVariableConsistingOfUndefinedSymbol) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("1+a#b+7"));
}
TEST(translator, canCalculateExpressionWithVariableBeginningWithUnderscoreSymbol) {

	workWithExpression W;

	ASSERT_NO_THROW(W.forTests("1+_ab+7"));
}
TEST(translator, canNotCalculateExpressionWithVariablebWhichisFunctionName) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("1+sin+7")); 
}
TEST(translator, canNotCalculateExpressionWithSomeOperationsFollowingEachOther) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("1+/*+7"));
}
TEST(translator, canCalculateExpressionWithUnaryFunctionSin) {

	workWithExpression W;

	EXPECT_EQ(W.forTests("a+b+sin(x)+4"),3.0+3.0+sinf(3.0)+4);
}
TEST(translator, canCalculateExpressionWithUnaryFunctionExp) {

	workWithExpression W;

	EXPECT_EQ(W.forTests("a+b+exp(x)+4"), 3.0 + 3.0 + expf(3.0) + 4);
}
TEST(translator, canNotCalculateExpressionWithMoreClosingBracket) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("(a+B)*7)+(8+9)*(1+2)"));
}
TEST(translator, canCalculateExpression1) {

	workWithExpression W;
	
	EXPECT_EQ(W.forTests("(1+2)/(3+4*6.7)-5.3*4.4"),(1.0 + 2.0)/(3.0 + 4.0 * 6.7) - 5.3 * 4.4);
}
TEST(translator, canNotCalculateExpressionWithImplicitDivisionByNull) {

	workWithExpression W;

	ASSERT_ANY_THROW(W.forTests("(1+2)/(3-3)-5.3*4.4"));
}
TEST(translator, canCalculateExpressionWithTwoOperationsWithEqualPriorityTogether) {

	workWithExpression W;
	EXPECT_EQ(W.forTests("(1+2)/(3-2)-5.3*4.4/3.0*8.0+123"), (1.0+2.0)/(3.0-2.0)-5.3*4.4/3.0*8.0+123.0);
}
TEST(translator, canCalculateExpressionWithVariableConsistingOfOneSymbol) {

	workWithExpression W;
	EXPECT_EQ(W.forTests("123*A+sin(x)+e+4"), 123.0 * 3.0 + sinf(3) + 3.0 + 4.0);
}
TEST(translator, canCalculateExpressionWithVariableConsistingOfMoreThanOneSymbols) {

	workWithExpression W;
	EXPECT_EQ(W.forTests("123*Variable1+sin(x)+Variable2+4"), 123.0 * 3.0 + sinf(3.0) +3.0 + 4);
}
