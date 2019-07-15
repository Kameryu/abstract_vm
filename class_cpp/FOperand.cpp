#include "FOperand.hpp"
#include "../template/TOperand.tpp"
#include <string>
#include <cstdint>
#include <functional>

FOperand::FOperand(void) {}
FOperand::~FOperand(void) {}

IOperand const *FOperand::createOperand(eOperandType type, std::string const& value) const
{
	IOperand const *(FOperand::*fs[])(std::string const&) const = 
	{
		&FOperand::createInt8,
		&FOperand::createInt16,
		&FOperand::createInt32,
		&FOperand::createFloat,
		&FOperand::createDouble,
	};
	return std::invoke(fs[static_cast<int>(type)], this, value);
}

IOperand const *FOperand::createInt8(std::string const& value) const
{
	return new Operand<int8_t>(std::stoll(value), eOperandType::Int8);
}

IOperand const *FOperand::createInt16(std::string const& value) const
{
	return new Operand<int16_t>(std::stoll(value), eOperandType::Int16);
}

IOperand const *FOperand::createInt32(std::string const& value) const
{
	return new Operand<int32_t>(std::stoll(value), eOperandType::Int32);
}

IOperand const *FOperand::createFloat(std::string const& value) const
{
	return new Operand<float>(std::stof(value), eOperandType::Float);
}

IOperand const *FOperand::createDouble(std::string const& value) const
{
	return new Operand<double>(std::stod(value), eOperandType::Double);
}
