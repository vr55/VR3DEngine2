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
#include "vrResourceMgr.h"

//==============================================================//
//																//
//==============================================================//


bool vrResourceManager::Load( LPSTR strFileName )			//загрузка скрипта
{

/*

FILE			*f;
STRLIST			*s_list;

e_log.WriteOut("[STATUS] Loading Resources from File %s\n", strFileName );

if ( ( f = fopen( strFileName, "rt" ) ) == NULL ) 
{
	e_log.WriteOut("[ERROR] Unable to Open Resource File %s\n", strFileName );
	return false;
}

s_list = new STRLIST();	//создаем новый список

while ( !feof( f ) ) 
{
	char *line  = (char*)malloc( 255 * sizeof ( char ) );//выдел€ем пам€ть под строку
	fgets( line, 255, f );	//читаем строку
	
	if ( LineProcess( line ) )				//если строка значима€, включаем ее в список дл€ компил€ции
		s_list->insert( s_list->end(), line );
	else free( line );						//если нет, освобождаем выделенную под неЄ пам€ть

}
fclose( f );

CompileList( s_list );						//компилируем список
Execute();									//выполн€ем его
//список надо обнулить
_code->clear();
//_code->erase( _code->begin(), _code->end() );
*/
return true;
}




//==============================================================//
//																//
//==============================================================//
