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
#include <bitset>


//==============================================================//
//																//
//==============================================================//

vrLandscape::vrLandscape()
{

iNumOfHeights	= 0;
hMap			= NULL;
lpOctree		= NULL;
aMap			= NULL;
material		= NULL;

lpOctree = new vrOctree;

vScale.x = 1.0;
vScale.y = 1.0;
vScale.z = 1.0;

Zoom = 150;
ZoomZ = Zoom/5;



}

//==============================================================//
//																//
//==============================================================//

vrLandscape::~vrLandscape()
{

if ( hMap ) delete[] hMap;
if ( lpMesh ) delete[] lpMesh;
if ( lpQuad ) delete[] lpQuad;


}

//==============================================================//
//																//
//==============================================================//

bool  vrLandscape::Load( LPSTR strFileName )
{


return true;
}

//==============================================================//
//																//
//==============================================================//

bool vrLandscape::LoadHeightMap( LPSTR strFileName )
{
HANDLE					bmpHandle;
BITMAPFILEHEADER		FileHeader;
BITMAPINFOHEADER		InfoHeader;


DWORD		rb;
RGBQUAD		palette[256];

e_log.WriteOut("[STATUS] Loading Landscape from File %s\n", strFileName );

bmpHandle = CreateFile( strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0 );
if( bmpHandle == INVALID_HANDLE_VALUE )
{
//	eLog.WriteOut( "\n\tCan't Load Height Map %s\n", strFileName );
	e_log.WriteOut("[ERROR] Unable to Open File %s\n", strFileName );

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
	e_log.WriteOut("[ERROR] 8bit Bitmaps Only" );
	return false;

}
/******************New Data**************/
this->iMapWidth			= InfoHeader.biWidth;
this->iMapHeight		= InfoHeader.biHeight;
/****************************************/


DWORD bitmapLenght = InfoHeader.biSizeImage;

if ( bitmapLenght == 0 ) bitmapLenght = InfoHeader.biWidth * InfoHeader.biHeight;


SetFilePointer( bmpHandle, sizeof( FileHeader ) + sizeof( InfoHeader ), NULL, FILE_BEGIN );
//палитра

ReadFile( bmpHandle, palette, sizeof( palette ), &rb, NULL );

if ( rb != sizeof( palette )  ) return NULL;

SetFilePointer( bmpHandle, FileHeader.bfOffBits, NULL, FILE_BEGIN );

DWORD	a = 0;

byte	*img = new byte[ bitmapLenght ];

ReadFile( bmpHandle, img, bitmapLenght, &rb, NULL );

//преобразуем byte в float
float *fData = (float*)malloc( iMapWidth*iMapHeight*sizeof(float) );

for( int i = 0; i<(iMapWidth*iMapHeight); i++ )
{

fData[i] = img[i];


}

this->hMap = fData;

CreateMesh();

CreateOctree();

//Normalize();
CloseHandle( bmpHandle );

return true;


}

//==============================================================//
//																//
//==============================================================//

BOOL	vrLandscape::LoadHeightMap( char *buffer, unsigned int width, unsigned int height )
{
	this->hMap = (float*)malloc( width*height*sizeof(float) );

	for( int i=0; i<width*height; i++ )
	{
		this->hMap[i] = (float)buffer[i];
	}

	this->iMapWidth = width;
	this->iMapHeight = height;
//	memcpy( this->hMap, (void*)buffer, width*height );
	CreateMesh();
	CreateOctree();

	return TRUE;
}

//==============================================================//
//																//
//==============================================================//

