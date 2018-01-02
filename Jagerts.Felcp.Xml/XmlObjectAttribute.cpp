#include "XmlObjectAttribute.hpp"

using namespace Jagerts::Felcp::Xml;

XmlObjectAttribute::XmlObjectAttribute(std::string name, void* value, XmlObjectValueType type)
{
	this->SetName(name);
	this->SetValue(value);
	this->SetType(type);
}