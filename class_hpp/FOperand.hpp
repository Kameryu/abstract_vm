#pragma once

#include "IOperand.hpp"

#include <string>

class FOperand
{
public:
	FOperand(void);
	~FOperand(void);

	IOperand const *createOperand(eOperandType type, std::string const& value) const;
	
	template<typename T>
	IOperand const *createOperand(eOperandType type, T value) const
	{
		return createOperand(type, std::to_string(value));
	}

private:
	IOperand const *createInt8(std::string const& value) const;
	IOperand const *createInt16(std::string const& value) const;
	IOperand const *createInt32(std::string const& value) const;
	IOperand const *createFloat(std::string const& value) const;
	IOperand const *createDouble(std::string const& value) const;
};
