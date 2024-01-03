#pragma once
#include <exception>

struct NegativeNumberException : std::exception {
	NegativeNumberException() : std::exception("Should be > 0") {
	
	}
};