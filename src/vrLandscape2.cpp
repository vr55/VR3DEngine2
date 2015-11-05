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


#include "vrLandscape.h"

/*
enum eOctreeNodes
{
	TOP_LEFT_FRONT,			// 0
	TOP_LEFT_BACK,			// 1
	TOP_RIGHT_BACK,			// etc...
	TOP_RIGHT_FRONT,
	BOTTOM_LEFT_FRONT,
	BOTTOM_LEFT_BACK,
	BOTTOM_RIGHT_BACK,
	BOTTOM_RIGHT_FRONT
};
*/

//==============================================================//
//																//
//==============================================================//


vrLandscape2::vrLandscape2()
{

	fHeightMap			= NULL;
	onOctree			= NULL;

	fZoom				= 1.0f;
	fZoomY				= 1.0f;

	iMinPointsInNode	= 200;

}


//==============================================================//
//																//
//==============================================================//
bool vrLandscape2::Load ( LPSTR strFileName )
{

	HANDLE					bmpHandle;
	BITMAPFILEHEADER		FileHeader;
	BITMAPINFOHEADER		InfoHeader;
	DWORD					rb;
	RGBQUAD					palette[256];


	bmpHandle = CreateFile( strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0 );
	if( bmpHandle == INVALID_HANDLE_VALUE )
	{

	return false;

	}

	ReadFile( bmpHandle, &FileHeader, sizeof( FileHeader ), &rb, NULL );//читаем заголовок

	if ( rb != sizeof( FileHeader ) ) return false;
	if ( FileHeader.bfType != 19778 ) return false;


	ReadFile( bmpHandle, &InfoHeader, sizeof( InfoHeader ), &rb, NULL );

	if( rb != sizeof( InfoHeader ) ) return false;

	if ( InfoHeader.biBitCount != 8 ) 
	{

	CloseHandle( bmpHandle );
	//e_log.WriteOut("[ERROR] 8bit Bitmaps Only" );
	return false;

	}

	if ( InfoHeader.biWidth != InfoHeader.biHeight ) return false;

	iMapSize = InfoHeader.biWidth;

	DWORD bitmapLenght = InfoHeader.biSizeImage;

	if ( bitmapLenght == 0 ) bitmapLenght = InfoHeader.biWidth * InfoHeader.biHeight;


	SetFilePointer( bmpHandle, sizeof( FileHeader ) + sizeof( InfoHeader ), NULL, FILE_BEGIN );

//палитра

	ReadFile( bmpHandle, palette, sizeof( palette ), &rb, NULL );

	if ( rb != sizeof( palette )  ) return NULL;

	SetFilePointer( bmpHandle, FileHeader.bfOffBits, NULL, FILE_BEGIN );

	byte	*img = new byte[ bitmapLenght ];
	ReadFile( bmpHandle, img, bitmapLenght, &rb, NULL );

	//преобразуем byte в float
	HeightMap *fData = (HeightMap*)malloc( iMapSize*iMapSize*sizeof(HeightMap) );

	for( int i = 0; i<(iMapSize*iMapSize); i++ )
	{

	fData[i].height = (float)img[i];
	fData[i].index	= i;



	}

	delete img;
	fHeightMap = fData;

	//fHeightMap = fData;


	return true;


}

//==============================================================//
//																//
//==============================================================//

void vrLandscape2::CreateOctree()

{
float		x, y, z;
vrVector3	vCtr;
vrVector3	vPt;


//Lists of node's points
INT_LIST	top_left_front;
INT_LIST	top_right_front;
INT_LIST	top_right_back;
INT_LIST	top_left_back;

INT_LIST	bottom_left_front;
INT_LIST	bottom_right_front;
INT_LIST	bottom_right_back;
INT_LIST	bottom_left_back;



//создаем корневую ноду
	onOctree = new vrOctreeNode();


	GetSceneDim();


//for ( int i=0; i<iMapSize*iMapSize; i++ )
//	list.push_back( i );
	vCtr = onOctree->vCenter;

//Распределяем точки
//*****************************************************************************
for ( int i=0; i< (iMapSize*iMapSize); i++ )
{

//TODO: Очень нерационально вычислять каждый раз координаты, если они неизменны
	vPt.z = (int)(fHeightMap[i].index / iMapSize);

	vPt.x = ( fHeightMap[i].index - ( vPt.z * iMapSize ));

	vPt.y = fHeightMap[i].height;

	vPt.x *= fZoom;
	vPt.z *= fZoom;
	vPt.y *= fZoomY;


	if ( ( vPt.x <= vCtr.x ) && ( vPt.y <= vCtr.y ) && ( vPt.z <= vCtr.z ) )
		bottom_left_back.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y <= vCtr.y) && (vPt.z <= vCtr.z) )
		bottom_right_back.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y <= vCtr.y) && (vPt.z >= vCtr.z) )
		bottom_right_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x <= vCtr.x) && (vPt.y <= vCtr.y) && (vPt.z >= vCtr.z) )
		bottom_left_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x <= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z <= vCtr.z) )
		top_left_back.push_back( fHeightMap[i].index );

	else if ( (vPt.x <= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z >= vCtr.z) )
		top_left_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z >= vCtr.z) )
		top_right_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z <= vCtr.z) )
		top_right_back.push_back( fHeightMap[i].index );

}
//****************************************************************************




