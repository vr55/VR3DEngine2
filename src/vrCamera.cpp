#include "vrCamera.h"
#include "vrConsole.h"

#pragma warning ( disable : 4244 )
#define pi	3.1415926f

//==============================================================//
//																//
//==============================================================//

vrCamera::vrCamera()
{

	this->Position.x	= 113.0f;
	this->Position.y	= 1.5f;
	this->Position.z	= 6.0f;

	this->Roll			= 0.0f;
	this->Pitch			= 0.0f;
	this->Yaw			= 0.0f;

	this->sensitivity	= 25.0f;


	this->Speed			= 400.0f;
	this->Znear			= 0.1f;
	this->Zfar			= 3000.0f;
	this->Fov			= 90.0;

	bActive				= true;

	uiViewPort[0]		= 0;
	uiViewPort[1]		= 0;
	uiViewPort[2]		= engine.uiScreenWidth;
	uiViewPort[3]		= engine.uiScreenHeight;

	bSmoothCamera		= true;

	f_radius			= 30;

	strcpy( cName, "Default" );


}

//==============================================================//
//																//
//==============================================================//

vrCamera::vrCamera( unsigned int x, unsigned int y, unsigned int width, unsigned int height )
{
  

	this->Position.x	= 10.0f;
	this->Position.y	= 1.5f;
	this->Position.z	= 6.0f;

	this->Roll			= 0.0f;
	this->Pitch			= 0.0f;
	this->Yaw			= 0.0f;

	this->sensitivity	= 5.0f;


	this->Speed			= 5.3f;
	this->Znear			= 0.1f;
	this->Zfar			= 3000.0f;
	this->Fov			= 45.0;

	bActive				= true;

	uiViewPort[0]		= x;
	uiViewPort[1]		= y;
	uiViewPort[2]		= width;
	uiViewPort[3]		= height;

	strcpy( cName, "Default" );

}
//==============================================================//
//	устанавливает текущую позицию камеры						//
//==============================================================//
/*public*/void vrCamera::SetPosition( vrVector3 newposition )
{
	this->Position = newposition;
}


//==============================================================//
//																//
//==============================================================//
/*public*/void vrCamera::SetPosition( float x, float y, float z )
{
	this->Position.x = x;
	this->Position.y = y;
	this->Position.z = z;

}

//==============================================================//
//																//
//==============================================================//
/*private*/void vrCamera::Move( float amount )
{
if ( bActive )
{
	vrVector3	MoveVector;

	this->GetDirection();

	MoveVector = ( Direction * -amount * Speed ) ;

	this->Position = this->Position + MoveVector;
}
}


//==============================================================//
//																//
//==============================================================//
/*public*/void vrCamera::Update()
{
	if ( console.iStatus == VR_CONSOLE_INVISIBLE ) bActive = TRUE; else bActive = FALSE;

	glViewport( uiViewPort[0], uiViewPort[1], uiViewPort[2],uiViewPort[3] );

      glRotatef( -this->Pitch, 1.0, 0.0, 0.0);			//Pitch
      glRotatef( -this->Yaw, 0.0, 1.0, 0.0);			//Yaw
      glRotatef( -this->Roll, 0.0, 0.0, 1.0);			//Roll
      glTranslatef( -this->Position.x, -this->Position.y, -this->Position.z );


}


//==============================================================//
//																//
//==============================================================//
/*private*/void vrCamera::Strafe( float amount )
{
if ( bActive )
{
	vrVector3	MoveVector;
	this->GetDirection();

	MoveVector.z = -Direction.x * -amount * this->Speed;
	MoveVector.y = 0.0;
	MoveVector.x = Direction.z * -amount * this->Speed;

	this->Position = this->Position + MoveVector;
}
}

