#pragma once

#include <string>
#include <deque>

class MyExceptions : public std::exception
{
public:
	explicit	MyExceptions(void);
	virtual		~MyExceptions(void) throw();
	MyExceptions(MyExceptions const &src);

	MyExceptions		&operator=(MyExceptions const &src);
	virtual const char	*what(void) const throw();

protected:
	std::string			_msg;
};


class	EmptyStackException : public MyExceptions
{
public:
	explicit EmptyStackException(void);
	virtual ~EmptyStackException(void) throw();
	EmptyStackException(std::string str);
};


class	WrongAssertionException : public MyExceptions
{
public:
	explicit WrongAssertionException(void);
	virtual ~WrongAssertionException(void) throw();
	WrongAssertionException(std::string str);
};


class	NotEnoughElementException : public MyExceptions
{
public:
	explicit NotEnoughElementException(void);
	virtual ~NotEnoughElementException(void) throw();
	NotEnoughElementException(std::string str);
};


class	LexicalErrorException : public MyExceptions
{
public:
	explicit LexicalErrorException(void);
	virtual ~LexicalErrorException(void) throw();
	LexicalErrorException(std::string str);
};


class	OpenFileException : public MyExceptions
{
public:
	explicit OpenFileException(void);
	virtual ~OpenFileException(void) throw();
	OpenFileException(std::string str);
};


class	NoExitException : public MyExceptions
{
public:
	explicit NoExitException(void);
	virtual ~NoExitException(void) throw();
	NoExitException(std::string str);
};


class	ParsingErrorException : public MyExceptions
{
public:
	explicit ParsingErrorException(void);
	virtual ~ParsingErrorException(void) throw();
	ParsingErrorException(std::string str);
};

class	MultipleErrorException : public MyExceptions
{
public:
	explicit MultipleErrorException(void);
	virtual ~MultipleErrorException(void) throw();
	MultipleErrorException(std::deque<std::string> err_line);
};
