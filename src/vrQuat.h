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

#pragma once

#ifndef __BORLANDC__
#include "D3dx8math.h"
#define pi 3.1415926f

class vrQuaternion : public D3DXQUATERNION 
{

public:
				vrQuaternion(){ x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; }
				vrQuaternion( float _x, float _y, float _z, float _w );

	void		Reset(){ x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f; }
	void		GetDirectionVector( vrVector3 *dir );

private:


};



void vrQuaternion::GetDirectionVector( vrVector3 *dir )
{

dir->x = 2.0f * ( x*z - w*y );
dir->y = 2.0f * ( y*z + w*x );
dir->z = 1.0f - 2.0f * ( x*x + y*y );

}

vrQuaternion::vrQuaternion( float _x, float _y, float _z, float _w )
{

x = _x;
y = _y;
z = _z;
w = _w;

}

#endif
