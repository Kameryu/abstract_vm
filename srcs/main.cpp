#include "lib_avm.hpp"

#include <iostream>
#include <string>


int		main(int argc, char ** argv)
{
	int			err = 0;
	int			_e = 0;
	int			ac = argc;
	std::string	opt_e ("-e");

	if (argc > 1 && !opt_e.compare(argv[1]))
	{
		_e = 1;
		ac--;
	}
	if (ac == 1)
	{
		try
		{
			if (_e)
				from_stdin_e();
			else
				from_stdin();
		}
		catch (std::exception const& e)
		{
			std::cerr << e.what() << std::endl;
			err = 1;
		}
		return (err);
	}
	for (int i = 1 + _e; i < argc; i++)
	{
		if (i != 1 + _e)
		{
			std::cout << std::endl;
			std::cerr << std::endl;
		}
		std::cout << argv[i] << std::endl;
		try
		{
			if (_e)
				from_file_e(argv[i]);
			else
				from_file(argv[i]);
		}
		catch (std::exception const& e)
		{
			std::cerr << e.what() << std::endl;
			err += 1;
		}
	}
	return (err);
}