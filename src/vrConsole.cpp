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
#include "vrConsole.h"


//==============================================================//
//																//
//==============================================================//
//***********GLOBAL*****
vrConsole	console;
//**********************

vrConsole::vrConsole() /*CONSTRUCTOR*/
{

	siHeight	= 0;
	uiMaxHeight = 250;//engine.uiScreenHeight/2;

	fAlpha		= 0.8f;

	vColor.x	= 0.0f;
	vColor.y	= 0.0f;
	vColor.z	= 0.0f;

	iStatus		= VR_CONSOLE_INVISIBLE;

	iPos		= -1;
	fFadeSpeed	= 10.0;

	ZeroMemory( &buffer, sizeof( buffer ) );

	material_p	= NULL;

	History		= new STRINGS();
	Commands	= new COMMANDS();

	AddString( " " );



}
//==============================================================//
//																//
//==============================================================//
vrConsole::~vrConsole()
{

History->clear();
Commands->clear();

}
//==============================================================//
//																//
//==============================================================//


bool vrConsole::Toggle()/*PUBLIC*/
{
switch( iStatus )
{
case VR_CONSOLE_INVISIBLE:
	{
	iStatus = VR_CONSOLE_FADE_IN;
	return true;
	}

case VR_CONSOLE_VISIBLE:
	{
	iStatus = VR_CONSOLE_FADE_OUT;
	return true;
	}

case VR_CONSOLE_FADE_IN:
	{
	return true;
	iStatus = VR_CONSOLE_FADE_OUT;
	return true;
	}

case VR_CONSOLE_FADE_OUT:
	{
	return true;
	iStatus = VR_CONSOLE_FADE_IN;
	return true;
	}

}
return true;


}

//==============================================================//
//																//
//==============================================================//
void vrConsole::Update() /*PUBLIC*/
{

if ( iStatus == VR_CONSOLE_INVISIBLE ) return;	//если консоль невидима, выходим

if ( iStatus == VR_CONSOLE_FADE_IN ) siHeight += fFadeSpeed * 2;//engine.GetTickCount()/10;

if ( iStatus == VR_CONSOLE_FADE_OUT ) siHeight -= fFadeSpeed * 2;//engine.GetTickCount()/10;

if ( siHeight <= 0.0 ) 
{
	siHeight = 0.0f;
	iStatus = VR_CONSOLE_INVISIBLE;
}

if ( siHeight >= uiMaxHeight ) 
{
siHeight = uiMaxHeight;
iStatus = VR_CONSOLE_VISIBLE;
}


uiMaxHeight = engine.uiScreenHeight/2.52;
this->Render();


}


//==============================================================//
//																//
//==============================================================//

void vrConsole::Render() /*PRIVATE*/
{


glPushAttrib( GL_ALL_ATTRIB_BITS );

//engine.glSetState( GL_BLEND, true );
glDisable( GL_ALPHA_TEST );
glBlendFunc( GL_ONE, GL_ONE );
engine.glSetState( GL_TEXTURE_2D, false );
engine.glSetState( GL_FOG, false );

glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );//???????


	engine.glStoreMatrix( GL_PROJECTION ); 
	glLoadIdentity();									// reset the matrix

	engine.glStoreMatrix( GL_MODELVIEW ); 
	glLoadIdentity();


	gluOrtho2D( 0, engine.uiScreenWidth, engine.uiScreenHeight, 0 );

if ( material_p ) material_p->Begin();

glBegin( GL_QUADS );
	glColor4f( vColor.x, vColor.y, vColor.z, fAlpha );

	glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 0.0f );
	glVertex2i( 0, 0 );

	glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 0.0f );
	glVertex2i( engine.uiScreenWidth,0  );

	glMultiTexCoord2f( GL_TEXTURE0, 1.0f, 1.0f );
	glVertex2i( engine.uiScreenWidth, siHeight );

	glMultiTexCoord2f( GL_TEXTURE0, 0.0f, 1.0f );
	glVertex2i( 0, siHeight );

glEnd();

if ( material_p ) material_p->End();

	engine.glRestoreMatrix( GL_PROJECTION );
	engine.glRestoreMatrix( GL_MODELVIEW );
glPopAttrib();


//
Font->Print( INDENTION, engine.uiScreenHeight - siHeight + INDENTION, ">>: %s", buffer );


