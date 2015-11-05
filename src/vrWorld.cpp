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
#include "vrWorld.h"


//***************************************************************
//---GLOBAL
vrWorld		world;
//***************************************************************

//==============================================================//
//																//
//==============================================================//


vrWorld::vrWorld()
{

camera			= NULL;
r_mgr			= NULL;

owSelected_p	= NULL;
wrappers_p		= NULL;
font_p			= NULL;
landscape_p		= NULL;


}

//==============================================================//
//																//
//==============================================================//

BOOL	vrWorld::AddFont( vrMaterial2 *f_material )
{

assert( f_material );

if ( f_material ) if ( font_p ) font_p->Init( f_material );
return TRUE;

}
//==============================================================//
//																//
//==============================================================//
void vrWorld::Free()
{
 r_mgr->Free();
 wrappers_p->clear();


}

//==============================================================//
//																//
//==============================================================//
void vrWorld::Prepare()
{

//Upload Textures to OpenGL
e_log.WriteOut( "[STATUS] Uploading Textures to OpenGL\n" );

int c = r_mgr->TextureCount();
vrTexture	*t;
int cnt = 0;

if ( c > 0 )
{
	for ( int i=0; i < c; i++ )
	{
		if( t = r_mgr->GetTexture( i ) )
		{
			t->Upload();
			cnt++;
			/*delete t->bData; t->bData = NULL;*/
		}

	}

}
e_log.WriteOut( "[STATUS] %i Textures Uploaded\n", cnt );


//Create Display Lists
e_log.WriteOut( "[STATUS] Creating Display Lists\n" );

c = r_mgr->ObjectCount();
vrTriObject2	*o;

if ( c>0 )
{
	for ( int i=0; i < c; i++ )
	{
		o = r_mgr->GetObject( i ); 
		if ( o ) o->Compile();
	}


}


}

//==============================================================//
//																//
//==============================================================//

bool	vrWorld::Init( )
{
if ( !r_mgr )
{
	r_mgr = new vrResourceManager();
	if ( r_mgr )this->r_mgr->Init();
}

wrappers_p = new WRAPPERS();	if( !wrappers_p ) return false;

font_p = new vrFont(); if ( !font_p ) return false;

return true;
}
//==============================================================//
//																//
//==============================================================//

bool vrWorld::LoadRes( LPSTR strFileName )
{
/*
	if  ( r_mgr->Load( strFileName ) ) console.AddString( "Loaded Data from File %s", strFileName );
	else {
		e_log.WriteOut("[ERROR] Error While Loading File %s\n", strFileName );
		console.AddString( "Error While Loading File %s", strFileName );
		}
*/
return true;
}
//==============================================================//
//																//
//==============================================================//


bool vrWorld::Replace( LPSTR strFileName )
{
	r_mgr->ClearWrapper();

	if  ( r_mgr->Load( strFileName ) ) console.AddString( "Loaded Data from File %s", strFileName );
	else console.AddString( "Error While Loading File %s", strFileName );

return true;
}
//==============================================================//
//																//
//==============================================================//
BOOL vrWorld::AddWrapper( vrWrapper *w )
{

if ( wrappers_p ) wrappers_p->push_back( w );

return TRUE;
}
//==============================================================//
//																//
//==============================================================//

int vrWorld::Render( void )
{
//wglMakeCurrent( GetDC( engine.hWindowHandle ), engine.hGLResourceContext );

	WRAPPERS::iterator i = wrappers_p->begin();
	vrWrapper *w;
	while( i != wrappers_p->end() )
	{
		w = *i;
		if ( w ) w->Render();

		i++;
	}

	//if ( landscape_p ) landscape_p->Render( NULL );

//wglMakeCurrent(NULL, NULL) ;

return 1; //?????????????????????почему 1??????
}


//==============================================================//
//																//
//==============================================================//

bool vrWorld::AddCamera( )
{

if ( this->camera ) delete camera;

vrCamera *camera_p = new vrCamera();

assert( camera_p );

if ( !camera_p ) return false;


this->camera = camera_p;

return true;

}

//==============================================================//
//		вызывается каждый фрейм									//
//==============================================================//

void vrWorld::Update()
{

//assert( camera );

if ( camera ) camera->Update();

engine.UpdateFrustum();

engine.ResetTimer();
engine.uiPolyCount = 0;

}
//==============================================================//
//																//
//==============================================================//
bool	vrWorld::Save( LPSTR strFileName )
{
return true;
}
//==============================================================//
//																//
//==============================================================//

BOOL vrWorld::AddLandscape( LPSTR strFileName )
{

landscape_p = new vrLandscape();
if ( landscape_p )landscape_p->LoadHeightMap( strFileName );



return TRUE;
}
//==============================================================//
//																//
//==============================================================//

BOOL vrWorld::AddLandscape( char *buffer, unsigned int width, unsigned int height )
{
	landscape_p = new vrLandscape();
	if ( landscape_p ) landscape_p->LoadHeightMap( buffer, width, height );

	return TRUE;
}

//==============================================================//
//																//
//==============================================================//


bool vrWorld::Load( LPSTR strFileName )
{

FILE	*f;
char	buffer[255];
char	dummy[255];
float	f1, f2, f3;


if ( ( f = fopen( strFileName, "rt" ) ) == NULL ) 
{
	e_log.WriteOut("[ERROR] Unable to Open Resource File %s\n", strFileName );
	return false;
}
while ( !feof(f) )
{
	//ищем начало тэга <WRAPPER>
	while ( strstr( buffer, "<wrapper>\n") == NULL ) 
	{
		if ( feof(f) ) { fclose(f);return true; }
		fgets( (char*)buffer, 255, f );
	}

	//создаем новый wrapper
	vrWrapper	*w = new vrWrapper();
	if ( !w ) return false;

	//ищем параметр "object"
	while( strstr( buffer, "object" ) == NULL ) fscanf(f, "%s %s", buffer, dummy );
	//объекты должны быть уже загружены!!!!
	w->object = r_mgr->GetObject( dummy );
	if ( !w->object ) 
	{
		e_log.WriteOut("[ERROR] Wrapper trying to access to not loaded object %s\n", dummy );
		console.AddString("[WARNING] Wrapper trying to access to not loaded object %s\n", dummy );
		delete[] w;
		return false;
	}

	//TODO: A little buggy, need to be rewrite

	//ищем параметр "pos"
	while( strstr( buffer, "pos" ) == NULL ) fscanf(f, "%s %f %f %f", buffer, &f1, &f2, &f3 );
	w->pos.x = f1;
	w->pos.y = f2;
	w->pos.z = f3;

	//ищем параметр "orient"
	while( strstr( buffer, "orient" ) == NULL ) fscanf(f, "%s %f %f %f", buffer, &f1, &f2, &f3 );
	w->orient.x = f1;
	w->orient.y = f2;
	w->orient.z = f3;

	//ищем параметр "scale"
	while( strstr( buffer, "scale" ) == NULL ) fscanf(f, "%s %f %f %f", buffer, &f1, &f2, &f3 );
	w->scale.x = f1;
	w->scale.y = f2;
	w->scale.z = f3;

	while ( strstr( buffer, "</wrapper>\n") == NULL ) fgets( (char*)buffer, 255, f );
	AddWrapper( w );

}

fclose( f );
return true;
}

