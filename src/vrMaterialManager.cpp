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
#include "vrMaterialManager.h"

//==============================================================//
//																//
//==============================================================//
vrMaterialManager::~vrMaterialManager()
{

MATERIALLIST::iterator i=ml->begin(), e = ml->end();

vrMaterial *m;

	while( i!=e )
	{

		m = *i;
	
		if ( m != NULL ) delete[] m;

		i++;
	}




}

//==============================================================//
//																//
//==============================================================//


bool vrMaterialManager::Create( )
{


ml = new MATERIALLIST();

return true;



}


//==============================================================//
//																//
//==============================================================//

bool vrMaterialManager::Add( vrMaterial *material )
{

if ( !material ) return false;

ml->insert( ml->end(), material );

return true;



}

//==============================================================//
//																//
//==============================================================//

vrMaterial*	vrMaterialManager::Get( LPSTR strMaterialName )
{

//ToUpperCase( strMaterialName );

MATERIALLIST::iterator i=ml->begin(), e = ml->end();

vrMaterial *m;
if ( IsBadReadPtr( strMaterialName, 32 )  != 0 ) return NULL;
//	 ^^^^^^^^^^^^это называется паранойа -:)
while( i!=e )
	{

		m = *i;
		if ( strncmp( m->cName , strMaterialName , 32 ) == 0 ) return m;
		i++;
	}

return NULL;

}


//==============================================================//
//																//
//==============================================================//
vrMaterial*	vrMaterialManager::GetLast()
{
if ( !ml->empty() ) return ml->back();
return NULL;

}

