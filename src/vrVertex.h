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
#ifndef __VRVERTEX_H__
#define __VRVERTEX_H__

#include <windows.h>

//==============================================================//
//																//
//==============================================================//


class vrVertex
{
public:
	vrVertex(){ x = 0; y = 0; z = 0; r = 0.0f; g = 1.0f; b = 1.0f; index=0; }
	//~vrVertex();

public:
	float r,g,b;	//цвет

	float x,y,z;	//координаты
	float u0,v0;	//координаты первого слоя текстуры
	float u1,v1;	//координаты второго слоя текстуры
//	float u2,v2;	//координаты третьего слоя текстуры
	float nx,ny,nz;	//нормаль
	int		index;


};

//==============================================================//
//																//
//==============================================================//
class VertexListItem
{
public:
	VertexListItem();

	VertexListItem	*next;
	VertexListItem	*prev;

	vrVertex		*data;

} ;
//==============================================================//
//																//
//==============================================================//

class vrVertexList
{
public:
	vrVertexList();
	~vrVertexList();
	void		insert( vrVertex v );
	vrVertex	get();
	int			size(){ return iSize; }
	void		empty();

private:
		VertexListItem	*first;		//указатель на первый злемент в списке
		VertexListItem	*current;	//указатель на текущий элемент
		int				iSize;

		HANDLE			hHeap;

};


#endif