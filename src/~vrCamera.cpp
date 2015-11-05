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
#include "vrCamera.h"

//==============================================================//
//																//
//==============================================================//


vrCamera::vrCamera()
{

	matrix.LoadIdentity();

}

//==============================================================//
//																//
//==============================================================//
vrCamera::~vrCamera()
{

}

//==============================================================//
//																//
//==============================================================//
void vrCamera::Update( void )
{

	  //glRotatef( -0, 1.0, 0.0, 0.0);			//Pitch
      //glRotatef( -0, 0.0, 1.0, 0.0);			//Yaw
      //glRotatef( -0, 0.0, 0.0, 1.0);			//Roll

      //glTranslatef( -0, -0, 10.0f );
	glLoadMatrixf( &matrix.m[0] );


}


//==============================================================//
//																//
//==============================================================//

void vrCamera::Apply( void )
{
// переводим метрицу в column-major order
vrMatrix4 temp( this->matrix );

	matrix.m[1] = temp.m[4];
	matrix.m[2] = temp.m[8];
	matrix.m[6] = temp.m[9];

	matrix.m[4] = temp.m[1];
	matrix.m[8] = temp.m[2];
	matrix.m[9] = temp.m[6];


//glMatrixMode(GL_PROJECTION);
glLoadMatrixf( &matrix.m[0] );
//glTranslatef(-Position.x,-Position.y,-Position.z);



}


//==============================================================//
//																//
//==============================================================//

void vrCamera::SetPosition( vrVector3 &vec )
{


/*---------------------------------------------------
Move to the desired place keeping the rotation.
That's done placing the translation in cam coords
----------------------------------------------------*/

matrix.m[12] = -DotProduct( vec, matrix.GetViewRight() );
matrix.m[13] = -DotProduct( vec, matrix.GetViewUp() );
matrix.m[14] = -DotProduct( vec, matrix.GetViewNormal() );





}


//==============================================================//
//																//
//==============================================================//

void vrCamera::RotateX( const float fAngle )
{

	float sine = ( float ) sin( fAngle );
	float cosine = ( float ) cos( fAngle );
	
	vrMatrix4 rotX;
	rotX.LoadIdentity();

rotX.m[5] = cosine;
rotX.m[6] = -sine;
rotX.m[9] = sine;
rotX.m[10] = cosine;


this->matrix = this->matrix * rotX;



}

//==============================================================//
//																//
//==============================================================//

void vrCamera::RotateY( const float fAngle )
{

	float sine = (float)sin( fAngle );
	float cosine = (float)cos( fAngle );

	vrMatrix4 rotY;
	rotY.LoadIdentity();

	rotY.m[0] = cosine;
	rotY.m[3] = sine;
	rotY.m[8] = -sine;
	rotY.m[10] = cosine;

this->matrix = this->matrix * rotY;



}

//==============================================================//
//																//
//==============================================================//
void vrCamera::RotateZ( const float fAngle )
{

	float sine = (float)sin(fAngle);
	float cosine = (float)cos(fAngle);
	
	vrMatrix4 rotZ;
	rotZ.LoadIdentity();

	rotZ.m[0] = cosine;
	rotZ.m[1] = -sine;
	rotZ.m[4]= sine;
	rotZ.m[5] = cosine;

this->matrix = this->matrix * rotZ;


}

//==============================================================//
//																//
//==============================================================//

void vrCamera::Rotate( vrVector3 &vAxis, const float fAngle )
{


	float Sin = (float)sin(fAngle);
	float Cos = (float)cos(fAngle);

	//normalize v 
	vrVector3 v = Normalize( vAxis );

	vrMatrix4 rotm;

	//rotation part
	rotm.m[0] = ( v.x * v.x ) * ( 1.0f - Cos ) + Cos;
    rotm.m[1] = ( v.x * v.y ) * ( 1.0f - Cos ) - (v.z * Sin);
    rotm.m[2] = ( v.x * v.z ) * ( 1.0f - Cos ) + (v.y * Sin);

    rotm.m[4] = ( v.y * v.x ) * ( 1.0f - Cos ) + (v.z * Sin);
    rotm.m[5] = ( v.y * v.y ) * ( 1.0f - Cos ) + Cos;
    rotm.m[6] = ( v.y * v.z ) * ( 1.0f - Cos ) - (v.x * Sin);

    rotm.m[8] = ( v.z * v.x ) * ( 1.0f - Cos ) - (v.y * Sin);
    rotm.m[9] = ( v.z * v.y ) * ( 1.0f - Cos ) + (v.x * Sin);
    rotm.m[10] = ( v.z * v.z ) * ( 1.0f - Cos ) + Cos;

	rotm.m[3] = rotm.m[7] = rotm.m[11] = 0.0f;
	rotm.m[12] = rotm.m[13] = rotm.m[14] = 0.0f;
	rotm.m[15] = 1.0f;


	this->matrix = this->matrix * rotm;

}

//==============================================================//
//																//
//==============================================================//

void vrCamera::RotateWX( const float fAngle )
{

	vrVector3 newx( matrix.m[0], matrix.m[1], matrix.m[2]);
	this->Rotate( newx, fAngle );


}
//==============================================================//
//																//
//==============================================================//

void vrCamera::RotateWY( const float fAngle )
{

	vrVector3 newy( matrix.m[4], matrix.m[5], matrix.m[6]);
	this->Rotate( newy, fAngle );


}
//==============================================================//
//																//
//==============================================================//

void vrCamera::RotateWZ( const float fAngle )
{
//	vect newz(matrix.m1[2][0], matrix.m1[2][1], matrix.m1[2][2]);

	vrVector3 newz( matrix.m[8], matrix.m[9], matrix.m[10]);
	this->Rotate( newz, fAngle );


}


//==============================================================//
//																//
//==============================================================//
void vrCamera::MoveForward( const float dist )
{

	if ( dist == 0.0f ) return;
/*
	vrVector3 view( matrix.GetViewNormal() );
	vrVector3 up( matrix.GetViewUp() );
	vrVector3 right( matrix.GetViewRight() );

	vrVector3  XZproj( view.x, 0, view.z );

	float len = Magnitude( XZproj );

	if ( len == 0.0 ) return;

	XZproj *= dist/len;

	float nproj = DotProduct( XZproj, view );
	float uproj = DotProduct( XZproj, up );
	float rproj = DotProduct( XZproj, right );

	this->matrix.Translate( vrVector3( -rproj, -uproj, -nproj ) );

*/

	vrVector3 up( matrix.m[8], matrix.m[9], matrix.m[10] );
	up *= dist;

	this->matrix.Translate( up );

}

//==============================================================//
//																//
//==============================================================//
void vrCamera::MoveUp( const float dist )
{

//vect up(matrix.m1[1][0], matrix.m1[1][1], matrix.m1[1][2]);

vrVector3 up( matrix.m[4], matrix.m[5], matrix.m[6] );

up *= dist;


matrix.Translate( up );

}


//==============================================================//
//																//
//==============================================================//
void vrCamera::Strafe( const float dist )
{

	vrVector3 view( matrix.GetViewNormal() );
	vrVector3 up( matrix.GetViewUp() );
	vrVector3 right( matrix.GetViewRight() );

	vrVector3  XZproj( right.x, 0, right.z );
	float len = Magnitude( XZproj );

	if ( len < EPS ) return;

	XZproj *= dist/len;

	float nproj = DotProduct( XZproj, view );
	float uproj = DotProduct( XZproj, up );
	float rproj = DotProduct( XZproj, right );

	this->matrix.Translate( vrVector3( -rproj, -uproj, -nproj ) );



}
