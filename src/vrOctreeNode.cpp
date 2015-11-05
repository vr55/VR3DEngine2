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
#include "vrOctreeNode.h"
#include "vrInclude.h"


vrOctreeNode::vrOctreeNode()
{

bSubDivided		= false;
fWidth			= 0.0f;
vCenter			= vrVector3( 0.0f, 0.0f, 0.0f );
iPointCount		= 0;
//Vertices_p		= NULL;
Index_p			= NULL;
iSubDividedLevel=0;
ZeroMemory( nChildNodes_p, sizeof( vrOctreeNode ) );

}

//==============================================================//
//																//
//==============================================================//


vrOctreeNode::~vrOctreeNode()
{

//if ( Vertices_p ) delete[] Vertices_p;
for ( int i=0; i<8; i++ )
if ( nChildNodes_p[i] ) delete nChildNodes_p[i];
if ( Index_p ) delete[] Index_p;


}
