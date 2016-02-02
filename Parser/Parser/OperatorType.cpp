#include "OperatorType.h"

OperatorType getOperatorType(const std::string & str)
{
	if (str.size() == 0)
		throw std::exception("getOperatorType str size 0");
	switch (str[0])
	{
	case '+' :
		return OperatorType::ADD;
	case '-' :
		return OperatorType::SUBSTRACT;
	case '/' : case '\\' : case ':' :
		return OperatorType::DIVIDE;
	case '*' :
		return OperatorType::MULTIPLY;
	case '^' :
		return OperatorType::POWER;
	case '%' :
		return OperatorType::MODULO;
	case '(' : case '[' : case '{' : case '<' :
		return OperatorType::LEFTBRACKET;
	case ')' : case ']' : case '}' : case '>' :
		return OperatorType::RIGHTBRACKET;
	default :
		throw std::exception("getOperatorType wrong value");
	}
}

std::string getOperator(OperatorType type)
{
	switch (type)
	{
	case ADD:
		return "+";
	case SUBSTRACT :
		return "-";
	case MULTIPLY :
		return "*";
	case DIVIDE :
		return "/";
	case MODULO :
		return "%";
	case POWER :
		return "^";
	}
}
