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
#include "vrMatrixDX.h"



//==============================================================//
//																//
//==============================================================//
/*
vrMatrix4DX::vrMatrix4DX( FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
                FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
                FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
                FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 )


{

D3DXMATRIX m( _11, _12, _13,  _14, 
			 _21,  _22,  _23,  _24, 
			 _31,  _32,  _33,  _34,
			 _41,  _42,  _43,  _44 );

mat = m;



}


//==============================================================//
//																//
//==============================================================//
vrMatrix4DX::vrMatrix4DX( const vrMatrix4DX &m )
{

D3DXMATRIX mt( m.mat );
mat = mt;

}

//==============================================================//
//																//
//==============================================================//
FLOAT vrMatrix4DX::operator () ( UINT Row, UINT Col ) const
{

return mat( Row, Col );

}
//==============================================================//
//																//
//==============================================================//
FLOAT& vrMatrix4DX::operator () ( UINT Row, UINT Col )
{

return mat( Row, Col );

}

//==============================================================//
//																//
//==============================================================//
void vrMatrix4DX::Multiply( vrMatrix4DX m )
{
D3DXMATRIX out;

D3DXMatrixMultiply( &out, &mat,  &m.mat );

mat = out;


}


//==============================================================//
//																//
//==============================================================//

void vrMatrix4DX::operator *= ( CONST vrMatrix4DX& m)
{

	 mat *= m.mat;

}

*/