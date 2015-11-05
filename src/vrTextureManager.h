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
#ifndef __VRTEXTUREMANAGER_H__
#define __VRTEXTUREMANAGER_H__


#include <list>
//#include "vrEngine.h"
#include "vrTexture.h"
#include "vrUtils.h"
#include "vrBase.h"
//==============================================================//
//						Менеджер Текстур						//
//==============================================================//

typedef std::list<vrTexture*> TEXTURELIST;

class vrTextureManager
{

//friend class vrWorld;
public:
					vrTextureManager();
					~vrTextureManager();

		bool		Create( );							//привязывает к классу vrEngine

		bool		Add( vrTexture *texture );			//добавляет текстуру из памяти
		bool		Add( LPSTR strFileName );			//добавляет текстуру из файла

		vrTexture*	Get( LPSTR strTextureName );		//возвращает указатель на текстуру по её имени
		vrTexture*	Get( unsigned int uiID );			//возвращает указатель на текстуру по её идентификатору
		vrTexture*	GetLast();

		void		Remove( LPSTR strTextureName );		//удаляет текстуру по имени
		void		Remove( unsigned int uiID );		//удаляет текстуру по идентификатору

		void		Clear();							//очищает список
		int			Count();							//возвращает количество элементов в списке

		int			UploadAll();

//		int			iCount;			//количество текстур в списке

//		bool		bUseCompression;
//		bool		bUseMipmapping;

private:

		TEXTURELIST			*tl;



};



#endif