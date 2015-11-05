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

#include "vrCamera2.h"
 #ifndef __BORLANDC__
//==============================================================//
//																//
//==============================================================//


vrCamera2::vrCamera2()
{

//default offset
	v_offset	= D3DXVECTOR3( 0.0f, 5.0f, -10.0f );
	v_pos		= D3DXVECTOR3( 0.0f , 0.0f, 0.0f );
	Init();

}

//==============================================================//
//																//
//==============================================================//
void vrCamera2::Init()
{
	f_speed		= 10.0f;
	D3DXQuaternionIdentity( &q_orient );
	D3DXMatrixIdentity( &m_view );
	D3DXMatrixIdentity( &m_proj );

	b_update = true;;


}

//==============================================================//
//																//
//==============================================================//
void vrCamera2::SetPos( D3DXVECTOR3 v_newpos )
{
	v_pos		= v_newpos;
	b_update	= true;


}
//==============================================================//
//																//
//==============================================================//
void vrCamera2::SetPerspective( float fov, float aspect, float zn, float zf )
{
	f_fov		= fov;
	f_aspect	= aspect;
	f_znear		= zn;
	f_zfar		= zf;

	
	UpdatePerspective();

}
//==============================================================//
//																//
//==============================================================//
void vrCamera2::UpdatePerspective( )
{
	D3DXMATRIX	m;
	D3DXMatrixPerspectiveFovLH( &m_proj, f_fov, f_aspect, f_znear, f_zfar );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glLoadMatrixf( (float*)m_proj.m );
	
}
//==============================================================//
//																//
//==============================================================//

D3DXVECTOR3 vrCamera2::GetAxisX() const
{

	D3DXVECTOR3 vAxis;

	vAxis.x = m_view._11;
	vAxis.y = m_view._21;
	vAxis.z = m_view._31;

	return vAxis;


}
//==============================================================//
//																//
//==============================================================//
D3DXVECTOR3 vrCamera2::GetAxisY() const
{

	D3DXVECTOR3 vAxis;

	vAxis.x = m_view._12;
	vAxis.y = m_view._22;
	vAxis.z = m_view._32;

	return vAxis;


}
//==============================================================//
//																//
//==============================================================//
D3DXVECTOR3 vrCamera2::GetAxisZ() const
{

	D3DXVECTOR3 vAxis;

	vAxis.x = m_view._13;
	vAxis.y = m_view._23;
	vAxis.z = m_view._33;

	return vAxis;


}
//==============================================================//
//																//
//==============================================================//

void vrCamera2::RotateAxes( D3DXVECTOR3* v_axes, float f_angle )
{

vrQuaternion q_rot;
D3DXQuaternionRotationAxis( &q_rot, TransformVector( v_axes ), f_angle );
q_orient *= q_rot;

}


//==============================================================//
//																//
//==============================================================//
void vrCamera2::Update()
{

if ( b_update )
{
D3DXMATRIX		m_trans;

D3DXMatrixTranslation( &m_trans, -v_pos.x, -v_pos.y, -v_pos.z );

D3DXMATRIX		m_rot;
D3DXMatrixRotationQuaternion( &m_rot, &vrQuaternion( -q_orient.x, -q_orient.y, -q_orient.z, q_orient.w ) );


D3DXMatrixMultiply( &m_view, &m_trans, &m_rot );

//Load it to OpenGL

glMatrixMode( GL_MODELVIEW );
glLoadMatrixf( (float*)m_view.m );
}


b_update = false;

}

//==============================================================//
//																//
//==============================================================//

void	vrCamera2::SetLookAt( D3DXVECTOR3 v_eye, D3DXVECTOR3 v_at, D3DXVECTOR3 v_up )
{

D3DXMATRIX		m_temp;

D3DXMatrixLookAtLH( &m_temp, &v_eye, &v_at, &v_up );

v_pos = v_at;

D3DXQuaternionRotationMatrix( &q_orient, &m_temp );

b_update = true;

}

//==============================================================//
//																//
//==============================================================//
void vrCamera2::SetTranslate( float f_dist, int dir )
{

	D3DXVECTOR3		v_dir;

	switch( dir )
	{
	case VR_MOVE:
		v_dir = GetAxisZ();
		break;

	case VR_STRAFE:
		v_dir = GetAxisX();
		break;

	case VR_UP:
		v_dir = GetAxisY();
		break;

	}

	v_pos += v_dir * f_dist * f_speed;
	b_update = true;


}
//==============================================================//
//																//
//==============================================================//
void vrCamera2::SetRotate( float f_angle, int dir )
{

switch( dir )
{
case VR_PITCH:

	RotateAxes( &D3DXVECTOR3( 1.0f, 0.0f, 0.0f ), f_angle );
	break;

case VR_ROLL:

	RotateAxes( &D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), f_angle );
	break;

case VR_YAW:

	RotateAxes( &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), f_angle );
	break;
}


