#include "Channel.hpp"
#include <math.h>

using namespace Kaleid::Imaging;

Channel::Channel(unsigned char* data, ChannelInfo channel_info)
{
	this->_data = data;
	this->_channel_info = channel_info;
}

unsigned char Channel::GetCodeValue()
{
	unsigned char value = *this->_data;
	return value;
}

double Channel::GetDecimalValue()
{
	double real_value = (double)this->GetCodeValue();
	return real_value / 255.0;
}