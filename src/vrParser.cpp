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
#include "vrParser.h"

//==============================================================//
//																//
//==============================================================//
vrParser::vrParser()
{

f			= NULL;
tempf		= NULL;


//code = new CODE();

}

//==============================================================//
//																//
//==============================================================//


/*private*/bool vrParser::CleanFile( LPSTR strFileName )
{
int pos;


if ( ( f = fopen( strFileName, "rt" ) ) == NULL ) return false;
//создаем временный файл
//================================================================
if ( (tempf = fopen( "temp.vr3d", "w+" ) ) == NULL ) return false;
char line[255];
while ( !feof( f ) )
{
	fgets( line, 255, f );
	
	if ( strstr( line, "//" ) != NULL )		//удал€ем коментарии
{
	pos = strcspn( line, "//" );
	if ( pos == 0 ) line[pos] = 0x00;
	else
	{
	line[pos] = 0x0a;
	line[pos+1] = 0x00;
	}


}

	ToUpperCase( line );

	fputs( line, tempf );


}
Compile();
//fclose( tempf );//!!!!!!!!!!!!!!!!!!!!!!!!!!!файл оставл€ем открытым
//================================================================
fclose( f ); 
return true;

}

//==============================================================//
//																//
//==============================================================//


/*private*/void vrParser::CleanString( LPSTR str )
{

if ( str != NULL )
{
	char	ln[255];
	char	a = 0x01;
	int		pos;
	int		index = 0;

if ( ( pos = strcspn( str, "//" )) != 0 )
{
	for ( int i=0; i<= pos-1; i++ ) ln[i] = str[i];
	ln[pos] = 0x00;

//str[pos] = 0x0a0d;


}
str = &ln[0];
}

}

//==============================================================//
//																//
//==============================================================//

/*private*/void vrParser::Compile()
{

char	line[255];

LPSTR tags[] = { "<WORLD>",
				"</WORLD>",
				"<MATERIAL>",
				"</MATERIAL>",
				"<DIFFUSEMAP>",
				"</DIFFUSEMAP>",
				"<DETAILMAP>",
				"</DETAILMAP>",
				"<BUMPMAP>",
				"</BUMPMAP>",
				"<OBJECT>",
				"</OBJECT>",
				"<MESH>",
				"</MESH>",
				"<TEXTURE>",
				"</TEXTURE>",
				"<GEOMETRY>",
				"</GEOMETRY>",
				"<CAMERA>",
				"</CAMERA>"

};

LPSTR params[] = { "NAME",
					"AMBIENT",
					"DIFFUSE",
					"SPECULAR",
					"EMISSION",
					"SHININESS",
					"SCALE",
					"ROTATE",
					"TRANSLATE",
					"FILE",
					"MATERIAL",
					"FOV",
					"SPEED",
					"SENSITIVITY"


};

char	dummy[255];
float	f1;
float	f2;
float	f3;

//ml->insert( ml->end(), material );
rewind( tempf );

while( !feof( tempf ) )
{

fgets( line, 255, tempf );
//предполагаем, что синтаксис и правописание уже проверено
for ( int i=0; i<sizeof( tags )/sizeof( LPSTR ); i++ )
{

	if ( strstr( line, tags[i] ) != NULL )	//сравниваем полученную строку с известными тэгами
	{
		op *oper = new op;
		oper->opcode = i;
		oper->strParam = NULL;
//		oper->vParam = NULL;
		oper->fParam = 0.0f;

		code->insert( code->end(), oper );
		break;

	}

}


for ( i=0; i<sizeof( params )/sizeof( LPSTR ); i++ )
{

	if ( strstr( line, params[i] ) != NULL )//сравниваем полученную строку с известными параметрами	
	{
		op *oper = new op;
		oper->opcode = i + sizeof( tags )/sizeof( LPSTR );

		switch( oper->opcode )
		{
		case PARAM_FILE:
		case PARAM_NAME:
		case PARAM_MATERIAL:

			{
			char	*str = new char[32];
			sscanf( line, "%s %s", dummy, str );
			oper->strParam = str;
			break;
			}
			
		case PARAM_AMBIENT:
//			break;
		case PARAM_DIFFUSE:
//			break;
		case PARAM_SPECULAR:
//			break;
		case PARAM_EMISSION:
//			break;
		case PARAM_SCALE:
//			break;
		case PARAM_ROTATE:
//			break;
		case PARAM_TRANSLATE:
			{
			sscanf( line, "%s %f %f %f", dummy, &f1, &f2, &f3 );
			oper->vParam.x = f1;
			oper->vParam.y = f2;
			oper->vParam.z = f3;

			break;
			}
		case PARAM_SHININESS:
		case PARAM_FOV:
		case PARAM_SPEED:
		case PARAM_SENSITIVITY:
			{
			sscanf( line, "%s %f", dummy, &f1 );
			oper->fParam = f1;
			break;
			}


		}



		code->insert( code->end(), oper );
		break;

	}
}



}



fclose( tempf );

}


//==============================================================//
//																//
//==============================================================//

/*public*/bool vrParser::CompileFile( LPSTR strFileName, CODE* code )
{
if ( ( !strFileName ) || ( !code ) ) return false;
	this->code = code;

	return CleanFile( strFileName );



}