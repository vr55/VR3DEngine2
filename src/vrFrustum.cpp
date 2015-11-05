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


#include "vrFrustum.h"
#include "vrBase.h"

//==============================================================//
//																//
//==============================================================//

enum PlaneData
{
	A = 0,				// The X value of the plane's normal
	B = 1,				// The Y value of the plane's normal
	C = 2,				// The Z value of the plane's normal
	D = 3				// The distance the plane is from the origin
};

//==============================================================//
//																//
//==============================================================//


void vrFrustum::Update()
{
//(c)Mark Morley
	float   proj[16];
	float   modl[16];
	float   clip[16];
	float   t;

   /* Get the current PROJECTION matrix from OpenGL */
   glGetFloatv( GL_PROJECTION_MATRIX, proj );

   /* Get the current MODELVIEW matrix from OpenGL */
   glGetFloatv( GL_MODELVIEW_MATRIX, modl );

   /* Combine the two matrices (multiply projection by modelview) */

   clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
   clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
   clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
   clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

   clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
   clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
   clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
   clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

   clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
   clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
   clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
   clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

   clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
   clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
   clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
   clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];
 
   /* Extract the numbers for the RIGHT plane */
   frustum[0][0] = clip[ 3] - clip[ 0];
   frustum[0][1] = clip[ 7] - clip[ 4];
   frustum[0][2] = clip[11] - clip[ 8];
   frustum[0][3] = clip[15] - clip[12];

   /* Normalize the result */
   t = (float)sqrt( frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2] );
   frustum[0][0] /= t;
   frustum[0][1] /= t;
   frustum[0][2] /= t;
   frustum[0][3] /= t;

   /* Extract the numbers for the LEFT plane */
   frustum[1][0] = clip[ 3] + clip[ 0];
   frustum[1][1] = clip[ 7] + clip[ 4];
   frustum[1][2] = clip[11] + clip[ 8];
   frustum[1][3] = clip[15] + clip[12];

   /* Normalize the result */
   t = (float)sqrt( frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2] );
   frustum[1][0] /= t;
   frustum[1][1] /= t;
   frustum[1][2] /= t;
   frustum[1][3] /= t;

   /* Extract the BOTTOM plane */
   frustum[2][0] = clip[ 3] + clip[ 1];
   frustum[2][1] = clip[ 7] + clip[ 5];
   frustum[2][2] = clip[11] + clip[ 9];
   frustum[2][3] = clip[15] + clip[13];

   /* Normalize the result */
   t = (float)sqrt( frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2] );
   frustum[2][0] /= t;
   frustum[2][1] /= t;
   frustum[2][2] /= t;
   frustum[2][3] /= t;

   /* Extract the TOP plane */
   frustum[3][0] = clip[ 3] - clip[ 1];
   frustum[3][1] = clip[ 7] - clip[ 5];
   frustum[3][2] = clip[11] - clip[ 9];
   frustum[3][3] = clip[15] - clip[13];

   /* Normalize the result */
   t = (float)sqrt( frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2] );
   frustum[3][0] /= t;
   frustum[3][1] /= t;
   frustum[3][2] /= t;
   frustum[3][3] /= t;

   /* Extract the FAR plane */
   frustum[4][0] = clip[ 3] - clip[ 2];
   frustum[4][1] = clip[ 7] - clip[ 6];
   frustum[4][2] = clip[11] - clip[10];
   frustum[4][3] = clip[15] - clip[14];

   /* Normalize the result */
   t = (float)sqrt( frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2] );
   frustum[4][0] /= t;
   frustum[4][1] /= t;
   frustum[4][2] /= t;
   frustum[4][3] /= t;

   /* Extract the NEAR plane */
   frustum[5][0] = clip[ 3] + clip[ 2];
   frustum[5][1] = clip[ 7] + clip[ 6];
   frustum[5][2] = clip[11] + clip[10];
   frustum[5][3] = clip[15] + clip[14];

   /* Normalize the result */
   t = (float)sqrt( frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2] );
   frustum[5][0] /= t;
   frustum[5][1] /= t;
   frustum[5][2] /= t;
   frustum[5][3] /= t;


}

//==============================================================//
//																//
//==============================================================//

bool vrFrustum::PointInFrustum( vrVector3	point )
{

return this->PointInFrustum( point.x, point.y, point.z );

}


//==============================================================//
//																//
//==============================================================//
bool vrFrustum::PointInFrustum( float x, float y, float z )
{
   for( int p = 0; p < 6; p++ )
   {
      if( frustum[p][0] * x + frustum[p][1] * y + frustum[p][2] * z + frustum[p][3] <= 0 )
         return false;
	}
   return true;

}

