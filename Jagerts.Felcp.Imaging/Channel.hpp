#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"

namespace Jagerts::Felcp::Imaging
{
	enum ChannelType
	{
		Red,
		Green,
		Blue,
		Alpha,
		Gray,
	};

	struct ChannelInfo
	{
		ChannelType Type;
	};

	class JAGERTS_FELCP_IMAGING_API Channel
	{
	public:
		Channel(unsigned char* data, ChannelInfo channel_info);

		unsigned char GetCodeValue();
		double GetDecimalValue();
	private:
		unsigned char* _data = NULL;
		ChannelInfo _channel_info;
	};
}