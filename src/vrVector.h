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
#ifndef __VRVECTOR_H__
#define __VRVECTOR_H__

#include <math.h>
#include <float.h>


class vrVector3
{

public: /*SUBROUTINES*/
		vrVector3();
		vrVector3( float f );
		vrVector3( float _x, float _y, float _z );
		vrVector3( float f[3] );
		void Reset();

		vrVector3& operator += ( const vrVector3& v );
		vrVector3& operator -= ( const vrVector3& v );
		vrVector3& operator *= ( const vrVector3& v );
		vrVector3& operator /= ( const vrVector3& v );

		vrVector3& operator *= ( float s );
		vrVector3& operator /= ( float s );

		vrVector3& operator = ( const vrVector3& v );



public: /*VARIABLES*/
		float x;
		float y;
		float z;


private: /*SUBROUTINES*/



private: /*VARIABLES*/



};

	vrVector3  operator +  ( const vrVector3& v );
	vrVector3  operator -  ( const vrVector3& v );

	vrVector3  operator +  ( const vrVector3& v1, const vrVector3& v2 );
	vrVector3  operator -  ( const vrVector3& v1, const vrVector3& v2 );
	vrVector3  operator /  ( const vrVector3& v1, const vrVector3& v2 );
	vrVector3  operator *  ( const vrVector3& v1, const vrVector3& v2 );

	vrVector3  operator *  ( const vrVector3& v, float s );
	vrVector3  operator /  ( const vrVector3& v, float s );

	int		   operator == ( const vrVector3& v1, const vrVector3& v2 );
	bool		operator !=( const vrVector3& v1, const vrVector3& v2 );

	vrVector3  CrossProduct( const vrVector3& v1, const vrVector3& v2 );
	float		DotProduct( const vrVector3& v1, const vrVector3& v2 );
	float		Magnitude ( const vrVector3& v );
	vrVector3	Normalize( const vrVector3& v );
	vrVector3	Normal( const vrVector3 v[3] );	//нормаль к треугольнику
	double		Angle( vrVector3 Vector1, vrVector3 Vector2 );

	float		Distance( vrVector3 vPoint1, vrVector3 vPoint2);


#endif