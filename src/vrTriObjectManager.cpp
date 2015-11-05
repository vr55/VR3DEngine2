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

//
//		THIS FILE IS OUT OF DATE!!!
//

#include "vrTriObjectManager.h"

//==============================================================//
//																//
//==============================================================//


vrTriObjectManager::vrTriObjectManager()
{




}

//==============================================================//
//																//
//==============================================================//
vrTriObjectManager::~vrTriObjectManager()
{


OBJECTLIST::iterator i=ol->begin(), e = ol->end();

vrTriObject *obj;

	while( i!=e )
	{

		obj = *i;
	
		if ( obj != NULL ) delete[] obj;

		i++;
	}


}


//==============================================================//
//																//
//==============================================================//

bool vrTriObjectManager::Create( )
{


ol = new OBJECTLIST();


return true;


}


//==============================================================//
//																//
//==============================================================//

bool vrTriObjectManager::Add( vrTriObject *object )
{

if ( !object ) return false;

ol->insert( ol->end(), object );

return true;

}


//==============================================================//
//																//
//==============================================================//

bool vrTriObjectManager::Add( LPSTR strFileName )
{

if ( !strFileName ) return false;

vrTriObject		*obj = new vrTriObject;

if ( !obj->Load( strFileName ) ) return false;

ol->insert( ol->end(), obj );

return true;



}


//==============================================================//
//																//
//==============================================================//

vrTriObject* vrTriObjectManager::Get( LPSTR strObjectName )
{


ToUpperCase( strObjectName );

OBJECTLIST::iterator i=ol->begin(), e = ol->end();

vrTriObject *obj;

while( i!=e )
	{

		obj = *i;
		if ( strncmp( obj->cName , strObjectName , 32 ) == 0 ) return obj;
		i++;
	}

return NULL;

}

//==============================================================//
//																//
//==============================================================//
vrTriObject* vrTriObjectManager::GetLast( )
{

	if ( !ol->empty() ) return ol->back();
	return NULL;
}

//==============================================================//
//																//
//==============================================================//
vrTriObject* vrTriObjectManager::Get( unsigned int uiID )
{

OBJECTLIST::iterator i=ol->begin(), e = ol->end();

vrTriObject *obj;

while( i!=e )
	{

		obj = *i;
		if ( obj->uiID == uiID ) return obj;
		i++;
	}

return NULL;


}