//выводим на экран все содержимое консоли
STRINGS::iterator b=History->begin(), e = History->end()-1;
LPSTR	s;
int pos = 0;
int i=0;
while ( b != e )
{
	s = *e;
	pos = engine.uiScreenHeight - siHeight + INDENTION + (Font->i_width*(i+1));
//	if ( pos >= uiMaxHeight ) break;
	i++;
	Font->Print( INDENTION, pos , "%s", s );

	e--;
}




		

}



//==============================================================//
//																//
//==============================================================//

void vrConsole::HandleInput( UINT uVirtKey )
{

if ( iStatus == VR_CONSOLE_VISIBLE )
{

iPos++;

if ( uVirtKey == 8 ) //Backspace
{
	if ( iPos < 0 ) iPos = -1;
	buffer[ iPos - 1] = 0x00;

	iPos-=2;

	return;
}

if ( uVirtKey == 13 )	//enter
{
	int len = strlen(buffer);

	char *s = new char[len + 1];
	ZeroMemory( s, len + 1);
	strncpy( s, buffer, len );
	AddString( "/%s", s );
	ZeroMemory( buffer, 255 );
	iPos = -1;

	ExecCMD( s );
	return;


}

if ( uVirtKey == 37 || uVirtKey == 38 || uVirtKey == 39 || uVirtKey == 40 ) //up//left//right/down keys
{
	iPos--;
	return;

}

char a = VKToAscii( uVirtKey );

buffer[ iPos ] = a;


}


}

//==============================================================//
//																//
//==============================================================//

char vrConsole::VKToAscii( UINT key )
{
char	ch = 0;

	BOOL bShiftDown = !!(GetKeyState (VK_SHIFT) & 0x8000);
	BOOL bCapsLockOn = !!(GetKeyState (VK_CAPITAL) & 0x01);
	BOOL bNumLockOn = !!(GetKeyState (VK_NUMLOCK) & 0x01);
	BOOL bUpperCase = (bCapsLockOn && !bShiftDown) || (!bCapsLockOn && bShiftDown);

	if ( key >= 'A' && key <= 'Z' && !bUpperCase)
	{
		key += 32;
	}
	else if ( ( key >= 48 && key <= 57 ) && bShiftDown )
	{
		// we are not checking explicitly for some of 
		// the values included in the ranges above since
		// because they are characters only derived with
		// a shift combination, they should not ever be 
		// encountered

		switch ( key )
		{
			case '0': key = ')'; break;
			case '1': key = '!'; break;
			case '2': key = '@'; break;
			case '3': key = '#'; break;
			case '4': key = '$'; break;
			case '5': key = '%'; break;
			case '6': key = '^'; break;
			case '7': key = '&'; break;
			case '8': key = '*'; break;
			case '9': key = '('; break;
		}
	}
	else if ((key >= 186 && key <= 191) || (key >= 219 && key <= 222))
	{
		switch (key)
		{
			case 186: key = bShiftDown ? ':' : ';'; break;
			case 187: key = bShiftDown ? '+' : '='; break;
			case 188: key = bShiftDown ? '<' : ','; break;
			case 189: key = bShiftDown ? '_' : '-'; break;
			case 190: key = bShiftDown ? '>' : '.'; break;
			case 191: key = bShiftDown ? '?' : '/'; break;
			
			case 219: key = bShiftDown ? '{' : '['; break;
			case 220: key = bShiftDown ? '|' : '\\'; break;
			case 221: key = bShiftDown ? '}' : ']'; break;
			case 222: key = bShiftDown ? '\"' : '\''; break;
		}
	}

	else if (key >= 96 && key <= 105 && bNumLockOn)
	{
		switch (key)
		{
			case VK_NUMPAD0: key = '0'; break;
			case VK_NUMPAD1: key = '1'; break;
			case VK_NUMPAD2: key = '2'; break;
			case VK_NUMPAD3: key = '3'; break;
			case VK_NUMPAD4: key = '4'; break;
			case VK_NUMPAD5: key = '5'; break;
			case VK_NUMPAD6: key = '6'; break;
			case VK_NUMPAD7: key = '7'; break;
			case VK_NUMPAD8: key = '8'; break;
			case VK_NUMPAD9: key = '9'; break;
		}
	}
	else if (key >= 106 && key <= 111)
	{
		switch (key)
		{
			case VK_MULTIPLY:	key = '*'; break;
			case VK_ADD:		key = '+'; break;
			case VK_SUBTRACT:	key = '-'; break;
			case VK_DECIMAL:	key = '.'; break;
			case VK_DIVIDE:		key = '/'; break;
		}
	}
ch = key;

return ch;
}

