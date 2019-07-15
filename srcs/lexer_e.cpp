#include "MyExceptions.hpp"
#include "Env.hpp"
#include "lib_avm.hpp"

#include <fstream>
#include <string>
#include <regex>
#include <deque>
#include <iostream>

static bool	my_getline(std::istream &my_stream, std::string *line)
{
	if (std::getline(my_stream, *line))
		return true;
	return false;
}

static void	check_regex(std::deque<std::string> all_lines, std::deque<std::string> *err_line, std::deque<int> *lex_err)
{
	std::regex	my_good_line("^((((push|pop|dump|assert|add|sub|mul|div|mod|print|exit)( (int8|int16|int32|float|double)\\(\\d+([\\.\\,]\\d+)?\\))?)?([\t ]*;([^;].*)?)?)$|;;)");
	int			cnt = 0;

	for (auto it = all_lines.begin() ; it != all_lines.end() ; it++)
	{
		cnt++;
		if (!std::regex_match(*it, my_good_line))
		{
			err_line->push_back("Lexical error at line " + std::to_string(cnt));
			lex_err->push_back(cnt);
		}
	}
}

void		from_stdin_e(void)
{
	Env						*env = new Env();
	std::string				my_line;
	std::deque<std::string>	all_lines;
	std::deque<std::string>	err_line;
	std::deque<int>			lex_err;
	int						cnt_line = 0;
	int						terminate = 0;

	while (my_getline(std::cin, &my_line))
	{
		all_lines.push_back(my_line);
		std::regex fin ("^;;");
		if (std::regex_match(my_line, fin))
			break ;
	}
	check_regex(all_lines, &err_line, &lex_err);
	auto le = lex_err.begin();
	for (auto it = all_lines.begin() ; it != all_lines.end() ; it++)
	{
		cnt_line++;
		if (le != lex_err.end() && *le == cnt_line)
		{
			le++;
			continue ;
		}
		if ((terminate = !parse_e(*it, env, &err_line, cnt_line)))
			break ;
	}
	if (!env->isExit() && !terminate)
		err_line.push_back("Missing exit value befor EOF.");
	else if (!terminate)
		err_line.push_back("Missing end of running symbole (';;').");
	if (!err_line.empty())
		throw MultipleErrorException(err_line);
	env->VM();
}

void		from_file_e(std::string const& file)
{
	Env						*env;
	std::ifstream			my_file;
	std::filebuf			*fb = my_file.rdbuf();
	std::string				my_line;
	std::deque<std::string>	all_lines;
	std::deque<std::string>	err_line;
	std::deque<int>			lex_err;
	int						cnt_line = 0;

	if (fb->open(file, std::ios::in))
	{
		env = new Env();
		while (my_getline(my_file, &my_line))
			all_lines.push_back(my_line);
		check_regex(all_lines, &err_line, &lex_err);
		auto le = lex_err.begin();
		for (auto it = all_lines.begin() ; it != all_lines.end() ; it++)
		{
			cnt_line++;
			if (le != lex_err.end() && *le == cnt_line)
			{
				le++;
				continue ;
			}
			if (!parse_e(*it, env, &err_line, cnt_line))
				break ;
		}
		if (!env->isExit())
			err_line.push_back("Missing exit value befor EOF.");
		if (!err_line.empty())
		{
			err_line.push_front(file + ":");
			throw MultipleErrorException(err_line);
		}
		env->VM();
	}
	else
		throw OpenFileException("Failed to open file " + file);
}
