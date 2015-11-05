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
#ifndef __VRMATERIALMANAGER_H__
#define __VRMATERIALMANAGER_H__

#include <list>
#include "vrEngine.h"
#include "vrMaterial.h"
#include "vrUtils.h"


typedef std::list<vrMaterial*> MATERIALLIST;

class vrMaterialManager
{


public: /*SUBROUTINES*/
		//	vrMaterialManager();
			~vrMaterialManager();

			bool		Create( );

			bool		Add( vrMaterial *material );

			vrMaterial*	Get( LPSTR strMaterialName );
			vrMaterial*	GetLast();
			//vrMaterial*	Get( uint uiID );
public: /*VARIABLES*/



private: /*SUBROUTINES*/



private: /*VARIABLES*/

		MATERIALLIST	*ml;



};

#endif