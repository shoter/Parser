#include "CharacterType.h"

CharacterType getCharacterType(const char character)
{
	if ((character >= '0' && character <= '9') || character == '.')
		return CharacterType::DIGIT;

	switch (character)
	{
	case '*' : case '/' : case '-' : case '+' : case '^' : case '%' : case ':' : case '\\' :
		return CharacterType::OPERATOR;
	case '(' : case '[' : case '{' : case '<' : //nawiasy tutaj bardzo fajnie nam pokazuja jak pod wiele znakow
		//przypisalismy jedna wartosc
		//co ulatwia ify
		//i mozemy pisac bardziej skomplikowane wyrazenia z roznymi typami nawiasow :)
		return CharacterType::CT_LEFTBRACKET;
	case ')':  case ']' : case '}' : case '>' :
		return CharacterType::CT_RIGHTBRACKET;
	case ' ' : case '\t' :
		return CharacterType::WHITESPACE;
	default :
		throw std::exception("getCharacterType wrong value");

	}
}

CharacterType getStringType(const std::string &str)
{
	if (str.size() == 0)
		return CharacterType::WHITESPACE;
	
	CharacterType cType = getCharacterType(str[0]);
	for (uint i = 1;i < str.size(); ++i)
	{
		CharacterType temp = getCharacterType(str[i]);
		if (cType != temp)
			throw std::exception("getStringType Wrong value");
	}
	return cType;
}
