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
#include "vrVertex.h"

//==============================================================//
//																//
//==============================================================//

vrVertexList::vrVertexList()
{

 first = NULL;
 current = NULL;
 iSize = 0;

// hHeap = HeapCreate( HEAP_GENERATE_EXCEPTIONS, 256000,  0 );

}

//==============================================================//
//																//
//==============================================================//

vrVertexList::~vrVertexList()
{
//HeapDestroy( hHeap );

}
//==============================================================//
//																//
//==============================================================//

VertexListItem::VertexListItem()
{ 
	next = NULL; prev = NULL; data = NULL; 
}


//==============================================================//
//																//
//==============================================================//
void vrVertexList::insert( vrVertex v )
{

	VertexListItem *lItem = new VertexListItem();
//	VertexListItem *lItem = (VertexListItem*)HeapAlloc( hHeap, HEAP_GENERATE_EXCEPTIONS || HEAP_ZERO_MEMORY,  sizeof(VertexListItem) );

	if ( lItem )
	{
		if ( first == NULL ) 
		{
			first = lItem;
			
		}
		if ( current == NULL ) //если это первый элемент в списке
		{
			current = lItem;
			lItem->prev = NULL;
			lItem->next = NULL;

		}
		else if ( current != NULL )
		{
			current->next = lItem;
			lItem->prev = current;
			lItem->next = NULL;


		}
			current = lItem;
			vrVertex *vi = new vrVertex();
		//	vrVertex *vi = ( vrVertex* )HeapAlloc( hHeap, HEAP_GENERATE_EXCEPTIONS || HEAP_ZERO_MEMORY, sizeof(vrVertex));
		//	vi->x = v.x;
		//	vi->y = v.y;
		//	vi->z = v.z;
			vi = &v;
			lItem->data = vi;

			iSize++;

	}


}

//==============================================================//
//																//
//==============================================================//

vrVertex vrVertexList::get()
{

	vrVertex vi;
	vi = *current->data;

	delete[] current->data;	//удаляем данные в текущем элементе
//	int a = HeapFree( hHeap, NULL, &current->data );

	VertexListItem *temp;
	temp = current;
if ( current->prev ) current->prev->next = NULL;//удаляем сам элемент
	current = current->prev;
	delete[] temp;
//	HeapFree( hHeap, NULL, &temp );


	iSize--;

	return vi;
	


}

//==============================================================//
//																//
//==============================================================//

void vrVertexList::empty()
{
/*
VertexListItem *ptr = first;
VertexListItem *temp = new VertexListItem;

while( ptr->next )
{

delete[] ptr->data;
temp = ptr->next;
delete[] ptr;

ptr = temp;
iSize--;
} 
*/
}