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

#ifndef __VROCTREENODE_H__
#define __VROCTREENODE_H__
#include "vrVector.h"
#include "vrVertex.h"

//==============================================================//
//																//
//==============================================================//


class vrOctreeNode
{
friend class vrOctree;
friend class vrLandscape2;

public:
	 ~vrOctreeNode();
	vrOctreeNode();
	
	float		GetWidth(){ return fWidth; }
	bool		IsSubDivided(){ return bSubDivided; }
	int			GetPointCount(){ return iPointCount; }
	vrVector3	GetCenter(){ return vCenter; }



private:

	bool			bSubDivided;	//флаг разделения ноды
									//true - если разделена
									//false - если нет
	int				iSubDividedLevel;//уровеь разбиения
	float			fWidth;			//ширина куба для ноды
	vrVector3		vCenter;		//центр куба ноды
	int				iPointCount;	//количество точек в ноде
//	vrVertex		*Vertices_p;	//точки

	int				*Index_p;		//массив индексов //если лист

	vrOctreeNode	*nChildNodes_p[8];//потомки
};


//==============================================================//
//																//
//==============================================================//


#endif