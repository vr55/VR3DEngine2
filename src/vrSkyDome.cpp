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


#include "vrSkyDome.h"

//==============================================================//
//																//
//==============================================================//
vrSkyDome::vrSkyDome()
{

quadric_p = gluNewQuadric();
material_p = NULL;

}

//==============================================================//
//																//
//==============================================================//
vrSkyDome::~vrSkyDome()
{
	gluDeleteQuadric( quadric_p );

}


//==============================================================//
//																//
//==============================================================//


void vrSkyDome::Render( vrCamera *camera_p )
{
glPushAttrib( GL_ALL_ATTRIB_BITS );

	engine.glStoreMatrix( GL_TEXTURE );

if ( material_p ) material_p->Set();

	engine.glStoreMatrix( GL_MODELVIEW );
//	glLoadIdentity();

	engine.glSetState( GL_CULL_FACE, false );
	engine.glSetState( GL_DEPTH_TEST, false );


	if ( engine.bUseWireframe )glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
if ( camera_p )
{
		glTranslatef( camera_p->Position.x, camera_p->Position.y, camera_p->Position.z );
		//glScalef( camera_p->GetZFar()-250, camera_p->GetZFar()-250, camera_p->GetZFar()-250 );
}
//		gluQuadricDrawStyle( quadric_p, GLU_FILL );
//		gluQuadricOrientation(quadric_p, GLU_INSIDE);
//		gluQuadricTexture( quadric_p, GL_TRUE );
//		gluSphere( quadric_p, camera_p->GetZFar()-250, 12, 12 );
float i, j, d;
for (j=-5; j<=5; j+=1.0f) 
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (i=-5; i<=5; i+=1.0f) 
		{
			d = (float)sqrt(i*i+j*j);

		//	glColor4f( fColor[0], fColor[1], fColor[2], 4-d );
			glTexCoord2f( i/10, j/10 );
			glVertex3f( i, 1-d/3, j );

			d = j + 1.0f;
			d = (float )sqrt(i*i+d*d);

//			glColor4f( fColor[0], fColor[1], fColor[2], 4-d );
			glTexCoord2f( i/10, (j+1.0f)/10 );
			glVertex3f( i, 1-d/3, (j+1.0f) );

		}
		glEnd();
	}
if ( material_p ) material_p->UnSet();

	engine.glRestoreMatrix( GL_MODELVIEW );
	engine.glRestoreMatrix( GL_TEXTURE );


glPopAttrib();
}

//==============================================================//
//																//
//==============================================================//

void vrSkyDome::SetMaterial( vrMaterial *m_p )
{


assert( m_p );
if ( !m_p ) return;

this->material_p = m_p;


}