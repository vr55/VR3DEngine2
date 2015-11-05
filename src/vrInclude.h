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
        char    magic[4];               //VRO2 �������������
        int     sizeofheader;           //������
        char    name[32];               //��� �������
        int     numofchunk;             //���������� ������ � �������
 //     DWORD   meshoffset[numofchunk]; //������� �������� � �����
                                        //���������� ��������� �����
                                        //���������� �����

} VROHeader2;
//==============================================================//

typedef struct tagVROMesh
{
        char            magic[4];      		//VROM
        int             sizeofheader;   	//������ ���������
        char            name[32];       	//��� ����


      	int				iNumVerts;			//���������� ������
      	int				iNumFaces;			//���������� ����������
      	int				iNumTVerts;			//���������� ���������� ���������
		int				iNumNormals;		//���������� �������� v2.6
      	

     	//Face			faces[iNumFaces];	//���������      	
      	//vrVector3		verts[ iNumVerts ];	//��������
    	//vrVector3		normals[iNumFaces];	//�������
      	//vrVector3		tverts[iNumTVerts]; //���������� ����������

      	
      	
} VROMesh;

//==============================================================//
typedef struct tagVRHheader
{
	char			magic[4];			//VRHM - Virtual Reality Height Map
	unsigned int	sizeofheader;		//������ ���������
	unsigned long	numofheights;		//���������� ������
	unsigned long	mapwidth;			//����� �����
	unsigned long	mapheight;			//������ �����

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
	int		i_width;	//������
	int		i_height;	//������
	int		i_format;	//���������� ������
	int		i_mapcnt;	//���������� mip-map ����
	void	*data;		//DIB-������ � ������� i_format;




} vr_image, *vr_lpimage;

#endif