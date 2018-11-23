#pragma once
#include <exception>
#include <iostream>

/*!
This class handles Exceptions that occur in the enginem and return a messagebox to the user.
*/

class MyEngineException : public std::exception
{
public:
	MyEngineException(std::string _message) { m_message = _message; }
	~MyEngineException() throw() {}
	const char* what() { return m_message.c_str(); }
private:
	std::string m_message;
};