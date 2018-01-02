#pragma once

namespace Jagerts::Felcp::Helpers
{
	template<class T>
	class Serializable
	{
	public:
		virtual void Serialize(T* output) = 0;
	};
}