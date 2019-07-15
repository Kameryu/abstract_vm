#include "Env.hpp"
#include "MyExceptions.hpp"

#include <string>
#include <regex>
#include <deque>

static eInstruction	wich_inst(std::string str, Env *env)
{
	if (str.find("push") != std::string::npos)
		return Push;
	if (str.find("pop") != std::string::npos)
		return Pop;
	if (str.find("dump") != std::string::npos)
		return Dump;
	if (str.find("assert") != std::string::npos)
		return Assert;
	if (str.find("add") != std::string::npos)
		return Add;
	if (str.find("sub") != std::string::npos)
		return Sub;
	if (str.find("mul") != std::string::npos)
		return Mul;
	if (str.find("div") != std::string::npos)
		return Div;
	if (str.find("mod") != std::string::npos)
		return Mod;
	if (str.find("print") != std::string::npos)
		return Print;
	if (str.find("exit") != std::string::npos)
	{
		env->addExit();
		return Exit;
	}
	return NoOp;
}

static eOperandType	wich_opt(std::string str)
{
	if (str.find("int8") != std::string::npos)
		return Int8;
	if (str.find("int16") != std::string::npos)
		return Int16;
	if (str.find("int32") != std::string::npos)
		return Int32;
	if (str.find("float") != std::string::npos)
		return Float;
	return Double;
}

static void			inst_val(std::string str, Env *env)
{
	eInstruction	inst;
	eOperandType	opt;
	std::string		val;

	inst = wich_inst(str, env);
	opt = wich_opt(str);

	auto	start = str.find("(") + 1;
	auto	end = str.find(")");
	val = str.substr(start, end - start);
	env->addInstr(inst, opt, val);
}

static void			inst_none(std::string str, Env *env)
{
	eInstruction	inst;

	inst = wich_inst(str, env);
	env->addInstr(inst);
}

int					parse_e(std::string str, Env *env, std::deque<std::string> *err_line, int cnt)
{
	std::string		str_val_int = "((int8|int16|int32)\\(-?\\d+\\))";
	std::string		str_val_flt = "((float|double)\\(-?\\d+[.,]\\d+\\))";
	std::string		str_comment = "[\t ]*;([^;].*|$)";
	std::regex		val_int(str_val_int + "(" + str_comment + ")?");
	std::regex		val_flt(str_val_flt + "(" + str_comment + ")?");
	std::regex		base_val("^(push|assert) (" + str_val_int + "|" + str_val_flt + ")" + "(" + str_comment + ")?");
	std::regex		base_end("^(pop|dump|add|sub|mul|div|mod|print|exit)(?!( " + str_val_int + "|" + str_val_flt + "))" + "(" + str_comment + ")?");
	std::regex		comment("^"+ str_comment);
	std::regex		end_all("^;;");
	std::regex		empty("^$");

	if (std::regex_match(str, end_all))
	{
		if (!env->isExit())
			err_line->push_back("Missing exit instruction before leaving execution at line " + std::to_string(cnt));
		env->addInstr(Terminate);
		return 0;
	}
	if (std::regex_match(str, comment) || std::regex_match(str, empty))
		return 1;
	if (!(std::regex_match(str, base_val) || std::regex_match(str, base_end)))
		err_line->push_back("Line " + std::to_string(cnt) + " is not parsed as expected.");
	else if (std::regex_match(str, base_val))
		inst_val(str, env);
	else
		inst_none(str, env);
	return 1;
}
