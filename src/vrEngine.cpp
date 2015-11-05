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

#include "vrEngine.h"
#include "vrEngineFunc.h"

#pragma warning( disable:4006 )

//Direct Input
typedef	bool ( CALLBACK *LPFNVRINITDIRECTINPUT )( HWND );
LPFNVRINITDIRECTINPUT		vrInitDirectInput;

typedef	void* ( CALLBACK *LPFNVRGETMOUSESTATE )( );
LPFNVRGETMOUSESTATE			vrGetMouseState;

typedef	void* ( CALLBACK *LPFNVRGETKEYBOARDSTATE )( );
LPFNVRGETKEYBOARDSTATE			vrGetKeyboardState;

typedef	void ( CALLBACK *LPFNVRKILLDIRECTINPUT )( );
LPFNVRKILLDIRECTINPUT			vrKillDirectInput;

//image lib

typedef BOOL ( CALLBACK *LPFNVRIMAGELOAD )( LPSTR, vr_image* ) ;
LPFNVRIMAGELOAD			vrImageLoad;


typedef BOOL ( CALLBACK *LPFNVRIMAGEFREE )( vr_image* );
LPFNVRIMAGEFREE			vrImageFree;

//==============================================================//
//																//
//==============================================================//
//************GLOBAL*********************
vrEngine engine;

//***************************************
vrEngine::vrEngine()/*CONSTRUCTOR*/
{
/*----------Default Settings------------*/
uiScreenWidth			= 640;
uiScreenHeight			= 480;
cColorBits				= 32;
cDepthBits				= 24;
cAccumBits				= 0;
cStencilBits			= 0;
strWindowName			= "Main Window";
lpWindowProc			= NULL;
hInstance				= 0;
hWindowHandle			= NULL;
strGLExtensions			= NULL;

timer					= NULL;

bFullScreen				= false;
bShowCursor				= true;


bUseMipMapping			= true;
bUseTextureFilter		= true;
bUseTextureCompression	= true;
bUseWireframe			= true;
bShowBBox				= false;
bUseMultitexture		= true; 
bPolygonCulling			= true;

fTextureLODBias			= 0.01f;

bAttachToWindow                 = FALSE;

//eLog.Create( ENGINE_LOG_PATH );

}



//==============================================================//
//																//
//==============================================================//

vrEngine::~vrEngine()/*DESTRUCTOR*/
{


//---------Free DLLs
	FreeLibrary( hDirectInputLib );
	FreeLibrary( hImageLib );

}


//==============================================================//
//																//
//==============================================================//

bool vrEngine::Initialize( )/*PUBLIC*/
{

e_log.Create( ENGINE_LOG_PATH );

e_log.WriteOut( "\n/*-------------------------------------------------------------*/\n" );
e_log.WriteOut( "\t\tLog File Started\n" );
e_log.WriteOut( "/*-------------------------------------------------------------*/\n" );
e_log.WriteDate();

e_log.WriteOut( "[STATUS] Initialization...\n" );

//-------------Loading DLLs
e_log.WriteOut( "[STATUS] Loading Libs\n" );

hDirectInputLib = LoadLibrary( "vrDirectInput.dll" );

if ( !hDirectInputLib ) 
{
	e_log.WriteOut( "[ERROR] Unable to Load vrDirectInput.dll\n" );
	return false;
}

hImageLib = LoadLibrary( "vrImage.dll" );

if ( !hImageLib )
{
	e_log.WriteOut( "[ERROR] Unable Load vrImage.dll\n" );
	return false;

}
//------------------------------------------------------
if ( !bAttachToWindow )
{
	e_log.WriteOut( "[STATUS] Creating Window\n" );
        if ( !CreateEngineWindow() ) return false;
}
	e_log.WriteOut( "[STATUS] Initializing Image Loader\n" );
if ( !InitImageLib() ) return false;

	e_log.WriteOut( "[STATUS] Initializing Render Device\n" );
if ( !InitRenderDevice() ) return false;

	e_log.WriteOut( "[STATUS] Initializing Input Device\n" );
if ( !bAttachToWindow )
   if ( InitInputDevice() == false ) return false;


	e_log.WriteOut( "[STATUS] Initializing Timer\n" );
vrTimer *t = new vrTimer();
if (!t ) e_log.WriteOut( "[ERROR] Unable to Initialize Timer\n" );
if ( t ) this->timer = t;


	e_log.WriteOut("[STATUS] Initializing GLSL\n" );
if ( !checkGL2() ) return false;
	e_log.WriteOut("[STATUS] GLEW Version %s\n", glewGetString(GLEW_VERSION) );
	e_log.WriteOut("[STATUS] OpenGL Version %s\n", glGetString(GL_VERSION) );
	e_log.WriteOut("[STATUS] OpenGL Driver Vendor %s\n", glGetString(GL_VENDOR) );
	e_log.WriteOut("[STATUS] OpenGL Renderer %s\n", glGetString(GL_RENDERER) );
	e_log.WriteOut("[STATUS] OpenGL Extentions %s\n", glGetString(GL_EXTENSIONS) );


e_log.WriteOut( "\n" );

return true;
}


