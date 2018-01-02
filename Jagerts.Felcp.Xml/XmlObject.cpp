#include "XmlObject.hpp"
#include "Jagerts.Felcp.Helpers\VectorHelper.hpp"
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>

using namespace Jagerts::Felcp::Xml;

XmlObjectAttribute::XmlObjectAttribute(std::string name, void* value, XmlObjectAttributeType type)
{
	this->SetName(name);
	this->_value = value;
	this->_type = type;
}

void XmlNamedObject::SetName(const std::string name)
{
	this->_name = name;
}

const std::string& XmlNamedObject::GetName() const
{
	return this->_name;
}

void XmlObjectAttribute::SetValue(void* const value)
{
	this->_value = value;
}

void* const& XmlObjectAttribute::GetValue() const
{
	return this->_value;
}

void XmlObjectAttribute::SetType(const XmlObjectAttributeType type)
{
	this->_type = type;
}

const XmlObjectAttributeType& XmlObjectAttribute::GetType() const
{
	return this->_type;
}

std::vector<XmlObject*>* XmlObjectArray::GetElements()
{
	return &this->_elements;
}

XmlObject* XmlObjectArray::Add()
{
	XmlObject* ptr = this->_constr();
	this->_elements.push_back(ptr);
	return ptr;
}

void XmlObjectArray::Clear()
{
	this->_name.clear();
	this->_elements.clear();
	this->_constr = NULL;
}

#define _CAST_NUMBER_CASE(TYPE, ATTRIBUTE, VALUE) \
case XmlObjectAttributeType::ATTRIBUTE: \
{ \
		std::ostringstream stream; \
		stream << *(TYPE*)VALUE; \
		return stream.str(); \
} \

std::string CastToString(void* value, const XmlObjectAttributeType& type)
{
	switch (type)
	{
	_CAST_NUMBER_CASE(short, Short, value)
	_CAST_NUMBER_CASE(unsigned short, UShort, value)
	_CAST_NUMBER_CASE(int, Int, value)
	_CAST_NUMBER_CASE(unsigned int, UInt, value)
	_CAST_NUMBER_CASE(long long, LongLong, value)
	_CAST_NUMBER_CASE(unsigned long long, ULongLong, value)
	case XmlObjectAttributeType::Float:
	{
		std::ostringstream stream;
		stream << *(float*)value;
		return stream.str();
	}
	_CAST_NUMBER_CASE(double, Double, value)
	case XmlObjectAttributeType::Boolean:
	{
		bool c_value = (*(bool*)value);
		return c_value ? "true" : "false";
	}
	case XmlObjectAttributeType::String:
		return (*(std::string*)value);
	default:
		throw new std::runtime_error("Type not supported expection");
	}
	return "";
}
#undef _CAST_NUMBER_CASE

void XmlObject::Serialize(XmlElement* output)
{
	output->Clear();
	for (const XmlObjectAttribute& attribute : this->_attributes)
		output->AddAttribute(XmlAttribute(attribute.GetName(), CastToString(attribute.GetValue(), attribute.GetType())));

	for (int index = 0; index < this->_elements.size(); index++)
	{
		XmlElement element;
		this->_elements[index]->Serialize(&element);
		output->AddElement(element);
	}

	for (int index = 0; index < this->_elements_array.size(); index++)
	{
		for (XmlObjectArray& object_array : this->_elements_array)
		{
			if (object_array.GetElements()->size() > 0)
			{
				for (XmlObject*& object : *object_array.GetElements())
				{
					XmlElement element;
					object->Serialize(&element);
					output->AddElement(element);
				}
			}
		}
	}

	if (this->_value != NULL && this->_elements.size() == 0 && this->_elements_array.size() == 0)
		output->SetValue(CastToString(this->_value, this->_type));
}

#define _DEFAULT_NUMBER_CASE(TYPE, ATTRIBUTE, VALUE) \
case XmlObjectAttributeType::ATTRIBUTE: \
{ \
	*(TYPE*)VALUE = 0; \
	break; \
} \

void SetDefaultValue(void* value, const XmlObjectAttributeType& type)
{
	switch (type)
	{
	_DEFAULT_NUMBER_CASE(short, Short, value)
	_DEFAULT_NUMBER_CASE(unsigned short, UShort, value)
	_DEFAULT_NUMBER_CASE(int, Int, value)
	_DEFAULT_NUMBER_CASE(unsigned int, UInt, value)
	_DEFAULT_NUMBER_CASE(long long, LongLong, value)
	_DEFAULT_NUMBER_CASE(unsigned long long, ULongLong, value)
	_DEFAULT_NUMBER_CASE(short, Float, value)
	_DEFAULT_NUMBER_CASE(short, Double, value)
	case XmlObjectAttributeType::Boolean:
	{
		*(bool*)value = false;
		break;
	}
	case XmlObjectAttributeType::String:
	{
		*(std::string*)value = "";
		break;
	}
	default:
		throw new std::runtime_error("Type not supported expection");
	}
}
#undef _DEFAULT_NUMBER_CASE

