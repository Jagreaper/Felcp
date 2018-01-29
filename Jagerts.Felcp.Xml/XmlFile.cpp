#include "XmlFile.hpp"
#include <algorithm>

using namespace Jagerts::Felcp::Xml;

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

void ParseElementAttributesString(XmlElement& element, const char*& str_ptr)
{
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
}

void ParseElementOpenTagNameString(std::string& tag_name, const char*& str_ptr)
{
	while (isalnum(*(++str_ptr)))
		tag_name += *str_ptr;
}

XmlElement ParseElementString(const char*& str_ptr)
{
	std::string tag_name;
	ParseElementOpenTagNameString(tag_name, str_ptr);

	XmlElement element(tag_name);
	ParseElementAttributesString(element, str_ptr);

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

			str_ptr++;
		}
	}
	else if (*str_ptr == '/')
	{
		if (*(++str_ptr) != '>')
			throw std::runtime_error("Bad xml formatting");

		return element;
	}

	throw std::runtime_error("Bad xml formatting");
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

	for (unsigned int index = 0; index < indenting; index++)
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

void XmlFile::Clear()
{
	this->_elements.clear();
}