#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"

#define jfxUsingXmlValueTypeObject \
using XmlValueTypeObject::SetValue; \
using XmlValueTypeObject::GetValue; \
using XmlValueTypeObject::SetType; \
using XmlValueTypeObject::GetType \

namespace Jagerts::Felcp::Xml
{
	enum class XmlObjectValueType
	{
		Short,
		UShort,
		Int,
		UInt,
		LongLong,
		ULongLong,
		Float,
		Double,
		Boolean,
		String,
	};

	class JAGERTS_FELCP_XML_API XmlValueTypeObject
	{
	public:
		void SetValue(void* const value);
		void* const& GetValue() const;
		void SetType(const XmlObjectValueType type);
		const XmlObjectValueType& GetType() const;
	private:
		void* _value = nullptr;
		XmlObjectValueType _type;
	};
}