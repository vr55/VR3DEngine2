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
#include "vrVector.h"

//==============================================================//
//																//
//==============================================================//

vrVector3::vrVector3()
{

	x = y = z = 0.0f;

}

//==============================================================//
//																//
//==============================================================//

vrVector3::vrVector3( float f )
{

x = y = z = f;

}


//==============================================================//
//																//
//==============================================================//

vrVector3::vrVector3( float _x, float _y, float _z )
{

x = _x;
y = _y;
z = _z;

}
//==============================================================//
//																//
//==============================================================//
void vrVector3::Reset()
{

x = y = z = 0.0f;

}

//==============================================================//
//																//
//==============================================================//

vrVector3::vrVector3( float f[3] )
{

x = f[0];
y = f[1];
z = f[2];

}


//==============================================================//
//																//
//==============================================================//

vrVector3& vrVector3::operator += ( const vrVector3& v )
{

x += v.x; y += v.y; z += v.z;

return *this;

}

//==============================================================//
//																//
//==============================================================//

vrVector3& vrVector3::operator -= ( const vrVector3& v )
{

x -= v.x; y -= v.y; z -= v.z;

return *this;

}

//==============================================================//
//																//
//==============================================================//

vrVector3& vrVector3::operator *= ( const vrVector3& v )
{

x *= v.x; y *= v.y; z *= v.z;

return *this;

}

//==============================================================//
//																//
//==============================================================//

vrVector3& vrVector3::operator /= ( const vrVector3& v )
{

x /= v.x; y /= v.y; z /= v.z;

return *this;

}


//==============================================================//
//																//
//==============================================================//
vrVector3& vrVector3::operator *= ( float s )
{

x *= s; y *= s; z *= s;

return *this;

}

//==============================================================//
//																//
//==============================================================//
vrVector3& vrVector3::operator /= ( float s )
{

x /= s; y /= s; z /= s;

return *this;

}

//==============================================================//
//																//
//==============================================================//
vrVector3&	vrVector3::operator = ( const vrVector3& v )
{

x = v.x; y = v.y; z = v.z;
return *this;

}


//==============================================================//
//																//
//==============================================================//

vrVector3 operator + ( const vrVector3& v )
{

return v;

}

//==============================================================//
//																//
//==============================================================//

/*__inline*/vrVector3 operator - ( const vrVector3& v )
{

return vrVector3( -v.x, -v.y, -v.z );

}

//==============================================================//
//																//
//==============================================================//
vrVector3  operator +  ( const vrVector3& v1, const vrVector3& v2 )
{

return vrVector3( v1.x+v2.x, v1.y+v2.y, v1.z+v2.z );


}

//==============================================================//
//																//
//==============================================================//
 vrVector3  operator -  ( const vrVector3& v1, const vrVector3& v2 )
{

return vrVector3( v1.x-v2.x, v1.y-v2.y, v1.z-v2.z );


}

//==============================================================//
//																//
//==============================================================//
 vrVector3  operator /  ( const vrVector3& v1, const vrVector3& v2 )
{

return vrVector3( v1.x/v2.x, v1.y/v2.y, v1.z/v2.z );


}

//==============================================================//
//																//
//==============================================================//
vrVector3  operator *  ( const vrVector3& v, float s )
{

return vrVector3( v.x*s, v.y*s, v.z*s );


}

//==============================================================//
//																//
//==============================================================//
 vrVector3  operator /  ( const vrVector3& v, float s )
{

return vrVector3( v.x/s, v.y/s, v.z/s );


}

//==============================================================//
//																//
//==============================================================//

int	operator == ( const vrVector3& v1, const vrVector3& v2 )
{

	return v1.x==v2.x && v1.y==v2.y && v1.z==v2.z;
}

bool		operator !=( const vrVector3& v1, const vrVector3& v2 )
{

if ( v1.x != v2.x ) return true;
if ( v1.y != v2.y ) return true;
if ( v1.z != v2.z ) return true;
return false;
}

//==============================================================//
//																//
//==============================================================//

 vrVector3 CrossProduct( const vrVector3& v1, const vrVector3& v2 )
{

// The X value for the vector is:  (V1.y * V2.z) - (V1.z * V2.y)
// The Y value for the vector is:  (V1.z * V2.x) - (V1.x * V2.z)
// The Z value for the vector is:  (V1.x * V2.y) - (V1.y * V2.x)
vrVector3 v;

v.x = ( v1.y * v2.z ) - ( v1.z * v2.y );
v.y = ( v1.z * v2.x ) - ( v1.x * v2.z );
v.z = ( v1.x * v2.y ) - ( v1.y * v2.x );

return v;


}


//==============================================================//
//																//
//==============================================================//

 float Magnitude( const vrVector3& v )
{

return (float)sqrt( ( v.x*v.x ) + ( v.y*v.y ) + ( v.z*v.z ));

}

//==============================================================//
//																//
//==============================================================//

vrVector3	Normalize( const vrVector3& v )
{

return v/Magnitude( v );


}

//==============================================================//
//																//
//==============================================================//

float DotProduct( const vrVector3& v1, const vrVector3& v2 )
{

return ( ( v1.x * v2.x ) + ( v1.y * v2.y ) + ( v1.z * v2.z ) );

}


//==============================================================//
//																//
//==============================================================//

vrVector3	Normal( const vrVector3 v[3] )	//нормаль к треугольнику
{

	vrVector3 v1 = v[2] - v[0];
	vrVector3 v2 = v[1] - v[0];

	vrVector3 norm = CrossProduct( v1, v2 );

	norm = Normalize( norm );

	return norm;

}


//==============================================================//
//																//
//==============================================================//

double Angle(vrVector3 Vector1, vrVector3 Vector2)
{							
	// Get the dot product of the vectors
	float dotProduct = DotProduct(Vector1, Vector2);				

	// Get the product of both of the vectors magnitudes
	float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;

	// Get the angle in radians between the 2 vectors
	double angle = acos( dotProduct / vectorsMagnitude );

	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate
	if(_isnan(angle))
		return 0;
	
	// Return the angle in radians
	return( angle );
}


//==============================================================//
//																//
//==============================================================//

float Distance(vrVector3 vPoint1, vrVector3 vPoint2)
{
	// This is the classic formula used in beginning algebra to return the
	// distance between 2 points.  Since it's 3D, we just add the z dimension:
	// 
	// Distance = sqrt(  (P2.x - P1.x)^2 + (P2.y - P1.y)^2 + (P2.z - P1.z)^2 )
	//
	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );

	// Return the distance between the 2 points
	return (float)distance;
}

