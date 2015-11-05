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
#include "vrResourceMgr.h"

//==============================================================//
//																//
//==============================================================//


vrResourceManager::vrResourceManager()
{
	t_list = NULL;
	m_list = NULL;
	o_list = NULL;
	f_list = NULL;
	w_list = NULL;

}

//==============================================================//
//																//
//==============================================================//

vrResourceManager::~vrResourceManager()
{

Free();

}
 //==============================================================//
//																//
//==============================================================//
void vrResourceManager::Free()
{

if ( t_list )t_list->clear();
if ( m_list )m_list->clear();
if ( o_list )o_list->clear();
if ( f_list )f_list->clear();
if ( w_list )w_list->clear();

}
//==============================================================//
//																//
//==============================================================//

bool vrResourceManager::Init()
{
e_log.WriteOut("[STATUS] Initializing Resource Manager\n");

	t_list = new T_LIST(); if ( !t_list ) return false;
	m_list = new M_LIST(); if ( !m_list ) return false;
	o_list = new O_LIST(); if ( !o_list ) return false;
	f_list = new F_LIST(); if ( !f_list ) return false;
	w_list = new W_LIST(); if ( !w_list ) return false;


return true;
}


//==============================================================//
//																//
//==============================================================//

bool vrResourceManager::AddTexture( LPSTR strFileName )
{
assert( t_list );

vrTexture *t = new vrTexture(); if( !t ) return false;

if ( !t->LoadFromFile( strFileName )) return false;
ToUpperCase( t->cName );
if ( t_list ) t_list->insert( t_list->end(), t );

return true;

}

//==============================================================//
//																//
//==============================================================//

bool vrResourceManager::AddTexture( vrTexture *texture_p )
{
assert( texture_p );
if ( !texture_p ) return false;
ToUpperCase( texture_p->cName );
if ( t_list ) t_list->insert( t_list->end(), texture_p );

return true;
}


//==============================================================//
//																//
//==============================================================//

vrTexture* vrResourceManager::GetTexture( LPSTR strTextureName )
{

ToUpperCase( strTextureName );

T_LIST::iterator i = t_list->begin();

vrTexture *texture;

while( i != t_list->end() )
	{

		texture = *i;
		if ( strncmp( texture->cName, strTextureName , 32 ) == 0 ) return texture;
		i++;
	}


return NULL;

}

//==============================================================//
//																//
//==============================================================//
vrTexture* vrResourceManager::GetTexture( int a )
{
//Unstable. Not Tested
assert( t_list );

T_LIST::iterator i = t_list->begin() + a;

//vrTexture *t = *i;

return *i;

}
//==============================================================//
//																//
//==============================================================//
void vrResourceManager::RemoveTexture( LPSTR strTextureName )
{
ToUpperCase( strTextureName );

T_LIST::iterator i = t_list->begin();

vrTexture *texture;

while( i != t_list->end() )
	{

		texture = *i;
		if ( strncmp( texture->cName, strTextureName , 32 ) == 0 )
				{
				//if ( texture->bUploaded ) texture->Unload();
				delete texture;
				t_list->erase( i );
				texture = NULL;

				break;
				}
		i++;
	}

return;


}
//==============================================================//
//																//
//==============================================================//

void vrResourceManager::ClearTextures()
{

T_LIST::iterator i = t_list->begin();

vrTexture *texture;

while( i != t_list->end() )
	{

		texture = *i;
		//if ( texture->bUploaded ) texture->Unload();
		delete texture;
       	i++;
	}

t_list->clear();

}

//==============================================================//
//																//
//==============================================================//

bool vrResourceManager::AddMaterial( LPSTR strFileName )
{

return true;
}

//==============================================================//
//																//
//==============================================================//

bool vrResourceManager::AddMaterial( vrMaterial2 *material_p )
{

assert( material_p );
assert( m_list );

if ( !material_p ) return false;
ToUpperCase( material_p->cName );
if ( m_list ) m_list->insert( m_list->end(), material_p );

return true;

}

//==============================================================//
//																//
//==============================================================//

vrMaterial2* vrResourceManager::GetMaterial( LPSTR strMaterialName )
{

ToUpperCase( strMaterialName );
assert( m_list );
if ( !m_list ) return NULL;

M_LIST::iterator i = m_list->begin();

vrMaterial2 *material;

while( i != m_list->end() )
	{

		material = *i;
		if ( strncmp( material->cName, strMaterialName , 64 ) == 0 ) return material;
		i++;
	}

return NULL;


}
//==============================================================//
//																//
//==============================================================//
void vrResourceManager::RemoveMaterial( LPSTR strMaterialName )
{
ToUpperCase( strMaterialName );
assert( m_list );
if ( !m_list ) return;

M_LIST::iterator i = m_list->begin();

vrMaterial2 *material;

while( i != m_list->end() )
	{

		material = *i;
		if ( strncmp( material->cName, strMaterialName , 64 ) == 0 )
        {
		m_list->erase( i );
		delete material;
        break;
        }
		i++;
	}

return ;

}

