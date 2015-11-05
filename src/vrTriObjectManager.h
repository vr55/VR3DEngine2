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
#ifndef __VRTRIOBJECTMANAGER_H__
#define __VRTRIOBJECTMANAGER_H__


#include <list>
//#include "vrEngine.h"
#include "vrTriObject.h"


typedef std::list<vrTriObject*> OBJECTLIST;

class vrTriObjectManager
{

public: /*SUBROUTINES*/
					vrTriObjectManager();
					~vrTriObjectManager();
		bool		Create( );

		bool		Add( vrTriObject *object );
		bool		Add( LPSTR strFileName );

		vrTriObject* Get( LPSTR strObjectName );
		vrTriObject* Get( unsigned int uiID );
		vrTriObject* GetLast();
		//vrTriObject* GetFirst();



public: /*VARIABLES*/



private: /*SUBROUTINES*/



private: /*VARIABLES*/

		OBJECTLIST			*ol;



};


#endif