//==============================================================//
//																//
//==============================================================//

bool vrEngine::CreateEngineWindow()/*PRIVATE*/
{

WNDCLASSEX		wc;
DWORD			dwFlags;

char			buffer[255];


	if ( this->lpWindowProc == NULL )
	{
		e_log.WriteOut( "[ERROR] Main WIndow Proc not specified\n" );
		sprintf( buffer, "Window Proc not set. File %s,  Line %i", __FILE__, __LINE__ );
		MessageBox( engine.hWindowHandle, buffer, "vrEngine::CreateWindow", MB_ICONERROR );
		return false;
	}

	ZeroMemory( &wc, sizeof( WNDCLASSEX ) );

	wc.cbSize			= sizeof( WNDCLASSEX );
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= ( WNDPROC )this->lpWindowProc;
	wc.hInstance		= this->hInstance;
	wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= ( HBRUSH ) ( COLOR_BACKGROUND );
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "vrEngine2";


	if ( !RegisterClassEx( &wc ) )
	{
		e_log.WriteOut( "[ERROR] Unable to register window class \n" );
		sprintf( buffer, "Can't Register Window Class. File %s Line %i", __FILE__, __LINE__);
		MessageBox( engine.hWindowHandle , buffer, "vrEngine::CreateWindow", MB_ICONERROR );
		return false;
	}


if ( this-> bFullScreen )
{
	dwFlags = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
	if ( !SetFullScreenMode() ) return false;

}
else dwFlags = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;


RECT	windowRect;
		windowRect.left		= 0;
		windowRect.top		= 0;
		windowRect.right	= this->uiScreenWidth;
		windowRect.bottom	= this->uiScreenHeight;

		AdjustWindowRect( &windowRect, dwFlags, false );


this->hWindowHandle = CreateWindowEx( WS_EX_TOPMOST,
										"vrEngine2",
										this->strWindowName,
										dwFlags,
										0, 0,
										windowRect.right - windowRect.left,
										windowRect.bottom - windowRect.top,
										HWND_DESKTOP,
										0,
										this->hInstance,
										NULL );


if ( !this->hWindowHandle )
{
		e_log.WriteOut( "[ERROR] Unable to create window\n" );

		sprintf( buffer, "Can't Create Window. File %s Line %i", __FILE__, __LINE__);
		MessageBox( engine.hWindowHandle, buffer, "vrEngine::CreateWindow", MB_ICONERROR );
		return false;

}


ShowWindow( this->hWindowHandle, SW_SHOWNORMAL );

UpdateWindow( this->hWindowHandle );

SetFocus( this->hWindowHandle );

if ( !this->bShowCursor ) ShowCursor( false );
else ShowCursor( true );


return true;
}

//==============================================================//
//																//
//==============================================================//

void vrEngine::KillEngineWindow( void )
{
if ( this->hWindowHandle )
{

DestroyWindow( this->hWindowHandle );

}

}

//==============================================================//
//																//
//==============================================================//

