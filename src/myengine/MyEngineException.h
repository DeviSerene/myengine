#pragma once
#include <exception>
#include <iostream>

class MyEngineException : public std::exception
{
public:
	MyEngineException(std::string _message) { m_message = _message; }
	~MyEngineException() throw() {}
	const char* what() { return m_message.c_str(); }
private:
	std::string m_message;
};