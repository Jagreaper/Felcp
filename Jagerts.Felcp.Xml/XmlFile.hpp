#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include <string>
#include <vector>

namespace Jagerts::Felcp::Xml
{
	struct JAGERTS_FELCP_XML_API XmlAttribute
	{
		XmlAttribute(const std::string name, const std::string value);
		std::string Name;
		std::string Value;
	};

	class JAGERTS_FELCP_XML_API XmlElement
	{
	public:
		XmlElement() { };
		XmlElement(const std::string name);
		XmlElement(const std::string name, const std::vector<XmlAttribute> attributes);
		XmlElement(const std::string name, const std::string value);
		XmlElement(const std::string name, const std::vector<XmlElement>& elements);
		XmlElement(const std::string name, const std::string value, const std::vector<XmlAttribute> attributes);
		XmlElement(const std::string name, const std::vector<XmlElement>& elements, const std::vector<XmlAttribute> attributes);

		const bool HasChildren() const;
		const bool HasElementChildren() const;
		const bool HasAttributes() const;

		const std::vector<XmlAttribute>* GetAttributes() const;
		const std::vector<XmlElement>* GetChildren() const;
		const std::vector<XmlAttribute> GetAttributes(const std::string name) const;
		const std::vector<XmlElement> GetChildren(const std::string name) const;
		const std::string* GetChild() const;
		const std::string& GetName() const;

		void AddAttribute(const XmlAttribute& attribute);
		void AddElement(const XmlElement& element);
		void SetValue(const std::string& value);
		void SetName(const std::string& name);

		void Clear();
	private:
		const void* InternalGetChildren() const;

		std::vector<XmlAttribute> _attributes;
		std::vector<XmlElement> _elements;
		std::string _name;
		std::string _value;
	};

	class JAGERTS_FELCP_XML_API XmlFile
	{
	public:
		const std::vector<XmlElement>* GetElements() const;
		const std::vector<XmlElement> GetElements(const std::string name) const;

		void AddElement(const XmlElement& element);

		static void FromString(const std::string& string, XmlFile* file);
		void ToString(std::string* string);
		void Clear();
	private:
		std::vector<XmlElement> _elements;
	};
}