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

#pragma once
 #ifndef __BORLANDC__
#include "D3dx8math.h"

class vrMatrix4DX :public D3DXMATRIX
{
/*
public:
	vrMatrix4DX( FLOAT _11, FLOAT _12, FLOAT _13, FLOAT _14,
                FLOAT _21, FLOAT _22, FLOAT _23, FLOAT _24,
                FLOAT _31, FLOAT _32, FLOAT _33, FLOAT _34,
                FLOAT _41, FLOAT _42, FLOAT _43, FLOAT _44 );

	vrMatrix4DX( const vrMatrix4DX &m );
	vrMatrix4DX() {};

	FLOAT Determinant(){ return D3DXMatrixfDeterminant( &mat ); };
	void  Identity() { D3DXMatrixIdentity( &mat ); };//немного неуверен
	void  Multiply( vrMatrix4DX m );


// access grants
    FLOAT& operator () ( UINT Row, UINT Col );
	FLOAT	operator () ( UINT Row, UINT Col ) const;

	void operator *= ( CONST vrMatrix4DX& m);


private:
	D3DXMATRIX	mat;
*/

};

#endif