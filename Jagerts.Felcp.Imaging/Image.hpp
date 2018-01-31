#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.Imaging/Channel.hpp"
#include "Jagerts.Felcp.Imaging/Pixel.hpp"
#include <vector>

namespace Jagerts::Felcp::Imaging
{
	class JAGERTS_FELCP_IMAGING_API Image
	{
	public:
		Image();
		Image(unsigned char* data, unsigned int data_length, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height);
		Image(unsigned char* data, unsigned int data_length, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height);
		Image(std::vector<unsigned char> data, ChannelInfo* channels, unsigned int num_channels, unsigned int width, unsigned int height);
		Image(std::vector<unsigned char> data, std::vector<ChannelInfo> channels, unsigned int width, unsigned int height);

		Pixel GetPixel(unsigned int x, unsigned int y);
		unsigned int& GetWidth();
		unsigned int& GetHeight();
		void GetSize(unsigned int* width, unsigned int* height);

		void SetData(unsigned char* data, unsigned int data_length);
		void SetData(std::vector<unsigned char> data);

		void SetChannels(ChannelInfo* channels, unsigned int num_channels);
		void SetChannels(std::vector<ChannelInfo> channels);

		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetSize(unsigned int width, unsigned int height);

		void CreateDefaults();
	private:

		std::vector<ChannelInfo> _channels;
		std::vector<unsigned char> _data;
		unsigned int _width = 0;
		unsigned int _height = 0;
		unsigned int _stride = 0;
		unsigned int _pixel_length = 0;
	};
}