//==============================================================//
//																//
//==============================================================//

bool vrFrustum::CubeInFrustum( float x, float y, float z, float size )
//size - ПОЛОВИНА ширины или длины или высоты
{

vrVector3 box[8];

box[0] = vrVector3( x-size, y-size, z-size);
box[1] = vrVector3( x+size, y-size,z-size);
box[2] = vrVector3( x+size, y-size, z+size);
box[3] = vrVector3( x-size, y-size, z+size);

box[4] = vrVector3( x-size, y+size, z-size );
box[5] = vrVector3( x-size, y+size, z+size );
box[6] = vrVector3( x+size, y+size, z+size );
box[7] = vrVector3( x+size, y+size, z-size );

for ( int i=0; i<8; i++ )
if ( PointInFrustum( box[i] ) ) return true;


if ( LineInFrustum( box[0], box[6] ) )return true;
if ( LineInFrustum( box[1], box[7] ) )return true;
if ( LineInFrustum( box[3], box[5] ) )return true;

for( i = 0; i < 6; i++ )
	{
		if( frustum[i][A] * (x) + frustum[i][B] * (y ) + frustum[i][C] * (z) + frustum[i][D] > 0)
		   continue;

		if( frustum[i][A] * (x - size) + frustum[i][B] * (y - size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)
		   continue;
		if( frustum[i][A] * (x + size) + frustum[i][B] * (y - size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)
		   continue;
		if( frustum[i][A] * (x - size) + frustum[i][B] * (y + size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)
		   continue;
		if( frustum[i][A] * (x + size) + frustum[i][B] * (y + size) + frustum[i][C] * (z - size) + frustum[i][D] > 0)
		   continue;
		if( frustum[i][A] * (x - size) + frustum[i][B] * (y - size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)
		   continue;
		if( frustum[i][A] * (x + size) + frustum[i][B] * (y - size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)
		   continue;
		if( frustum[i][A] * (x - size) + frustum[i][B] * (y + size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)
		   continue;
		if( frustum[i][A] * (x + size) + frustum[i][B] * (y + size) + frustum[i][C] * (z + size) + frustum[i][D] > 0)
		   continue;

		// If we get here, it isn't in the frustum
		return false;
	}

	return true;

}


//==============================================================//
//																//
//==============================================================//

bool vrFrustum::CubeInFrustum( vrVector3 center, float size )
{

return this->CubeInFrustum( center.x, center.y, center.z, size );

}

//==============================================================//
//																//
//==============================================================//

bool	vrFrustum::LineInFrustum( vrVector3 start, vrVector3 end )
{
	float fStartD;	//расстояние до плоскости от точки начала линии
	float fEndD;	//расстояние до плоскости от точки конца линии

	for( int p = 0; p<6; p++ )
	{
		fStartD = frustum[p][0] * start.x + frustum[p][1] * start.y + frustum[p][2] * start.z + frustum[p][3];
		fEndD = frustum[p][0] * end.x + frustum[p][1] * end.y + frustum[p][2] * end.z + frustum[p][3];

		
		if ( (fStartD * fEndD) < 0 )return true;

		

	}

return false;
}


//==============================================================//
//																//
//==============================================================//

bool vrFrustum::QuadInFrustum( vr_quad quad )
{

for ( int i=0; i<4; i++ )
{
if ( PointInFrustum( quad.v[i].x, quad.v[i].y, quad.v[i].z ) ) return true;
}


float r = sqrt((quad.v[2].x - quad.v[0].x) * (quad.v[2].x - quad.v[0].x) + 
			( quad.v[2].y - quad.v[0].y ) * ( quad.v[2].y - quad.v[0].y ) +
			( quad.v[2].z - quad.v[0].z ) * ( quad.v[2].z - quad.v[0].z ));

vrVector3 c( quad.v[0].x,quad.v[0].y, quad.v[0].z);


return SphereInFrustum( c, r );



return false;
}

//==============================================================//
//																//
//==============================================================//

bool   vrFrustum::SphereInFrustum( vrVector3 center, float radius )
{
	// Go through all the sides of the frustum
	for(int i = 0; i < 6; i++ )	
	{
		// If the center of the sphere is farther away from the plane than the radius
		if( frustum[i][A] * center.x + frustum[i][B] * center.y + frustum[i][C] * center.z + frustum[i][D] <= -radius )
		{
			// The distance was greater than the radius so the sphere is outside of the frustum
			return false;
		}
	}
	
	// The sphere was inside of the frustum!
	return true;



}

