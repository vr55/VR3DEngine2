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

BOOL vrResourceManager::LoadMaterials( LPSTR strFileName )
{
 char	buffer[255];
 char	dummy[255];
 char   read[255];

 char	vs[255];
 char	fs[255];
 

 int    iCurLayer = 0;
 int	iMatCount = 0;

 memset(  buffer, 0, 255 );
 memset( vs, 0, sizeof (vs) );
 memset( fs, 0, sizeof (fs) );

 e_log.WriteOut("[STATUS] Parsing Resources from File %s \n", strFileName );

  FILE *f = fopen( strFileName, "rt" );
  if ( f == NULL ) return FALSE;

  while ( !feof(f) )
  {

   while ( (strcmp( buffer, "<material>") != 0) && (strcmp( buffer, "<material>\n") != 0 ) )
   {
		if ( feof( f ) ) return TRUE;
		fgets( (char*)buffer, 255, f );

   }

   vrMaterial2	*m = new vrMaterial2();
   if ( !m ) return FALSE;

   while ( strcmp( buffer, "</material>" ) != 0 )//читаем данные до конца тэга 
   {//--------------------------------------------------------------
		fgets( (char*)read, 255, f );
        sscanf( read, "%s %s", buffer, dummy );
		ToUpperCase( dummy );
        if ( strcmp( buffer, "name" ) == 0 ) strcpy( &m->cName[0], dummy );
		else if ( strcmp(buffer, "fs") == 0 ) strcpy( &fs[0], dummy );
		else if ( strcmp(buffer, "vs") == 0 ) strcpy( &vs[0], dummy );
		else if (strcmp( buffer, "layer" ) == 0 )
		{
			m->tLayers[iCurLayer] = GetTexture( dummy );
			iCurLayer++;

		}


   }//--------------------------------------------------------------
	if ( vs[0] != 0x00 ) m->LoadShader( vs, fs );

	m->iNumLayers = iCurLayer - 1;
	e_log.WriteOut("[STATUS] Creating Material: %s \n", m->cName );

	AddMaterial( m );
	iCurLayer = 0;
	iMatCount++;


  }



e_log.WriteOut("%i Materials Created \n", iMatCount );
fclose(f);
return TRUE;
}