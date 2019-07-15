#pragma once

#include "FOperand.hpp"
#include "Operator.hpp"

#include <deque>

class Env
{
public:
	Env(void);
	Env(Env const& e);
	~Env(void);

	Env &operator=(Env const& e);

	IOperand const					*get_new_op(eOperandType type, std::string const& value);

	std::deque<IOperand const *>	get_stack(void) const;
	IOperand const					*get_stack_front(void) const;
	int								get_stack_size(void) const;
	bool							isExit(void) const;
	bool							doneExit(void) const ;

	void							add_stack_front(IOperand const *o);
	void							dell_stack_front(void);
	void							aff_stack(void) const;
	void							setExit(void);
	void							addExit(void);

	void							addInstr(eInstruction act);
	void							addInstr(eInstruction act, eOperandType opt, std::string val);
	std::deque<Operator const *>	getInstr(void) const;

	void							VM(void);

protected:
	FOperand						*_fact;

private:
	std::deque<IOperand const *>	_stack;
	std::deque<Operator const *>	_instr;
	bool							_inst_exit;
	bool							_done_exit;
};
