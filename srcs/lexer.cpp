#include "MyExceptions.hpp"
#include "Env.hpp"
#include "lib_avm.hpp"

#include <fstream>
#include <string>
#include <regex>
#include <iostream>

static bool	check_regex(std::istream &my_stream, std::string *line, int cnt)
{
	std::regex		my_good_line("^((((push|pop|dump|assert|add|sub|mul|div|mod|print|exit)( (int8|int16|int32|float|double)\\(\\d+([\\.\\,]\\d+)?\\))?)?([\t ]*;([^;].*)?)?)$|;;)");

	if (std::getline(my_stream, *line))
	{
		if (std::regex_match(*line, my_good_line))
			return (true);
		throw LexicalErrorException("Lexical error at line " + std::to_string(cnt));
	}
	return (false);
}

void		from_stdin(void)
{
	Env				*env = new Env();
	std::string		my_line;
	int				cnt_line = -1;
	int				terminate = 0;

	while (check_regex(std::cin, &my_line, ++cnt_line))
	{
		if ((terminate = !parse(my_line, env, cnt_line)))
			break ;
	}
	if (!env->isExit() && !terminate)
		throw NoExitException("Missing exit value befor EOF.");
	if (!terminate)
		throw NoExitException("Missing end of running symbole (';;').");
	env->VM();
}

void		from_file(std::string const& file)
{
	Env				*env;
	std::ifstream	my_file;
	std::filebuf	*fb = my_file.rdbuf();
	std::string		my_line;
	int				cnt_line = -1;

	if (fb->open(file, std::ios::in))
	{
		env = new Env();
		while (check_regex(my_file, &my_line, ++cnt_line))
		{
			if (!parse(my_line, env, cnt_line))
				break ;
		}
		if (!env->isExit())
			throw NoExitException("Missing exit value befor EOF.");
		env->VM();
	}
	else
		throw OpenFileException("Failed to open file " + file);
}
