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
/*

	This code implement come ideas from Alan Baylis 




*/

#include "vrObject.h"


//==============================================================//
//																//
//==============================================================//
#ifndef __BORLANDC__

void vrObject::Reset()
{

v_pos.Reset();
q_orient.Reset();
v_speed.Reset();
v_rot.Reset();

v_maxspeed.x = v_maxspeed.y = v_maxspeed.z = 200.0f;

f_roll = f_pitch = f_yaw = 0.0f;


}
//==============================================================//
//																//
//==============================================================//

void	vrObject::Move( )
{
/*
if ( v_speed.x > v_maxspeed.x ) v_speed.x = v_maxspeed.x;
if ( v_speed.y > v_maxspeed.y ) v_speed.y = v_maxspeed.y;
if ( v_speed.z > v_maxspeed.z ) v_speed.z = v_maxspeed.z;
*/

//v_speed.x = ( v_speed.x > v_maxspeed.x ) ? v_maxspeed.x : v_speed.x;
if ( v_speed.x !=0 ) MoveX( );
if ( v_speed.y !=0 ) MoveY( );
if ( v_speed.z !=0 ) MoveZ( ); 


}

//==============================================================//
//																//
//==============================================================//

void vrObject::MoveX()
{

    vrQuaternion TempQuat;
    vrQuaternion TempQuat2;

	D3DXQuaternionRotationYawPitchRoll( &TempQuat2, 0.0, -90.0*(pi/180), 0.0 );

	D3DXQuaternionMultiply( &TempQuat, &q_orient, &TempQuat2 );
	vrVector3 dir;
	TempQuat.GetDirectionVector( &dir );

    v_pos.x += dir.x * v_speed.x;
    v_pos.y += dir.y * v_speed.x;
    v_pos.z += dir.z * v_speed.x;


}

//==============================================================//
//																//
//==============================================================//
void vrObject::MoveY( )
{

    vrQuaternion TempQuat;
    vrQuaternion TempQuat2;


	D3DXQuaternionRotationYawPitchRoll( &TempQuat2, 90.0*(pi/180), 0.0, 0.0 );


	D3DXQuaternionMultiply( &TempQuat, &q_orient, &TempQuat2 );

	vrVector3 dir;
	TempQuat.GetDirectionVector( &dir );

    v_pos.x += dir.x * v_speed.y;
    v_pos.y += dir.y * v_speed.y;
    v_pos.z += dir.z * v_speed.y;


}


//==============================================================//
//																//
//==============================================================//
void vrObject::MoveZ( )
{
	vrVector3 dir;
	q_orient.GetDirectionVector( &dir );

    v_pos.x += dir.x * v_speed.z;
    v_pos.y += dir.y * v_speed.z;
    v_pos.z += dir.z * v_speed.z;


}

//==============================================================//
//																//
//==============================================================//


void	vrObject::Rotate( )
{
/*
if ( v_rot.x > v_maxrot.x ) v_rot.x = v_maxrot.x;
if ( v_rot.y > v_maxrot.y ) v_rot.y = v_maxrot.y;
if ( v_rot.z > v_maxrot.z ) v_rot.z = v_maxrot.z;
*/

vrQuaternion	temp_quat;

//D3DXQuaternionRotationYawPitchRoll( &temp_quat, v_rot.x*pi/2, v_rot.y*pi/2, v_rot.z*pi/2 );
D3DXQuaternionRotationYawPitchRoll( &temp_quat, f_yaw*pi/2, f_pitch*pi/2, f_yaw*pi/2 );

D3DXQuaternionMultiply( &q_orient, &q_orient, &temp_quat );


}

#endif
