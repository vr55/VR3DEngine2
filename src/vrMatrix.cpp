
//==============================================================//
//																//
//==============================================================//
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
#include "vrMatrix.h"


//==============================================================//
//																//
//==============================================================//


vrMatrix4::vrMatrix4()
{

 for ( int i=0; i<16; i++ ) this->m[i] = 0.0f;

}


//==============================================================//
//																//
//==============================================================//

vrMatrix4::vrMatrix4( const vrMatrix4 &m )
{

for ( int i=0; i<16; i++ ) this->m[i] = m.m[i];

}


//==============================================================//
//																//
//==============================================================//

vrMatrix4::vrMatrix4(	float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33 )
{

m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
m[4] = m10; m[5] = m11; m[6] = m12; m[7] = m13;
m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;


}

//==============================================================//
//																//
//==============================================================//
vrMatrix4::vrMatrix4( float matrix[4][4] )
{
for ( int i=0; i<4; i++ )
	for ( int j=0; j<4; j++ )
		m[ j*4+i ] = matrix[i][j];

}


//==============================================================//
//																//
//==============================================================//
float vrMatrix4::operator() ( unsigned int uiRow, unsigned int uiCol )
{

return m[uiCol*4+uiRow];

}



//==============================================================//
//																//
//==============================================================//
vrMatrix4& vrMatrix4::operator= ( const vrMatrix4 &m )
{

for ( int i=0; i<16; i++ ) this->m[i] = m.m[i];

return *this;
}

//==============================================================//
//																//
//==============================================================//

vrMatrix4& vrMatrix4::operator+= ( const vrMatrix4 &m )
{
for ( int i=0; i<16; i++ ) this->m[i] += m.m[i];

return *this;

}


//==============================================================//
//																//
//==============================================================//
vrMatrix4& vrMatrix4::operator-= ( const vrMatrix4 &m )
{
for ( int i=0; i<16; i++ ) this->m[i] -= m.m[i];

return *this;

}


//==============================================================//
//																//
//==============================================================//

vrMatrix4::operator float* ()
{

return (float *) &m;

}


//==============================================================//
//																//
//==============================================================//

vrMatrix4::operator vrMatrix4* ()
{

return (vrMatrix4 *) &m;

}


//==============================================================//
//																//
//==============================================================//

vrMatrix4 vrMatrix4::operator+ ()
{
 return *this;
}


//==============================================================//
//																//
//==============================================================//
 vrMatrix4 vrMatrix4::operator- ()
{

return vrMatrix4( -m[0], -m[1], -m[2], -m[3],
				  -m[4], -m[5], -m[6], -m[7],
				  -m[8], -m[9], -m[10], -m[11],
				  -m[12], -m[13], -m[14], -m[15] );
}


//==============================================================//
//																//
//==============================================================//

vrMatrix4 vrMatrix4::operator* ( const vrMatrix4& matrix )
{

 return vrMatrix4(  m[0] * matrix.m[0] + m[4] * matrix.m[1] + m[8] * matrix.m[2] + m[12] * matrix.m[3],
				    m[1] * matrix.m[0] + m[5] * matrix.m[1] + m[9] * matrix.m[2] + m[13] * matrix.m[3],
					m[2] * matrix.m[0] + m[6] * matrix.m[1] + m[10] * matrix.m[2] + m[14] * matrix.m[3],
					m[3] * matrix.m[0] + m[7] * matrix.m[1] + m[11] * matrix.m[2] + m[15] * matrix.m[3],
					m[0] * matrix.m[4] + m[4] * matrix.m[5] + m[8] * matrix.m[6] + m[12] * matrix.m[7],
					m[1] * matrix.m[4] + m[5] * matrix.m[5] + m[9] * matrix.m[6] + m[13] * matrix.m[7],
			 		m[2] * matrix.m[4] + m[6] * matrix.m[5] + m[10] * matrix.m[6] + m[14] * matrix.m[7],
				   m[3] * matrix.m[4] + m[7] * matrix.m[5] + m[11] * matrix.m[6] + m[15] * matrix.m[7],
				   m[0] * matrix.m[8] + m[4] * matrix.m[9] + m[8] * matrix.m[10] + m[12] * matrix.m[11],
				   m[1] * matrix.m[8] + m[5] * matrix.m[9] + m[9] * matrix.m[10] + m[13] * matrix.m[11],
				   m[2] * matrix.m[8] + m[6] * matrix.m[9] + m[10] * matrix.m[10] + m[14] * matrix.m[11],
				   m[3] * matrix.m[8] + m[7] * matrix.m[9] + m[11] * matrix.m[10] + m[15] * matrix.m[11],
				   m[0] * matrix.m[12] + m[4] * matrix.m[13] + m[8] * matrix.m[14] + m[12] * matrix.m[15],
				   m[1] * matrix.m[12] + m[5] * matrix.m[13] + m[9] * matrix.m[14] + m[13] * matrix.m[15],
				   m[2] * matrix.m[12] + m[6] * matrix.m[13] + m[10] * matrix.m[14] + m[14] * matrix.m[15],
				   m[3] * matrix.m[12] + m[7] * matrix.m[13] + m[11] * matrix.m[14] + m[15] * matrix.m[15]);


}

