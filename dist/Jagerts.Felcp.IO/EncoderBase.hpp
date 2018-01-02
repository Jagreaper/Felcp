#pragma once

#include <ostream>
#include <fstream>

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

	template<class InputType, class ArgumentType>
	class StreamPathEncoder : public StreamEncoderBase<InputType, ArgumentType>, public PathEncoderBase<InputType, ArgumentType>
	{
	public:
		virtual bool TryEncode(std::ostream& source, InputType input, ArgumentType arg = NULL) = 0;

		inline virtual bool TryEncode(const char* source, InputType input, ArgumentType arg = NULL)
		{
			std::ofstream stream;
			stream.open(source, std::ofstream::out | std::ofstream::trunc);
			bool success = this->TryEncode(stream, input, arg);
			stream.close();
			return success;
		}
	};
}