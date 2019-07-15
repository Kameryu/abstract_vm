#include "Operator.hpp"
#include "lib_avm.hpp"

Operator::Operator(void): _inst(NoOp) {}

Operator::Operator(eInstruction act): _inst(act) {}

Operator::Operator(eInstruction act, eOperandType opt, std::string val): _inst(act), _optype(opt), _value(val) {}

Operator::Operator(Operator const& op)
{ *this = op; }

Operator::~Operator(void) {}

Operator&		Operator::operator=(Operator const& op)
{
	this->_inst = op.getAct();
	this->_optype = op.getOpType();
	this->_value = op.getVal();
	return (*this);
}

eInstruction	Operator::getAct(void) const
{ return this->_inst; }

eOperandType	Operator::getOpType(void) const
{ return this->_optype; }

std::string		Operator::getVal(void) const
{ return this->_value; }
