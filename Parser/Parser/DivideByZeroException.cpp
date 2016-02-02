#include "DivideByZeroException.h"

DivideByZeroException::DivideByZeroException(const char * message)
	:std::exception(message)
{
}
