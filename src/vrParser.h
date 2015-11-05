
//==============================================================//
//																//
//==============================================================//
/*
-----------------------------------------------------------------
					Virtual Reality 3D Engine 2
					(c)vr5
					contact: vr5@bk.ru
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

//==============================================================//
//																//
//==============================================================//

#ifndef __VRPARSER_H__
#define __VRPARSER_H__


#include "vrInclude.h"
#include "vrVector.h"
#include "vrUtils.h"
#include <list>

//тэги
#define TAG_WORLD_OPEN					0x00000000
#define TAG_WORLD_CLOSE					0x00000001

#define TAG_MATERIAL_OPEN				0x00000002	//<material>
#define TAG_MATERIAL_CLOSE				0x00000003	//</material>

#define TAG_DIFFUSEMAP_OPEN				0x00000004
#define TAG_DIFFUSEMAP_CLOSE			0x00000005

#define TAG_DETAILMAP_OPEN				0x00000006
#define TAG_DETAILMAP_CLOSE				0x00000007

#define TAG_BUMPMAP_OPEN				0x00000008
#define TAG_BUMPMAP_CLOSE				0x00000009

#define TAG_OBJECT_OPEN					0x0000000a
#define TAG_OBJECT_CLOSE				0x0000000b

#define TAG_MESH_OPEN					0x0000000c
#define TAG_MESH_CLOSE					0x0000000d

#define TAG_TEXTURE_OPEN				0x0000000e
#define TAG_TEXTURE_CLOSE				0x0000000f

#define TAG_GEOMETRY_OPEN				0x00000010
#define TAG_GEOMETRY_CLOSE				0x00000011
#define TAG_CAMERA_OPEN					0x00000012
#define TAG_CAMERA_CLOSE				0x00000013


//параметры

#define PARAM_NAME						0x00000014
#define PARAM_AMBIENT					0x00000015
#define PARAM_DIFFUSE					0x00000016
#define PARAM_SPECULAR					0x00000017
#define PARAM_EMISSION					0x00000018
#define PARAM_SHININESS					0x00000019
#define PARAM_SCALE						0x0000001a
#define PARAM_ROTATE					0x0000001b
#define PARAM_TRANSLATE					0x0000001c
#define PARAM_FILE						0x0000001d
#define	PARAM_MATERIAL					0x0000001e
#define PARAM_FOV						0x0000001f
#define PARAM_SPEED						0x00000020
#define PARAM_SENSITIVITY				0x00000021



//==============================================================//
//																//
//==============================================================//

typedef struct tagOperation
{
	unsigned int	opcode;
	LPSTR			strParam;
	vrVector3		vParam;
	float			fParam;

}op;

/*!!!!!!!!!!!!*/typedef std::list<op*> CODE;/*!!!!!!!!!!!!*/

class vrParser
{

public: /*SUBROUTINES*/

		vrParser();
		bool CompileFile( LPSTR strFileName, CODE* code );

public: /*VARIABLES*/



private: /*SUBROUTINES*/
		void CleanString( LPSTR str );	//удаляет из строки все лишнее
		//void CheckSpell();
		void Compile();
		bool CleanFile( LPSTR strFileName );



private: /*VARIABLES*/
		FILE		*f;
		FILE		*tempf;
		CODE		*code;




};


#endif