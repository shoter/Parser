#pragma once
#include <iostream>
#include "typedefs.h"

enum CharacterType
{
	DIGIT = 0,
	OPERATOR = 1,
	CT_LEFTBRACKET,
	CT_RIGHTBRACKET,
	WHITESPACE
};

CharacterType getCharacterType(const char); //dlaczego nie & bo 'a' nie daloby sie przeslac.
CharacterType getStringType(const std::string &str);