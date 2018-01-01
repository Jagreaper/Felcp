#include "Image.hpp"

using namespace Jagerts::Felcp::Imaging;

Image::Image()
{
	// Skip
}

Image::Image(unsigned char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height)
{
	this->SetSize(width, height);
	this->SetData(data, data_length);
	this->SetChannels(channels, num_channels);

	this->CreateDefaults();
}

Image::Image(unsigned char* data, unsigned int data_length, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height)
{
	this->SetSize(width, height);
	this->SetData(data, data_length);
	this->SetChannels(channels);

	this->CreateDefaults();
}

Image::Image(std::vector<unsigned char> data, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height)
{
	this->SetSize(width, height);
	this->SetData(data);
	this->SetChannels(channels, num_channels);;

	this->CreateDefaults();
}

Image::Image(std::vector<unsigned char> data, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height)
{
	this->SetSize(width, height);
	this->SetData(data);
	this->SetChannels(channels);

	this->CreateDefaults();
}

void Image::CreateDefaults()
{
	this->_pixel_length = (unsigned int)((float)this->_data.size() / (float)(this->_width * this->_height));
	this->_stride = this->_pixel_length * this->_width;
}

Pixel Image::GetPixel(unsigned int x, unsigned int y)
{
	if (x >= this->_width || y >= this->_height)
		throw std::runtime_error("Arguement out of bounds");

	unsigned int pos = x + (y * this->_stride);
	unsigned char* pixel_data = this->_data.data() + pos;

	return Pixel(pixel_data, this->_pixel_length, this->_channels.data(), this->_channels.size());
}
unsigned int& Image::GetWidth()
{
	return this->_width;
}

unsigned int& Image::GetHeight()
{
	return this->_height;
}

void Image::GetSize(unsigned int* width, unsigned int* height)
{
	*width = this->_width;
	*height = this->_height;
}

void Image::SetData(unsigned char* data, unsigned int data_length)
{
	for (int index = 0; index < data_length; index++)
		this->_data.push_back(*data++);
}

void Image::SetData(std::vector<unsigned char> data)
{
	for (int index = 0; index < data.size(); index++)
		this->_data.push_back(data[index]);
}

void Image::SetChannels(ChannelInfo* channels, unsigned int num_channels)
{
	for (int index = 0; index < num_channels; index++)
		this->_channels.push_back(*channels++);
}

void Image::SetChannels(std::vector<ChannelInfo> channels)
{
	for (int index = 0; index < channels.size(); index++)
		this->_channels.push_back(channels[index]);
}

void Image::SetWidth(unsigned int width)
{
	this->_width = width;
}

void Image::SetHeight(unsigned int height)
{
	this->_height = height;
}

void Image::SetSize(unsigned int width, unsigned int height)
{
	this->_width = width;
	this->_height = height;
}