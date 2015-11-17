#include "utilities.h"

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

void Utilities::DisplayErrorMessage(const std::string& error_message)
{
	std::cout << &error_message << std::endl;
}