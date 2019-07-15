#include "MyExceptions.hpp"

MyExceptions::MyExceptions(void): _msg("Error") {}

MyExceptions::~MyExceptions(void) throw() {}

MyExceptions::MyExceptions(MyExceptions const &src)
{
	this->_msg = src._msg.c_str();
}

MyExceptions	&MyExceptions::operator=(MyExceptions const &src)
{
	this->_msg = src._msg.c_str();
	return (*this);
}

const char		*MyExceptions::what(void) const throw()
{
	return (this->_msg.c_str());
}


EmptyStackException::EmptyStackException(void)
{
	this->_msg = "Stack is empty.";
}
EmptyStackException::~EmptyStackException(void) throw() {}
EmptyStackException::EmptyStackException(std::string str)
{
	this->_msg = str;
}


WrongAssertionException::WrongAssertionException(void)
{
	this->_msg = "Assertion failed.";
}
WrongAssertionException::~WrongAssertionException(void) throw() {}
WrongAssertionException::WrongAssertionException(std::string str)
{
	this->_msg = str;
}


NotEnoughElementException::NotEnoughElementException(void)
{
	this->_msg = "Not enough element.";
}
NotEnoughElementException::~NotEnoughElementException(void) throw() {}
NotEnoughElementException::NotEnoughElementException(std::string str)
{
	this->_msg = str;
}


LexicalErrorException::LexicalErrorException(void)
{
	this->_msg = "Lexical error.";
}
LexicalErrorException::~LexicalErrorException(void) throw() {}
LexicalErrorException::LexicalErrorException(std::string str)
{
	this->_msg = str;
}


OpenFileException::OpenFileException(void)
{
	this->_msg = "Fail to open file.";
}
OpenFileException::~OpenFileException(void) throw() {}
OpenFileException::OpenFileException(std::string str)
{
	this->_msg = str;
}


NoExitException::NoExitException(void)
{
	this->_msg = "Missing exit.";
}
NoExitException::~NoExitException(void) throw() {}
NoExitException::NoExitException(std::string str)
{
	this->_msg = str;
}


ParsingErrorException::ParsingErrorException(void)
{
	this->_msg = "Parsing error.";
}
ParsingErrorException::~ParsingErrorException(void) throw() {}
ParsingErrorException::ParsingErrorException(std::string str)
{
	this->_msg = str;
}


MultipleErrorException::MultipleErrorException(void)
{
	this->_msg = "Multiple errors occured.";
}
MultipleErrorException::~MultipleErrorException(void) throw() {}
MultipleErrorException::MultipleErrorException(std::deque<std::string> err_line)
{
	for (auto it = err_line.begin(); it != err_line.end(); it++)
		this->_msg += (it == err_line.begin() ? "~>" : "\n") + *it;
}
