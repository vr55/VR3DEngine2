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

#ifndef __VROCTREENODE_H__
#define __VROCTREENODE_H__
#include "vrVector.h"
#include "vrVertex.h"

//==============================================================//
//																//
//==============================================================//


class vrOctreeNode
{
friend class vrOctree;
friend class vrLandscape2;

public:
	 ~vrOctreeNode();
	vrOctreeNode();
	
	float		GetWidth(){ return fWidth; }
	bool		IsSubDivided(){ return bSubDivided; }
	int			GetPointCount(){ return iPointCount; }
	vrVector3	GetCenter(){ return vCenter; }



private:

	bool			bSubDivided;	//���� ���������� ����
									//true - ���� ���������
									//false - ���� ���
	int				iSubDividedLevel;//������ ���������
	float			fWidth;			//������ ���� ��� ����
	vrVector3		vCenter;		//����� ���� ����
	int				iPointCount;	//���������� ����� � ����
//	vrVertex		*Vertices_p;	//�����

	int				*Index_p;		//������ �������� //���� ����

	vrOctreeNode	*nChildNodes_p[8];//�������
};


//==============================================================//
//																//
//==============================================================//


#endif