//==============================================================//
//																//
//==============================================================//

void vrResourceManager::ClearMaterials()
{
M_LIST::iterator i = m_list->begin();

vrMaterial2 *material;

while( i != m_list->end() )
	{
	 material = *i;
	 delete material;

	 i++;
	}
 m_list->clear();
 
}

//==============================================================//
//																//
//==============================================================//

bool vrResourceManager::AddObject( LPSTR strFileName )
{

if ( !strFileName ) return false;

assert( o_list );
if ( !o_list ) return false;

vrTriObject2 *object = new vrTriObject2();
if ( !object ) return false;

if ( !object->Load( strFileName ) ) return false;
ToUpperCase( object->cName );
o_list->insert( o_list->end(), object );

return true;


}

//==============================================================//
//																//
//==============================================================//

bool vrResourceManager::AddObject( vrTriObject2 *object_p )
{
assert( object_p );
assert( o_list );
if ( !object_p ) return false;
ToUpperCase( object_p->cName );
if ( o_list ) o_list->insert( o_list->end(), object_p );
return true;

}
//==============================================================//
//																//
//==============================================================//
vrTriObject2* vrResourceManager::GetObject( int a )
{

assert( o_list );
if ( !o_list ) return NULL;

O_LIST::iterator i = o_list->begin() + a;

return *i;


}
//==============================================================//
//																//
//==============================================================//

vrTriObject2* vrResourceManager::GetObject( LPSTR strObjectName )
{

ToUpperCase( strObjectName );
assert( o_list );
if ( !o_list ) return NULL;

O_LIST::iterator i = o_list->begin();

vrTriObject2 *object;

while( i != o_list->end() )
	{

		object = *i;
		ToUpperCase( object->cName );
		if ( strncmp( object->cName, strObjectName , 32 ) == 0 ) return object;
		i++;
	}

return NULL;

}

//==============================================================//
//																//
//==============================================================//

void vrResourceManager::RemoveObject( LPSTR strObjectName )
{

ToUpperCase( strObjectName );
assert( o_list );
if ( !o_list ) return;

O_LIST::iterator i = o_list->begin();

vrTriObject2 *object;

while( i != o_list->end() )
	{

		object = *i;
		ToUpperCase( object->cName );
		if ( strncmp( object->cName, strObjectName , 32 ) == 0 )
        {
		o_list->erase( i );
		delete object;
        break;

        }
		i++;
	}

return;



}
//==============================================================//
//																//
//==============================================================//
bool vrResourceManager::AddWrapper( ObjectWrapper *wrapper_p )
{
assert( wrapper_p );
assert( w_list );

if ( !wrapper_p ) return false;
if ( w_list ) w_list->insert( w_list->end(), wrapper_p );

//идентификатором является порядковый номер
wrapper_p->uiID = w_list->size();

return true;

}

//==============================================================//
//																//
//==============================================================//

ObjectWrapper* vrResourceManager::GetWrapper( int a )
{
assert( w_list );
//я здесь немного неуверен
//по идее такой подход к использованию вектора должен привести к
//более быстрому доступу к элементам, имено поэтому 
//используем vector а не list, но я неуверен
W_LIST::iterator i = w_list->begin() + a;

ObjectWrapper *o = *i;

return o;

}
//==============================================================//
//																//
//==============================================================//
void vrResourceManager::ClearWrapper()
{
assert( w_list );

if ( w_list ) w_list->clear();

}
//==============================================================//
//																//
//==============================================================//
ObjectWrapper* vrResourceManager::GetWrapper( LPSTR strName )
{

	W_LIST::iterator i = w_list->begin();

ObjectWrapper *o;

	while ( i != w_list->end() )
	{
		o = *i;
		if ( strncmp( o->cName, strName, 32 ) == NULL ) return o;

		i++;
	}

return NULL;
}

//==============================================================//
//																//
//==============================================================//
bool vrResourceManager::AddShader( glShader *shader_p )
{
assert( s_list );
assert ( shader_p );

if ( !shader_p ) return false;
s_list->insert( s_list->end(), shader_p );

return true;
}

