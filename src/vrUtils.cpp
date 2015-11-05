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
#include "vrUtils.h"


#define MAX_STRING_LENGHT	255

//==============================================================//
//																//
//==============================================================//

void ToUpperCase( LPSTR strString )
{
 #ifdef __BORLANDC__
      char *copy = std::strupr(  std::strdup(strString)  );
 #else
      char *copy = _strupr(  _strdup(strString)  );
	  
	  //strString = _strupr( strString );
 #endif


	strcpy( strString, copy ); 
//	memcpy( strString, copy, strlen( copy ) +1 );

return;
}


//==============================================================//
//																//
//==============================================================//

void ExtractFilenameFromPath( LPSTR strString )
{


int len = strlen( strString );
int j = len;
char i = 0;

while( ( i != 0x2f ) && ( len >= 0 ) )		// ищем в строке символ "/" начиная с конца
{

	i = (char)strString[len];
	len--;

}

if ( len == -1 ) return;		//len = -1 если символ "/" ненайден
len++;
j -= abs(len);					//j = длина имени файла

for ( int a=0; a<j; a++ )
{
	len++;
	i = (char)strString[len];
	strString[a] = i;

}


//strncpy( strString, &strString[len], j );
}

//==============================================================//
//																//
//==============================================================//

bool PointInCube( vrVector3 vPoint, vrVector3 fCubeCenter, float fCubeWidth )
{
	vrVector3	cube[8];
//	vrVector3D	tri[3];
	float halfWidth = fCubeWidth / 2;
//найдем координаты вершин куба

for ( int i=0; i<8; i++ )
{
	cube[i] = fCubeCenter;
}

//-------первая вершина
cube[0].x = cube[0].x - halfWidth;
cube[0].y = cube[0].y + halfWidth;
cube[0].z = cube[0].z - halfWidth;
//---------------------
//-------вторая вершина
cube[1].x = cube[1].x - halfWidth;
cube[1].y = cube[1].y + halfWidth;
cube[1].z = cube[1].z + halfWidth;
//---------------------
//-------третья вершина
cube[2].x = cube[2].x + halfWidth;
cube[2].y = cube[2].y + halfWidth;
cube[2].z = cube[2].z + halfWidth;
//---------------------
//-------четвертая вершина
cube[3].x = cube[3].x + halfWidth;
cube[3].y = cube[3].y + halfWidth;
cube[3].z = cube[3].z - halfWidth;
//------------------------
//-------пятая вершина
cube[4].x = cube[4].x - halfWidth;
cube[4].y = cube[4].y - halfWidth;
cube[4].z = cube[4].z - halfWidth;
//--------------------
//-------шестая вершина
cube[5].x = cube[5].x - halfWidth;
cube[5].y = cube[5].y - halfWidth;
cube[5].z = cube[5].z + halfWidth;
//---------------------
//-------седьмая вершина
cube[6].x = cube[6].x + halfWidth;
cube[6].y = cube[6].y - halfWidth;
cube[6].z = cube[6].z + halfWidth;
//----------------------
//-------восьмая вершина
cube[7].x = cube[7].x + halfWidth;
cube[7].y = cube[7].y - halfWidth;
cube[7].z = cube[7].z - halfWidth;
//----------------------
 
if ( ( abs(vPoint.x) >= cube[0].x ) && ( abs(vPoint.x) <= cube[3].x ) )
{
	if ( (abs(vPoint.y) >= cube[7].y ) && ( abs(vPoint.y) <= cube[3].y ) )
	{
		if ( ( abs(vPoint.z) >= cube[4].z ) && ( abs(vPoint.z) <= cube[5].z ) )
		{
			return true;
		}
	}
}



return false;
}


