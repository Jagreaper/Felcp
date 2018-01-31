#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.Helpers/Serializable.hpp"
#include "Jagerts.Felcp.Helpers/Deserializable.hpp"
#include "Jagerts.Felcp.Xml/XmlNamedObject.hpp"
#include "Jagerts.Felcp.Xml/XmlValueTypeObject.hpp"
#include "Jagerts.Felcp.Xml/XmlObjectAttribute.hpp"
#include "XmlFile.hpp"
#include <vector>
#include <functional>

/// Add Method Body
#define jfxXmlObjectAddBody(TYPE, INDEX) \
TYPE* ptr = (TYPE*)this->GetElementsArray()->at(INDEX).Add(); \
*ptr = game_object \
///

/// Add Header Definitions
#define jfxXmlObjAddNameHeaderDefine(NAME, TYPE) void NAME(const TYPE game_object)

#define jfxXmlObjectAddHeaderDefine(TYPE) jfxXmlObjAddNameHeaderDefine(Add, TYPE)

#define jfxXmlObjectAddNameHeader(NAME, TYPE, INDEX) \
jfxXmlObjAddNameHeaderDefine(NAME, TYPE) \
{ \
	jfxXmlObjectAddBody(TYPE, INDEX); \
} \

#define jfxXmlObjectAddHeader(TYPE, INDEX) jfxXmlObjectAddNameHeader(Add, TYPE, INDEX)
///

/// Add Source Definitions
#define jfxXmlObjAddNameSourceDefine(NAME, CLASS, TYPE) void CLASS::NAME(const TYPE game_object)

#define jfxXmlObjAddSourceDefine(CLASS, TYPE) jfxXmlObjAddNameSourceDefine(Add, CLASS, TYPE)

#define jfxXmlObjectAddNameSource(NAME, CLASS, TYPE, INDEX) \
jfxXmlObjAddNameSourceDefine(NAME, CLASS, TYPE) \
{ \
	jfxXmlObjectAddBody(TYPE, INDEX); \
} \

#define jfxXmlObjAddSource(CLASS, TYPE, INDEX) jfxXmlObjectAddNameSource(Add, CLASS, TYPE, INDEX)
///

/// Constructor Method Body
#define jfxXmlArrayConstructorBody(XML_OBJECT, ARRAY) \
ARRAY.push_back(XML_OBJECT()); \
XML_OBJECT* xml_object = &ARRAY[ARRAY.size() - 1]; \
xml_object->Register(); \
return xml_object \

#define jfxXmlArrayConstructorBodyPtr(XML_OBJECT, ARRAY) \
ARRAY->push_back(XML_OBJECT()); \
XML_OBJECT* xml_object = &(*ARRAY)[ARRAY->size() - 1]; \
xml_object->Register(); \
return xml_object \
///

/// Constructor Header Definitions
#define jfxXmlArrayConstructorNameHeaderDefine(NAME, XML_OBJECT) XML_OBJECT* NAME()

#define jfxXmlArrayConstructorHeaderDefine(XML_OBJECT) XML_OBJECT* jfxXmlArrayConstructorNameHeaderDefine(XmlConstructor, XML_OBJECT)

#define jfxXmlArrayConstructorNameHeader(NAME, XML_OBJECT, ARRAY) \
jfxXmlArrayConstructorNameHeaderDefine(NAME, XML_OBJECT) \
{ \
	jfxXmlArrayConstructorBody(XML_OBJECT, ARRAY); \
} \

#define jfxXmlArrayConstructorHeader(XML_OBJECT, ARRAY) jfxXmlArrayConstructorNameHeader(XmlConstructor, XML_OBJECT, ARRAY)
///

/// Constructor Source Definitions
#define jfxXmlArrayConstructorNameSourceDefine(NAME, CLASS, XML_OBJECT) XML_OBJECT* CLASS::NAME()

#define jfxXmlArrayConstructorSourceDefine(CLASS, XML_OBJECT) XML_OBJECT* jfxXmlArrayConstructorNameSourceDefine(XmlConstructor, CLASS, XML_OBJECT)

