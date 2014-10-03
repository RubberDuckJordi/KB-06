#ifndef _HEIGHTMAPLOADER_H_
#define _HEIGHTMAPLOADER_H_

#include "Ground.h"
#include "Renderer.h"
#include "LoggerPool.h"
#include "CustomD3DVertex.h"

namespace pengine
{

	class HeightmapLoader
	{
	public:
		HeightmapLoader();
		~HeightmapLoader();
		Ground* LoadHeightmap(std::string filename);

	private:
		char* m_bitmapData;
		BITMAPINFOHEADER m_bitmapInfoHeader;
		short m_fileSignature;
		long m_fileSize;
		long m_offset;
		Logger* logger;

		void AddPosition(int p_vertexIndex, int p_pointIndex, int p_y, Ground& ground);
		void BuildGround(byte* p_vertices, Ground& ground);
		bool ReadHeightMapFile(const std::string& p_filename);
		void LoadDefaultHeightMap(byte* p_heights, int p_cellCount);
		bool GetHeightMapDimensions(long& p_width, long& p_height);
		bool GetHeightMapValues(byte* p_heights);
		void ReadBitmapFileHeader();
		void ReadBitmapInformationHeader();
		bool ReadFileContent(const std::string& p_filename);
		bool ReadFileHeader();
		bool ReadInformationHeader();

	};
}

#endif