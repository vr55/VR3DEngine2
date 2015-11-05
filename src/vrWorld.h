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

//#include "vrEngine.h"
#include "vrInclude.h"
#include "vrErrorLog.h"
#include "vrGameObject.h"

#include "vrTextureManager.h"
#include "vrParser.h"
#include "vrGameObject.h"
//#include "vrCamera.h"
#include "vrBase.h"

#include "vrConsole.h"
#include "vrResourceMgr.h"

#include "vrLandscape.h"


#ifndef __VRWORLD_H__
#define __VRWORLD_H__

typedef std::vector<vrWrapper*>		WRAPPERS;

//==============================================================//
//																//
//==============================================================//

class vrWorld
{

public: /*SUBROUTINES*/
		vrWorld();
		//~vrWorld();
		bool			LoadRes( LPSTR strFileName );	//добавляет в мир ресурсы из файла
		bool			Load( LPSTR strFileName );
                void                    Free();
		bool			Replace( LPSTR strFileName );	//заменяет данные мира данными из файла

		bool			Save( LPSTR strFileName );		//сохраняем мир в файл

		bool			Init( );						//инициализация ресурсов
		void			Prepare();		//Better name is "Lock"					
		int				Render( void );	//возвращает количество отрендеренных треугольников
		void			Update();

//  операции с камерой
		bool			AddCamera();

		BOOL			AddWrapper( vrWrapper *w );
		BOOL			AddFont( vrMaterial2 *f_material );
		vrFont*			GetFont() { return font_p; };

		BOOL			AddLandscape( LPSTR strFileName );
		BOOL			AddLandscape( char *buffer, unsigned int width, unsigned int height );
		vrLandscape*	GetLandscape(){ return landscape_p; }


public: /*VARIABLES*/

		vrCamera				*camera;//камера//public временно
		vrResourceManager		*r_mgr;

		ObjectWrapper			*owSelected_p;//указатель на текущий выделенный wrapper



private: /*SUBROUTINES*/
		
		


private: /*VARIABLES*/
		WRAPPERS				*wrappers_p;
		vrFont					*font_p;

		vrLandscape				*landscape_p;


};

//************************************************************
//---GLOBAL
extern	vrWorld		world;



#endif



