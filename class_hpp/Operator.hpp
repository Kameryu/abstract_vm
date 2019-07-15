#pragma once

#include "defines.hpp"

#include <string>

class Operator
{
public:
	Operator(void);
	Operator(eInstruction act);
	Operator(eInstruction act, eOperandType opt, std::string val);
	Operator(Operator const& op);
	~Operator(void);

	Operator		&operator=(Operator const& op);

	eInstruction	getAct(void) const;
	eOperandType	getOpType(void) const;
	std::string		getVal(void) const;

private:
	eInstruction	_inst;
	eOperandType	_optype;
	std::string		_value;
};