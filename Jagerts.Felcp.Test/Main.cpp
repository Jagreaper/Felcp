#include "Jagerts.Felcp.Xml\XmlFile.hpp"
#include "Jagerts.Felcp.Xml\XmlObject.hpp"
#include "Jagerts.Felcp.IO.Xml\XmlEncoder.hpp"
#include "Jagerts.Felcp.IO.Xml\XmlDecoder.hpp"
#include "Jagerts.Felcp.IO.Imaging\ImageDecoder.hpp"

using namespace Jagerts::Felcp::Xml;
using namespace Jagerts::Felcp::IO::Xml;
using namespace Jagerts::Felcp::IO::Imaging;

class XmlGameObject : public XmlObject
{
public:
	XmlGameObject()
	{
		this->SetName("GameObject");
		this->RegisterAttribute("Health", &this->_health);
		this->RegisterAttribute("Armor", &this->_armor);
		this->RegisterArray("GameObject", &this->GameObjects, std::bind(&XmlGameObject::XmlConstructor, this));
		this->RegisterValue(&this->_value);
	}

	XmlGameObject* XmlConstructor()
	{
		this->GameObjects.push_back(XmlGameObject());
		return &this->GameObjects[this->GameObjects.size() - 1];
	}

	jfxXmlObjectAddHeader(XmlGameObject, 0);

	std::vector<XmlGameObject> GameObjects;
private:
	float _health = 10;
	double _armor = 5;
	std::string _value = "Hello World!";
};

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

void DecodeXml()
{
	XmlFile xml;
	const char* xml_path = "D:\\Users\\James\\Desktop\\Xml Test.xml";
	XmlDecoder xml_decoder;
	xml_decoder.TryDecode(xml_path, &xml);
}

void SerializeXml()
{
	XmlElement element;
	XmlGameObject game_object;
	game_object.Add(game_object);
	game_object.Serialize(&element);
}

#ifdef DEBUG
int main()
#endif
#ifdef RELEASE
#include <Windows.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#endif
{
	SerializeXml();
}