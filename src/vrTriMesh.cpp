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


#include "vrTriMesh.h"


//==============================================================//
//																//
//==============================================================//

vrTriMesh::vrTriMesh()
{

	faces		= NULL;
	verts		= NULL;
	normals		= NULL;
	tverts		= NULL;

	iNumVerts	= 0;
	iNumFaces	= 0;
	iNumTVerts	= 0;
	iNumNormals = 0;
	uiID	= -1;


}


//==============================================================//
//																//
//==============================================================//

vrTriMesh::~vrTriMesh()
{

if ( faces )	delete[] faces;
if ( verts )	delete[] verts;
if ( normals )	delete[] normals;
if ( tverts )	delete[] tverts;

}

//==============================================================//
//																//
//==============================================================//

void vrTriMesh::CreateBV()
{
float		fMinX, fMinY, fMinZ;
float		fMaxX, fMaxY, fMaxZ;
vrVector3	vPoint;

fMinX = verts[0].x; fMinY = verts[0].y; fMinZ = verts[0].z;
fMaxX = verts[0].x;	fMaxY = verts[0].y; fMaxZ = verts[0].z;

for ( int i = 0; i < iNumVerts; i++ )	//цикл по всем точкам
{


	vPoint = verts[i];
	if ( vPoint.x > fMaxX ) fMaxX = vPoint.x;
	if ( vPoint.y > fMaxY ) fMaxY = vPoint.y;
	if ( vPoint.z > fMaxZ ) fMaxZ = vPoint.z;

	if ( vPoint.x < fMinX ) fMinX = vPoint.x;
	if ( vPoint.y < fMinY ) fMinY = vPoint.y;
	if ( vPoint.z < fMinZ ) fMinZ = vPoint.z;

}

AABB[0].x = fMinX; AABB[0].y = fMinY; AABB[0].z = fMinZ;
AABB[1].x = fMaxX; AABB[1].y = fMaxY; AABB[1].z = fMaxZ;


//Sphere
float a = (AABB[1].x - AABB[0].x ) * (AABB[1].x - AABB[0].x ); 
float b = (AABB[1].y - AABB[0].y ) * (AABB[1].y - AABB[0].y ); 
float c = (AABB[1].z - AABB[0].z ) * (AABB[1].z - AABB[0].z ); 

//float d = a + b + c;

BSphere.radius = sqrt( a + b + c )/2;

BSphere.radius == ( AABB[1] - AABB[0] )/2; //?????????????????????????????

/*BSphere.center.x = ( AABB[1].x - AABB[0].x )/2;
BSphere.center.y = ( AABB[1].y - AABB[0].y )/2;
BSphere.center.z = ( AABB[1].z - AABB[0].z )/2;
*/
}
//==============================================================//
//##############################################################//
//==============================================================//

void vrTriMesh::Render()
{
if ( engine.bUseWireframe ) glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

engine.glBeginScene( GL_TRIANGLES );

vrVertex tri[3];

for ( int i=0; i<iNumFaces; i++ )
{

	tri[0].r = 1; 	tri[1].r = 1; tri[2].r = 1;	
	tri[0].g = 1;	tri[1].g = 1; tri[2].g = 1;
	tri[0].b = 1;	tri[1].b = 1; tri[2].b = 1; 

	tri[0].nx = normals[faces[i].an].x;	tri[1].nx = normals[faces[i].bn].x;	tri[2].nx = normals[faces[i].cn].x;
	tri[0].ny = normals[faces[i].an].y;	tri[1].ny = normals[faces[i].bn].y;	tri[2].ny = normals[faces[i].cn].y;
	tri[0].nz = normals[faces[i].an].z;	tri[1].nz = normals[faces[i].bn].z;	tri[2].nz = normals[faces[i].cn].z;

	tri[0].u0 = tverts[faces[i].at].x;	tri[1].u0 = tverts[faces[i].bt].x;	tri[2].u0 = tverts[faces[i].ct].x;	
	tri[0].v0 = tverts[faces[i].at].y;	tri[1].v0 = tverts[faces[i].bt].y;	tri[2].v0 = tverts[faces[i].ct].y;

	tri[0].x = verts[faces[i].a].x;		tri[1].x = verts[faces[i].b].x;		tri[2].x = verts[faces[i].c].x;
	tri[0].y = verts[faces[i].a].y;		tri[1].y = verts[faces[i].b].y;		tri[2].y = verts[faces[i].c].y;
	tri[0].z = verts[faces[i].a].z;		tri[1].z = verts[faces[i].b].z;		tri[2].z = verts[faces[i].c].z;

	engine.glRenderPrimitive( 3, (vrVertex*)tri );

}

engine.glEndScene();

if ( engine.bShowBBox )
{
	RenderBV();
}

}

