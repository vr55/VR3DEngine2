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
#include "vrGameObject.h"
#include "vrInclude.h"
//==============================================================//
//																//
//==============================================================//
vrWrapper::vrWrapper()
{
object = NULL;
pos.x = 0.0;
pos.y = 0.0;
pos.z = 0.0;

orient.x = 0.0f;
orient.y = 0.0f;
orient.z = 0.0f;

scale.x	= 1.0f;
scale.y = 1.0f;
scale.z = 1.0f;

}
//==============================================================//
//																//
//==============================================================//
void vrWrapper::Render()
{

Begin();

	if ( object ) 
	{
		vrTriObject2 *o = ( vrTriObject2* )object;
		
		if ( o ) o->Render();

	}

End();




}
//==============================================================//
//																//
//==============================================================//
void vrWrapper::Begin()
{

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
//	glLoadIdentity();

	glTranslatef( pos.x, pos.y, pos.z );
	glScalef( scale.x, scale.y, scale.z );
	glRotatef( orient.x, 1.0, 0.0, 0.0 );
	glRotatef( orient.y, 0.0, 1.0, 0.0 );
	glRotatef( orient.z, 0.0, 0.0, 1.0 );


}

//==============================================================//
//																//
//==============================================================//
void vrWrapper::End()
{

	glPopMatrix();

}



//==============================================================//
//																//
//==============================================================//


vrMaterial2* vrWrapper::GetObjectMaterial()
{
if ( !object ) return NULL;

	vrTriObject2 *o = ( vrTriObject2* )object;
	return	&o->skin_p->materials[0];
		

}
