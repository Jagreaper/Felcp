#include "ImageDecoder.hpp"
#include "Jagerts.Felcp.Imaging\Image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <STB\stb_image.h>

using namespace Jagerts::Felcp::IO;
using namespace Jagerts::Felcp::Imaging;

unsigned char* LoadImageFromFile(char const* file, int* width, int* height, int* channels, int req_comp)
{
	return stbi_load(file, width, height, channels, req_comp);
}

void FreeImage(unsigned char* data)
{
	stbi_image_free(data);
}

void RawImageData::Free(RawImageData* data)
{
	stbi_image_free(data->_data);
	data->_size = 0;
}

void RawImageData::SetData(unsigned char* data, int size)
{
	if (this->_data != NULL)
		RawImageData::Free(this);

	this->_size = size;
	this->_data = data;
}

void RawImageData::SetWidth(int width)
{
	this->_width = width;
}

void RawImageData::SetHeight(int height)
{
	this->_height = height;
}

void RawImageData::SetPixelSize(int pixel_size)
{
	this->_pixel_size = pixel_size;
}

const unsigned char* RawImageData::GetData() const
{
	return this->_data;
}

const int RawImageData::GetWidth() const
{
	return this->_width;
}

const int RawImageData::GetHeight() const
{
	return this->_height;
}

const int RawImageData::GetPixelSize() const
{
	return this->_pixel_size;
}

const size_t RawImageData::GetSize() const
{
	return this->_size;
}

void RawImageData::ToImage(Image* image)
{
	image->SetSize(this->_width, this->_height);
	image->SetData(this->_data, this->_size);
	if (this->_pixel_size == 1)
	{
		ChannelInfo info[1];
		info[0].Type = ChannelType::Gray;
		image->SetChannels(info, this->_pixel_size);
	}
	else if (this->_pixel_size == 2)
	{
		ChannelInfo info[2];
		info[0].Type = ChannelType::Gray;
		info[1].Type = ChannelType::Alpha;
		image->SetChannels(info, this->_pixel_size);
	}
	else if (this->_pixel_size == 3)
	{
		ChannelInfo info[3];
		info[0].Type = ChannelType::Red;
		info[1].Type = ChannelType::Green;
		info[2].Type = ChannelType::Blue;
		image->SetChannels(info, this->_pixel_size);
	}
	else if (this->_pixel_size == 4)
	{
		ChannelInfo info[4];
		info[0].Type = ChannelType::Red;
		info[1].Type = ChannelType::Green;
		info[2].Type = ChannelType::Blue;
		info[3].Type = ChannelType::Alpha;
		image->SetChannels(info, this->_pixel_size);
	}

	image->CreateDefaults();
}

bool ImagePathDecoder::TryDecode(const char* source, RawImageData* output, void* arg)
{
	int width, height, comp;
	unsigned char* data = LoadImageFromFile(source, &width, &height, &comp, STBI_rgb_alpha);
	output->SetWidth(width);
	output->SetHeight(height);
	output->SetPixelSize(comp);
	output->SetData(data, width * height * comp);
	return true;
}

bool ImagePathDecoder::TryDecode(const char* source, Image* output, void* arg)
{
	RawImageData data;
	this->TryDecode(source, &data, arg);
	data.ToImage(output);
	RawImageData::Free(&data);
	return true;
}