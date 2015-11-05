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
#ifndef __VRGAMEOBJECT_H__
#define __VRGAMEOBJECT_H__

#include "vrTriObject.h"

//==============================================================//
//																//
//==============================================================//
class vrWrapper
{
public:

	void*		object;	//указатель на объект
	vec3		pos;
	vec3		orient;
	vec3		scale;

public:
	vrWrapper();
	void	Render();

	void	SetPos( vec3 newpos ){ pos.x = newpos.x; pos.y = newpos.y; pos.z = newpos.z; }
	void	SetPos( float x, float y, float z ){ pos.x = x; pos.y = y; pos.z = z; }
	void	SetScale( vec3 newscale ){ scale.x = newscale.x; scale.y = newscale.y; scale.z = newscale.z; }
	void	SetScale( float x, float y, float z ){ scale.x = x; scale.y = y; scale.z = z; }
	void	SetRotate( float x, float y, float z ){ orient.x = x; orient.y = y; orient.z = z; }
	vrMaterial2* GetObjectMaterial();

private:
	void Begin();
	void End();
};


//==============================================================//
//																//
//==============================================================//

class ObjectWrapper
{
public:
	ObjectWrapper()
	{ 
		
		object			= NULL; 
		material		= NULL;
		vScale.x		= vScale.y		= vScale.z		= 1.0;
		vRotate.x		= vRotate.y		= vRotate.z		= 1.0;
		vTranslate.x	= vTranslate.y	= vTranslate.z	= 1.0;
		bSelected		= FALSE;
		uiID			= 0;
		ZeroMemory( &cName, 32 );
	
	}

	vrTriObject		*object;	//указатель на объект
	vrMaterial		*material;		//материал
	vrVector3		vScale;
	vrVector3		vRotate;
	vrVector3		vTranslate;

	UINT			uiID;		//присваивается менеджером ресурсов при загрузке
	char			cName[32];	//имя

	BOOL			bSelected;	//флаг выделения


};

#endif