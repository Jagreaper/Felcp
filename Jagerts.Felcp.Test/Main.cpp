#include "Jagerts.Felcp.Xml/XmlFile.hpp"
#include "Jagerts.Felcp.Xml/XmlObject.hpp"
#include "Jagerts.Felcp.IO/File.hpp"
#include "Jagerts.Felcp.IO/Environment.hpp"
#include "Jagerts.Felcp.IO.Xml/XmlEncoder.hpp"
#include "Jagerts.Felcp.IO.Xml/XmlDecoder.hpp"
#include "Jagerts.Felcp.IO.Imaging/ImageDecoder.hpp"
#include "Jagerts.Felcp.IO.Archive/ArchiveEncoder.hpp"
#include "Jagerts.Felcp.IO.Archive/ArchiveDecoder.hpp"
#include "Jagerts.Felcp.IO.Archive/ArchiveFile.hpp"
#include "Jagerts.Felcp.IO.Archive/ArchiveFileItem.hpp"
#include <iostream>
#include <string>

using namespace Jagerts::Felcp::Xml;
using namespace Jagerts::Felcp::IO;
using namespace Jagerts::Felcp::IO::Xml;
using namespace Jagerts::Felcp::IO::Imaging;
using namespace Jagerts::Felcp::IO::Archive;

class XmlGameObject : public XmlObject
{
public:
	void Register()
	{
		this->SetName("GameObject");
		this->RegisterAttribute("Health", &this->_health);
		this->RegisterAttribute("Armor", &this->_armor);
		this->RegisterArray("GameObject", &this->GameObjects, std::bind(&XmlGameObject::XmlConstructor, this));
		this->RegisterValue(&this->_value);
	}

	jfxXmlArrayConstructorHeader(XmlGameObject, this->GameObjects);
	jfxXmlObjectAddHeader(XmlGameObject, 0);

	std::vector<XmlGameObject> GameObjects;
private:
	float _health = 0;
	double _armor = 0;
	std::string _value = "";
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

	std::string xml_path = Environment::GetPath(Environment::Directory::Desktop) + "/Xml Test.xml";
	XmlEncoder xml_encoder;
	xml_encoder.TryEncode(xml_path.c_str(), &xml);
}

void DecodeXml()
{
	XmlFile xml;
	std::string xml_path = Environment::GetPath(Environment::Directory::Desktop) + "/Xml Test.xml";
	XmlDecoder xml_decoder;
	xml_decoder.TryDecode(xml_path.c_str(), &xml);
}

void SerializeXml()
{
	XmlElement element;
	XmlGameObject game_object;
	game_object.Register();
	game_object.Add(game_object);
	game_object.Serialize(&element);
	XmlFile xml;
	xml.AddElement(element);

	std::string xml_path = Environment::GetPath(Environment::Directory::Desktop) + "/Xml Test.xml";
	XmlEncoder xml_encoder;
	xml_encoder.TryEncode(xml_path.c_str(), &xml);
}

void DerializeXml()
{
	XmlFile xml;
	std::string xml_path = Environment::GetPath(Environment::Directory::Desktop) + "/Xml Test.xml";
	XmlDecoder xml_decoder;
	xml_decoder.TryDecode(xml_path.c_str(), &xml);

	XmlGameObject game_object;
	game_object.Register();
	game_object.Deserialize(xml.GetElements()->at(0));
}

void ArchiveEncoderTest()
{
	ArchiveFile archive;

	File file(Environment::GetPath(Environment::Directory::Desktop) + "/Xml Test.xml");
	ArchiveFileItem* item = ArchiveFileItem::Create(file.GetSize());
	file.ReadAll(item->GetData());
	item->SetName("Xml Test");
	item->SetExtension("xml");

	std::cout << item->GetData() << "\n";
	
	archive.AddFile(ArchiveFileItemType::Managed, item);

	std::string jarc_path = Environment::GetPath(Environment::Directory::Desktop) + "/Xml Test.jarc";
	ArchiveEncoder encoder;
	encoder.TryEncode(jarc_path.c_str(), &archive);
}

void ArchiveDecoderTest()
{
	ArchiveFile archive;

	std::string jarc_path = Environment::GetPath(Environment::Directory::Desktop) + "/Xml Test.jarc";
	ArchiveDecoder decoder;
	decoder.TryDecode(jarc_path.c_str(), &archive);
}

#if defined(_WIN32) && defined(RELEASE)
#include <Windows.h>
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else
int main()
#endif
{
	ArchiveEncoderTest();
	ArchiveDecoderTest();
}