bool vrEngine::InitRenderDevice()/*PRIVATE*/
{

char	buffer[255];

PIXELFORMATDESCRIPTOR	pfd = {
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,						// version number
		PFD_DRAW_TO_WINDOW |	// support window
		PFD_SUPPORT_OPENGL |	// support OpenGL
		PFD_DOUBLEBUFFER,		// double buffered
		PFD_TYPE_RGBA,			// RGBA type
		this->cColorBits,		// color depth
		0, 0, 0, 0, 0, 0,		// color bits ignored
		0,                     // no alpha buffer
		0,                     // shift bit ignored
		this->cAccumBits,
		0, 0, 0, 0,            // accum bits ignored
		this->cDepthBits,
		this->cStencilBits,
		0,                     // no auxiliary buffer
		PFD_MAIN_PLANE,        // main layer
		0,                     // reserved
		0, 0, 0                // layer masks ignored
	};

int iPixelFormat = ChoosePixelFormat( GetDC( this->hWindowHandle ), &pfd );

if ( iPixelFormat == 0 )
{
	sprintf( buffer, "Can't Choose Pixel Format. File %s Line %i\n", __FILE__, __LINE__ );
	MessageBox( engine.hWindowHandle, buffer, "vrEngine::InitDevice", MB_ICONERROR );

	return false;

}

if ( !SetPixelFormat( GetDC( this->hWindowHandle ), iPixelFormat, &pfd ) )
{
	e_log.WriteOut( "[ERROR] Unable to Set Pixel Format\n" );

	sprintf( buffer, "Can't Set Pixel Format. File %s Line %i", __FILE__, __LINE__ );
	MessageBox( engine.hWindowHandle, buffer, "vrEngine::InitDevice", MB_ICONERROR );

	return false;

}

//HGLRC			hglrc;

hGLResourceContext = wglCreateContext( GetDC( this->hWindowHandle ) );
if ( hGLResourceContext == NULL ) return false;

if ( !wglMakeCurrent( GetDC( this->hWindowHandle ), hGLResourceContext ) ) return false;

glViewport( 0, 0, this->uiScreenWidth, this->uiScreenHeight );


return true;

}


//==============================================================//
//																//
//==============================================================//
bool vrEngine::SetFullScreenMode( void )/*PRIVATE*/
{

DEVMODE dmSettings;

ZeroMemory( &dmSettings, sizeof( DEVMODE ) );

if ( !EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &dmSettings ) ) return false;

dmSettings.dmBitsPerPel = this->cColorBits;
dmSettings.dmPelsWidth	= this->uiScreenWidth;
dmSettings.dmPelsHeight	= this->uiScreenHeight;


dmSettings.dmDisplayFrequency = 0;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^Очень важный момент. Если не установить частоту обновления дисплея, то в WinXP неработает



int result = ChangeDisplaySettings( &dmSettings, CDS_FULLSCREEN );

if( result != DISP_CHANGE_SUCCESSFUL )

	{	switch( result )
		{
			case DISP_CHANGE_BADMODE:
				e_log.WriteOut( "[ERROR] Unable to Set Fullscreen Mode. The graphics mode is not supported.\n" );
				break;
			case DISP_CHANGE_FAILED:
				e_log.WriteOut( "[ERROR] Unable to Set Fullscreen Mode. The display driver failed the specified graphics mode.\n" );
				break;
			case DISP_CHANGE_NOTUPDATED:
				e_log.WriteOut( "[ERROR] Unable to Set Fullscreen Mode. Unable to write settings to the registry.\n" );
				break;

		}
		//e_log.WriteOut( "[ERROR] Unable to Set Fullscreen Mode\n" );



		MessageBox( engine.hWindowHandle, "Can't Set Full Screen Mode", "vrEngine::SetFullScreenMode", MB_ICONERROR );
		return false;

	}
e_log.WriteOut( "[STATUS] Full Screen Mode at %i x %i @ %i Hz\n", this->uiScreenWidth, this->uiScreenHeight, dmSettings.dmDisplayFrequency );


return true;

}

//==============================================================//
//																//
//==============================================================//

void vrEngine::ResizeWindow( int width, int height )
{

if ( !bFullScreen ) 
{

uiScreenWidth = width;
uiScreenHeight = height;

glViewport( 0, 0, width, height );

}
}
//==============================================================//
//																//
//==============================================================//

void vrEngine::ShutDown( void )/*PUBLIC*/
{

e_log.WriteOut( "[STATUS] Killing Sequence Initialized...\n" );


e_log.WriteOut( "[STATUS] Killing Render Device\n" );
KillRenderDevice();


if ( !bAttachToWindow )
{
   e_log.WriteOut( "[STATUS] Killing Input Device\n" );
   KillInputDevice();

   e_log.WriteOut( "[STATUS] Killing Main Window\n" );
   KillEngineWindow();

   e_log.WriteOut( "[STATUS]Quit Aplication\nBYE BYE\n\n" );
   PostQuitMessage( 0 );

 }
return;
}

