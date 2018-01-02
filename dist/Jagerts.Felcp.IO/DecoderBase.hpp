#pragma once

#include <istream>
#include <fstream>

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

	template<class OutputType, class ArgumentType>
	class StreamPathDecoder : public StreamDecoderBase<OutputType, ArgumentType>, public PathDecoderBase<OutputType, ArgumentType>
	{
	public:
		virtual bool TryDecode(std::istream& source, OutputType output, ArgumentType arg = NULL) = 0;

		inline bool TryDecode(const char* source, OutputType output, ArgumentType arg = NULL)
		{
			std::ifstream stream;
			stream.open(source);
			bool success = this->TryDecode(stream, output, arg);
			stream.close();
			return success;
		}
	};
}