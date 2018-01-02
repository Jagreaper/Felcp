#pragma once

#include "Jagerts.Felcp.Shared\Common.hpp"
#include <string>

#define jfxUsingXmlNamedObject \
using XmlNamedObject::SetName; \
using XmlNamedObject::GetName \

namespace Jagerts::Felcp::Xml
{
	class JAGERTS_FELCP_XML_API XmlNamedObject
	{
	public:
		void SetName(const std::string name);
		const std::string& GetName() const;
	private:
		std::string _name;
	};
}