//==============================================================//
//																//
//==============================================================//

bool vrEngine::InitInputDevice( void )/*PRIVATE*/
{

vrInitDirectInput = ( LPFNVRINITDIRECTINPUT ) GetProcAddress( ( HMODULE ) hDirectInputLib, "vrInitDirectInput" );
vrGetMouseState = ( LPFNVRGETMOUSESTATE ) GetProcAddress( ( HMODULE ) hDirectInputLib, "vrGetMouseState" );
vrGetKeyboardState = ( LPFNVRGETKEYBOARDSTATE )GetProcAddress( ( HMODULE ) hDirectInputLib, "vrGetKeyboardState" );
vrKillDirectInput = ( LPFNVRKILLDIRECTINPUT ) GetProcAddress( ( HMODULE ) hDirectInputLib, "vrKillDirectInput" );

return vrInitDirectInput( this->hWindowHandle );

}
//==============================================================//
//																//
//==============================================================//
bool vrEngine::InitImageLib( void )
{

vrImageLoad = ( LPFNVRIMAGELOAD ) GetProcAddress( ( HMODULE ) hImageLib, "vrImage_Load" );
vrImageFree = ( LPFNVRIMAGEFREE ) GetProcAddress( ( HMODULE ) hImageLib, "vrImage_Free" );

if ( !vrImageLoad ) return false;
if ( !vrImageFree ) return false;

return true;


}

//==============================================================//
//																//
//==============================================================//

void vrEngine::KillInputDevice( void )/*PRIVATE*/
{

	vrKillDirectInput();

}
//==============================================================//
//																//
//==============================================================//
void vrEngine::KillRenderDevice( void )/*PRIVATE*/
{

if ( wglGetCurrentContext() != NULL )
{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( wglGetCurrentContext() );

}

if ( GetDC( this->hWindowHandle ) != NULL )
	{
		ReleaseDC( this->hWindowHandle, GetDC( this->hWindowHandle ) );
	}

if ( this->bFullScreen ) ChangeDisplaySettings( NULL,0 );
if ( !this->bShowCursor ) ShowCursor( true );


UnregisterClass( "vrEngine2", this->hInstance );


}
//==============================================================//
//																//
//==============================================================//


void vrEngine::GetDriverInfo( void )/*PRIVATE*/
{

this->strGLExtensions = ( LPSTR )glGetString( GL_EXTENSIONS );
//char *pdest = strstr( this->strGLExtensions, "GL_ARB_multitexture" );

//CPUID
/*
__asm
{
 xor eax, eax

 mov byte ptr[lb],0fh
 mov byte ptr[lb+1], 0a2h


 lb:
	 nop
	 nop
	 nop
	 nop

}


*/

}

//==============================================================//
//																//
//==============================================================//

bool vrEngine::IsGLExtensionSupport( LPSTR strGLExtension )/*PUBLIC*/
{
if ( !this->strGLExtensions ) return false;

char *pdest = strstr( this->strGLExtensions,  strGLExtension );

if ( pdest == NULL ) return false;
else 
return true;

}


//==============================================================//
//																//
//==============================================================//
void* vrEngine::GetMouseState()/*PUBLIC*/
{
	return vrGetMouseState();
}


//==============================================================//
//																//
//==============================================================//
void*	vrEngine::GetKeyboardState()
{
	return vrGetKeyboardState();
}

//==============================================================//
//																//
//==============================================================//

bool vrEngine::LoadSettings( LPSTR strFileName )
{

FILE		*f;
int			iChar;
char		buffer[255];


if ( ( f = fopen( strFileName, "r" ) ) == NULL ) return false;
else
{
	while ( !feof( f ) )
	{
		iChar = fgetc( f );										//читаем символ

		switch( iChar )
		{
		case 0x0a: continue;	//spacebar
		case 0x09: continue;	//tab

		case 0x23:				//#

			fgets( buffer, sizeof( buffer ), f );
			continue;
			
		case 0x5b:
			break;

		default:
			break;
		}
		




	}





}
return true;
}