CreateOctreeNode( top_left_front,		0, onOctree, TOP_LEFT_FRONT );
CreateOctreeNode( top_left_back,		0, onOctree, TOP_LEFT_BACK );
CreateOctreeNode( top_right_back,		0, onOctree, TOP_RIGHT_BACK );
CreateOctreeNode( top_right_front,		0, onOctree, TOP_RIGHT_FRONT );
CreateOctreeNode( bottom_left_front,	0, onOctree, BOTTOM_LEFT_FRONT );
CreateOctreeNode( bottom_left_back,		0, onOctree, BOTTOM_LEFT_BACK );
CreateOctreeNode( bottom_right_back,	0, onOctree, BOTTOM_RIGHT_BACK );
CreateOctreeNode( bottom_right_front,	0, onOctree, BOTTOM_RIGHT_FRONT );


/*
vCtr = onOctree->vCenter;
for ( int i=0; i<iMapSize*iMapSize; i++ )
{

//ищем координаты
	z = (int)(i / iMapSize);
	x = ( i - ( z*iMapSize ));
	y = fHeightMap[i].height;

	if ( ( x <= vCtr.x ) && ( y >= vCtr.y ) && ( z >= vCtr.z ) )
	{
		top_left_front.push_back( i );	
	}



}
*/
//int a = top_left_front.size();
	//CreateOctreeNode( ___, iMapSize*iMapSize, onOctree, ___ );


}
//==============================================================//
//																//
//==============================================================//

void vrLandscape2::CreateRoot()
{




}
//==============================================================//
//																//
//==============================================================//
void vrLandscape2::GetSceneDim()
{

if ( !fHeightMap ) return;


vrVector3 temp;

float x = 0.0f;
float y = 0.0f;
float z = 0.0f;

vrVector3	min, max;

for ( int i=0; i<iMapSize*iMapSize; i++ )
{//проходим по всем точкам на карте высот

//ищем координаты центра
	z = (int)(i / iMapSize);
	x = ( i - ( z*iMapSize ));
	y = fHeightMap[i].height;

	x *= fZoom;
	z *= fZoom;
	y *= fZoomY;
	temp += vrVector3( x, y, z );

//и размеры

	if ( x > max.x ) max.x = x;
	if ( y > max.y ) max.y = y;
	if ( z > max.z ) max.z = z;

	if ( x <= min.x ) min.x = x;
	if ( y <= min.y ) min.y = y;
	if ( z <= min.z ) min.z = z;


}
	onOctree->vCenter  = temp / (iMapSize*iMapSize);

	float maxWidth = 0.0f, maxHeight = 0.0f, maxDepth = 0.0f;
	maxWidth = sqrt( (max.x-min.x)*(max.x-min.x) );
	maxHeight = sqrt( ( max.z - min.z ) * ( max.z - min.z ));
	maxDepth = sqrt( (max.y - min.y)*(max.y - min.y));


/*Это меня смущает
	maxWidth *= 2;
	maxHeight *= 2;
	maxDepth *= 2;
*/
	onOctree->fWidth = __max( maxWidth, maxHeight );
	onOctree->iPointCount = iMapSize*iMapSize;
	onOctree->iSubDividedLevel = 0;
	onOctree->bSubDivided = true;

}



//==============================================================//
//																//
//==============================================================//