//==============================================================//
//																//
//==============================================================//
vrMatrix4& vrMatrix4::operator*= ( const vrMatrix4 matrix )
{


(*this) *= matrix;

return *this;

}


//==============================================================//
//																//
//==============================================================//

vrMatrix4 vrMatrix4::operator+ ( const float f )
{

for ( int i=0; i<16; i++ ) m[i] += f;

return *this;

}

//==============================================================//
//																//
//==============================================================//
vrMatrix4 vrMatrix4::operator- ( const float f )
{

for ( int i=0; i<16; i++ ) m[i] -= f;

return *this;

}

//==============================================================//
//																//
//==============================================================//

vrMatrix4 vrMatrix4:: operator* ( const float f )
{
for ( int i=0; i<16; i++ ) m[i] *= f;

return *this;


}


//==============================================================//
//																//
//==============================================================//

void vrMatrix4::LoadIdentity( void )
{

for ( int i=0; i<16; i++ ) m[i] = 0;

m[0] = 1.0f;
m[5] = 1.0f;
m[10] = 1.0f;
m[15] = 1.0f;

}


//==============================================================//
//																//
//==============================================================//

void vrMatrix4::Zero( void )
{

for ( int i=0; i<16; i++ ) m[i] = 0;

}


//==============================================================//
//																//
//==============================================================//
vrVector3 vrMatrix4::GetViewUp( void )
{

	return vrVector3( m[1], m[5], m[9] );


}


//==============================================================//
//																//
//==============================================================//
vrVector3 vrMatrix4::GetViewRight( void )
{
	return vrVector3( m[0], m[4], m[8] );


}


//==============================================================//
//																//
//==============================================================//
vrVector3 vrMatrix4::GetViewNormal( void )
{

return vrVector3( m[3], m[7], m[11] );


}

//==============================================================//
//																//
//==============================================================//
void vrMatrix4::SetViewUp( vrVector3 v )
{


	m[1] = v.x;
	m[5] = v.y;
	m[9] = v.z;

}

//==============================================================//
//																//
//==============================================================//
void vrMatrix4::SetViewRight( vrVector3 v )
{

	m[0] = v.x;
	m[4] = v.y;
	m[8] = v.z;


}

//==============================================================//
//																//
//==============================================================//
void vrMatrix4::SetViewNormal( vrVector3 v )
{

	m[3] = v.x;
	m[7] = v.y;
	m[11] = v.z;


}

//==============================================================//
//																//
//==============================================================//

void vrMatrix4::Translate( vrVector3 &v )
{

	vrMatrix4 transmat;

	transmat.LoadIdentity();
	transmat.m[12] = v.x;
	transmat.m[13] = v.y;
	transmat.m[14] = v.z;

	vrMatrix4 newm;
	newm = *this;

	*this = newm * transmat;

	//(*this) = *this * transmat;


}

//==============================================================//
//																//
//==============================================================//
void vrMatrix4::RotateX( const float rad )
{
/*

матрица поворота вокруг оси x  : 

  [ 0    0      0    0 ]
  [ 0  cos a  sin a  0 ]
  [ 0 -sin a  cos a  0 ]
  [ 0    0      0    1 ]

*/
vrMatrix4 rotm;
rotm.LoadIdentity();
float sine = (float)sin( rad );
float cosine = (float)cos( rad );

rotm.m[5] = cosine;
rotm.m[6] = sine;
rotm.m[9] = -sine;
rotm.m[10] = cosine;

*this = *this * rotm;

}

//==============================================================//
//																//
//==============================================================//
void vrMatrix4::RotateY( const float rad )
{
/*
[ cos(yaw) 0  -sin(yaw)  0 ]
[   0      1     0       0 ]
[ sin(yaw) 0   cos(yaw)  0 ] 
[	0	   0		0	 1 ]
*/
vrMatrix4 rotm;
float sine = (float)sin( rad );
float cosine = (float)cos( rad );
rotm.LoadIdentity();

rotm.m[0] = cosine;
rotm.m[2] = -sine;
rotm.m[8] = sine;
rotm.m[10] = cosine;

*this = *this * rotm;


}

//==============================================================//
//																//
//==============================================================//


void vrMatrix4::RotateZ( const float rad )
{
/*
[ cos(roll)     sin(roll)   0	  0 ]
[ -sin(roll)    cos(roll)   0     0 ]
[   0             0         1     0 ]
[	0			  0			0	  1 ]
*/
vrMatrix4 rotm;
float sine = (float)sin( rad );
float cosine = (float)cos( rad );
rotm.LoadIdentity();


rotm.m[0] = cosine;
rotm.m[1] = sine;
rotm.m[4] = -sine;
rotm.m[5] = cosine;

}


//==============================================================//
//																//
//==============================================================//


//==============================================================//
//																//
//==============================================================//
void vrMatrix4::Scale( vrVector3 &v )
{



}

