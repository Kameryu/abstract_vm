#pragma once

enum	eOperandType {
	Int8,
	Int16,
	Int32,
	Float,
	Double,
};

enum	eInstruction {
	NoOp,
	Push,
	Pop,
	Dump,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Exit,
	Terminate,
};