void vrLandscape2::CreateOctreeNode( INT_LIST points_p, int count, vrOctreeNode *nParentNode, int nodeID )
{


if ( points_p.size == 0 ) return;
if ( !nParentNode ) return;


//Lists of node's points
INT_LIST	top_left_front;
INT_LIST	top_right_front;
INT_LIST	top_right_back;
INT_LIST	top_left_back;

INT_LIST	bottom_left_front;
INT_LIST	bottom_right_front;
INT_LIST	bottom_right_back;
INT_LIST	bottom_left_back;


//Создаем новую ноду
vrOctreeNode *nCurrentNode = new vrOctreeNode();

//Вычисляем координаты центра ноды
vrVector3	vCtr = this->GetNewNodeCenter( nParentNode->vCenter, nParentNode->fWidth, nodeID );

nCurrentNode->vCenter				= vCtr;
nCurrentNode->iPointCount			= points_p.size();//
nCurrentNode->fWidth				= nParentNode->fWidth/2;
nCurrentNode->bSubDivided			= true;
nCurrentNode->iSubDividedLevel		= nParentNode->iSubDividedLevel + 1;

nParentNode->nChildNodes_p[nodeID]	= nCurrentNode;


//если количество точек в ноде меньше заданного, или глубина разделения максимальна, создаем лист
//TODO:ЗАКОНЧИТЬ!!!********************************************************

if ( points_p.size() <= iMinPointsInNode )
{




return;
}




vrVector3	vPt;

//Распределяем точки
for ( int i=0; i< points_p.size(); i++ )
{

//TODO: Очень нерационально вычислять каждый раз координаты, если они неизменны
	vPt.z = (int)(fHeightMap[i].index / iMapSize);
	vPt.x = ( fHeightMap[i].index - ( vPt.z * iMapSize ));
	vPt.y = fHeightMap[i].height;

	vPt.x *= fZoom;
	vPt.z *= fZoom;
	vPt.y *= fZoomY;



	if ( ( vPt.x <= vCtr.x ) && ( vPt.y <= vCtr.y ) && ( vPt.z <= vCtr.z ) )
		bottom_left_back.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y <= vCtr.y) && (vPt.z <= vCtr.z) )
		bottom_right_back.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y <= vCtr.y) && (vPt.z >= vCtr.z) )
		bottom_right_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x <= vCtr.x) && (vPt.y <= vCtr.y) && (vPt.z >= vCtr.z) )
		bottom_left_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x <= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z <= vCtr.z) )
		top_left_back.push_back( fHeightMap[i].index );

	else if ( (vPt.x <= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z >= vCtr.z) )
		top_left_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z >= vCtr.z) )
		top_right_front.push_back( fHeightMap[i].index );

	else if ( (vPt.x >= vCtr.x) && (vPt.y >= vCtr.y) && (vPt.z <= vCtr.z) )
		top_right_back.push_back( fHeightMap[i].index );

}



//рекурсвно продолжаем разделение

CreateOctreeNode( top_left_front,		0, onOctree, TOP_LEFT_FRONT );
CreateOctreeNode( top_left_back,		0, onOctree, TOP_LEFT_BACK );
CreateOctreeNode( top_right_back,		0, onOctree, TOP_RIGHT_BACK );
CreateOctreeNode( top_right_front,		0, onOctree, TOP_RIGHT_FRONT );
CreateOctreeNode( bottom_left_front,	0, onOctree, BOTTOM_LEFT_FRONT );
CreateOctreeNode( bottom_left_back,		0, onOctree, BOTTOM_LEFT_BACK );
CreateOctreeNode( bottom_right_back,	0, onOctree, BOTTOM_RIGHT_BACK );
CreateOctreeNode( bottom_right_front,	0, onOctree, BOTTOM_RIGHT_FRONT );


/*
int a = bottom_left_back.size();
a = bottom_right_back.size(); 
*/


}

//==============================================================//
//																//
//==============================================================//

vrVector3 vrLandscape2::GetNewNodeCenter( vrVector3 vParentCenter, float fParentWidth, int nodeID )
{

// Initialize the new node center
	vrVector3 vNodeCenter(0, 0, 0);

	// Create a dummy variable to cut down the code size
	vrVector3	vCtr	= vParentCenter;
	float		fWidth	= fParentWidth;

	// Switch on the ID to see which subdivided node we are finding the center
	switch(nodeID)							
	{
		case TOP_LEFT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y + fWidth/4, vCtr.z + fWidth/4);
			break;

		case TOP_LEFT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y + fWidth/4, vCtr.z - fWidth/4);
			break;

		case TOP_RIGHT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y + fWidth/4, vCtr.z - fWidth/4);
			break;

		case TOP_RIGHT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y + fWidth/4, vCtr.z + fWidth/4);
			break;

		case BOTTOM_LEFT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y - fWidth/4, vCtr.z + fWidth/4);
			break;

		case BOTTOM_LEFT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x - fWidth/4, vCtr.y - fWidth/4, vCtr.z - fWidth/4);
			break;

		case BOTTOM_RIGHT_BACK:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y - fWidth/4, vCtr.z - fWidth/4);
			break;

		case BOTTOM_RIGHT_FRONT:
			// Calculate the center of this new node
			vNodeCenter = vrVector3(vCtr.x + fWidth/4, vCtr.y - fWidth/4, vCtr.z + fWidth/4);
			break;
	}

	// Return the new node center
	return vNodeCenter;

}