void CastFromString(void* value, XmlObjectAttributeType type, std::string string)
{
	*(double*)value = std::stod(string);
	switch (type)
	{
	case XmlObjectAttributeType::Short:
	{
		*(short*)value = (short)std::stoi(string);
		break;
	}
	case XmlObjectAttributeType::UShort:
	{
		*(unsigned short*)value = (unsigned short)std::stoi(string);
		break;
	}
	case XmlObjectAttributeType::Int:
	{
		*(int*)value = (short)std::stoi(string);
		break;
	}
	case XmlObjectAttributeType::UInt:
	{
		*(unsigned int*)value = (unsigned int)std::stoul(string);
		break;
	}
	case XmlObjectAttributeType::LongLong:
	{
		*(long long*)value = (long long)std::stoll(string);
		break;
	}
	case XmlObjectAttributeType::ULongLong:
	{
		*(unsigned long long*)value = (unsigned long long)std::stoull(string);
		break;
	}
	case XmlObjectAttributeType::Float:
	{
		*(float*)value = (float)std::stof(string);
		break;
	}
	case XmlObjectAttributeType::Double:
	{
		*(double*)value = (double)std::stod(string);
		break;
	}
	case XmlObjectAttributeType::Boolean:
	{
		*(std::string*)value = (string == "true" || string == "1") ? true : false;
		break;
	}
	case XmlObjectAttributeType::String:
	{
		*(std::string*)value = string;
		break;
	}
	default:
		throw new std::runtime_error("Type not supported expection");
	}
}

void XmlObject::Deserialize(const XmlElement& input)
{
	for (int index = 0; index < this->_attributes.size(); index++)
	{
		XmlObjectAttribute& attribute = this->_attributes[index];
		SetDefaultValue(attribute.GetValue(), attribute.GetType());
	}

	for (const XmlAttribute& attribute : *input.GetAttributes())
	{
		for (int index = 0; index < this->_attributes.size(); index++)
		{
			const XmlObjectAttribute& o_attribute = this->_attributes[index];
			if (o_attribute.GetName() == attribute.Name)
				CastFromString(o_attribute.GetValue(), o_attribute.GetType(), attribute.Value);
		}
	}

	if (input.HasElementChildren())
	{
		const std::vector<XmlElement>* elements = input.GetChildren();
		for (int index = 0; index < elements->size(); index++)
		{
			const XmlElement& element = elements->at(index);
			for (XmlObject*& object : this->_elements)
			{
				if (object->GetName() == element.GetName())
					object->Deserialize(element);
			}

			for (XmlObjectArray& object_array : this->_elements_array)
			{
				if (object_array.GetName() == element.GetName())
				{
					XmlObject* object = object_array._constr();
					object->Deserialize(element);
					object_array.GetElements()->push_back(object);
				}
			}
		}
	}

	if (input.HasChildren() && !input.HasElementChildren() && this->_value != NULL)
		CastFromString(this->_value, this->_type, *input.GetChild());
}

#define _REGISTER_ATTRIBUTE_TYPE(TYPE, ENUM_TYPE) \
void XmlObject::RegisterAttribute(const std::string name, TYPE* value) \
{ \
	this->_attributes.push_back(XmlObjectAttribute(name, value, XmlObjectAttributeType::ENUM_TYPE)); \
} \

_REGISTER_ATTRIBUTE_TYPE(short, Short)
_REGISTER_ATTRIBUTE_TYPE(unsigned short, UShort)
_REGISTER_ATTRIBUTE_TYPE(int, Int)
_REGISTER_ATTRIBUTE_TYPE(unsigned int, UInt)
_REGISTER_ATTRIBUTE_TYPE(long long, LongLong)
_REGISTER_ATTRIBUTE_TYPE(unsigned long long, ULongLong)
_REGISTER_ATTRIBUTE_TYPE(float, Float)
_REGISTER_ATTRIBUTE_TYPE(double, Double)
_REGISTER_ATTRIBUTE_TYPE(bool, Boolean)
_REGISTER_ATTRIBUTE_TYPE(std::string, String)
#undef REGISTER_ATTRIBUTE_TYPE

void XmlObject::RegisterElement(XmlObject* element)
{
	this->_elements.push_back(element);
}

void XmlObject::Clear()
{
	this->_attributes.clear();
	this->_elements.clear();
	this->_elements_array.clear();
	this->_name.clear();
	this->_value = NULL;
}

std::vector<XmlObjectArray>* XmlObject::GetElementsArray()
{
	return &this->_elements_array;
}

#define _REGISTER_VALUE_TYPE(TYPE, ENUM_TYPE) \
void XmlObject::RegisterValue(TYPE* value) \
{ \
	this->_value = (void*)value; \
	this->_type = XmlObjectAttributeType::ENUM_TYPE; \
} \

_REGISTER_VALUE_TYPE(short, Short)
_REGISTER_VALUE_TYPE(unsigned short, UShort)
_REGISTER_VALUE_TYPE(int, Int)
_REGISTER_VALUE_TYPE(unsigned int, UInt)
_REGISTER_VALUE_TYPE(long long, LongLong)
_REGISTER_VALUE_TYPE(unsigned long long, ULongLong)
_REGISTER_VALUE_TYPE(float, Float)
_REGISTER_VALUE_TYPE(double, Double)
_REGISTER_VALUE_TYPE(bool, Boolean)
_REGISTER_VALUE_TYPE(std::string, String)
#undef REGISTER_ATTRIBUTE_TYPE