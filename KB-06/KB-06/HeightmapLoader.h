#ifndef _HEIGHTMAPLOADER_H_
#define _HEIGHTMAPLOADER_H_

#include "Ground.h"
#include "Renderer.h"
#include "LoggerPool.h"

/*
Loader class responsible for reading the bitmap file and
generating a Ground object.
*/

namespace pengine
{
	class HeightmapLoader
	{
	public:
		HeightmapLoader();
		~HeightmapLoader();

		// Loads bitmap file and returns a pointer to the newly created ground.
		// X and Z axis of the heightmap are multiplied by cellSize. This can be used for scaling.
		Ground* LoadHeightmap(std::string filename, float cellSize);

	private:
		char* m_bitmapData;
		BITMAPINFOHEADER m_bitmapInfoHeader;
		short m_fileSignature;
		long m_fileSize;
		long m_offset;
		Logger* logger;

		// Adds a position to the vertices array
		void AddPosition(int p_vertexIndex, int p_pointIndex, float p_y, Ground& ground);
		// Builds ground based on a byte array of heightmap points
		void BuildGround(byte* p_vertices, Ground& ground);
		/*
		Loads and reads the HeightMap file 
		Results are loaded into the private fields of this class.

		If the file does not start with 0x424D
		Or if the BMP is not:
		- 24bpp
		- uncompressed
		Then the file is not in the correct format and false will be returned.
		Else true will be returned.
		*/
		bool ReadHeightMapFile(const std::string& p_filename);
		// Fallback heightmap in case the loading fails
		void LoadDefaultHeightMap(byte* p_heights, int p_cellCount);
		// Returns width and height of the heightmap in p_width and p_height
		bool GetHeightMapDimensions(long& p_width, long& p_height);
		// Returns a array of bytes (0-255). These are the Y values of the ground.
		bool GetHeightMapValues(byte* p_heights);
		/*
		Loads the entire file content into m_bitmapData
		return = true	If Bitmap content is loaded
		return = false	If Bitmap content is not loaded because the file could not be opened
		*/
		bool ReadFileContent(const std::string& p_filename);
		/*
		Reads the Bitmap Header

		Byte 6-9 are skipped because they are reserved
		and the valuesdepend on the application that created the image
		return = true	If Bitmap is loaded
		return = false	If Bitmap is not loaded
		*/
		bool ReadFileHeader();
		/*
		Reads the entire Bitmap Information Header
		return = true	If Bitmap is loaded
		return = false	If Bitmap is not loaded
		*/
		bool ReadInformationHeader();

	};
}

#endif