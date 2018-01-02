#include "XmlFile.hpp"
#include <algorithm>

using namespace Jagerts::Felcp::Xml;

XmlAttribute::XmlAttribute(const std::string name, const std::string value)
{
	this->Name = name;
	this->Value = value;
}

XmlElement::XmlElement(const std::string name)
{
	this->_name = name;
}

XmlElement::XmlElement(const std::string name, const std::vector<XmlAttribute> attributes)
{
	this->_name = name;
	this->_attributes = attributes;
}

XmlElement::XmlElement(const std::string name, const std::string value)
{
	this->_name = name;
	this->_value = value;
}

XmlElement::XmlElement(const std::string name, const std::vector<XmlElement>& elements)
{
	this->_name = name;
	this->_elements = elements;
}

XmlElement::XmlElement(const std::string name, const std::string value, const std::vector<XmlAttribute> attributes)
{
	this->_name = name;
	this->_value = value;
	this->_attributes = attributes;
}

XmlElement::XmlElement(const std::string name, const std::vector<XmlElement>& elements, const std::vector<XmlAttribute> attributes)
{
	this->_name = name;
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

const std::string& XmlElement::GetName() const
{
	return this->_name;
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

void XmlElement::SetName(const std::string& name)
{
	this->_name = name;
}


const std::vector<XmlElement>* XmlFile::GetElements() const
{
	return &this->_elements;
}

const std::vector<XmlElement> XmlFile::GetElements(const std::string name) const
{
	std::vector<XmlElement> elements;
	for (const XmlElement& element : this->_elements)
	{
		if (element.GetName() == name)
			elements.push_back(element);
	}
	return elements;
}

void XmlFile::AddElement(const XmlElement& element)
{
	this->_elements.push_back(element);
}

XmlElement ParseElementString(const char*& str_ptr)
{
	std::string tag_name;
	while (isalnum(*(++str_ptr)))
		tag_name += *str_ptr;

	XmlElement element(tag_name);

	if (!isspace(*str_ptr) && *str_ptr != '/' && *str_ptr != '>')
		throw std::runtime_error("Bad xml formatting");

	while (*str_ptr != '/' && *str_ptr != '>')
	{
		while (isspace(*str_ptr))
			str_ptr++;

		std::string attr_name;
		while (isalnum(*(str_ptr)))
			attr_name += *str_ptr++;

		if (*str_ptr != '=')
			throw std::runtime_error("Bad xml formatting");

		if (*(++str_ptr) != '\"')
			throw std::runtime_error("Bad xml formatting");

		std::string attr_value;
		while (*(++str_ptr) != '\"')
			attr_value += *str_ptr;

		str_ptr++;

		element.AddAttribute(XmlAttribute(attr_name, attr_value));
	}

	if (*str_ptr == '>')
	{
		std::string tag_value;
		while (*(++str_ptr) != '<')
			tag_value += *str_ptr;

		bool ruuning = true;

		while (ruuning)
		{
			if (*str_ptr == '<')
			{
				if (*(++str_ptr) != '/')
				{
					if (!std::all_of(tag_value.begin(), tag_value.end(), isspace))
						throw std::runtime_error("Bad xml formatting");

					element.AddElement(ParseElementString(--str_ptr));
				}
				else
				{
					std::string end_tag_name;
					while (isalnum(*(++str_ptr)))
						end_tag_name += *str_ptr;

					while (isspace(*str_ptr))
						str_ptr++;

					if (*str_ptr != '>')
						throw std::runtime_error("Bad xml formatting");

					if (tag_name != end_tag_name)
						throw std::runtime_error("Bad xml formatting");

					if (!std::all_of(tag_value.begin(), tag_value.end(), isspace) && element.HasElementChildren())
						throw std::runtime_error("Bad xml formatting");

					if (!std::all_of(tag_value.begin(), tag_value.end(), isspace) && !element.HasElementChildren())
						element.SetValue(tag_value);

					return element;
				}
			}

			*str_ptr++;
		}
	}
	else if (*str_ptr == '/')
	{
		if (*(++str_ptr) != '>')
			throw std::runtime_error("Bad xml formatting");

		return element;
	}
}

void XmlFile::FromString(const std::string& string, XmlFile* file)
{
	file->_elements.clear();
	const char* str_ptr = string.c_str();
	const char* str_ptr_end = str_ptr + (string.size() - 1);
	while (str_ptr <= str_ptr_end)
	{
		if (*str_ptr == '<')
			file->AddElement(ParseElementString(str_ptr));
		else if (!isspace(*str_ptr))
			throw std::runtime_error("Bad xml formatting");

		str_ptr++;
	}

}

void ParseElementAttributes(const XmlElement& element, std::string* const& output_str, unsigned int indenting)
{
	if (element.HasAttributes())
	{
		for (const XmlAttribute& attribute : *element.GetAttributes())
		{
			*output_str += " ";
			*output_str += attribute.Name;
			*output_str += "=\"";
			*output_str += attribute.Value;
			*output_str += "\"";
		}
	}
}

void ParseElement(const XmlElement& element, std::string* const& output_str, unsigned int indenting = 0)
{
	std::string indenting_str;

	for (int index = 0; index < indenting; index++)
		indenting_str += "  ";

	*output_str += indenting_str;
	*output_str += "<";
	*output_str += element.GetName();

	ParseElementAttributes(element, output_str, indenting);

	if (!element.HasChildren())
	{
		*output_str += "/>";
	}
	else
	{
		*output_str += ">";
		if (element.HasElementChildren())
		{
			*output_str += "\n";
			for (const XmlElement& element : *element.GetChildren())
				ParseElement(element, output_str, indenting + 1);
		}
		else
			*output_str += *element.GetChild();

		*output_str += "</";
		*output_str += element.GetName();
		*output_str += ">";
	}

	*output_str += "\n";
}

void XmlFile::ToString(std::string* string)
{
	string->clear();

	for (const XmlElement& element : this->_elements)
		ParseElement(element, string);
}