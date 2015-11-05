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
#ifndef __VRMATRIX_H__
#define __VRMATRIX_H__

#include <memory.h>
#include "vrVector.h"


/*
------------------------IMPORTANT----------------------

Используется так называемая row-major матрица. т.е. порядковый номер 
элемента матрицы возрастает по строке. В OpenGL используется column-major матрица
т.е для использования матрицы в glLoadMatrix нужно предварительно ее транспонировать

*/
class vrMatrix4
{

public: /*SUBROUTINES*/
		vrMatrix4();
		vrMatrix4(	float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33 );
		vrMatrix4( const vrMatrix4 &m );
	//	vrMatrix4( float &matrix[16] );
		vrMatrix4( float matrix[4][4] );

		void LoadIdentity( void );
		void Zero( void );
		vrVector3 GetViewUp( void );
		vrVector3 GetViewRight( void );
		vrVector3 GetViewNormal( void );

		void SetViewUp( vrVector3 v );
		void SetViewRight( vrVector3 v );
		void SetViewNormal( vrVector3 v );

		void Translate( vrVector3 &v );
		void RotateX( const float rad );
		void RotateY( const float rad );
		void RotateZ( const float rad );
		void Rotate( float pitch, float yaw, float roll );

		void Scale( vrVector3 &v );



		vrMatrix4& operator= ( const vrMatrix4 &m );
		vrMatrix4& operator+= ( const vrMatrix4 &m );
		vrMatrix4& operator-= ( const vrMatrix4 &m );
		vrMatrix4& operator*= ( const vrMatrix4 matrix );

//access
		float		operator() ( unsigned int uiRow, unsigned int uiCol );

//unary
		vrMatrix4 operator+ ();
		vrMatrix4 operator- ();

//binary
		vrMatrix4 operator* ( const vrMatrix4& matrix );
		vrMatrix4 operator+ ( const float f );
		vrMatrix4 operator- ( const float f );
		vrMatrix4 operator* ( const float f );


//casting

	   operator float* ();
	   operator vrMatrix4*();



public: /*VARIABLES*/

		float m[16];

private: /*SUBROUTINES*/



private: /*VARIABLES*/





};


#endif