
/*
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free
	Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef __VRFRUSTUM_H__
#define __VRFRUSTUM_H__

//#include "vrBase.h"
#include "vrVector.h"
#include "vrInclude.h"

class vrFrustum
{


public: /*SUBROUTINES*/
		void		Update();

		bool		PointInFrustum( vrVector3	point );
		bool		PointInFrustum( float x, float y, float z );
		bool		CubeInFrustum( float x, float y, float z, float size );
		bool		CubeInFrustum( vrVector3 center, float size );
		bool		LineInFrustum( vrVector3 start, vrVector3 end );
		bool		QuadInFrustum( vr_quad quad );
		bool		SphereInFrustum( vrVector3 center, float radius );




public: /*VARIABLES*/



private: /*SUBROUTINES*/



private: /*VARIABLES*/
		float	frustum[6][4];



};





#endif