/*
-----------------------------------------------------------------
					Virtual Reality 3D Engine 2
					(c)vr5
					contact: vr5@bk.ru
					Texture Class 
-----------------------------------------------------------------
*/

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
#pragma once


#include "vrTexture.h"
#include "vrEngineFunc.h"

//==============================================================//
//																//
//==============================================================//

vrTexture::vrTexture()
{
 
bData = NULL;
eLog.Create( TEXTURE_LOG_PATH );

bCompress	= true;
bUploaded	= false;
bMipmap		= true;

uiID = -1;

}

//==============================================================//
//																//
//==============================================================//

vrTexture::~vrTexture()
{

vr_image *image = new vr_image;

image->data = (void*)bData;

engine.FreeImage ( image );

if ( bUploaded ) Unload();
delete image;
}


//==============================================================//
//																//
//==============================================================//

bool vrTexture::LoadFromFile( LPSTR strFileName )
{

e_log.WriteOut("[STATUS] Loading Texture: %s \n", strFileName );

vr_image *image = new vr_image();

ZeroMemory( image, sizeof( vr_image ) );

if ( (!engine.LoadImage( strFileName, image )) || (image->data == NULL ) ) 
{
	e_log.WriteOut("[ERROR] Unable to Load Texture from File %s\n", strFileName );

	return false;
}

uiWidth			= image->i_width;
uiHeight		= image->i_height;
iFormat			= image->i_format;
iMipMapCount	= image->i_mapcnt;
bData			= (unsigned char*)image->data;

delete image;
return true;

}


//==============================================================//
//																//
//==============================================================//

bool vrTexture::Upload()
{

if ( !bData ) return false;
//if (  ( uiWidth % 2 != 0 ) || ( uiHeight % 2 != 0 ) ) return false;


unsigned int comp;

glGenTextures( 1, &uiID );
glBindTexture( GL_TEXTURE_2D, uiID );

bUploaded = true;

//--------если текстура уже сжата (DDS) просто грузим ее
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	


if ( ( iFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ) || ( iFormat == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT ) || ( iFormat == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT ) )
{

	DWORD	blockSize = ( iFormat == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	DWORD	offset = 0;
	int		width = this->uiWidth;
	int		height = this->uiHeight;

	for ( int i = 0; i < iMipMapCount && (width || height); i++ )
	{

		if (width == 0)
		width = 1;
		if (height == 0)
		height = 1;

	DWORD	size = ((width+3)/4)*((height+3)/4)*blockSize;
	//glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS,  GL_TRUE );
	glCompressedTexImage2D( GL_TEXTURE_2D, i, iFormat, width, height, 0, size, bData + offset );

	offset += size;
	width >>= 1;
	height >>= 1;

	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DeleteData();
	return true;
}

if ( bCompress )
{
	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS,  GL_FALSE );

	unsigned int cformat;
	if ( iFormat == GL_BGR_EXT )			cformat = GL_COMPRESSED_RGB;
	if ( iFormat == GL_RGB )				cformat = GL_COMPRESSED_RGB;
	if ( iFormat == GL_RGBA )				cformat = GL_COMPRESSED_RGBA;
	if ( iFormat == GL_BGRA_EXT )			cformat = GL_COMPRESSED_RGBA;
	if ( iFormat == GL_ALPHA )				cformat = GL_COMPRESSED_ALPHA;
	if ( iFormat == GL_LUMINANCE )			cformat = GL_COMPRESSED_LUMINANCE;
	if ( iFormat == GL_LUMINANCE_ALPHA  )	cformat = GL_COMPRESSED_LUMINANCE_ALPHA;

//	glHint( GL_TEXTURE_COMPRESSION_HINT, GL_NICEST );
	gluBuild2DMipmaps( GL_TEXTURE_2D, cformat, uiWidth, uiHeight, iFormat, GL_UNSIGNED_BYTE, (void*)bData );

	int compressed;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compressed);


	int internalformat;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT,&internalformat);

if ( compressed == 1 ) 
{
	iFormat = internalformat;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DeleteData();

	return true;
}

else return false;



}
else
{
	if ( iFormat == GL_BGR ) comp = 3;
	if ( iFormat == GL_RGB ) comp = 3;
	if ( iFormat == GL_RGBA )comp = 4;
	if ( iFormat == GL_BGRA )comp = 4;

glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS,  GL_FALSE );
int i = gluBuild2DMipmaps( GL_TEXTURE_2D, comp, uiWidth, uiHeight, iFormat, GL_UNSIGNED_BYTE, (void*)bData );

if ( i == 0 ) 
{
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DeleteData();

	return true;
}
 else return false;

}

glBindTexture( GL_TEXTURE_2D, 0 );
//


return true;
}


//==============================================================//
//																//
//==============================================================//

void vrTexture::Unload()
{

if ( glIsTexture( uiID ) )		//OpenGL 1.1 and later
{
	glDeleteTextures( 1, &uiID );
	bUploaded = false;
}

}


//==============================================================//
//																//
//==============================================================//
void vrTexture::DeleteData()
{


//if ( bData ) delete bData;
//bData = NULL;

vr_image *image = new vr_image;

image->data = (void*)bData;

engine.FreeImage ( image );
bData = NULL;

delete image;


}

//==============================================================//
//																//
//==============================================================//

void vrTexture::Bind()
{
if ( bUploaded ) glBindTexture( GL_TEXTURE_2D, uiID );


}

//==============================================================//
//																//
//==============================================================//

void vrTexture::UnBind()
{

glBindTexture( GL_TEXTURE_2D, 0 );


}
