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
#ifndef __VRLANDSCAPE_H__
#define __VRLANDSCAPE_H__

#include "vrCamera.h"
#include "vrCamera2.h"

#include "vrInclude.h"
#include "vrBase.h"
#include "vrMaterial.h"

#include "vrOctree.h"
#include "vrTriObject.h"
#include "vrGameObject.h"



typedef struct tagHeightMap
{

	float	height;			//������ �����
	//float	u;				//���������� ����������
	//float	v;				//---------------------
	int		index;


}HeightMap, *lpHeightMap;




typedef struct
{
	float		*hmap;		//����� ����� ��� �����
	vrOctree	*octree;	//�������� ������ ��� �����


}cell, *lp_cell;

typedef std::list<cell*> CELLS;

//---------------------------------------------------------------
typedef struct 
{
	int numheights;		//���������� ������ � ������ �����
						//�������� ��� ������� ����� ����������
						//����� � ������ ����������
	int	numcells;		//���������� ������


	CELLS	*cells;	//��������� �� �����

} hmap_array;

//==============================================================//
//																//
//==============================================================//
typedef std::vector<int> INT_LIST;	

class vrLandscape2
{

public:
		vrLandscape2();
		bool Load( LPSTR strFileName );


public:
		float	fZoom;
		float	fZoomY;

		void		CreateOctree();


private:

	//	void		CreateOctree();


		void		GetSceneDim();
		void		CreateOctreeNode( INT_LIST points_p, int count, vrOctreeNode *nParentNode, int nodeID );
		void		CreateRoot();
		vrVector3	GetNewNodeCenter( vrVector3 vParentCenter, float fParentWidth, int nodeID );

		int			iMapSize;			//������ ����� ����� width = height
		HeightMap*	fHeightMap;			//����� �����
		int			iMinPointsInNode;	//����������� ���������� ����� � ����


		vrOctreeNode *onOctree;	//�������� ���� ��������� ������



};


//==============================================================//
//																//
//==============================================================//

class vrLandscape
{



public: /*SUBROUTINES*/
				vrLandscape();
				~vrLandscape();
		bool	Load( LPSTR	strFileName );
		bool	LoadHeightMap( LPSTR strFileName );
		BOOL	LoadHeightMap( char *buffer, unsigned int width, unsigned int height );
		bool	LoadAMap( LPSTR strFileName );
		void	Render( Camera *camera_p );
		float	GetHeight( int x, int y ){ return hMap[y*iMapWidth+x];};
		float	ClipPoint( float x, float y );
		BOOL	AccessPoint( float x, float y );
		BOOL	SetMaterial( vrMaterial2 *m ){ if(m) material = m; return TRUE; }
		vrMaterial2* GetMaterial(){ return material; }





public: /*VARIABLES*/

			vrOctree		*lpOctree;
			vrMaterial2		*material;			//��������


			int				iNumOfHeights;	//���������� ������
			int				iMapWidth;		//������ �����
			int				iMapHeight;		//������ �����
			float			Zoom;
			float			ZoomZ;


			vr_quad			*lpQuad;

private: /*SUBROUTINES*/
		void Normalize();
		void RenderHeightMap( );
		void CreateMesh();

		void RenderOctree( Camera *camera_p );
		bool CreateOctree(  );





private: /*VARIABLES*/

			float			*hMap;			//��������� �� ����� �����
			vrVertex		*lpMesh;		// TEMP
			byte			*aMap;			//Access map - ����� ������� � �����������
											//������ ����� �� ����� ����� ������������ �������� 0 ��� 1
											//���� 0 - ����� ���������� ��� ������, ���� 1 - ��������
											//����� ������������ ������� ���� ��� �������� ������

			

			vrVector3		vScale;
			






};

//==============================================================//
//																//
//==============================================================//


#endif
