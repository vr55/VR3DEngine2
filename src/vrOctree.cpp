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
#include "vrOctree.h"


//==============================================================//
//																//
//==============================================================//



vrOctree::vrOctree()
{

Octree_p			= NULL;
camera_p			= NULL;

iMaxPoints			= 200;		//????????//минимальное количество точек в ноде
iMaxSubdivitions	= 8;		//????????//максимальная глубина разбиения

}


//==============================================================//
//																//
//==============================================================//

vrOctree::~vrOctree()
{

if ( Octree_p ) delete[] Octree_p;

}


//==============================================================//
//																//
//==============================================================//

vrVector3	vrOctree::CalcNewNodeCenter( vrVector3 vCenter, float fWidth, int nodeID )
{

// Initialize the new node center
	vrVector3 vNodeCenter(0, 0, 0);

	// Create a dummy variable to cut down the code size
	vrVector3 vCtr = vCenter;

	// Switch on the ID to see which subdivided node we are finding the center
	switch(nodeID)							
	{
		case TOP_LEFT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y + fWidth/4, vCtr.z + fWidth/4);
			break;

		case TOP_LEFT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y + fWidth/4, vCtr.z - fWidth/4);
			break;

		case TOP_RIGHT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y + fWidth/4, vCtr.z - fWidth/4);
			break;

		case TOP_RIGHT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y + fWidth/4, vCtr.z + fWidth/4);
			break;

		case BOTTOM_LEFT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y - fWidth/4, vCtr.z + fWidth/4);
			break;

		case BOTTOM_LEFT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y - fWidth/4, vCtr.z - fWidth/4);
			break;

		case BOTTOM_RIGHT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y - fWidth/4, vCtr.z - fWidth/4);
			break;

		case BOTTOM_RIGHT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y - fWidth/4, vCtr.z + fWidth/4);
			break;
	}

	// Return the new node center
	return vNodeCenter;




}

//==============================================================//
//																//
//==============================================================//

void vrOctree::GetSceneDim( vrVertex *Vertices_p, int count )
{

if ( !Vertices_p || count <= 0 ) return;

//находим центр
if ( Octree_p )
{
	for ( int i=0; i<count; i++ )
	{
		
		Octree_p->vCenter += vrVector3( Vertices_p[i].x, Vertices_p[i].y, Vertices_p[i].z );

	}

	Octree_p->vCenter /= count;
//находим размеры
float maxWidth = 0.0f, maxHeight = 0.0f, maxDepth = 0.0f;

vrVertex min, max, v;
	for( i = 0; i<count; i++ )
	{

	v = Vertices_p[i];

	if ( v.x > max.x ) max.x = v.x;
	if ( v.y > max.y ) max.y = v.y;
	if ( v.z > max.z ) max.z = v.z;

	if ( v.x <= min.x ) min.x = v.x;
	if ( v.y <= min.y ) min.y = v.y;
	if ( v.z <= min.z ) min.z = v.z;

	}

	maxWidth = sqrt( (max.x-min.x)*(max.x-min.x) );
	maxHeight = sqrt( ( max.z - min.z ) * ( max.z - min.z ));
	maxDepth = sqrt( (max.y - min.y)*(max.y - min.y));



	maxWidth *= 2;		maxHeight *= 2;		maxDepth *= 2;

	//Octree_p->fWidth = __max( maxWidth, maxHeight );
        #ifdef __BORLANDC__
              Octree_p->fWidth = std::max( maxWidth, maxHeight );
        #else
              Octree_p->fWidth = __max( maxWidth, maxHeight );
        #endif


}

Octree_p->iPointCount = count;

}


//==============================================================//
//																//
//==============================================================//

