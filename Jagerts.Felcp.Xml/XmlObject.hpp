#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include "Jagerts.Felcp.Helpers\Serializable.hpp"
#include "Jagerts.Felcp.Helpers\Deserializable.hpp"
#include "Jagerts.Felcp.Xml\XmlNamedObject.hpp"
#include "Jagerts.Felcp.Xml\XmlValueTypeObject.hpp"
#include "Jagerts.Felcp.Xml\XmlObjectAttribute.hpp"
#include "XmlFile.hpp"
#include <vector>
#include <functional>

#define jfxXmlObjectAddBody(TYPE, INDEX) \
TYPE* ptr = (TYPE*)this->GetElementsArray()->at(INDEX).Add(); \
*ptr = game_object \

#define jfxXmlObjectAddHeaderDefine(TYPE) void Add(const TYPE game_object)

#define jfxXmlObjectAddHeader(TYPE, INDEX) \
jfxXmlObjectAddHeaderDefine(TYPE) \
{ \
	jfxXmlObjectAddBody(TYPE, INDEX); \
} \

#define jfxXmlObjAddSourceDefine(CLASS, TYPE) void CLASS::Add(const TYPE game_object)

#define jfxXmlObjAddSource(CLASS, TYPE, INDEX) \
jfxXmlObjAddSourceDefine(CLASS, TYPE) \
{ \
	jfxXmlObjectAddBody(TYPE, INDEX); \
} \

#define jfxXmlObjAddNameHeaderDefine(NAME, TYPE) void AddNAME(const TYPE game_object)

#define jfxXmlObjectAddNameHeader(NAME, TYPE, INDEX) \
jfxXmlObjAddNameHeaderDefine(NAME, TYPE) \
{ \
	jfxXmlObjectAddBody(TYPE, INDEX); \
} \

#define jfxXmlObjAddNameSourceDefine(NAME, CLASS, TYPE) void CLASS::AddNAME(const TYPE game_object)

#define jfxXmlObjectAddNameSource(NAME, CLASS, TYPE, INDEX) \
jfxXmlObjAddNameSourceDefine(NAME, CLASS, TYPE) \
{ \
	jfxXmlObjectAddBody(TYPE, INDEX); \
} \

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
			for (int index = 0; index < elements->size(); index++)
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
