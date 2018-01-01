#pragma once

#include <ostream>

namespace Jagerts::Felcp::IO
{
	template<class SourceType, class InputType, class ArgumentType>
	class EncoderBase
	{
	public:
		virtual bool TryEncode(SourceType source, InputType input, ArgumentType arg = NULL) = 0;
	};

	template<class InputType, class ArgumentType>
	using StreamEncoderBase = EncoderBase<std::ostream&, InputType, ArgumentType>;

	template<class InputType, class ArgumentType>
	using PathEncoderBase = EncoderBase<const char*, InputType, ArgumentType>;
}