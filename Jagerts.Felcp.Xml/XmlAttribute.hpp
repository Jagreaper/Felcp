#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include <string>

namespace Jagerts::Felcp::Xml
{
	struct JAGERTS_FELCP_XML_API XmlAttribute
	{
		XmlAttribute(const std::string name, const std::string value)
		{
			this->Name = name;
			this->Value = value;
		}

		std::string Name;
		std::string Value;
	};
}