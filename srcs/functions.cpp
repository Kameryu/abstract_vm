#include "lib_avm.hpp"
#include "MyExceptions.hpp"
#include "../template/TOperand.tpp"

#include <string>
#include <iostream>

void	fn_push (Env *env, eOperandType type, std::string const& value)
{
	auto op = env->get_new_op(type, value);
	env->add_stack_front(op);
}

void	fn_pop (Env *env)
{
	if (!env->get_stack_size())
		throw EmptyStackException("Can not POP an empty stack");
	env->dell_stack_front();
}

void	fn_dump (Env *env)
{
	env->aff_stack();
}

void	fn_assert (Env *env, eOperandType type, std::string const& value)
{
	if (!env->get_stack_size())
		throw EmptyStackException("Can not ASSERT an empty stack");

	auto elm = env->get_stack_front();

	if (elm->getType() != type || elm->toString() != value)
		throw WrongAssertionException(value + " does not match " + elm->toString() + " with the specified type.");
}

void	fn_add (Env *env)
{
	int stack_len = env->get_stack_size();
	if (stack_len < 2)
		throw NotEnoughElementException("Can not ADD a " + std::to_string(stack_len) + " element(s) stack");
	auto &a = *env->get_stack_front();
	env->dell_stack_front();
	auto &b = *env->get_stack_front();
	env->dell_stack_front();
	auto c = b + a;
	env->add_stack_front(c);
}

void	fn_sub (Env *env)
{
	int stack_len = env->get_stack_size();
	if (stack_len < 2)
		throw NotEnoughElementException("Can not SUB a " + std::to_string(stack_len) + " element(s) stack");
	auto &a = *env->get_stack_front();
	env->dell_stack_front();
	auto &b = *env->get_stack_front();
	env->dell_stack_front();
	auto c = b - a;
	env->add_stack_front(c);
}

void	fn_mul (Env *env)
{
	int stack_len = env->get_stack_size();
	if (stack_len < 2)
		throw NotEnoughElementException("Can not MUL a " + std::to_string(stack_len) + " element(s) stack");
	auto &a = *env->get_stack_front();
	env->dell_stack_front();
	auto &b = *env->get_stack_front();
	env->dell_stack_front();
	auto c = b * a;
	env->add_stack_front(c);
}

void	fn_div (Env *env)
{
	int stack_len = env->get_stack_size();
	if (stack_len < 2)
		throw NotEnoughElementException("Can not DIV a " + std::to_string(stack_len) + " element(s) stack");
	auto &a = *env->get_stack_front();
	env->dell_stack_front();
	auto &b = *env->get_stack_front();
	env->dell_stack_front();
	auto c = b / a;
	env->add_stack_front(c);
}

void	fn_mod (Env *env)
{
	int stack_len = env->get_stack_size();
	if (stack_len < 2)
		throw NotEnoughElementException("Can not MOD a " + std::to_string(stack_len) + " element(s) stack");
	auto &a = *env->get_stack_front();
	env->dell_stack_front();
	auto &b = *env->get_stack_front();
	env->dell_stack_front();
	auto c = b % a;
	env->add_stack_front(c);
}

void	fn_print (Env *env)
{
	if (!env->get_stack_size())
		throw EmptyStackException("Can not PRINT an empty stack");

	auto &a = *env->get_stack_front();
	if (a.getType() > Int8)
		throw WrongAssertionException("Top element is not an 8-bit integer.");
	std::cout << a.toString() << std::endl;
}

void	fn_exit (Env *env)
{
	env->setExit();
}

int		doOp(const Operator *op, Env *env)
{
	eInstruction	instr = op->getAct();
	if (instr == Terminate)
		return -1;
	if (env->doneExit())
		return 0;
	if (instr == Push)
		fn_push(env, op->getOpType(), op->getVal());
	if (instr == Pop)
		fn_pop (env);
	if (instr == Dump)
		fn_dump (env);
	if (instr == Assert)
		fn_assert (env, op->getOpType(), op->getVal());
	if (instr == Add)
		fn_add (env);
	if (instr == Sub)
		fn_sub (env);
	if (instr == Mul)
		fn_mul (env);
	if (instr == Div)
		fn_div (env);
	if (instr == Mod)
		fn_mod (env);
	if (instr == Print)
		fn_print (env);
	if (instr == Exit)
		fn_exit (env);
	return 1;
}
