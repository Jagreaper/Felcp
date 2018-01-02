#include "XmlValueTypeObject.hpp"

using namespace Jagerts::Felcp::Xml;

void XmlValueTypeObject::SetValue(void* const value)
{
	this->_value = value;
}

void* const& XmlValueTypeObject::GetValue() const
{
	return this->_value;
}

void XmlValueTypeObject::SetType(const XmlObjectValueType type)
{
	this->_type = type;
}

const XmlObjectValueType& XmlValueTypeObject::GetType() const
{
	return this->_type;
}