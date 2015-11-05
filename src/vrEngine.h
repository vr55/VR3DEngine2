
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


/*				
					VR3D [II] - http:\\www.vr3d.by.ru\

					����� ������������� ������

*/
#ifndef __VRENGINE_H__
#define __VRENGINE_H__

//#ifndef __VRENGINE_H__
//#define __VRENGINE_H__


#include "vrErrorLog.h"

#include "vrInclude.h"
#include "vrVertex.h"
#include "vrFrustum.h"
#include "vrTimer.h"

//==============================================================//
//																//
//==============================================================//


void DummyGLExtension();

class vrEngine
{
//friend class vrWorld;

public: /*SUBROUTINES*/
						vrEngine();
						~vrEngine();

		bool			LoadSettings( LPSTR strFileName );	//�������� ���������� �� �����

		bool			Initialize( );
        bool			AttachToWindow( HWND hWindowHandle );
		void			ShutDown( void );
		bool			IsGLExtensionSupport( LPSTR strGLExtension );
		void			ResizeWindow( int width, int height );
		void			ResizeWindow();

//��������� ��� ������ � OpenGL
		void			glSetState( GLenum cap, bool state );
		void			glBeginScene( GLenum mode );
		void			glEndScene();
		void			glRenderPrimitive( DWORD count, vrVertex *buffer );
		void			glRenderPrimitive( DWORD count, vrVector3 *buffer );
		void			glStoreMatrix( GLenum mode );
		void			glRestoreMatrix( GLenum mode );
		void			glActiveTexture( GLenum mode );


//��������� ��� ������ � DirectInput
		void*			GetMouseState();
		void*			GetKeyboardState();

//�������
		void			UpdateFrustum();


//������
		float			GetTickCount();
		void			ResetTimer();

//Image Loading/Unloading
		bool			LoadImage( LPSTR strFileName, vr_image *image );
		void			FreeImage ( vr_image *image );

public: /*VARIABLES*/
		void			*lpWindowProc;			//��������� �� ������� ��������� ��������� ���������
		LPSTR			strWindowName;			//��� ����
		HWND			hWindowHandle;
		HGLRC           hGLResourceContext;
		unsigned int	uiScreenWidth;			// ������ ������
		unsigned int	uiScreenHeight;			// ������ ������
		BYTE			cColorBits;
		bool			bFullScreen;			//������ �����
		float			fTextureLODBias;	

		vrFrustum		frustum;

		unsigned int	uiPolyCount;			//
		glShaderManager SM;




//���������� ����������
		bool			bUseMipMapping;			//���-������� (on/off)
		bool			bUseTextureFilter;		//���������� �������
		bool			bUseTextureCompression;	//������ �������
		bool			bUseMultitexture;		//���������������������
		BOOL			bPolygonCulling;

		BOOL			bUseWireframe;
		BOOL			bShowBBox;



private: /*SUBROUTINES*/
		bool			CreateEngineWindow( void );	//������� �������� ����
		void			KillEngineWindow( void );
		bool			InitRenderDevice( void );	//�������������� OpenGL
		void			KillRenderDevice( void );
		bool			SetFullScreenMode( void );	//������������� ������������� �����
		bool			InitInputDevice( void );	//�������������� DirectInput
		void			KillInputDevice( void );
		void			GetDriverInfo( void );

		bool			InitImageLib( void );




private: /*VARIABLES*/

		BYTE			cDepthBits;				// ������� z-������
		BYTE			cAccumBits;
		BYTE			cStencilBits;
		HINSTANCE		hInstance;
		LPSTR			strGLExtensions;

		BOOL			bAttachToWindow;
		

		
		bool			bShowCursor;

		HINSTANCE				hDirectInputLib;
		HINSTANCE				hImageLib;

		DIMOUSESTATE2			dims2;        // DirectInput mouse state structure
		BYTE					diks[256];	  // DirectInput keyboard state buffer
		


		vrTimer					*timer;		//������
		float					tTimerCount;
				



};



#endif