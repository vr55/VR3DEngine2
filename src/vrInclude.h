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
#ifndef __VRINCLUDE_H__
#define __VRINCLUDE_H__

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>


#include "glew\glew.h"
#include "glew\wglew.h"

#include <gl\glu.h>
#include "glsl\glsl.h"

#include <list>
#include <assert.h>
#include <ctype.h>
#include <list>
#include <vector>
#include <assert.h>

#include <basetsd.h>
#include <dinput.h>

#include <ddraw.h>
/*
#include "vrCommonStruct.h"
#include "vrTriFace.h"
#include "vrBase.h"

#include "vrTriMesh.h"
#include "vrGameObject.h"
#include "vrWorld.h"
#include "vrTexture.h"
#include "vrMaterial.h"
#include "vrFont.h"
#include "vrUtils.h"
*/
#include "vrVector.h"
#include "vrVertex.h"


typedef unsigned int uint;

#define RAD pi/180

//PFNGLCOMPRESSEDTEXIMAGE2DARBPROC glCompressedTexImage2DARB = NULL;



/*
#define		LOG_FILE_PATH		"../log/Main.log"
#define		WORLD_LOG_PATH		"../log/vrWorld.log"
#define		TEXTURE_LOG_PATH	"../log/vrTexture.log"
#define		ENGINE_LOG_PATH		"../log/vrEngine.log"
*/
#define		LOG_FILE_PATH		"../log/Main.log"
#define		WORLD_LOG_PATH		"../log/Main.log"
#define		TEXTURE_LOG_PATH	"../log/Main.log"
#define		ENGINE_LOG_PATH		"../log/Main.log"


#define		VR_MOVE			0
#define		VR_STRAFE		1
#define		VR_UP			2
#define		VR_ROLL			3
#define		VR_PITCH		4
#define		VR_YAW			5

//==============================================================//
//				structures 										//
//==============================================================//

typedef struct tagVROHeader2
{
        char    magic[4];               //VRO2 идентификатор
        int     sizeofheader;           //размер
        char    name[32];               //имя объекта
        int     numofchunk;             //количество секций в объекте
 //     DWORD   meshoffset[numofchunk]; //таблица смещений к мешам
                                        //количество элементов равно
                                        //количеству мешей

} VROHeader2;
//==============================================================//

typedef struct tagVROMesh
{
        char            magic[4];      		//VROM
        int             sizeofheader;   	//размер заголовка
        char            name[32];       	//имя меша


      	int				iNumVerts;			//количество вершин
      	int				iNumFaces;			//количество плоскостей
      	int				iNumTVerts;			//количество текстурных координат
		int				iNumNormals;		//количество нормалей v2.6
      	

     	//Face			faces[iNumFaces];	//Плоскости      	
      	//vrVector3		verts[ iNumVerts ];	//вертексы
    	//vrVector3		normals[iNumFaces];	//нормали
      	//vrVector3		tverts[iNumTVerts]; //Текстурные координаты

      	
      	
} VROMesh;

//==============================================================//
typedef struct tagVRHheader
{
	char			magic[4];			//VRHM - Virtual Reality Height Map
	unsigned int	sizeofheader;		//размер заголовка
	unsigned long	numofheights;		//количество вершин
	unsigned long	mapwidth;			//длина карты
	unsigned long	mapheight;			//ширина карты

}	VRHheader, *LPVRHheader;
//==============================================================//

typedef struct tagVRSphere
{

	vrVector3		center;
	float			radius;

}	vrSphere, *lpvrSphere;

//==============================================================//
typedef struct tagVRQuad
{

vrVertex	v[4];


} vr_quad, *vr_lpquad;


//==============================================================//
typedef struct tagImage
{
	int		i_width;	//ширина
	int		i_height;	//высота
	int		i_format;	//внутренний формат
	int		i_mapcnt;	//количество mip-map карт
	void	*data;		//DIB-данные в формате i_format;




} vr_image, *vr_lpimage;

#endif