float vrLandscape::ClipPoint( float x, float y )
{
float	fX, fY;
int		iX, iY;

fX = x / Zoom;
fY = y / Zoom;

iX = (int)fX;
iY = (int)fY;

fX = fX - (float)iX;
fY = fY - (float)iY;

if((iX<0) || (iX>=(iMapWidth)) || (iY<0) || (iY>=(iMapWidth))) return 0.0f;

	float lowYh = (1-fX) * ( GetHeight( iX, iY ) * ZoomZ ) + fX * (GetHeight((iX + 1), iY) * ZoomZ);
	float highYh = (1-fX) * ( GetHeight( iX, (iY+1 ) ) * ZoomZ ) + fX * (GetHeight((iX + 1), (iY+1)) * ZoomZ);
	
	return (1-fY)*lowYh + fY*highYh;




//index = j*iMapWidth + i

}



BOOL vrLandscape::AccessPoint( float x, float y )
{

float	fX, fY;
int		iX, iY;

fX = x / Zoom;
fY = y / Zoom;

iX = (int)fX;
iY = (int)fY;


if((iX<0) || (iX>=(iMapWidth)) || (iY<0) || (iY>=(iMapWidth))) return FALSE;

GetHeight(iX, iY);



if ( aMap[iY*iMapWidth+iX] < 255 ) return FALSE; else return TRUE;

}

//==============================================================//
//																//
//==============================================================//

void vrLandscape::Render( Camera *camera_p )
{


if ( material ) 
{
	material->Begin();
	//if ( material->sShader ) material->sShader->setUniform1i("t1scale", 80 );
}

//RenderHeightMap();

RenderOctree( camera_p );

if ( material ) material->End();


}
//==============================================================//
//		функция для отладки. рендерит ландшафт без octree		//
//==============================================================//
void vrLandscape::RenderHeightMap(  )
{


//float		z;
int			index;
//vrVertex	dot;
vrVertex	quad[4];

//glRotatef( -90, 1, 0, 0 );

//---------Let's Render It

float x,y;

float fStepU = 1/(float)iMapWidth;
float fStepV = 1/(float)iMapHeight;

engine.glBeginScene( GL_QUADS );

for ( int i=0; i<iMapWidth-1; i++ )
{
	for ( int j=0; j<iMapHeight-1; j++ )
	{
		x = (float)i * Zoom;
		y = (float)j * Zoom;

		//1
		index = j*iMapWidth + i;
		quad[0].x = x;
		quad[0].z = y;
		quad[0].y = hMap[ index ] * ZoomZ;
		quad[0].u0 = i * fStepU;
		quad[0].v0 = j * fStepV;

		//2
		quad[1].x = x + Zoom  ;
		quad[1].z = y;
		quad[1].y = hMap[ index + 1 ] * ZoomZ;
		quad[1].u0 = (i+1) * fStepU;
		quad[1].v0 = j * fStepV;


		//3
		quad[2].x = x + Zoom;
		quad[2].z = y + Zoom;
		quad[2].y = hMap[ index + 1 + iMapWidth ] * ZoomZ;
		quad[2].u0 = (i+1) * fStepU;
		quad[2].v0 = (j+1) * fStepV;


		//4
		quad[3].x = x;
		quad[3].z = y + Zoom;
		quad[3].y = hMap[ index + iMapWidth ] * ZoomZ;
		quad[3].u0 = i * fStepU;
		quad[3].v0 = (j+1) * fStepV;


		engine.glRenderPrimitive( 4, (vrVertex*)quad );



	}
}
engine.glEndScene();
//--------End rendering


//engine.glRestoreMatrix( GL_MODELVIEW );


}

//==============================================================//
//																//
//==============================================================//