//==============================================================//
//																//
//==============================================================//
void vrEngine::glSetState( GLenum cap, bool state )
{

switch ( cap )
{
case GL_COLOR_ARRAY:
case GL_EDGE_FLAG_ARRAY:
case GL_INDEX_ARRAY:
case GL_NORMAL_ARRAY:
case GL_TEXTURE_COORD_ARRAY:
case GL_VERTEX_ARRAY:
	{
		if ( state ) glEnableClientState( cap );
		if ( !state ) glDisableClientState( cap );
		break;	
	}

default:
	{
		if ( state ) glEnable( cap );
		if ( !state ) glDisable( cap );
		break;

	}
}


}

//==============================================================//
//																//
//==============================================================//

void DummyGLExtension()
{

__asm nop
return;
}

//==============================================================//
//																//
//	mode:	тип примитива: GL_LINE, GL_POINT, GL_TRIANGLE...	//
//																//
//==============================================================//
void vrEngine::glBeginScene( GLenum mode )
{

glBegin( mode );

}

//==============================================================//
//																//
//==============================================================//

void vrEngine::glEndScene()
{

	glEnd();

}
//==============================================================//
//																//
//	count:	количество точек
//
//	buffer: указатель на вершины 
//==============================================================//
void vrEngine::glRenderPrimitive( DWORD count, vrVertex *buffer )
{
assert( buffer );
if ( !buffer ) return;
	for ( int i=0; i<count; i++ )
	{
		
		glNormal3f( buffer[i].nx, buffer[i].ny, buffer[i].nz );
		glMultiTexCoord2f( GL_TEXTURE0, buffer[i].u0, buffer[i].v0 );
		glMultiTexCoord2f( GL_TEXTURE1, buffer[i].u0, buffer[i].v0 );
		glColor3f( buffer[i].r, buffer[i].g, buffer[i].b );

//		glTexCoord2f( buffer[i].u0, buffer[i].v0 );
		glVertex3f( buffer[i].x, buffer[i].y, buffer[i].z );
		uiPolyCount++;

	}




}

//==============================================================//
//																//
//==============================================================//


void vrEngine::glRenderPrimitive( DWORD count, vrVector3 *buffer )
{

	for ( int i=0; i<count; i++ )
	{
		glVertex3f( buffer[i].x, buffer[i].y, buffer[i].z );
		uiPolyCount++;
	}

}

//==============================================================//
//																//
//==============================================================//

void vrEngine::glStoreMatrix( GLenum mode )
{

glMatrixMode( mode );
glPushMatrix();

}

//==============================================================//
//																//
//==============================================================//

void vrEngine::glRestoreMatrix( GLenum mode )
{

glMatrixMode( mode );
glPopMatrix();


}

//==============================================================//
//																//
//==============================================================//

void vrEngine::glActiveTexture( GLenum mode )
{

glActiveTextureARB( mode );

}
//==============================================================//
//																//
//==============================================================//

void vrEngine::UpdateFrustum()
{

frustum.Update();

}


//==============================================================//
//																//
//==============================================================//

float vrEngine::GetTickCount()
{

//это неверно
//значение TickCount нужно обновлять каждый фрейм, а не при каждом
//вызове процедуры

//return timer->GetCount();
return tTimerCount;
}

//==============================================================//
//																//
//==============================================================//
void vrEngine::ResetTimer()
{
tTimerCount = timer->GetCount();
timer->Reset();

}
//==============================================================//
//																//
//==============================================================//
void vrEngine::ResizeWindow()
{

	ResizeWindow( uiScreenWidth, uiScreenHeight );

}
//==============================================================//
//																//
//==============================================================//

bool	vrEngine::LoadImage( LPSTR strFileName, vr_image *image )

{

bool a = vrImageLoad( strFileName, image );
return a;

 __asm nop

}
//==============================================================//
//																//
//==============================================================//


void vrEngine::FreeImage ( vr_image *image )
{
BOOL a = vrImageFree( image );

return;
}
//==============================================================//
//																//
//==============================================================//

bool	vrEngine::AttachToWindow( HWND hWindowHandle )
{

e_log.WriteOut( "[STATUS] Attach To Window Handle\n" );
bAttachToWindow = TRUE;
this->hWindowHandle = hWindowHandle;

return Initialize();
}