//==============================================================//
//																//
//==============================================================//
bool vrConsole::AddString( LPSTR str, ... )
{

char	*Text = new char[ 255 ];
ZeroMemory( Text, 255 );

va_list	l_print;

	va_start( l_print, str );

	    vsprintf( Text, str, l_print );	// Конвертитуем все что передали процедуре в строку

	va_end( l_print );


History->push_back( Text );

return true;

}

//==============================================================//
//																//
//==============================================================//
bool vrConsole::AddCMD( char *token, int type, void* param, void(*proc)( const char &c ) )
{
	cmd *c= new cmd;
	strncpy( c->token, token, 32 );
	ToUpperCase( c->token );
	c->type		= type;
	c->param	= param;
	c->proc		= proc;

	Commands->push_back( c );

return true;

}
//==============================================================//
//																//
//==============================================================//
bool vrConsole::AddCMD( lp_cmd command )
{

if ( command ) Commands->push_back( command );


return true;
}

//==============================================================//
//																//
//==============================================================//

bool vrConsole::ExecCMD( LPSTR strCMD )
{

//1.выделяем из строки первое слово, которое <предположительно> является командой
	char	c_cmd[32];	//максимальный размер 32 символа
	char	c_param1[64];
	char	c_param2[64];
	char	c_param3[64];

	
	int field = sscanf( strCMD, "%s %s %s %s %s %s %s %s", (char*)c_cmd, (char*)c_param1, (char*)c_param2, (char*)c_param3 ); //переменная field = количеству слов в строке
	if ( field < 1 ) return false;

	ToUpperCase( c_cmd );

	cmd* c = FindCMD( c_cmd );

	if ( c == NULL )//если команды нет
	{

		AddString( "%s - Invalid Command", c_cmd );//если команда не найдена, выводим сообщение об этом

		return false;
	}
//*****************************************************************
//----EXECUTIVE
//*****************************************************************
switch( c->type )
{
case VR_TYPE_UINT://-----------------------------------------------
	if ( field > 2 ) return false;
	if ( field < 2 )
	{
		if ( c->param ) AddString("%i", *(UINT *)c->param );
		return true;

	}
	if ( c->param ) *(UINT *) c->param = atoi( c_param1 );
	if ( c->proc ) c->proc( *strCMD );

	break;

	
case VR_TYPE_COM://------------------------------------------------
	//if ( field != 1 ) return false;
	if ( c->proc ) c->proc( *strCMD );
	return true;
	break;

case VR_TYPE_FLOAT://----------------------------------------------
	if ( field > 2 ) return false; //больше двух полей быть неможет
	if ( field < 2 )				//если меньне двух, просто выводим значение
	{
		if ( c->param ) AddString( "%f", *(float*)c->param );
		return true;

	}
	if ( c->param ) *(float *) c->param = atof( c_param1 );
	if ( c->proc ) c->proc( *strCMD );


	break;	

case VR_TYPE_BOOL://------------------------------------------------
	if ( field > 2 ) return false;
	if ( field < 2 )
	{
		if ( c->param ) AddString( "%d", (*(BOOL*)c->param) );
		return true;


	}
	if ( c->param ) *( BOOL* )c->param = ( atof( c_param1 )  > 0 ) ? TRUE : FALSE;
	if ( c->proc ) c->proc( *strCMD );

	break;//---------------------------------------------------------
case VR_TYPE_VEC://--------------------------------------------------
	if ( field < 2 )
	{
		if ( c->param )
		{
		vrVector3	v( *(float*)c->param, *(float*)c->param+sizeof(float), *(float*)c->param+sizeof(float)+sizeof(float) );
		AddString( "pos: %.3f %.3f %.3f", v.x, v.y, v.z );
		return true;
		}

	}
	if ( field == 4 )
	{

		if ( c->param )
		{

			vrVector3	v( atof( c_param1 ), atof( c_param2 ), atof( c_param3 ) );
			*(vrVector3*)c->param = v;
		//	*(float*)c->param + sizeof(float ) = v.y;


			

		}


	}
	if ( c->proc ) c->proc( *strCMD );


	break;//--------------------------------------------------------

case VR_TYPE_STR://BUGS BUGS BUGS!!!!!
		if ( field >2 ) return false;
		if ( field < 2 )
		{
			if ( c->param ) AddString( "%s", (*( LPSTR )c->param ));
			return true;

		}

//		if ( c->param ) strcpy( ( LPSTR )c->param, c_param1  );//!!!!!I'M NOT SHURE HERE!!!!
		if ( c->proc ) c->proc( *strCMD );

	break;
}
return true;
}