//==============================================================//
//																//
//==============================================================//

void vrTriMesh::RenderBV()//BV - Bounding Volumes
{

vrVertex	v[23];


v[0].x = AABB[0].x; v[0].y = AABB[0].y; v[0].z = AABB[0].z; 
v[1].x = AABB[1].x; v[1].y = AABB[0].y; v[1].z = AABB[0].z;
v[2].x = AABB[1].x; v[2].y = AABB[0].y; v[2].z = AABB[1].z;
v[3].x = AABB[0].x; v[3].y = AABB[0].y; v[3].z = AABB[1].z;
v[4].x = AABB[0].x; v[4].y = AABB[0].y; v[4].z = AABB[0].z;
 
v[5].x = AABB[0].x; v[5].y = AABB[1].y; v[5].z = AABB[0].z; 
v[6].x = AABB[1].x; v[6].y = AABB[1].y; v[6].z = AABB[0].z; 
v[7].x = AABB[1].x; v[7].y = AABB[0].y; v[7].z = AABB[0].z;
v[8].x = AABB[0].x; v[8].y = AABB[0].y; v[8].z = AABB[0].z;
 
v[9].x = AABB[0].x; v[9].y = AABB[0].y; v[9].z = AABB[1].z; 
v[10].x = AABB[0].x; v[10].y = AABB[1].y; v[10].z = AABB[1].z; 
v[11].x = AABB[0].x; v[11].y = AABB[1].y; v[11].z = AABB[0].z;
v[12].x = AABB[0].x; v[12].y = AABB[0].y; v[12].z = AABB[1].z; 

 
v[13].x = AABB[1].x; v[13].y = AABB[0].y; v[13].z = AABB[1].z; 
v[14].x = AABB[1].x; v[14].y = AABB[1].y; v[14].z = AABB[1].z; 
v[15].x = AABB[0].x; v[15].y = AABB[1].y; v[15].z = AABB[1].z; 
v[16].x = AABB[0].x; v[16].y = AABB[0].y; v[16].z = AABB[1].z; 
v[17].x = AABB[1].x; v[17].y = AABB[0].y; v[17].z = AABB[1].z; 


v[18].x = AABB[1].x; v[18].y = AABB[0].y; v[18].z = AABB[0].z; 
v[19].x = AABB[1].x; v[19].y = AABB[1].y; v[19].z = AABB[0].z; 
v[20].x = AABB[1].x; v[20].y = AABB[1].y; v[20].z = AABB[1].z;
v[21].x = AABB[1].x; v[21].y = AABB[0].y; v[21].z = AABB[1].z;
v[22].x = AABB[1].x; v[22].y = AABB[0].y; v[22].z = AABB[0].z; 




engine.glSetState( GL_TEXTURE_2D, false );
glColor3f( 0.0f, 1.0f, 0.0f );

glLineWidth( 2 );
glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
engine.glBeginScene( GL_LINE_STRIP );

//	glColor3f( 1.0f, 0.0f, 0.0f );

	engine.glRenderPrimitive( 23, (vrVertex*)v );

engine.glEndScene( );


//glPointSize( 50 );
//engine.glBeginScene( GL_POINTS );
//glVertex3f( BSphere.center.x , BSphere.center.y , BSphere.center.z );
//engine.glEndScene();
//glPointSize( 1 );

//Sphere
/*
engine.glStoreMatrix( GL_MODELVIEW );



glTranslatef( BSphere.center.x , BSphere.center.y , BSphere.center.z  );

GLUquadricObj * sphere = gluNewQuadric();
gluQuadricDrawStyle( sphere, GLU_LINE );
gluQuadricOrientation(sphere, GLU_OUTSIDE);

gluSphere ( sphere, BSphere.radius, 12, 12 );

engine.glRestoreMatrix( GL_MODELVIEW ); 

gluDeleteQuadric( sphere );

glColor3f( 1.0f, 1.0f, 1.0f );
*/
engine.glSetState( GL_TEXTURE_2D, true );


glLineWidth( 1 );


}