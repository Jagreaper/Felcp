#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include "Jagerts.Felcp.Xml\XmlNamedObject.hpp"
#include "Jagerts.Felcp.Xml\XmlValueTypeObject.hpp"

namespace Jagerts::Felcp::Xml
{
	class JAGERTS_FELCP_XML_API XmlObjectAttribute : public XmlNamedObject, public XmlValueTypeObject
	{
	public:
		XmlObjectAttribute(std::string name, void* value, XmlObjectValueType type);
		jfxUsingXmlNamedObject;
		jfxUsingXmlValueTypeObject;
	};
}
