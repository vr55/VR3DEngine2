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
#ifndef __VRCOLLISION_H__
#define __VRCOLLISION_H__

#include "vrVector.h"
#include "vrBase.h"

//#define PI 3.1415926535897932

#define BEHIND		0
#define INTERSECTS	1
#define FRONT		2

float	c_PointTriDistance( vrVector3 point, vrVector3 tri[3] );
float	PlaneDistance(vrVector3 Normal, vrVector3 Point);

int		ClassifySphere(vrVector3 &vPos, vrVector3 &vNormal, vrVector3 &vPoint, float radius, float &distance);
bool	InsidePolygon(vrVector3 vIntersection, vrVector3 Poly[], long verticeCount);
bool	EdgeSphereCollision(vrVector3 &vCenter, vrVector3 vPolygon[], int vertexCount, float radius);

vrVector3 ClosestPointOnLine(vrVector3 vA, vrVector3 vB, vrVector3 vPoint);
vrVector3 GetCollisionOffset( vrVector3 &vNormal, float radius, float distance );













#endif