bool vrOctree::Create( vrVertex *Vertices_p, int count )
{

Octree_p	= new vrOctreeNode;
lpMesh		= Vertices_p;

//определяем размеры сцены
GetSceneDim( Vertices_p, count );


int *TOP_LEFT_FRONT_LIST	= new int[ count ];
int TOP_LEFT_FRONT_COUNT	= 0;

int *TOP_LEFT_BACK_LIST		= new int[ count ];
int TOP_LEFT_BACK_COUNT		= 0;

int *TOP_RIGHT_BACK_LIST	= new int[ count ];
int TOP_RIGHT_BACK_COUNT	= 0;

int *TOP_RIGHT_FRONT_LIST	= new int[ count ];
int TOP_RIGHT_FRONT_COUNT	= 0;

int *BOTTOM_LEFT_FRONT_LIST = new int[ count ];
int BOTTOM_LEFT_FRONT_COUNT = 0;

int *BOTTOM_LEFT_BACK_LIST	= new int[ count ];
int BOTTOM_LEFT_BACK_COUNT  = 0;

int *BOTTOM_RIGHT_BACK_LIST = new int[ count ];
int BOTTOM_RIGHT_BACK_COUNT	= 0;

int *BOTTOM_RIGHT_FRONT_LIST= new int[ count ];
int BOTTOM_RIGHT_FRONT_COUNT=0;


vrVertex v;
int index;
vrVector3 vCtr = Octree_p->vCenter;
//FILE *f = fopen( "Mesh", "w+");

for ( int i=0; i<count; i++ )
{

v = Vertices_p[i];
index = Vertices_p[i].index;

//fprintf( f, "%i: %f %f %f \n", i, v.x, v.y, v.z );

if( (v.x <= vCtr.x) && (v.y <= vCtr.y) && (v.z <= vCtr.z) ) 
{
	BOTTOM_LEFT_BACK_LIST[ BOTTOM_LEFT_BACK_COUNT ] = index;
	BOTTOM_LEFT_BACK_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y <= vCtr.y) && (v.z <= vCtr.z) ) 
{
	BOTTOM_RIGHT_BACK_LIST[ BOTTOM_RIGHT_BACK_COUNT ] = index;
	BOTTOM_RIGHT_BACK_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y <= vCtr.y) && (v.z >= vCtr.z) ) 
{
	BOTTOM_RIGHT_FRONT_LIST[ BOTTOM_RIGHT_FRONT_COUNT ] = index;
	BOTTOM_RIGHT_FRONT_COUNT++;
}


else if( (v.x <= vCtr.x) && (v.y <= vCtr.y) && (v.z >= vCtr.z) ) 
{
	BOTTOM_LEFT_FRONT_LIST[ BOTTOM_LEFT_FRONT_COUNT ] = index;
	BOTTOM_LEFT_FRONT_COUNT++;
}

else if( (v.x <= vCtr.x) && (v.y >= vCtr.y) && (v.z <= vCtr.z) ) 
{
	TOP_LEFT_BACK_LIST[ TOP_LEFT_BACK_COUNT ] = index;
	TOP_LEFT_BACK_COUNT++;
}

else if( (v.x <= vCtr.x) && (v.y >= vCtr.y) && (v.z >= vCtr.z) ) 
{
	TOP_LEFT_FRONT_LIST[ TOP_LEFT_FRONT_COUNT ] = index;
	TOP_LEFT_FRONT_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y >= vCtr.y) && (v.z >= vCtr.z) ) 
{
	TOP_RIGHT_FRONT_LIST[ TOP_RIGHT_FRONT_COUNT ] = index;
	TOP_RIGHT_FRONT_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y >= vCtr.y) && (v.z <= vCtr.z) ) 
{
	TOP_RIGHT_BACK_LIST[ TOP_RIGHT_BACK_COUNT ] = index;
	TOP_RIGHT_BACK_COUNT++;
}


}
//fclose(f);
//*******************************************************************
Octree_p->bSubDivided = true;			//нода разделена
Octree_p->iSubDividedLevel = 0;			//уровень разделения 0

CreateNode( TOP_LEFT_FRONT_LIST, TOP_LEFT_FRONT_COUNT, this->Octree_p, TOP_LEFT_FRONT );
CreateNode( TOP_LEFT_BACK_LIST, TOP_LEFT_BACK_COUNT, this->Octree_p, TOP_LEFT_BACK );
CreateNode( TOP_RIGHT_BACK_LIST, TOP_RIGHT_BACK_COUNT, this->Octree_p, TOP_RIGHT_BACK );
CreateNode( TOP_RIGHT_FRONT_LIST, TOP_RIGHT_FRONT_COUNT, this->Octree_p, TOP_RIGHT_FRONT );
CreateNode( BOTTOM_LEFT_FRONT_LIST, BOTTOM_LEFT_FRONT_COUNT, this->Octree_p, BOTTOM_LEFT_FRONT );
CreateNode( BOTTOM_LEFT_BACK_LIST, BOTTOM_LEFT_BACK_COUNT, this->Octree_p, BOTTOM_LEFT_BACK );
CreateNode( BOTTOM_RIGHT_BACK_LIST, BOTTOM_RIGHT_BACK_COUNT, this->Octree_p, BOTTOM_RIGHT_BACK );
CreateNode( BOTTOM_RIGHT_FRONT_LIST, BOTTOM_RIGHT_FRONT_COUNT, this->Octree_p, BOTTOM_RIGHT_FRONT );



return true;
}



