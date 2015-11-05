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

#ifndef __VRCONSOLE_H__
#define __VRCONSOLE_H__

#include "vrEngine.h"
#include "vrInclude.h"
#include "vrVector.h"
#include "vrFont.h"
#include "vrTimer.h"
#include "vrWorld.h"
#include <list>
#include <vector>

#define INDENTION	3		//отступ

#define VR_CONSOLE_FADE_IN		0	//консоль выдвигается
#define	VR_CONSOLE_FADE_OUT		1	//консоль задвигается
#define	VR_CONSOLE_VISIBLE		2	//консоль полностью видна
#define	VR_CONSOLE_INVISIBLE	3	//консоль полностью невидна


#define VR_TYPE_UINT			0
#define VR_TYPE_INT				1
#define VR_TYPE_FLOAT			2
#define VR_TYPE_STR				3
#define VR_TYPE_BOOL			4
#define VR_TYPE_COM				5
#define VR_TYPE_VEC				6

//===============================================================
typedef struct
{
	char	token[32];	//токен на который отзывается команда
	int		type;		//тип переменной
	void*	param;		//ссылка на параметры

	void	(*proc)( const char &c );		//указатель на процедуру, которую выполняет команда

}cmd, *lp_cmd;

//===============================================================
typedef std::vector<LPSTR>	STRINGS;

typedef std::list<lp_cmd>	COMMANDS;
//=============================================================================
class vrConsole
{

public: /*SUBROUTINES*/

		vrConsole();
		~vrConsole();
		bool Toggle();

		bool Init();

		void Update( void );
		void HandleInput( UINT uVirtKey );

		bool AddCMD( char *token, int type, void* param, void(*proc)( const char &c ) );
		bool AddCMD( lp_cmd command );
		bool ExecCMD( LPSTR strCMD );

		bool AddString( LPSTR str, ... );



public: /*VARIABLES*/

		vrFont			*Font;			//шрифт
		vrMaterial2		*material_p;	//материал	
		int				iStatus;		//текущий статус консоли: VR_CONSOLE_FADE_IN/VR_CONSOLE_FADE_OUT/...
		float			fFadeSpeed;		//скорость развертывания


private: /*SUBROUTINES*/
		void			Render();		//отрисовка консоли
		char			VKToAscii( UINT key );
		bool			ExecCMD( cmd *command );
		cmd*			FindCMD( LPSTR strCMD );



private: /*VARIABLES*/
		signed int		siHeight;		//ТЕКУЩАЯ ВЫСОТА КОНСОЛИ в экранных координатах
		unsigned int	uiMaxHeight;	//максимальная высота консоли
		

		float			fAlpha;			//прозрачность
		vrVector3		vColor;			//цвет
		char			buffer[255];	//текстовый буфер, содержание которого выводится в консоли
		int				iPos;			//текущая позиция в массиве buffer


		STRINGS			*History;		//весь текст консоли
		COMMANDS		*Commands;		//команды



};
//--------------------------------------------------------------------
//консольные процедуры

void conResizeWindow( const char &c );
void conVer( const char &c );


//GLOBAL
//*******************************************************************
extern	vrConsole	console;
//*******************************************************************
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#endif













