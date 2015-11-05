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


/*--------------------------------------------------------------------
this code is based on code of DigiBen		digiben@gametutorials.com		
---------------------------------------------------------------------*/

#ifndef __VROCTREE_H__
#define __VROCTREE_H__

#include <list>
#include <vector>
#include <malloc.h>
#include <assert.h>


#include "vrOctreeNode.h"
#include "vrLandscape.h"
#include "vrUtils.h"
#include "vrFrustum.h"
#include "vrCollision.h"
//#include "vrCamera.h"
#include "vrCamera2.h"

typedef std::vector<int> VERTEX_INDEX;

//==============================================================//
//																//
//==============================================================//


enum eOctreeNodes
{
	TOP_LEFT_FRONT,			// 0
	TOP_LEFT_BACK,			// 1
	TOP_RIGHT_BACK,			// etc...
	TOP_RIGHT_FRONT,
	BOTTOM_LEFT_FRONT,
	BOTTOM_LEFT_BACK,
	BOTTOM_RIGHT_BACK,
	BOTTOM_RIGHT_FRONT
};

//==============================================================//
//																//
//==============================================================//


class vrOctree
{


public: /*SUBROUTINES*/
		vrOctree();				//конмтруктор
		~vrOctree();			//деструктор
		vrOctreeNode*	GetOctree( ){return Octree_p;}
		bool			Create( vrVertex *Vertices_p, int count );
		void			Render( Camera *c_p );
		void			AssignCamera( Camera *c_p );




public: /*VARIABLES*/

		vrVertex			*lpMesh;		//массив точек для построения дерева
		vr_quad				*lpQuad;		//массив треугольников(квадратов) для рендеринга


private: /*SUBROUTINES*/

			void		AssignVertices( int *Vertices_p, int count, vrOctreeNode *node );
			vrVector3	CalcNewNodeCenter( vrVector3 vCenter, float fWidth, int nodeID );
			void		GetSceneDim( vrVertex *Vertices_p, int count );
			void		CreateNode( int *Vertices_p, int count, vrOctreeNode *nParentNode, int nodeID );
			void		RenderNode( vrOctreeNode *node );
			void		RenderDebug( vrOctreeNode *node );

			void		PerformCollide( vrVector3 vTri[3] );



private: /*VARIABLES*/
		int					iMaxPoints;
		int					iMaxSubdivitions;

//		int					iSubdivitionLevel;

		vrOctreeNode*		Octree_p;	//указатель на корневую ноду
		Camera				*camera_p;


};

#endif

