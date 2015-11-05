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

#ifndef __VRCAMERA2_H__
#define __VRCAMERA2_H__

#include "vrInclude.h"

#include "vrMatrixDX.h"
#include "vrObject.h"
#include "vrFrustum.h"
#include "vrBase.h"
#include "vrInclude.h"

#include "vrCommonStruct.h"
 #ifndef __BORLANDC__
class vrCamera2
{


public:
				vrCamera2();
				void	Init();
				void	Update();

				void	SetPos( D3DXVECTOR3 v_newpos );
				void	SetLookAt( D3DXVECTOR3 v_eye, D3DXVECTOR3 v_at, D3DXVECTOR3 v_up );
				void	SetPerspective( float fov, float aspect, float zn, float zf );


				void	Move( float f_dist ){ SetTranslate( f_dist, VR_MOVE ); };
				void	Strafe( float f_dist ){ SetTranslate( f_dist, VR_STRAFE ); };
				void	Up( float f_dist ){ SetTranslate( f_dist, VR_UP ); };


				void	Roll( float f_angle ){ SetRotate( f_angle, VR_ROLL ); };
				void	Pitch( float f_angle ){ SetRotate( f_angle, VR_PITCH ); };
				void	Yaw( float f_angle ) { SetRotate( f_angle, VR_YAW ); };


private:/*SUBROUTINES*/
				 D3DXVECTOR3 GetAxisX() const;
				 D3DXVECTOR3 GetAxisY() const;
				 D3DXVECTOR3 GetAxisZ() const;
					void RotateAxes( D3DXVECTOR3* v_axes, float f_angle );

				void		SetTranslate( float f_dist, int dir );
				void		SetRotate( float f_angle, int dir );

				void		UpdatePerspective();

				D3DXVECTOR3* TransformVector( D3DXVECTOR3 *pAxis );



private:/*VARIABLES*/

				float			f_fov;
				float			f_aspect;
				float			f_znear;
				float			f_zfar;

				D3DXVECTOR3		v_pos;
				D3DXVECTOR3		v_offset;
				vrQuaternion	q_orient;
				D3DXMATRIX		m_view;
				D3DXMATRIX		m_proj;

				float			f_speed;

				bool			b_update;


};
#endif



//*****************************************************************************

/*
Module     : Camera
Purpose    : Does OpenGL camera things
Details    : v0.01
Methods    : 
Author (c) : TopcaT

*/
class Camera {
public:
	Camera();
	Camera(float x, float y, float z, float ax, float ay, float az);
	~Camera();

	// Public methods
	void MoveRelative();
	void LookAt(void);

	void	Update();


	vec3 pos, ang;
	vec3 oldpos;

	float	f_speedx, f_speedz; 
	float	f_deltaspeed;

	float	sensitivity;
	vrFrustum	*frustum_p;


private:
	// OpenGL view information
	GLint viewPort[4];
	GLdouble modelViewMatrix[16];
	GLdouble projectionMatrix[16];


};


#endif
