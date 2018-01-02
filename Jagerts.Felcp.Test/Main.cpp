#include "Jagerts.Felcp.Xml\XmlFile.hpp"
#include "Jagerts.Felcp.IO.Xml\XmlEncoder.hpp"

using namespace Jagerts::Felcp::Xml;
using namespace Jagerts::Felcp::IO::Xml;

void EncodeXml()
{
	XmlFile xml;
	XmlElement element("GameObject", "Hello World!");
	element.AddAttribute(XmlAttribute("armor", "5"));
	element.AddAttribute(XmlAttribute("health", "10"));
	element.AddElement(element);
	element.AddElement(XmlElement("GameObject"));
	xml.AddElement(element);

	const char* xml_path = "D:\\Users\\James\\Desktop\\Xml Test.xml";
	XmlEncoder xml_encoder;
	xml_encoder.TryEncode(xml_path, &xml);
}

#ifdef DEBUG
int main()
#endif
#ifdef RELEASE
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#endif
{
	EncodeXml();
}