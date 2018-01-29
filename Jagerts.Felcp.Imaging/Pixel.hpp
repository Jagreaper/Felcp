#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.Imaging/Channel.hpp"
#include <vector>

namespace Jagerts::Felcp::Imaging
{
	class JAGERTS_FELCP_IMAGING_API Pixel
	{
	public:
		Pixel(unsigned char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels);

		Channel GetChannel(unsigned int channel);
		Channel GetChannel(ChannelType channel);
	private:
		ChannelInfo* _channels;
		unsigned char* _data;

		unsigned int _num_channels;
		unsigned int _data_length;
	};
}