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

#include "vrVector.h"
#include "vrInclude.h"
#include "vrQuat.h"

//������� ����� �������
#ifndef __BORLANDC__
class vrObject
{
public:

	void		Reset();
	void		Move( );
	void		Rotate( );


	void	Render();



		char			c_name[32];		//��� �������
		unsigned int	ui_id;			//�������������
		vrVector3		v_pos;			//������� � ������������

		vrQuaternion	q_orient;		//����������


//�������� ��������
		vrVector3		v_speed;		//������� �������� �������� �� ����
		vrVector3		v_maxspeed;		//������������ ��������

// �������� ��������
		vrVector3		v_rot;			//������� �������� ��������
		vrVector3		v_maxrot;		//������������ �������� ��������

		float			f_roll;
		float			f_pitch;
		float			f_yaw;

private:

	void		MoveX( );
	void		MoveY( );
	void		MoveZ( );




};
#endif
