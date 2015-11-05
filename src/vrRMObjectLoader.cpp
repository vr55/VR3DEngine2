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


BOOL vrResourceManager::LoadObjects( LPSTR strFileName )
{
 char	buffer[255];
 char	dummy[255];
 char   read[255];
 int	iObjectCount = 0;

 memset(  buffer, 0, 255 );
e_log.WriteOut("[STATUS] Parsing Resources from File %s \n", strFileName );

  FILE *f = fopen( strFileName, "rt" );
  if ( f == NULL ) return FALSE;

  while ( !feof(f) )
  {
	while ( (strcmp( buffer, "<object>") != 0) && (strcmp( buffer, "<object>\n") != 0 ) )
   {

	if ( feof( f ) ) return TRUE;
	fgets( (char*)buffer, 255, f );

   }

	vrTriObject2 *o = new vrTriObject2();
	if ( !o ) return FALSE;

   while ( strcmp( buffer, "</object>" ) != 0 )//читаем данные до конца тэга 
   {//--------------------------------------------------------------
	
		fgets( (char*)read, 255, f );
        sscanf( read, "%s %s", buffer, dummy );
		ToUpperCase( dummy );
		if ( strcmp( buffer, "file" ) == 0 ) if ( !o->Load ( dummy ) ) return FALSE;
		if ( strcmp( buffer, "skin" ) == 0 ) if ( !o->LoadSkin ( dummy ) ) return FALSE;



   }//--------------------------------------------------------------

	this->AddObject (o);
	iObjectCount++;

  }
e_log.WriteOut("[STATUS] %i Objects Loaded \n", iObjectCount );
 fclose(f);
return TRUE;
}