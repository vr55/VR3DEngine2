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

#include "vrRandom.h"

#define RANDOM_NUM (static_cast<float>(rand())/static_cast<float>(RAND_MAX))

//==============================================================//
//																//
//==============================================================//

vrRandom::vrRandom()
{

lastRandomNumber = 0xA2A9;

}


//==============================================================//
//																//
//==============================================================//
void vrRandom::Randomize( void )
{

UINT cnt;

	cnt = clock();
	cnt &= 0xFFFF;

	while(cnt--)
	{
		lastRandomNumber = lastRandomNumber * 65539 + 3;
		lastRandomNumber = lastRandomNumber * 1009 + 7;
	}




}

//==============================================================//
//																//
//==============================================================//
UINT vrRandom::Rand( UINT max )
{

UINT a;

	lastRandomNumber = lastRandomNumber * 65539 + 3;

	a = lastRandomNumber>>16;

return a%max;


}
//==============================================================//
//																//
//==============================================================//
float vrRandom::Rand( float min, float max )
{
return  min + (max - min) * RANDOM_NUM;


}
