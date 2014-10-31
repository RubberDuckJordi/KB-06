#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

/*
Beam used to determine collision
*/

namespace pengine
{
	struct BEAM
	{
		float x;
		float y;
		float z;
		float width;
		float height;
		float depth;
		float yaw;
		float pitch;
		float roll;
		//Coordinates of the corners in object space, note: only beam shapes are supported (meaning the values need to be able to be axis-aligned)
		Vector3 frontBottomLeft, frontBottomRight, backBottomLeft, backBottomRight, frontTopLeft, frontTopRight, backTopLeft, backTopRight;
		Vector3 rotFrontBottomLeft, rotFrontBottomRight, rotBackBottomLeft, rotBackBottomRight, rotFrontTopLeft, rotFrontTopRight, rotBackTopLeft, rotBackTopRight;
	};
}
#endif