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
#include "vrManager.h"


//==============================================================//
//																//
//==============================================================//


vrManager::vrManager()
{

	ol = new OBJECTLIST;

}


//==============================================================//
//																//
//==============================================================//


bool vrManager::Add( void *object )
{

if ( !object ) return false;

ol->insert( ol->end(), object );

return true;


}

//==============================================================//
//																//
//==============================================================//


void* vrManager::GetFirst( )
{

itr = ol->begin();
return *itr;

}

//==============================================================//
//																//
//==============================================================//
void* vrManager::GetNext( )
{

if( itr == ol->end() ) return NULL;		//?????здесь немного непонятно

itr++;

if ( *itr ) return *itr; else return NULL;

}

