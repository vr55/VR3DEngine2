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
#ifndef __VRCAMERA_H__
#define __VRCAMERA_H__



#include "vrEngine.h"
#include "vrVector.h"
#include "vrMatrix.h"

#define EPS		   1.19e-07f		//epsilon

class vrCamera
{

public: /*SUBROUTINES*/
		vrCamera();
		~vrCamera();

		void Update( void );
		void Apply( void );

		void SetPosition( vrVector3 &vec );

//rotations
		void RotateX( const float fAngle );
		void RotateY( const float fAngle );
		void RotateZ( const float fAngle );

		void RotateWX( const float fAngle );
		void RotateWY( const float fAngle );
		void RotateWZ( const float fAngle );

//movement
		void MoveForward( const float dist );
		void MoveUp( const float dist );
		void Strafe( const float dist );

		

public: /*VARIABLES*/

		vrMatrix4		matrix;


private: /*SUBROUTINES*/

		void Rotate( vrVector3 &vAxis, const float fAngle );


private: /*VARIABLES*/

		unsigned int	uiViewPort[4];		//viewport камеры 
											// первые два элемента - координаты левого нижнего угла
											// вторые две - ширина и высота
		vrVector3		vTarget;			// позиция камеры


		float			fFov;				// угол обзора камеры
		float			fZnear;				// ближняя плоскость отсечения
		float			fZfar;				// дальняя плоскость отсечения
		

};





#endif