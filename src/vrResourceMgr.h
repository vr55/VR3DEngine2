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

#ifndef __VRRESOURCEMGR_H__
#define __VRRESOURCEMGR_H__

#include "vrTriObject.h"

#include "vrFont.h"

//==============================================================//
//																//
//==============================================================//
typedef std::vector<vrTexture*>		T_LIST;
typedef std::vector<vrMaterial2*>	M_LIST;
typedef std::vector<vrTriObject2*>	O_LIST;
typedef std::vector<vrFont*>		F_LIST;
typedef	std::vector<ObjectWrapper*>	W_LIST;
typedef std::vector<glShader*>		S_LIST;

//==============================================================//
//																//
//==============================================================//


class vrResourceManager
{
public:
			vrResourceManager();
			~vrResourceManager();
			bool		Init();
			bool		Load( LPSTR strFileName );
                        void		Free();
//Текстуры
			bool		AddTexture( LPSTR strFileName );
			bool		AddTexture( vrTexture *texture_p );
			vrTexture*	GetTexture( LPSTR strTextureName );
			vrTexture*	GetTexture( int a );
			void		RemoveTexture( LPSTR strTextureName );
			void		ClearTextures();
			int			TextureCount(){ return t_list->size();};
//Материалы
			bool		AddMaterial( LPSTR strFileName );
			bool		AddMaterial( vrMaterial2 *material_p );
			vrMaterial2* GetMaterial( LPSTR strMaterialName );
			void		RemoveMaterial( LPSTR strMaterialName );
			void		ClearMaterials();
			int			MaterialCount(){ return m_list->size(); };
//Объекты
			bool		AddObject( LPSTR strFileName );
			bool		AddObject( vrTriObject2 *object_p );
			vrTriObject2* GetObject( LPSTR strObjectName );
			vrTriObject2* GetObject( int a );
            void		RemoveObject( LPSTR strObjectName );
			int			ObjectCount(){ return o_list->size(); };
//Шрифты
			bool		AddFont( LPSTR strFileName );
			bool		AddFont( vrFont	*font_p );
			vrFont*		GetFont( LPSTR strFontName );
			int			FontCount(){ return f_list->size(); };
//Врапперы
			bool		AddWrapper( ObjectWrapper *wrapper_p );
		ObjectWrapper* GetWrapper( int a );
		ObjectWrapper* GetWrapper( LPSTR strName );
        //void		RemoveWrapper( LPSTR strName );
		int			WrapperCount(){ return w_list->size();};
		void		ClearWrapper();

//Шейдеры
			bool		AddShader( glShader *shader_p );
			bool		AddShader( LPSTR strFileName );
			glShader*	GetShader( LPSTR strShaderName );	

			
			BOOL		LoadTextures( LPSTR strFileName );
			BOOL		LoadMaterials( LPSTR strFileName );
			BOOL		LoadObjects( LPSTR strFileName );

private:


//******************************************************************************

//Cache

		T_LIST	*t_list;		//текстуры
		M_LIST	*m_list;		//материалы
		O_LIST	*o_list;		//объекты
		F_LIST	*f_list;		//шрифты
		W_LIST	*w_list;		//object wrappers
		S_LIST	*s_list;		//шейдеры
 

};


#endif