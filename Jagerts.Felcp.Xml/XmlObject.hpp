#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include "XmlFile.hpp"
#include <vector>
#include <functional>

namespace Jagerts::Felcp::Xml
{
	template<class T>
	class Serializable
	{
	public:
		virtual void Serialize(T* output) = 0;
	};

	template<class T>
	class Deserializable
	{
	public:
		virtual void Deserialize(const T& input) = 0;
	};

	using XmlFileSerializable = Serializable<XmlFile>;
	using XmlFileDeserializable = Deserializable<XmlFile>;
	using XmlElementSerializable = Serializable<XmlElement>;
	using XmlElementDeserializable = Deserializable<XmlElement>;

	enum class XmlObjectAttributeType
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

	class JAGERTS_FELCP_XML_API XmlNamedObject
	{
	public:
		void SetName(const std::string name);
		const std::string& GetName() const;
	private:
		std::string _name;
	};

	class JAGERTS_FELCP_XML_API XmlObjectAttribute : public XmlNamedObject
	{
	public:
		XmlObjectAttribute(std::string name, void* value, XmlObjectAttributeType type);
		void SetValue(void* const value);
		void* const& GetValue() const;
		void SetType(const XmlObjectAttributeType type);
		const XmlObjectAttributeType& GetType() const;
		using XmlNamedObject::SetName;
		using XmlNamedObject::GetName;
	private:
		void* _value;
		XmlObjectAttributeType _type;
	};

	class XmlObject;

	class XmlObjectArray : public XmlNamedObject
	{
	public:
		template<class XmlType>
		void Register(std::vector<XmlType>* elements, std::function<XmlObject*()> constr)
		{
			for (int index = 0; index < elements->size(); index++)
				this->_elements->push_back(&(*elements)[index]);
			
			this->constr = _constr;
		}

		std::vector<XmlObject*>* const& GetElements() const;
		void Clear();
		using XmlNamedObject::SetName;
		using XmlNamedObject::GetName;
	private:
		std::string _name;
		std::vector<XmlObject*>* _elements = NULL;
		std::function<XmlObject*()> _constr;

		friend class XmlObject;
	};

	class JAGERTS_FELCP_XML_API XmlObject : public XmlNamedObject, public XmlElementSerializable, public XmlElementDeserializable, public XmlFileSerializable, public XmlFileDeserializable
	{
	public:
		void Serialize(XmlElement* output);
		void Deserialize(const XmlElement& input);
		void Serialize(XmlFile* output);
		void Deserialize(const XmlFile& input);
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
		void Clear();
		using XmlNamedObject::SetName;
		using XmlNamedObject::GetName;
	private:
		void* _value = NULL;
		XmlObjectAttributeType _type;
		std::string _name;
		std::vector<XmlObjectAttribute> _attributes;
		std::vector<XmlObject*> _elements;
		std::vector<XmlObjectArray> _elements_array;
	};
}
