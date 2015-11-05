#ifndef __VRCAMERA_H__
#define __VRCAMERA_H__
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


//#include "vrEngine.h"
#include "vrInclude.h"
#include "vrVector.h"
#include "vrMatrix.h"

#include "vrBase.h"


class vrCamera
{
friend class vrConsole;
public:
	vrCamera( unsigned int x, unsigned int y, unsigned int width, unsigned int height );
	vrCamera();
	 ~vrCamera();
	 BOOL	bActive;		//флаг активности камеры

	void	Update( );
	void	ApplyChanges();

//-----------Set Functions----------------------------------------
	void SetAspect( float aspect );
	void SetZNear( float znear );
	void SetZFar( float zfar );
	void SetFov( float fov );
	void SetPosition( float x, float y, float z );
	void SetPosition( vrVector3 newposition );
	void SetSensitivity( float sens );
	void SetYaw( float yaw );
	void SetRoll( float roll);
	void SetPitch( float pitch );



//-----------Get Functions----------------------------------------
	vrVector3	GetPosition( void ) { return this->Position; };
	float		GetZNear(){ return Znear;}

	float		GetZFar(){ return Zfar; }

	vrVector3		Position;			//Camera position
	float			Speed;
	float			Fov;				//Field of view

	float			f_radius;

	void Strafe( float amount );
	void Move( float amount );
	void RotateX( float amount );
	void RotateY( float amount );
	void RotateZ( float amount );

	void Rotate( float pitch, float yaw, float roll );


public:
		char			cName[32];

private:

	void			GetDirection( void );
	float			sensitivity;



	float			Roll;				//Around the z axis
	float			Pitch;				//Around the x axis
	float			Yaw;				//Around the y axis

	float			Aspect;
	float			Znear;
	float			Zfar;

	unsigned int	uiViewPort[4];		//viewport

	vrVector3		Direction;			//Camera direction

	float			PitchLock;
	float			RollLock;
	float			YawLock;


	bool			bSmoothCamera;



};


#endif