//==============================================================//
//																//
//==============================================================//


void	vrOctree::CreateNode( int *Vertices_p, int count, vrOctreeNode *nParentNode, int nodeID )
{

//int count = Vertices_p.size();
if ( count <=0 ) return;
if ( !Vertices_p ) return;

if ( nParentNode )
{

	vrOctreeNode *nCurrentNode = ( vrOctreeNode*)malloc( sizeof( vrOctreeNode ) );
	if ( !nCurrentNode ) return;
	ZeroMemory( nCurrentNode, sizeof( vrOctreeNode) );
	vrVector3 vCtr = CalcNewNodeCenter( nParentNode->GetCenter(), nParentNode->GetWidth(), nodeID );

	nCurrentNode->vCenter				= vCtr;
	nCurrentNode->iPointCount			= count;
	nCurrentNode->fWidth				= nParentNode->GetWidth()/2;
	nParentNode->nChildNodes_p[nodeID]	= nCurrentNode;
	nCurrentNode->bSubDivided			= true;
	nCurrentNode->iSubDividedLevel		= nParentNode->iSubDividedLevel + 1;



	//если количество точек в ноде меньше заданного, или глубина разделения максимальна, создаем лист
	if ( (count <= iMaxPoints) || ( nParentNode->iSubDividedLevel >= iMaxSubdivitions ))
	{
		AssignVertices( Vertices_p, count, nCurrentNode );
		nCurrentNode->bSubDivided	= false;//если есть лист, то флаг разбиения false

//		nCurrentNode->vCenter		= nParentNode->GetCenter();
//		nCurrentNode->fWidth		= nParentNode->GetWidth();


	for ( int i=0; i<8; i++ ) nCurrentNode->nChildNodes_p[i] = NULL;
		return;

	}
//	vrVector3 vCtr = nParentNode->GetCenter();



int *TOP_LEFT_FRONT_LIST	= new int[ count ];
int TOP_LEFT_FRONT_COUNT	= 0;

int *TOP_LEFT_BACK_LIST		= new int[ count ];
int TOP_LEFT_BACK_COUNT		= 0;

int *TOP_RIGHT_BACK_LIST	= new int[ count ];
int TOP_RIGHT_BACK_COUNT	= 0;

int *TOP_RIGHT_FRONT_LIST	= new int[ count ];
int TOP_RIGHT_FRONT_COUNT	= 0;

int *BOTTOM_LEFT_FRONT_LIST = new int[ count ];
int BOTTOM_LEFT_FRONT_COUNT = 0;

int *BOTTOM_LEFT_BACK_LIST	= new int[ count ];
int BOTTOM_LEFT_BACK_COUNT  = 0;

int *BOTTOM_RIGHT_BACK_LIST = new int[ count ];
int BOTTOM_RIGHT_BACK_COUNT	= 0;

int *BOTTOM_RIGHT_FRONT_LIST= new int[ count ];
int BOTTOM_RIGHT_FRONT_COUNT=0;

///////////////////////////////////////////////////////////////////

int			index;
vrVertex	v;
for ( int i=0; i<count; i++ )
{
	index = Vertices_p[i];
	v = lpMesh[ index ]; 

if( (v.x <= vCtr.x) && (v.y <= vCtr.y) && (v.z <= vCtr.z) ) 
{
	BOTTOM_LEFT_BACK_LIST[ BOTTOM_LEFT_BACK_COUNT ] = index;
	BOTTOM_LEFT_BACK_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y <= vCtr.y) && (v.z <= vCtr.z) ) 
{
	BOTTOM_RIGHT_BACK_LIST[ BOTTOM_RIGHT_BACK_COUNT ] = index;
	BOTTOM_RIGHT_BACK_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y <= vCtr.y) && (v.z >= vCtr.z) ) 
{
	BOTTOM_RIGHT_FRONT_LIST[ BOTTOM_RIGHT_FRONT_COUNT ] = index;
	BOTTOM_RIGHT_FRONT_COUNT++;
}


else if( (v.x <= vCtr.x) && (v.y <= vCtr.y) && (v.z >= vCtr.z) ) 
{
	BOTTOM_LEFT_FRONT_LIST[ BOTTOM_LEFT_FRONT_COUNT ] = index;
	BOTTOM_LEFT_FRONT_COUNT++;
}

else if( (v.x <= vCtr.x) && (v.y >= vCtr.y) && (v.z <= vCtr.z) ) 
{
	TOP_LEFT_BACK_LIST[ TOP_LEFT_BACK_COUNT ] = index;
	TOP_LEFT_BACK_COUNT++;
}

else if( (v.x <= vCtr.x) && (v.y >= vCtr.y) && (v.z >= vCtr.z) ) 
{
	TOP_LEFT_FRONT_LIST[ TOP_LEFT_FRONT_COUNT ] = index;
	TOP_LEFT_FRONT_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y >= vCtr.y) && (v.z >= vCtr.z) ) 
{
	TOP_RIGHT_FRONT_LIST[ TOP_RIGHT_FRONT_COUNT ] = index;
	TOP_RIGHT_FRONT_COUNT++;
}

