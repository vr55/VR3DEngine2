#include "vrInclude.h"
#include "vrTimer.h"



//==============================================================//
//																//
//==============================================================//

/*constructor*/vrTimer::vrTimer()
{
	QueryPerformanceCounter( (LARGE_INTEGER*)&before );


}


//==============================================================//
//																//
//==============================================================//
/*public*/float vrTimer::GetCount()
{
	__int64	temp1;
	
	QueryPerformanceCounter( (LARGE_INTEGER*)&after ) ;
	QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );

	temp1 = after - before;
	temp1 /= 0.001;


	float out;
	out = temp1 / freq;
//	QueryPerformanceCounter( (LARGE_INTEGER*)&before );


	return out;

}


//==============================================================//
//																//
//==============================================================//
/*public*/void vrTimer::Reset()
{

	QueryPerformanceCounter( (LARGE_INTEGER*)&before );

}
