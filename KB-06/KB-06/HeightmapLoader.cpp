#include "HeightmapLoader.h"

namespace pengine
{
	HeightmapLoader::HeightmapLoader()
	{
		m_bitmapData = NULL;
		logger = LoggerPool::GetInstance().GetLogger();
	}

	HeightmapLoader::~HeightmapLoader()
	{
		delete[] m_bitmapData;
		LoggerPool::GetInstance().ReturnLogger(logger);
	}

	Ground* HeightmapLoader::LoadHeightmap(std::string filename)
	{
		Ground* ground = new Ground();
		bool result = true;

		byte* heightMapValues;
		long height;
		long width;

		if (ReadHeightMapFile(filename))
		{
			GetHeightMapDimensions(height, width);
			heightMapValues = new byte[width*height];
			GetHeightMapValues(heightMapValues);

			ground->SetWidth(width);
			ground->SetHeight(height);
			ground->SetCellSize(1); // default value

			BuildGround(heightMapValues, *ground);

			logger->Log(Logger::DEBUG, "Heightmaploader: Heightmap succesfully loaded");
		}
		else
		{
			width = 2;
			height = 2;
			heightMapValues = new byte[width*height];
			LoadDefaultHeightMap(heightMapValues, width);
			ground->SetCellSize(200);

			ground->SetWidth(width);
			ground->SetHeight(height);

			BuildGround(heightMapValues, *ground);

			logger->Log(Logger::DEBUG, "Heightmaploader: Default Heightmap loaded");
		}

		delete[] heightMapValues;

		return ground;
	}

	void HeightmapLoader::BuildGround(byte* p_vertices, Ground& ground)
	{
		ground.SetAmountOfIndices(((ground.GetWidth() - 1) * (ground.GetHeight() - 1) * 6));
		D3DCustomVertex* vertex = new D3DCustomVertex[ground.GetAmountOfIndices()];
		ground.SetVertices(vertex);
		int vertexIndex = 0;

		//You start at z1, x1 to draw back to the begin. 
		for (int z = 1; z < ground.GetHeight(); ++z)
		{
			for (int x = 1; x < ground.GetWidth(); ++x)
			{
				//Used to calculte the four points in a square. With formula: index = (x+z) * width.
				int point1Index = ((x - 1) + ((z - 1))*ground.GetWidth());
				int point2Index = ((x)+((z - 1))*ground.GetWidth());
				int point3Index = ((x - 1) + ((z))*ground.GetWidth());
				int point4Index = ((x)+((z))*ground.GetWidth());

				//First triangle for the square
				AddPosition(vertexIndex + 0, point3Index, p_vertices[point3Index], ground);
				AddPosition(vertexIndex + 1, point2Index, p_vertices[point2Index], ground);
				AddPosition(vertexIndex + 2, point1Index, p_vertices[point1Index], ground);

				//Second triangle for the square
				AddPosition(vertexIndex + 5, point3Index, p_vertices[point3Index], ground);
				AddPosition(vertexIndex + 4, point2Index, p_vertices[point2Index], ground);
				AddPosition(vertexIndex + 3, point4Index, p_vertices[point4Index], ground);

				vertexIndex += 6;
			}
		}
	}

	void HeightmapLoader::AddPosition(int p_vertexIndex, int p_pointIndex, int p_y, Ground& ground)
	{
		//Calculate x from p_pointIndex 
		int x = p_pointIndex % ground.GetWidth();

		//Calculate z from p_pointIndex
		int z = p_pointIndex / ground.GetWidth();

		//Calculate texture coordinates
		float tu = (1 / static_cast<float>(ground.GetWidth())) * static_cast<float>(x);
		float tv = (1 / static_cast<float>(ground.GetHeight())) * static_cast<float>(z);

		D3DCustomVertex* vertex = ground.GetVertices();

		vertex[p_vertexIndex].x = x * ground.GetCellSize();
		vertex[p_vertexIndex].y = p_y;
		vertex[p_vertexIndex].z = z * ground.GetCellSize();
		vertex[p_vertexIndex].tu = tu;
		vertex[p_vertexIndex].tv = tv;
	}

