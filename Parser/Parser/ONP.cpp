#include "ONP.h"
#include <stack>
#include "Operations.h"
#include "OperatorAssociation.h"
#include "CharacterType.h"
#include "Utils.h"
#include "OperatorType.h"
#include "typedefs.h"
#include <iostream> //dla debugu

///Pobiera nastepny wyraz (liczbe/operator lub 1 nawias)
///onp jest podawany przez referencje &
///onp jest const bo on nie bedzie edytowany
///position jest podawane przez referencje. po pobraniu wyrazu position bedzie wskazywac na miejsce w stringu onp tuz po pobranym wyrazie
std::string getNextString(const std::string &onp, uint &position)
{
	//jesli juz jestesmy poza stringiem :D
	if (position >= onp.size())
		return ""; //poza zakresem - zwroc pusty
	char c = onp[position]; //wez znak na aktualnej pozycji
	uint i = 1; //indeks nastepnego znaku wzgledem [position] to 1.
	CharacterType cType; //typ znaku
	//nigdy nie zwroci bialego znaku dzieki tej petli
	//ta petla idzie do nastepnego znaku ktory nie jest bialym znakiem
	while ((cType = getCharacterType(c)) == CharacterType::WHITESPACE)
	{
		c = onp[i++ + position]; 
	}
	//nie mozna out = c, uzylem konstruktora ktory wstawia 1 znak c do stringu out
	std::string out = std::string(1, c); // wypelnij 1 znakiem c
	//lecimy aż nie natrafimy na wyraz (jest break)
	for (;i + position < onp.size(); ++i)
	{
		c = onp[i + position];
		CharacterType newCType = getCharacterType(c);
		if (newCType != cType //jesli typy wyrazow sie nie zgadzaja. Na przyklad wczytywal liczby i tu nagle pojawil mu sie operator 
			|| cType == CharacterType::CT_LEFTBRACKET  //jesli to nawias
			|| cType == CharacterType::CT_RIGHTBRACKET //jest to nawias
			)
			break; // to przerwij
		out += c; //jesli nie przerwal to dodaje ten znak do out'a
	}
	position = i + position; //upadtuje pozycje (zobacz ze pozycja jest przekazywana przez referencje!!!)
	return out; //zwraca wyraz
}

//zwykly prosty konstruktor
ONP::ONP(const char * expression)
{
	this->expression = expression;
	this->expression = trim(this->expression); //obcina biale znaki z poczatku stringa i z konca
}

double ONP::Calculate()
{
	std::string onpString = "";
	uint pos = 0; //musimy przekazac pozycje. ConvertToOnp dziala na zasadzie rekurencji i pierwsze wywolanie musi miec jakies 
	//warunki poczatkowe ktore przekazujemy.
	//jako ze position jest przekazywane przez referencje to tutaj ponizej nie mozemy wpisac 0 zamiast pos, musi to byc zmienna
	convertToONP(expression, pos, onpString); 
	onpExpression = onpString; //przypisujemy do zmiennej globalnej. Przyda sie przy wypisywaniu w WINAPI
	return calculateONP(onpString); //zwraca nam wzkalkulowany wynik
}

//kazda zmienna ONP moze byc NIEJAWNIE zmieniona na double'a dzieki temu. Uzyjemy tego w WINAPI
ONP::operator double()
{
	return Calculate();
}