#define jfxXmlArrayConstructorNameSource(NAME, CLASS, XML_OBJECT, ARRAY) \
jfxXmlArrayConstructorNameSourceDefine(NAME, CLASS, XML_OBJECT) \
{ \
	jfxXmlArrayConstructorBody(XML_OBJECT, ARRAY); \
} \

#define jfxXmlArrayConstructorSource(CLASS, XML_OBJECT, ARRAY) jfxXmlArrayConstructorNameSource(XmlConstructor, CLASS, XML_OBJECT, ARRAY)
///

namespace Jagerts::Felcp::Xml
{
	using XmlElementSerializable = Jagerts::Felcp::Helpers::Serializable<XmlElement>;
	using XmlElementDeserializable = Jagerts::Felcp::Helpers::Deserializable<XmlElement>;

	class XmlObject;

	class JAGERTS_FELCP_XML_API XmlObjectArray : public XmlNamedObject
	{
	public:
		template<class XmlType>
		void Register(const std::vector<XmlType>* elements, std::function<XmlObject*()> constr)
		{
			for (unsigned int index = 0; index < (unsigned int)elements->size(); index++)
				this->_elements.push_back((XmlObject*)&(*elements)[index]);
			
			this->_constr = constr;
		}

		std::vector<XmlObject*>* GetElements();

		XmlObject* Add();
		void Clear();
		jfxUsingXmlNamedObject;
	private:
		std::string _name;
		std::vector<XmlObject*> _elements;
		std::function<XmlObject*()> _constr;

		friend class XmlObject;
	};

	class JAGERTS_FELCP_XML_API XmlObject : public XmlNamedObject, public XmlValueTypeObject, public XmlElementSerializable, public XmlElementDeserializable
	{
	public:
		virtual void Register() = 0;
		void Serialize(XmlElement* output);
		void Deserialize(const XmlElement& input);
	protected:
	#define REGISTER_ATTRIBUTE_TYPE(TYPE) \
		void RegisterAttribute(const std::string name, TYPE* value); \

		REGISTER_ATTRIBUTE_TYPE(short)
		REGISTER_ATTRIBUTE_TYPE(unsigned short)
		REGISTER_ATTRIBUTE_TYPE(int)
		REGISTER_ATTRIBUTE_TYPE(unsigned int)
		REGISTER_ATTRIBUTE_TYPE(long long)
		REGISTER_ATTRIBUTE_TYPE(unsigned long long)
		REGISTER_ATTRIBUTE_TYPE(float)
		REGISTER_ATTRIBUTE_TYPE(double)
		REGISTER_ATTRIBUTE_TYPE(bool)
		REGISTER_ATTRIBUTE_TYPE(std::string)
	#undef REGISTER_ATTRIBUTE_TYPE

#define REGISTER_VALUE_TYPE(TYPE) \
		void RegisterValue(TYPE* value); \

		REGISTER_VALUE_TYPE(short)
		REGISTER_VALUE_TYPE(unsigned short)
		REGISTER_VALUE_TYPE(int)
		REGISTER_VALUE_TYPE(unsigned int)
		REGISTER_VALUE_TYPE(long long)
		REGISTER_VALUE_TYPE(unsigned long long)
		REGISTER_VALUE_TYPE(float)
		REGISTER_VALUE_TYPE(double)
		REGISTER_VALUE_TYPE(bool)
		REGISTER_VALUE_TYPE(std::string)
#undef REGISTER_VALUE_TYPE
		void RegisterElement(XmlObject* element);

		template<class XmlType>
		void RegisterArray(const std::string name, const std::vector<XmlType>* elements, std::function<XmlObject*()> constr)
		{
			XmlObjectArray xml_array;
			xml_array.SetName(name);
			xml_array.Register(elements, constr);
			this->_elements_array.push_back(xml_array);
		}

		void Clear();
		std::vector<XmlObjectArray>* GetElementsArray();
		jfxUsingXmlValueTypeObject;
		jfxUsingXmlNamedObject;
	private:
		std::string _name;
		std::vector<XmlObjectAttribute> _attributes;
		std::vector<XmlObject*> _elements;
		std::vector<XmlObjectArray> _elements_array;
	};
}
