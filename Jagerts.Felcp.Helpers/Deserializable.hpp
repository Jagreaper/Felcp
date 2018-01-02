#pragma once

namespace Jagerts::Felcp::Helpers
{
	template<class T>
	class Deserializable
	{
	public:
		virtual void Deserialize(const T& input) = 0;
	};
}