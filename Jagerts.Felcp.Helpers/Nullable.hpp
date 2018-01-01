#pragma once

namespace Kaleid::Helpers
{
	template <class T>
	class Nullable sealed
	{
	public:
		inline Nullable()
		{
			this->_null = true;
		}

		inline Nullable(const T& value)
		{
			this->_null = false;
			this->_value = value;
		}

		inline void MakeNull()
		{
			this->_null = true;
		}

		inline T& GetValue()
		{
			return this->_value;
		}

		inline bool IsNull()
		{
			return this->_null;
		}

		inline void operator=(const T& value)
		{
			this->_null = false;
			this->_value = value;
		}

		inline operator T&()
		{
			return this->_value;
		}

		inline operator T() const
		{
			return this->_value;
		}
	private:
		bool _null;
		T _value;
	};
}