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

#ifndef __VRTEXTURE_H__
#define __VRTEXTURE_H__


//#include "vrEngine.h"


//#include <ddraw.h>
//#include "vrCommonStruct.h"

//#include "vrInclude.h"
#include "ijl.h"
#include "vrErrorLog.h"
#include "vrUtils.h"
#include "vrBase.h"

//#include "glext.h"

//==============================================================//
//																//
//==============================================================//


class vrTexture
{

public: /*SUBROUTINES*/

		vrTexture();
		~vrTexture();

		bool		LoadFromFile( LPSTR strFileName );
		bool		Upload();				//��������� �������� � ����� ������
		void		Unload();				//������� �������� �� ������
		void		Bind();
		void		UnBind();

public: /*VARIABLES*/
		unsigned int	uiWidth;			//������
		unsigned int	uiHeight;			//������

	//	unsigned int	uiGLID;				//GL �������������
		unsigned int	uiID;

		char			cName[64];	//��� ��������
		int				iFormat;
		int				iMipMapCount;		//������ ��� DDS

		byte			*bData;

		bool			bCompress;			//������������� ������
		bool			bMipmap;			//mipmaping
		bool			bUploaded;		

		void		DeleteData();			//������� DIB ������( bData )

private: /*SUBROUTINES*/



private: /*VARIABLES*/

//		int				iCompressedInternalFormat;
		
		vrErrorLog		eLog;
};



#endif