//==============================================================//
//																//
//==============================================================//
/*private*/void vrCamera::GetDirection()
{

vrVector3		Step1, Step2;

	Step1.x = (float)cos( ( this->Yaw + 90 ) * pi / 180 );
	Step1.z = (float)-sin( ( this->Yaw + 90 ) * pi / 180 );

	Step2.x = Step1.x * cos( this->Pitch * pi / 180 );
	Step2.z = Step1.z * cos( this->Pitch * pi / 180 );
	Step2.y = sin( this->Pitch * pi / 180 );

	this->Direction = Step2;



}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetFov( float fov )
{
	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();

	this->Fov = fov;

	gluPerspective( fov, this->Aspect, this->Znear, this->Zfar );

	glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
	glLoadIdentity();

}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetZFar( float zfar )
{

	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();


	gluPerspective( this->Fov, this->Aspect, this->Znear, zfar );

	glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
	glLoadIdentity();

	this->Zfar = zfar;
}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetZNear( float znear )
{

	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();


	gluPerspective( this->Fov, this->Aspect, znear, this->Zfar );

	glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
	glLoadIdentity();

	this->Znear = znear;
}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetAspect( float aspect )
{
	if ( !this ) return;

	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();

	gluPerspective( this->Fov, aspect, this->Znear, this->Zfar );

	glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
	glLoadIdentity();

	uiViewPort[2] = engine.uiScreenWidth;
	uiViewPort[3] = engine.uiScreenHeight;
	this->Aspect = aspect;
}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetSensitivity( float sens )
{
	this->sensitivity = sens;
}


//==============================================================//
//																//
//==============================================================//

vrCamera::~vrCamera()
{


}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetPitch( float pitch )
{
	this->Pitch = pitch;
}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetRoll(float roll)
{
	this->Roll = roll;
}


//==============================================================//
//																//
//==============================================================//

/*public*/void vrCamera::SetYaw(float yaw)
{
	this->Yaw = yaw;
}

//==============================================================//
//																//
//==============================================================//
void vrCamera::RotateX( float amount )
{
if ( bActive ) this->Pitch += amount * sensitivity;

}

//==============================================================//
//																//
//==============================================================//
void vrCamera::RotateY( float amount )
{
if ( bActive ) this->Yaw += amount * sensitivity;

}

//==============================================================//
//																//
//==============================================================//
void vrCamera::RotateZ( float amount )
{
if ( bActive ) this->Roll += amount * sensitivity;

}


//==============================================================//
//																//
//==============================================================//

void vrCamera::Rotate( float pitch, float yaw, float roll )
{


vrMatrix4 rotm;
rotm.LoadIdentity();

float spitch = (float)sin( pitch );
float cpitch = (float)cos( pitch );

float sroll = (float)sin( roll );
float croll = (float)cos( roll );

float syaw = (float)sin( yaw );
float cyaw = (float)cos( yaw );


rotm.m[0] = cyaw * sroll + syaw*spitch*sroll;
rotm.m[1] = spitch * sroll;
rotm.m[2] = -syaw * croll + cyaw*spitch*sroll;
rotm.m[3] = -( Position.x * rotm.m[0] + Position.y * rotm.m[1] + Position.z * rotm.m[2] );

rotm.m[4] = -cyaw*sroll + syaw*spitch*croll;
rotm.m[5] = cpitch*croll;
rotm.m[6] = syaw*sroll + cyaw*spitch*croll;
rotm.m[7] = -( Position.x * rotm.m[4] + Position.y * rotm.m[5] + Position.z * rotm.m[6] );

rotm.m[8] = syaw*cpitch;
rotm.m[9] = -spitch;
rotm.m[10] = cyaw*cpitch;
rotm.m[11] = -( Position.x * rotm.m[8] + Position.y * rotm.m[9] + Position.z * rotm.m[10] );




glMultMatrixf( &rotm.m[0] );


}

//==============================================================//
//																//
//==============================================================//
void vrCamera::ApplyChanges()
{
	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();

	gluPerspective( this->Fov, this->Aspect, this->Znear, this->Zfar );


	glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
	glLoadIdentity();

	glFogf(GL_FOG_START, world.camera->GetZNear());
	glFogf(GL_FOG_END, world.camera->GetZFar()-200 );



}