else if( (v.x >= vCtr.x) && (v.y >= vCtr.y) && (v.z <= vCtr.z) ) 
{
	TOP_RIGHT_BACK_LIST[ TOP_RIGHT_BACK_COUNT ] = index;
	TOP_RIGHT_BACK_COUNT++;
}


}


delete[] Vertices_p;
Vertices_p = NULL;

//**********************************************************************
//рекурсия

CreateNode( TOP_LEFT_FRONT_LIST, TOP_LEFT_FRONT_COUNT, nCurrentNode, TOP_LEFT_FRONT );
CreateNode( TOP_LEFT_BACK_LIST, TOP_LEFT_BACK_COUNT, nCurrentNode, TOP_LEFT_BACK );
CreateNode( TOP_RIGHT_BACK_LIST, TOP_RIGHT_BACK_COUNT, nCurrentNode, TOP_RIGHT_BACK );
CreateNode( TOP_RIGHT_FRONT_LIST, TOP_RIGHT_FRONT_COUNT, nCurrentNode, TOP_RIGHT_FRONT );
CreateNode( BOTTOM_LEFT_FRONT_LIST, BOTTOM_LEFT_FRONT_COUNT, nCurrentNode, BOTTOM_LEFT_FRONT );
CreateNode( BOTTOM_LEFT_BACK_LIST, BOTTOM_LEFT_BACK_COUNT, nCurrentNode, BOTTOM_LEFT_BACK );
CreateNode( BOTTOM_RIGHT_BACK_LIST, BOTTOM_RIGHT_BACK_COUNT, nCurrentNode, BOTTOM_RIGHT_BACK );
CreateNode( BOTTOM_RIGHT_FRONT_LIST, BOTTOM_RIGHT_FRONT_COUNT, nCurrentNode, BOTTOM_RIGHT_FRONT );



}




}

//==============================================================//
//																//
//==============================================================//

void vrOctree::AssignVertices( int *Vertices_p, int count, vrOctreeNode *node )
{

if ( Vertices_p )
{
//node->Index_p = new int[ count ];

node->Index_p = (int*)malloc( count * sizeof(int));

for ( int i=0; i<count; i++ )
{

node->Index_p[i] = Vertices_p[i];


}
delete[] Vertices_p;
Vertices_p = NULL;
}
}


//==============================================================//
//																//
//==============================================================//

void	vrOctree::Render( Camera *c_p )
{

	this->camera_p = c_p;
if ( !Octree_p ) return;
if ( !camera_p->frustum_p->CubeInFrustum( Octree_p->vCenter, Octree_p->fWidth/2 ) ) return;

//RenderDebug( Octree_p );


RenderNode( Octree_p->nChildNodes_p[0] );
RenderNode( Octree_p->nChildNodes_p[1] );
RenderNode( Octree_p->nChildNodes_p[2] );
RenderNode( Octree_p->nChildNodes_p[3] );
RenderNode( Octree_p->nChildNodes_p[4] );
RenderNode( Octree_p->nChildNodes_p[5] );
RenderNode( Octree_p->nChildNodes_p[6] );
RenderNode( Octree_p->nChildNodes_p[7] );

//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

}

//==============================================================//
//																//
//==============================================================//