//==============================================================//
//																//
//==============================================================//
bool vrConsole::ExecCMD( cmd *c )
{

if ( strcmp( c->token, "VER") == 0 ) 

AddString( "VR3D Engine II - %s ...", __DATE__ );



return true;
}

//==============================================================//
//																//
//==============================================================//
cmd* vrConsole::FindCMD( LPSTR strCMD )
{

COMMANDS::iterator i = Commands->begin();
cmd *cmd_cmd;

	while ( i != Commands->end() )
	{
		cmd_cmd = *i;
		if ( strcmp( strCMD, cmd_cmd->token ) == 0 )
		{
			//выполняем команду
			return cmd_cmd;

		}

		i++;
	}

return NULL;
}
//==============================================================//
//																//
//==============================================================//
bool vrConsole::Init()
{

	AddCMD( "VER",			VR_TYPE_COM,	NULL,						&conVer );
	AddCMD( "SCREENWIDTH",	VR_TYPE_UINT,	&engine.uiScreenWidth,		&conResizeWindow );
	AddCMD( "SCREENHEIGHT", VR_TYPE_UINT,	&engine.uiScreenHeight,		&conResizeWindow );

	AddCMD( "CAMSPEED",		VR_TYPE_FLOAT,	&world.camera->Speed,		NULL );
//	AddCMD(	"FOV",			VR_TYPE_FLOAT,	&world.camera->Fov,			&conCamera );
//	AddCMD( "SENSITIVITY",	VR_TYPE_FLOAT,	&world.camera->sensitivity,	&conCamera );
//	AddCMD( "ZFAR",			VR_TYPE_FLOAT,	&world.camera->Zfar,		&conCamera );
	AddCMD(	"WIREFRAME",	VR_TYPE_BOOL,	&engine.bUseWireframe,		NULL );
	AddCMD( "SHOWBBOX",		VR_TYPE_BOOL,	&engine.bShowBBox,			NULL );
	AddCMD( "CONSPEED",		VR_TYPE_FLOAT,	&console.fFadeSpeed,		NULL );
	AddCMD( "CAMPOS",		VR_TYPE_VEC,	&world.camera->Position,	NULL );

/*
	AddCMD( "SELWRAPPER",	VR_TYPE_COM,	NULL,						&conSelWrapper );
	AddCMD( "SELBYNAME",	VR_TYPE_COM,	NULL,						&conSelWrapperByName );
	AddCMD( "SCALE",		VR_TYPE_COM,	NULL,						&conWrapperScale );
	AddCMD( "POS",			VR_TYPE_COM,	NULL,						&conWrapperTranslate );
	AddCMD( "ROT",			VR_TYPE_COM,	NULL,						&conWrapperRotate );
	AddCMD( "SAVEWORLD",	VR_TYPE_COM,	NULL,						&conSaveWorld );
	AddCMD( "LOADWORLD",	VR_TYPE_COM,	NULL,						&conLoadWorld );
	AddCMD( "REPLACEWORLD",	VR_TYPE_COM,	NULL,						&conReplaceWorld );
	AddCMD( "WRAPPERLIST",	VR_TYPE_COM,	NULL,						&conWrapperList );
	AddCMD( "CLONE",		VR_TYPE_COM,	NULL,						&conCloneWrapper );

*/
//TODO;
	//AddCMD( "CLS"
	//AddCMD( "CONDUMP"

return true;
}

//==============================================================//
//																//
//==============================================================//
void conResizeWindow( const char &c )
{

//engine.ResizeWindow();

}
//==============================================================//
//																//
//==============================================================//
void conVer( const char &c )
{
#ifdef _DEBUG 
console.AddString( "VR3D Engine II - %s - DEBUG BUILD...", __DATE__ );
#else 
console.AddString( "VR3D Engine II - %s - RELEASE BUILD...", __DATE__ );

#endif


}

//==============================================================//
//																//
//==============================================================//
/*
void conWrapperList( const char &c )
{

char c_cmd[32];
char c_param[255];
int i = sscanf( &c, "%s %s ", (char*)c_cmd, &c_param ); //переменная i = количеству слов в строке

if ( i == 1 )
{

	int c = world.r_mgr->WrapperCount();
	ObjectWrapper *ow;
	for ( int a = 0; a<c; a++ )
	{
		ow = world.r_mgr->GetWrapper(a);
		console.AddString( "%i: %s %s pos: %.2f %.2f %.2f", a, ow->cName, ow->object->cName, ow->vTranslate.x, ow->vTranslate.y, ow->vTranslate.z );
	
	}

}

else console.AddString( "WrapperList - Display Wrappers List" );



}
*/