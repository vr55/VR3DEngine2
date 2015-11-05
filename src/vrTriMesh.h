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

#include "vrInclude.h"
#include "vrCommonStruct.h"

#include "vrTriFace.h"
#include "vrMaterial.h"

//==============================================================//
//																//
//==============================================================//
//Last Edit 12.09.2k5
//


//		OUTOFDATED
//		���� ���� ������� � ������ ��������������

class vrTriMesh2
{
public:

		char		cName[NAME_MAXCHARS];	//��� ����
		int			iNumSurfaces;			//���������� ������������
		lp_surface	surfaces;				//�����������

		int			iID;					//�������������

		//�� ������ ����������� ������ ���� ���� ��������




private:



};
//==============================================================//
//																//
//==============================================================//



class vrTriMesh
{

friend class vrTriObject;

public:/*SUBROUTINES*/
					vrTriMesh();
					~vrTriMesh();
		void		Render( );
		void		CreateBV();				//CreateBoundingVolumes



public:/*VARIABLES*/
		char	cName[32];		//���

		int		iNumVerts;		//���������� �����
		int		iNumFaces;		//���������� ����������
		int		iNumTVerts;		//���������� ���������� ���������
		int		iNumNormals;	//���������� ��������
		//���������� �������� ����� ���������� ���������� TODO: ��� �������� ���������.
																//����� ������� ������� � ������ �����

		unsigned int	uiID;	//�������������, ���������� ����� -1

private:
		void		RenderBV();
	//	void		SetMaterial( MeshParams param );

private:
		vrTriFace	*faces;		//���������
		vrVector3	*verts;		//�����
		vrVector3	*normals;	//�������
		vrVector3	*tverts;	//���������� ����������
		vrVector3	AABB[2];	//Bounding Box//����� ������ BBox ��� ���������� ����� 2 �����:
								//���������� ������ ������� �������� ���� � �������� �������� �������� ����
		vrSphere	BSphere;	//Bounding Sphere


		vrMaterial	material;	//��������
//TODO
//������ ��-�������� �������� ������ ���� �������� ��� ������ ��������� � �����������(��� ������ ����� � ���������)
//�� ����� ��������� ��� ��������� � �������� ������� �������� ������ �������
// ��� ��� ���� �������� ��������� ����� ���� �������
};