void	vrOctree::RenderDebug( vrOctreeNode *node )
{
		vrVector3 quad[4];
		vrVector3 ctr = node->GetCenter();
		float w = node->GetWidth()/2;
		glPushAttrib( GL_POLYGON_MODE );
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		engine.glSetState( GL_TEXTURE_2D, false );
		glLineWidth( 2 );
		glColor3f( 0.0, 1.0, 0.0 );


		quad[0] = vrVector3( ctr.x - w, ctr.y - w, ctr.z - w);
		quad[1] = vrVector3( ctr.x - w, ctr.y - w, ctr.z + w);
		quad[2] = vrVector3( ctr.x - w, ctr.y + w, ctr.z + w);
		quad[3] = vrVector3( ctr.x - w, ctr.y + w, ctr.z - w);

		engine.glBeginScene( GL_QUADS );
		glColor3f( 0.0, 1.0, 0.0 );
		engine.glRenderPrimitive( 4, &quad[0] );
		engine.glEndScene();


		quad[0] = vrVector3( ctr.x - w, ctr.y + w, ctr.z - w);
		quad[1] = vrVector3( ctr.x + w, ctr.y + w, ctr.z - w);
		quad[2] = vrVector3( ctr.x + w, ctr.y + w, ctr.z + w);
		quad[3] = vrVector3( ctr.x - w, ctr.y + w, ctr.z + w);

		engine.glBeginScene( GL_QUADS );
		glColor3f( 0.0, 1.0, 0.0 );
		engine.glRenderPrimitive( 4, &quad[0] );
		engine.glEndScene();

		quad[0] = vrVector3( ctr.x + w, ctr.y + w, ctr.z - w);
		quad[1] = vrVector3( ctr.x + w, ctr.y + w, ctr.z + w);
		quad[2] = vrVector3( ctr.x + w, ctr.y - w, ctr.z + w);
		quad[3] = vrVector3( ctr.x + w, ctr.y - w, ctr.z - w);

		engine.glBeginScene( GL_QUADS );
		glColor3f( 0.0, 1.0, 0.0 );
		engine.glRenderPrimitive( 4, &quad[0] );
		engine.glEndScene();

		quad[0] = vrVector3( ctr.x - w, ctr.y - w, ctr.z - w);
		quad[1] = vrVector3( ctr.x - w, ctr.y - w, ctr.z + w);
		quad[2] = vrVector3( ctr.x + w, ctr.y - w, ctr.z + w);
		quad[3] = vrVector3( ctr.x + w, ctr.y - w, ctr.z - w);

		engine.glBeginScene( GL_QUADS );
		glColor3f( 0.0, 1.0, 0.0 );
		engine.glRenderPrimitive( 4, &quad[0] );
		engine.glEndScene();

		//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glPopAttrib();
		engine.glSetState( GL_TEXTURE_2D, true );



}
//==============================================================//
//																//
//==============================================================//

void	vrOctree::RenderNode( vrOctreeNode *node )
{

if( node ) 
{
	if ( engine.bShowBBox )
	{

		RenderDebug( node );

	}

	//если нода непопадает во фрустум, то пропускаем ее
	if ( camera_p->frustum_p->CubeInFrustum( node->vCenter, node->fWidth/2 ) ) 
	{

		if ( node->IsSubDivided() ) //если нода разделена, проходим глубже
		{

			RenderNode( node->nChildNodes_p[0] );
			RenderNode( node->nChildNodes_p[1] );
			RenderNode( node->nChildNodes_p[2] );
			RenderNode( node->nChildNodes_p[3] );
			RenderNode( node->nChildNodes_p[4] );
			RenderNode( node->nChildNodes_p[5] );
			RenderNode( node->nChildNodes_p[6] );
			RenderNode( node->nChildNodes_p[7] );


		}

		else //если нет, то рисуем ее
		{
		if ( !node->Index_p ) return;

		engine.glBeginScene( GL_QUADS );

		int			index;
		for (  int i=0; i<node->iPointCount; i++ )
		{

			index = node->Index_p[i];

				if ( engine.frustum.QuadInFrustum( lpQuad[ index ] ) )
				engine.glRenderPrimitive( 4, &lpQuad[ index ].v[0] );

			


		}

		engine.glEndScene();

		}
	}
}

}

//==============================================================//
//																//
//==============================================================//

void	vrOctree::AssignCamera( Camera *c_p )
{

if ( c_p ) this->camera_p = c_p;

}

//==============================================================//
//																//
//==============================================================//
void	vrOctree::PerformCollide( vrVector3 vTri[3] )
{
if ( !camera_p ) return;

//	vrVector3 m_vPos = camera_p->Position;
	




/*
	vrVector3 vNormal = Normal(vTri);
	vrVector3 m_vPos;

	float dist = 0.0f;

	m_vPos = camera_p->Position;

	int classification = ClassifySphere( m_vPos, vNormal, vTri[0], camera_p->f_radius, dist );

	if(classification == INTERSECTS) 
	{
		vrVector3 vOffset = vNormal * dist;
		vrVector3 vIntersection = m_vPos - vOffset;

		if(InsidePolygon(vIntersection, vTri, 3) ||
			EdgeSphereCollision(m_vPos, vTri, 3, camera_p->f_radius ))// g_current.radius/2
		{
			vOffset = GetCollisionOffset(vNormal, camera_p->f_radius, dist);
					
			camera_p->Position = m_vPos.x+vOffset;
		}
	}


*/
}

