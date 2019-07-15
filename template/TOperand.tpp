#include "IOperand.hpp"
#include "FOperand.hpp"
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <cmath>

template <class T> class Operand : public IOperand
{
	public:

		Operand(T value, eOperandType type)
			:_value(value), _type(type), _str(std::to_string(value)), _factory() { }
		Operand(Operand const& o) : Operand(o._value, o._type) { }

		virtual ~Operand(void) {}

		virtual int getPrecision(void) const
		{
			return static_cast<int>(_type);
		}

		virtual eOperandType getType(void) const { return _type; }
		virtual T getValue(void) const { return _value; }

		virtual IOperand const *operator+(IOperand const& rhs) const
		{
			auto const b = std::stod(rhs.toString());

			return _factory.createOperand(rhs.getType() > getType() ? rhs.getType() : getType(), _value + b);
		}

		virtual IOperand const *operator-(IOperand const& rhs) const
		{
			auto const b = std::stod(rhs.toString());

			return _factory.createOperand(rhs.getType() > getType() ? rhs.getType() : getType(), _value - b);
		}

		virtual IOperand const *operator*(IOperand const& rhs) const
		{
			auto const b = std::stod(rhs.toString());

			return _factory.createOperand(rhs.getType() > getType() ? rhs.getType() : getType(), _value * b);
		}

		virtual IOperand const *operator/(IOperand const& rhs) const
		{
			auto const b = std::stod(rhs.toString());
			if (fabs(b) < std::numeric_limits<double>::epsilon())
				throw std::domain_error("Divider operand can not be 0");

			return _factory.createOperand(rhs.getType() > getType() ? rhs.getType() : getType(), _value / b);
		}

		virtual IOperand const *operator%(IOperand const& rhs) const
		{
			if (_type >= eOperandType::Float || rhs.getType() >= eOperandType::Float)
				throw std::domain_error("Modulus operator require integer operands");
			if (static_cast<intmax_t>(std::stod(rhs.toString())) == 0)
				throw std::domain_error("Divider operand can not be 0");

			return _factory.createOperand(rhs.getType() > getType() ? rhs.getType() : getType(), std::fmod(static_cast<intmax_t>(_value), static_cast<intmax_t>(std::stod(rhs.toString()))));
		}

		virtual std::string const& toString(void) const
		{
			return (_str);
		}

		Operand(IOperand& o) = delete;

	private:
		const T				_value;
		const eOperandType	_type;
		const std::string	_str;
		const FOperand		_factory;

		Operand(void);
};
