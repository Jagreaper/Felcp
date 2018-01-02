#include "XmlElement.hpp"

using namespace Jagerts::Felcp::Xml;

XmlElement::XmlElement(const std::string name)
{
	this->SetName(name);
}

XmlElement::XmlElement(const std::string name, const std::vector<XmlAttribute> attributes)
{
	this->SetName(name);
	this->_attributes = attributes;
}

XmlElement::XmlElement(const std::string name, const std::string value)
{
	this->SetName(name);
	this->_value = value;
}

XmlElement::XmlElement(const std::string name, const std::vector<XmlElement>& elements)
{
	this->SetName(name);
	this->_elements = elements;
}

XmlElement::XmlElement(const std::string name, const std::string value, const std::vector<XmlAttribute> attributes)
{
	this->SetName(name);
	this->_value = value;
	this->_attributes = attributes;
}

XmlElement::XmlElement(const std::string name, const std::vector<XmlElement>& elements, const std::vector<XmlAttribute> attributes)
{
	this->SetName(name);
	this->_elements = elements;
	this->_attributes = attributes;
}

const bool XmlElement::HasChildren() const
{
	return this->_value.size() > 0 || this->_elements.size() > 0;
}

const bool XmlElement::HasElementChildren() const
{
	return this->_elements.size() > 0;
}

const bool XmlElement::HasAttributes() const
{
	return this->_attributes.size() > 0;
}

const std::vector<XmlAttribute>* XmlElement::GetAttributes() const
{
	return &this->_attributes;
}

const std::vector<XmlElement>* XmlElement::GetChildren() const
{
	if (!this->HasChildren() || !this->HasElementChildren())
		return NULL;
	else
		return (const std::vector<XmlElement>*)this->InternalGetChildren();
}

const std::vector<XmlAttribute> XmlElement::GetAttributes(const std::string name) const
{
	std::vector<XmlAttribute> attributes;
	for (const XmlAttribute& attribute : this->_attributes)
	{
		if (attribute.Name == name)
			attributes.push_back(attribute);
	}
	return attributes;
}

const std::vector<XmlElement> XmlElement::GetChildren(const std::string name) const
{
	std::vector<XmlElement> elements;

	if (!this->HasChildren() || !this->HasElementChildren())
		return elements;

	for (const XmlElement& element : this->_elements)
	{
		if (element.GetName() == name)
			elements.push_back(element);
	}
	return elements;
}

const std::string* XmlElement::GetChild() const
{
	if (!this->HasChildren() || this->HasElementChildren())
		return NULL;
	else
		return (const std::string*)this->InternalGetChildren();
}

const void* XmlElement::InternalGetChildren() const
{
	if (!this->HasChildren())
		return NULL;

	if (this->HasElementChildren())
		return &this->_elements;
	else
		return &this->_value;
}

void XmlElement::AddAttribute(const XmlAttribute& attribute)
{
	this->_attributes.push_back(attribute);
}

void XmlElement::AddElement(const XmlElement& element)
{
	this->_elements.push_back(element);
	this->_value = "";
}

void XmlElement::SetValue(const std::string& value)
{
	this->_value = value;
	this->_elements.clear();
}

void XmlElement::Clear()
{
	this->SetName("");
	this->_value.clear();
	this->_attributes.clear();
	this->_elements.clear();
}