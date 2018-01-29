#pragma once

#include "Jagerts.Felcp.Xml/XmlAttribute.hpp"
#include "Jagerts.Felcp.Xml/XmlElement.hpp"

namespace Jagerts::Felcp::Xml
{
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