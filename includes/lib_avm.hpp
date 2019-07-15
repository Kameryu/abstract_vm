#pragma once

#include "Env.hpp"

#include <string>

void	fn_push(Env *env, eOperandType type, std::string const& value);
void	fn_pop(Env *env);
void	fn_dump(Env *env);
void	fn_assert(Env *env, eOperandType type, std::string const& value);
void	fn_add(Env *env);
void	fn_sub(Env *env);
void	fn_mul(Env *env);
void	fn_div(Env *env);
void	fn_mod(Env *env);
void	fn_print(Env *env);
void	fn_exit(Env *env);

int		doOp(const Operator *op, Env *env);

void	from_stdin(void);
void	from_file(std::string const& file);
void	from_stdin_e(void);
void	from_file_e(std::string const& file);
int		parse(std::string str, Env *env, int cnt);
int		parse_e(std::string str, Env *env, std::deque<std::string> *err_line, int cnt);