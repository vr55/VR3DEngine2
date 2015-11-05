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


#ifndef __VRTRIOBJECT_H__
#define __VRTRIOBJECT_H__

#include "vrInclude.h"
#include "vrTriMesh.h"
#include "vrCommonStruct.h"
#include "vrGameObject.h"


//Last Edit 10.11.2k5

//==============================================================//
//																//
//==============================================================//
class vrTriObject2
{
public:/*constructor/destructor*/

	vrTriObject2();
	~vrTriObject2();

public: /*subroutines*/

	BOOL	Load( LPSTR strFileName );		//грузим объект из файла
	BOOL	LoadSkin( LPSTR strfileName );	
	void	Render();						//рисуем объект
	BOOL	Compile();						//создаем дисплейный список
	void	CreateBBox();

	//void	Free();


public:/*variables*/
	char		cName[ NAME_MAXCHARS ];		//имя объекта
	int			iID;						//идентификатор
	int			iNumSurfaces;				//количество поверхностей
	lp_surface	surfaces;					//поверхности

	vrVector3	center;						//центр масс
	float		width;
	float		height;

	BOOL		bCompiled;					//флаг компиляции???


	skin*		skin_p;						//скин - указатель на массив материалов для каждой поверхности
											//количество элементов равно iNumSurfaces

private:/*subroutines*/


private:
	GLuint	uiRenderList;


};




//					OLD					//
//---------------------------------------
//==============================================================//
//																//
//==============================================================//

class vrTriObject
{

public: /*SUBROUTINES*/
		vrTriObject();								//конструктор
		~vrTriObject();								//деструктор

		bool Load( LPSTR strFileName );				//загружает объект из файла
//		void Render( ObjectWrapper *o );			//рисует объект основывясь на данных враппера
		int	 MeshCount();							//возвращает количество мешей в объекте

		vrTriMesh*  GetMesh( );						//возвращает указатель на меш



public: /*VARIABLES*/

		char		cName[32];						//имя объекта
		unsigned int uiID;							//идентификатор


private: /*SUBROUTINES*/

		bool		AddMesh( vrTriMesh *fromMesh );	//добавляет меш в список из памяти


private: /*VARIABLES*/

		vrTriMesh					*mesh_p;					//меш
		vrErrorLog					eLog;						//лог


};



//==============================================================//
//																//
//==============================================================//
#endif