D3DXQuaternionNormalize( &q_orient, &q_orient );
b_update = true;

}
//==============================================================//
//																//
//==============================================================//
D3DXVECTOR3* vrCamera2::TransformVector( D3DXVECTOR3 *pAxis )
{

D3DXMATRIX	matRotation;
D3DXVECTOR3	vNewAxis;

D3DXMatrixRotationQuaternion( &matRotation, &q_orient );

	// Transform the queried axis vector by the matrix.
	vNewAxis.x = pAxis->x * matRotation._11 + pAxis->y * matRotation._21 + pAxis->z * matRotation._31 + matRotation._41; 
	vNewAxis.y = pAxis->x * matRotation._12 + pAxis->y * matRotation._22 + pAxis->z * matRotation._32 + matRotation._42;
	vNewAxis.z = pAxis->x * matRotation._13 + pAxis->y * matRotation._23 + pAxis->z * matRotation._33 + matRotation._43;

	memcpy( pAxis, &vNewAxis, sizeof( vNewAxis ) ); // Copy axis.

	return( pAxis );



}


#endif


//****************************************************************************
//****************************************************************************
//****************************************************************************
//***********************//
//***********************//
// Camera Module Follows //
//***********************//
//***********************//
Camera::Camera() {
	pos.x = pos.y = pos.z = 0.0f;
	ang.x = ang.y = ang.z = 0.0f;
	oldpos.x = 0.0f; oldpos.y = 0.0f; oldpos.z = 0.0f;

	f_speedx = 0.0f;
	f_speedz = 0.0f;
	f_deltaspeed = 0.1f;

	sensitivity = 3;

	frustum_p = new vrFrustum();
	
}



Camera::Camera(float x, float y, float z, float ax, float ay, float az) {
	pos.x  = x;
	pos.y  = y;
	pos.z  = z;
	ang.x = ax;
	ang.y = ay;
	ang.z = az;

	oldpos.x = x;
	oldpos.y = y;
	oldpos.z = z;

	f_speedx = 0.0f;
	f_speedz = 0.0f;
	f_deltaspeed = 0.1f;

	sensitivity = 3;

	frustum_p = new vrFrustum();


}



Camera::~Camera() 
{
}



void Camera::MoveRelative() {
	float temp, c, s;

	float x = f_speedx;
	float z = f_speedz;
	float y = 0.0f;
	
	// Rotate around X axis
	s = (float )sin(Deg2Rad(ang.x));
	c = (float )cos(Deg2Rad(ang.x));
	temp = y*c - z*s;
	z = z*c + y*s;
	y = temp;

	// Rotate around Z axis
	s = (float )sin(Deg2Rad(ang.z));
	c = (float )cos(Deg2Rad(ang.z));
	temp = x*c - y*s;
	y = y*c + x*s;
	x = temp;

	// Rotate around Y axis
	s = (float )sin(Deg2Rad(ang.y));
	c = (float )cos(Deg2Rad(ang.y));
	temp = x*c + z*s;
	z = z*c - x*s;
	x = temp;


	oldpos.x = pos.x;
	oldpos.y = pos.y;
	oldpos.z = pos.z;

	pos.x += x;
	pos.y += y;
	pos.z += z;
	
}




void Camera::LookAt(void) 
{
	if ( ang.x > 85.0f ) ang.x = 85.0f;
	if ( ang.x < -85.0f ) ang.x = -85.0f;

	//if ( ang.y > 360.0f ) ang.y = 0.0f;
	//if ( ang.y < 0.0f ) ang.y = 360.0f;
	( ang.y > 360.0f ) ? ang.y = 0.0f : ang.y = ang.y;
	( ang.y < 0.0f ) ? ang.y = 360.0f : ang.y = ang.y;

	float x, y, z, temp, s, c;

	x = y = 0.0f;
	z = 1.0f;
	// Rotate around X axis
	s = (float )sin(Deg2Rad(ang.x));
	c = (float )cos(Deg2Rad(ang.x));
	temp = y*c - z*s;
	z = z*c + y*s;
	y = temp;

	// Rotate around Z axis
	s = (float )sin(Deg2Rad(ang.z));
	c = (float )cos(Deg2Rad(ang.z));
	temp = x*c - y*s;
	y = y*c + x*s;
	x = temp;

	// Rotate around Y axis
	s = (float )sin(Deg2Rad(ang.y));
	c = (float )cos(Deg2Rad(ang.y));
	temp = x*c + z*s;
	z = z*c - x*s;
	x = temp;

	gluLookAt(pos.x, pos.y, pos.z,
		pos.x - x, pos.y - y, pos.z - z,
		0, 1, 0
	);

if ( (f_speedx > -0.001) && (f_speedx < 0.001) ) f_speedx = 0.0f;	//treshold
if ( (f_speedz > -0.001) && (f_speedz < 0.001) ) f_speedz = 0.0f;	//treshold

	if ( f_speedx > 0 ) f_speedx -= f_deltaspeed;
	if ( f_speedx < 0 ) f_speedx += f_deltaspeed;
	if ( f_speedz > 0 ) f_speedz -= f_deltaspeed;
	if ( f_speedz < 0 ) f_speedz += f_deltaspeed;


}

void Camera::Update( )
{
	//Optimize Needed
	LookAt();
	MoveRelative();

	frustum_p->Update();


}