//To juz wikipedia :). 
void ONP::convertToONP(const std::string &expr, uint &position, std::string &out)
{
	std::stack<OperatorType> operators;

	while (position < expr.size()) //Póki zostały symbole do przeczytania wykonuj:
	{
		std::string symbol = getNextString(expr, position); //

		if (getStringType(symbol) == DIGIT)
			out += symbol  + " "; //Jeśli symbol jest liczbą dodaj go do kolejki wyjście.
		else if (getStringType(symbol) == OPERATOR) //Jeśli symbol jest operatorem, o1, wtedy:
		{
			OperatorType type = getOperatorType(symbol); //pobieram typ operatora (czy to mnozenie , dzielenie , etc...)
			OperatorAssociation ass = getOperatorAssociation(type); //pobieram łącznosc operatora //https://pl.wikipedia.org/wiki/%C5%81%C4%85czno%C5%9B%C4%87_(matematyka)
			Priority qP = operators.empty() ? -1 : getOperatorPriority(operators.top()); //priorytet operatora z kolejki
			Priority sP = getOperatorPriority(type); //priorytet operatora o1

			while (operators.empty() == false //1) dopóki na górze stosu znajduje się operator, o2 taki, że:
				&& ((ass == LEFT && sP <= qP) || //o1 jest lewostronnie łączny i jego kolejność wykonywania jest mniejsza lub równa kolejności wyk. o2, 
					(ass == RIGHT && sP < qP))) //lub o1 jest prawostronnie łączny i jego kolejność wykonywania jest mniejsza od o2,

			{
				std::string op = getOperator(operators.top());//bierzemy znak operatora ze stosu
				operators.pop(); //wywalamy go ze stosu
				out += op + " "; //zdejmij o2 ze stosu i dołóż go do kolejki wyjściowej i wykonaj jeszcze raz 1)

				qP = operators.empty() ? -1 : getOperatorPriority(operators.top()); //dopóki  <- więc zapętlamy. Musimy ponownie przypisać wartość
			}
			operators.push(type); //2) włóż o1 na stos operatorów.

		}
		else if (getOperatorType(symbol) == LEFTBRACKET) //Jeżeli symbol jest lewym nawiasem
			operators.push(LEFTBRACKET); //  to włóż go na stos.
		else if (getOperatorType(symbol) == RIGHTBRACKET) //Jeżeli symbol jest prawym nawiasem 
		{
			while (operators.top() != LEFTBRACKET) //dopóki symbol na górze stosu nie jest lewym nawiasem
			{
				std::string op = getOperator(operators.top()); //zdejmuj operatory ze stosu
				operators.pop();
				out += op + " "; // i dokładaj je do kolejki wyjście,
			}
			operators.pop(); //kiedy dojdziesz do tego miejsca zdejmij lewy nawias ze stosu bez dokładania go do kolejki wyjście.
		}
	}

	while (operators.empty() == false) //Jeśli nie ma więcej symboli do przeczytania,
	{
		std::string op = getOperator(operators.top());
		operators.pop();
		out += op + " "; //zdejmuj wszystkie symbole ze stosu (jeśli jakieś są) i dodawaj je do kolejki wyjścia
	}

	
	out = trim(out); //obcinamy biale znaki jesli sa z wyniku
}


//funkcja po prostu wykonuje operacje ktora przekazujemy jako parametr szablonu. 
//Nie wiem co tutaj moge tlumaczyc :?. 
template <typename TOperation>
Operation *MakeOperation(std::stack<Operation *> &stack) //jeśli i-ty symbol jest operatorem to:
{ 
	Operation *a = stack.top(); stack.pop(); //zdejmij ze stosu jeden element (ozn. a),
	Operation *b = stack.top(); stack.pop(); //zdejmij ze stosu kolejny element (ozn. b),

	Operation *result = new TOperation(*b, *a);  //wykonaj operacje
	stack.push(result); //odłóż na stos wartość b operator a.


	delete a; //zdjelismy to ze stosu, jest nie potrzebne, wiec skasujmy
	delete b;

	return result; // zwroc wynik ( moze komus sie przyda! :D), racze nie potrzebne ale kto wie :P
}

void MakeOperation(std::stack<Operation *> &stack, OperatorType type)
{
	//ta funkcja w zaleznosci od typu operatora wybiera nam jaka operacje na stosie chcemy zrobic.
	if (type == ADD)
		MakeOperation<Add>(stack);
	if (type == SUBSTRACT)
		MakeOperation<Substract>(stack);
	if (type == MULTIPLY)
		MakeOperation<Multiply>(stack);
	if (type == DIVIDE)
		MakeOperation<Divide>(stack);
	if (type == POWER)
		MakeOperation<Power>(stack);
	if (type == MODULO)
		MakeOperation<Modulo>(stack);
}


double ONP::calculateONP(const std::string & onp)
{
	std::stack<Operation *> stack;
	uint position = 0;

	while (position < onp.size()) //Dla wszystkich symboli z wyrażenia ONP wykonuj:
	{
		std::string expr = getNextString(onp, position); //pobierz nastepny wyraz (liczbe/operator/nawias)
		CharacterType type = getStringType(expr); //co to za typ znaku
		
		if (type == OPERATOR) //operator, no to robimy operacje :D na przyklad operacje dodawania
			MakeOperation(stack, getOperatorType(expr));
		else if (expr.size() > 0 && getCharacterType(expr[0]) == DIGIT) //a jednak to liczba, no to ... dodajemy na stos tak jak nam algorytm kaze XD
		{
			Operation *number = new Number(std::stod(expr)); //jeśli i-ty symbol jest liczbą, to odłóż go na stos,
			stack.push(number); // na stos! 
		}
		else
			position++; //pewnie bialy znak czy jakis inny fajerwerk ktorego skrypt nie rozpoznal. Idziemy o 1 znak dalej. 
	}

	Operation *result = stack.top(); //Zdejmij ze stosu wynik.
	double _out = *result;
	delete result;
	return _out; //zwroc wynik
}
