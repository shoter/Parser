#pragma once
#include <string>

//typ oepratora. Nawiasy tutaj też sa bo algorytm przeksztalcania w ONP jest tak zjebany ze traktuje nawias jak operator , hur duh.
//nawias to operator, to prawda XD. Ale to brzydko dla mnie wyglada
//przez to ze CharacterType ma takze te dwa nawiasy musialem ta dodac CT_LEFTBRACKET i CT_RIGHTBRACKET
enum OperatorType
{
	ADD = 1,
	SUBSTRACT,
	DIVIDE,
	MULTIPLY,
	MODULO,
	POWER,
	LEFTBRACKET,
	RIGHTBRACKET
};

//pobiera typ operatora ze stringa. Dasz mu "-" to zwroci ci SUBSTRACT
OperatorType getOperatorType(const std::string &str);
//zwraca nam operator z typu. Np dasz mu ADD to zwroci ci "+"
std::string getOperator(OperatorType type);
