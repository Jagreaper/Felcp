#pragma once

#include "Jagerts.Felcp.Shared/Common.hpp"
#include "Jagerts.Felcp.IO/DecoderBase.hpp"

namespace Jagerts::Felcp::Imaging
{
	class Image;
}

namespace Jagerts::Felcp::IO::Imaging
{
	class JAGERTS_FELCP_IO_IMAGING_API RawImageData
	{
	public:
		static void Free(RawImageData* data);

		void SetData(unsigned char* data, int size);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetPixelSize(int pixel_size);

		unsigned char* GetData();
		const int GetWidth() const;
		const int GetHeight() const;
		const int GetPixelSize() const;
		const size_t GetSize() const;
		
		void ToImage(Jagerts::Felcp::Imaging::Image* image);
	private:
		unsigned char* _data = NULL;
	    int _width;
		int _height;
		int _pixel_size;
		size_t _size;
	};

	class JAGERTS_FELCP_IO_IMAGING_API ImageDecoder : public PathDecoderBase<Jagerts::Felcp::Imaging::Image*, void*>, public PathDecoderBase<RawImageData*, void*>
	{
	public:
		bool TryDecode(const char* source, Jagerts::Felcp::Imaging::Image* output, void* arg = NULL);
		bool TryDecode(const char* source, RawImageData* output, void* arg = NULL);
	};
}