void vrLandscape::CreateMesh()
{

int iMapSize = iMapWidth * iMapHeight;

vrVertex *Mesh_p = (vrVertex*)malloc( iMapSize * sizeof( vrVertex ) );

ZeroMemory( Mesh_p, iMapSize * sizeof( vrVertex ) );

if ( Mesh_p )
{
float	x,y;
int		index;
float	fStepU = 1/(float)iMapWidth;
float	fStepV = 1/(float)iMapHeight;
int c=0;

	for ( int i=0; i<iMapWidth; i++ )
	{
		for ( int j=0; j<iMapHeight; j++ )	

		{
			x = (float)i * Zoom;
			y = (float)j * Zoom;

		index = j*iMapWidth + i;
		Mesh_p[index].index = index;
		Mesh_p[index].x = x;
		Mesh_p[index].z = y;
		Mesh_p[index].y = hMap[ index ] * ZoomZ;
		Mesh_p[index].u0= i * fStepU;
		Mesh_p[index].v0= j * fStepV;

		}


	}
this->lpMesh = Mesh_p;
}




}
//==============================================================//
//																//
//==============================================================//

bool vrLandscape::CreateOctree()
{

lpOctree->Create( this->lpMesh, iMapWidth * iMapHeight );


if ( lpMesh ) delete[] lpMesh;
lpMesh = NULL;

//*************************************создаем массив треугольников*
lpQuad = ( vr_quad* ) malloc( iMapHeight * iMapWidth * sizeof(vr_quad));

lpOctree->lpQuad = lpQuad;

vr_quad	quad;


float x,y;
int	index;

float fStepU = 1/(float)iMapWidth;
float fStepV = 1/(float)iMapHeight;

for ( int i=0; i<iMapWidth-1; i++ )
{
	for ( int j=0; j<iMapHeight-1; j++ )
	{
		x = (float)i * Zoom;
		y = (float)j * Zoom;

		//1
		index = j*iMapWidth + i;
		quad.v[0].x = x;
		quad.v[0].z = y;
		quad.v[0].y = hMap[ index ] * ZoomZ;
		quad.v[0].u0 = i * fStepU;
		quad.v[0].v0 = j * fStepV;

		//2
		quad.v[1].x = x + Zoom  ;
		quad.v[1].z = y;
		quad.v[1].y = hMap[ index + 1 ] * ZoomZ;
		quad.v[1].u0 = (i+1) * fStepU;
		quad.v[1].v0 = j * fStepV;


		//3
		quad.v[2].x = x + Zoom;
		quad.v[2].z = y + Zoom;
		quad.v[2].y = hMap[ index + 1 + iMapWidth ] * ZoomZ;
		quad.v[2].u0 = (i+1) * fStepU;
		quad.v[2].v0 = (j+1) * fStepV;


		//4
		quad.v[3].x = x;
		quad.v[3].z = y + Zoom;
		quad.v[3].y = hMap[ index + iMapWidth ] * ZoomZ;
		quad.v[3].u0 = i * fStepU;
		quad.v[3].v0 = (j+1) * fStepV;


lpQuad[index]	= quad;

	}
}
//**************************************

return true;

}
//==============================================================//
//																//
//==============================================================//
void vrLandscape::RenderOctree( Camera *camera_p )
{


lpOctree->Render( camera_p );


}
//==============================================================//
//																//
//==============================================================//
bool	vrLandscape::LoadAMap( LPSTR strFileName )
{
DWORD		rb;

//aMap = new byte[iMapWidth * iMapHeight];

aMap = (byte*)malloc( iMapWidth * iMapHeight * sizeof(byte) ); 
if ( !aMap ) return false;

HANDLE h = CreateFile( strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0 );

if( h == INVALID_HANDLE_VALUE )
{

return false;

}


ReadFile( h, aMap, (iMapWidth * iMapHeight)*sizeof(byte), &rb, NULL );

CloseHandle( h );

return true;
}
//==============================================================//
//																//
//==============================================================//


void vrLandscape::Normalize()
{

if ( hMap )
{
	float	fMax = -1000000;
	for ( int i = 0; i < (iMapWidth*iMapHeight); i++ )
	{
		if ( abs(hMap[i]) > fMax ) fMax = hMap[i];
	}

	for ( i = 0; i < (iMapWidth*iMapHeight); i++ )
	{
		hMap[i] = hMap[i] / fMax;
	}


}

}