	/*
	Loads and reads the HeightMap file
	If the file does not start with 0x424D
	Or if the BMP is not:
	- 24bpp
	- uncompressed
	Then the file is not in the correct format and false will be returned.
	Else true will be returned.
	*/
	bool HeightmapLoader::ReadHeightMapFile(const std::string& p_filename)
	{
		std::string message;
		message.append("HeightMapImporter: Reading Bitmap file content: ");
		message.append(p_filename);
		logger->Log(Logger::DEBUG, message.c_str());

		if (ReadFileContent(p_filename))
		{
			ReadFileHeader();

			//Bitmap Signature must be equal to 0x424D (Hex) or BM (ASCII)
			if (m_fileSignature != 0x4D42)
			{
				logger->Log(Logger::DEBUG, "HeightmapLoader: File signature did not match to BMP signature 0x424D.");
				return false;
			}

			ReadInformationHeader();

			if ((m_bitmapInfoHeader).biBitCount != 24)
			{
				logger->Log(Logger::DEBUG, "HeightmapLoader: Bitmap is not 24bpp.");

				return false;
			}

			if ((m_bitmapInfoHeader).biCompression != 0)
			{
				logger->Log(Logger::DEBUG, "HeightMapImporter: Bitmap is compressed.");
				return false;
			}
			logger->Log(Logger::DEBUG, "HeightMapImporter: Bitmap loading successful");
			return true;
		}
		else
		{
			logger->Log(Logger::DEBUG, "HeightMapImporter: Bitmap loading failed");
			return false;
		}
	}

	/*
	Loads the entire file content into m_bitmapData
	return = true	If Bitmap content is loaded
	return = false	If Bitmap content is not loaded because the file could not be opened
	*/
	bool HeightmapLoader::ReadFileContent(const std::string& p_filename)
	{
		//ios::ate sets the reading pointer at the end of the file
		std::ifstream file(p_filename, std::ios::in | std::ios::binary | std::ios::ate);

		if (file.is_open())
		{
			//The reading pointer is at the end of the file.
			//Function tellg() returns the current pointer position.
			//In this case, this is equal to the size of the file.
			unsigned long size = static_cast<unsigned long>(file.tellg());
			m_bitmapData = new char[size];
			file.seekg(0, std::ios::beg);	//Set reading pointer to 0, relative to the beginning of the file (ios::beg).
			file.read(m_bitmapData, size); //Load the entire file to m_bitmapData
			file.close();

			logger->Log(Logger::DEBUG, "HeightMapImporter: Reading Bitmap file content successful.");
			return true;
		}
		else
		{
			logger->Log(Logger::DEBUG, "HeightMapImporter: Reading Bitmap file content failed.");
			return false;
		}
	}

	/*
	Reads the Bitmap Header

	Byte 6-9 are skipped because they are reserved
	and the valuesdepend on the application that created the image
	return = true	If Bitmap is loaded
	return = false	If Bitmap is not loaded
	*/
	bool HeightmapLoader::ReadFileHeader()
	{
		if (m_bitmapData != NULL)
		{
			//Read file signature
			memcpy(&m_fileSignature, &m_bitmapData[0], sizeof(m_fileSignature));

			//Read file size
			memcpy(&m_fileSize, &m_bitmapData[2], sizeof(m_fileSize));

			//Skip 4 bytes (reserved application bytes)

			//Read offset for the pixel data.
			memcpy(&m_offset, &m_bitmapData[10], sizeof(m_offset));

			return true;
		}
		else
		{
			logger->Log(Logger::DEBUG, "HeightMapImporter: Unable to read Bitmap File Header. No BMP file has been loaded.");
			return false;
		}
	}

