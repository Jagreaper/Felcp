#include "Pixel.hpp"

using namespace Kaleid::Imaging;

Pixel::Pixel(unsigned char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels)
{
	this->_data = data;
	this->_data_length = data_length;
	this->_channels = channels;
	this->_num_channels = num_channels;
}

Channel Pixel::GetChannel(unsigned int channel)
{
	return Channel(this->_data + channel, this->_channels[channel]);
}

Channel Pixel::GetChannel(ChannelType channel)
{
	for (int index = 0; index < this->_num_channels; index++)
	{
		if (this->_channels[index].Type == channel)
			return Channel(this->_data + index, this->_channels[channel]);
	}

	throw std::exception("Channel not found exception");
}