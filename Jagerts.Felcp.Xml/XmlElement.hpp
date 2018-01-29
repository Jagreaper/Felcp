#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.Xml/XmlAttribute.hpp"
#include "Jagerts.Felcp.Xml/XmlNamedObject.hpp"
#include <vector>

namespace Jagerts::Felcp::Xml
{
	class JAGERTS_FELCP_XML_API XmlElement : public XmlNamedObject
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

		void AddAttribute(const XmlAttribute& attribute);
		void AddElement(const XmlElement& element);
		void SetValue(const std::string& value);

		jfxUsingXmlNamedObject;

		void Clear();
	private:
		const void* InternalGetChildren() const;

		std::vector<XmlAttribute> _attributes;
		std::vector<XmlElement> _elements;
		std::string _value;
	};
}