	/*
	Reads the entire Bitmap Information Header
	return = true	If Bitmap is loaded
	return = false	If Bitmap is not loaded
	*/
	bool HeightmapLoader::ReadInformationHeader()
	{
		if (m_bitmapData != NULL)
		{
			//Start of the bitmap information header data
			int offset = 14;

			//Read size of the header
			memcpy(&(m_bitmapInfoHeader).biSize, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biSize));

			//Read image width
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biWidth, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biWidth));

			//Read image height
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biHeight, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biHeight));

			//Read amount of planes, must be 1.
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biPlanes, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biPlanes));

			//Read amount of bits per pixel, must be 24.
			offset += 2;
			memcpy(&(m_bitmapInfoHeader).biBitCount, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biBitCount));

			//Read compression level, must be 0.
			offset += 2;
			memcpy(&(m_bitmapInfoHeader).biCompression, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biCompression));

			//Read image size, this is the amount of bytes in the actual image data, including padding.
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biSizeImage, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biSizeImage));

			//Read pixels per meter (horizontally)
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biXPelsPerMeter, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biXPelsPerMeter));

			//Read pixels per meter (vertically)
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biYPelsPerMeter, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biYPelsPerMeter));

			//Read amount of used colors, 0 is default.
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biClrUsed, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biClrUsed));

			//Read amount of important colors, 0 is default.
			offset += 4;
			memcpy(&(m_bitmapInfoHeader).biClrImportant, &m_bitmapData[offset], sizeof((m_bitmapInfoHeader).biClrImportant));

			return true;
		}
		else
		{
			logger->Log(Logger::DEBUG, "HeightMapImporter: Unable to read Bitmap Information Header. No BMP file has been loaded.");
			return false;
		}
	}

	/*
	Fills the 1 dimensional-array p_heightMapValues with height values set to 0
	p_cellCount is the amount of cells in the default height map
	*/
	void HeightmapLoader::LoadDefaultHeightMap(byte* p_heights, int p_cellCount)
	{
		logger->Log(Logger::DEBUG, "Loading default heightmap.");
		for (int z = 0; z < p_cellCount; ++z)
		{
			for (int x = 0; x < p_cellCount; ++x)
			{
				p_heights[x + p_cellCount * z] = 0;
			}
		}
	}

	/*
	p_width and p_height are filled with the width and height of the Bitmap
	return = true	If Bitmap is loaded
	return = false	If Bitmap is not loaded
	*/
	bool HeightmapLoader::GetHeightMapDimensions(long& p_width, long& p_height)
	{
		if (m_bitmapData != NULL)
		{
			p_width = m_bitmapInfoHeader.biWidth;
			p_height = m_bitmapInfoHeader.biHeight;

			return true;
		}
		else
		{
			logger->Log(Logger::DEBUG, "HeightMapImporter: Unable to determine HeightMap dimensions. No BMP file has been loaded.");
			return false;
		}
	}

	/*
	Fills the 1 dimensional-array p_heightMapValues with all the HeightMap values from the Bitmap
	return = true	If Bitmap is loaded
	return = false	If Bitmap is not loaded
	*/
	bool HeightmapLoader::GetHeightMapValues(byte* p_heightMapValues)
	{
		if (m_bitmapData != NULL)
		{
			/*
			Source: http://en.wikipedia.org/wiki/BMP_file_format#Pixel_array_.28bitmap_data.29

			Padding bytes (not necessarily 0) must be appended to the end of the rows in order to bring up the length of the rows to a multiple of four bytes.
			When the pixel array is loaded into memory, each row must begin at a memory address that is a multiple of 4.
			This address/offset restriction is mandatory only for Pixel Arrays loaded in memory. For file storage purposes,
			only the size of each row must be a multiple of 4 bytes while the file offset can be arbitrary.
			A 24-bit bitmap with Width=1, would have 3 bytes of data per row (blue, green, red) and 1 byte of padding,
			while Width=2 would have 2 bytes of padding, Width=3 would have 3 bytes of padding, and Width=4 would not have any padding at all.
			*/

			int pitch = m_bitmapInfoHeader.biWidth * 3; //Pitch is the amount of bytes per 'line'
			int padding = 0;

			//Every pitch must be divisible by 4.
			//Padding is added if this is not the case.
			if (pitch % 4 != 0)
			{
				padding = 4 - (pitch % 4);
			}

			for (int z = 0; z < m_bitmapInfoHeader.biHeight; ++z)
			{
				for (int x = 0; x < m_bitmapInfoHeader.biWidth; ++x)
				{
					/* *m_offset Fileposition calculation starts with the offset. This variable is stored in the file, it indicates where the actual RGB data starts.
					* (x * 3) Every pixel contains three values, R, G and B. We only need one. Therefore, we skip 3 bytes for every x.
					* (((*m_bih).biHeight - 1) - z) The RGB data is stored in reverse order. For this reason, we subtract the z from the height.
					* (3 * (*m_bih).biWidth) + padding) For every z, we need to skip 3 * the width of the image (one 'line' of data) plus another byte..
					*
					* This method reads the Blue data, not Red or Green.
					* Example of the order in the RGB data (every coordinate contains R,G and B data.:
					*
					*	0,4	1,4	2,4	3,4	4,4	PADDING
					*	0,3	1,3	2,3	3,3	4,3 PADDING
					*	0,2	1,2	2,2	3,2	4,2	PADDING
					*	0,1	1,1	2,1	3,1	4,1	PADDING
					*	0,0	1,0	2,0	3,0	4,0	PADDING
					*/

					int filePosition = m_offset + (x * 3) + (((m_bitmapInfoHeader.biHeight - 1) - z) * ((3 * m_bitmapInfoHeader.biWidth) + padding));

					p_heightMapValues[x + m_bitmapInfoHeader.biWidth * z] = m_bitmapData[filePosition];
					//memcpy(&p_heightMapValues[x + m_bitmapInfoHeader.biWidth * z], &m_bitmapData[filePosition], sizeof(p_heightMapValues));
				}
			}

			return true;
		}
		else
		{
			logger->Log(Logger::DEBUG, "HeightMapImporter: Unable to determine HeightMap heights. No BMP file has been loaded.");
			return false;
		}
	}
}