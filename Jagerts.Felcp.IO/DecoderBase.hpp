#pragma once

#include <istream>

namespace Jagerts::Felcp::IO
{
	template<class SourceType, class OutputType, class ArgumentType>
	class DecoderBase
	{
	public:
		virtual bool TryDecode(SourceType source, OutputType output, ArgumentType arg = NULL) = 0;
	};

	template<class OutputType, class ArgumentType>
	using StreamDecoderBase = DecoderBase<std::istream&, OutputType, ArgumentType>;

	template<class OutputType, class ArgumentType>
	using PathDecoderBase = DecoderBase<const char*, OutputType, ArgumentType>;
}