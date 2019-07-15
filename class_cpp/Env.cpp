#include "Env.hpp"
#include "lib_avm.hpp"

#include <iostream>

Env::Env(void): _inst_exit(false), _done_exit(false)
{}

Env::Env(Env const& e)
{ *this = e; }

Env::~Env(void) {}

Env&	Env::operator=(Env const& e)
{
	auto t1 = e.get_stack();
	this->_stack.clear();
	for (auto it = t1.begin() ; it != t1.end() ; it++)
		this->add_stack_front(*it);
	auto t2 = e.getInstr();
	this->_instr.clear();
	for (auto it = t2.begin() ; it != t2.end() ; it++)
	{
		auto	elm = (*it)->getAct();
		if (elm == Push || elm == Assert)
			this->addInstr(elm, (*it)->getOpType(), (*it)->getVal());
		else
			this->addInstr(elm);
	}
	this->_inst_exit = e.doneExit();
	this->_done_exit = e.isExit();
	return *this;
}

IOperand const					*Env::get_new_op(eOperandType type, std::string const& value)
{
	auto	ret = this->_fact->createOperand(type, value);

	return ret;
}

std::deque<IOperand const *>	Env::get_stack(void) const
{
	return this->_stack;
}

IOperand const					*Env::get_stack_front(void) const
{
	// auto a =
	return this->_stack.front();
	// return a;
}

int								Env::get_stack_size(void) const
{
	return this->_stack.size();
}

bool							Env::isExit(void) const
{
	return this->_inst_exit;
}

bool							Env::doneExit(void) const
{
	return this->_done_exit;
}

void							Env::add_stack_front(IOperand const *o)
{
	this->_stack.push_front(o);
}

void							Env::dell_stack_front(void)
{
	this->_stack.pop_front();
}

void							Env::aff_stack(void) const
{
	for (auto it : this->_stack)
		std::cout << it->toString() << std::endl;
}

void							Env::addExit(void)
{
	this->_inst_exit = true;
}

void							Env::setExit(void)
{
	this->_done_exit = true;
}

void							Env::addInstr(eInstruction act)
{
	Operator	*op = new Operator(act);
	this->_instr.push_back(op);
}

void							Env::addInstr(eInstruction act, eOperandType opt, std::string val)
{
	Operator	*op = new Operator(act, opt, val);
	this->_instr.push_back(op);
}

std::deque<Operator const *>	Env::getInstr(void) const
{
	return this->_instr;
}

void							Env::VM(void)
{
	auto	elm = this->getInstr();

	for (auto it : elm)
		if (doOp(it, this) == -1)
			return ;
}
