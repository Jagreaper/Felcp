#include "XmlNamedObject.hpp"

using namespace Jagerts::Felcp::Xml;

void XmlNamedObject::SetName(const std::string name)
{
	this->_name = name;
}

const std::string& XmlNamedObject::GetName() const
{
	return this->_name;
}