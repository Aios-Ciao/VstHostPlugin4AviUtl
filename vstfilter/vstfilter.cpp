#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
//#include <Windows.h>
//#include <tchar.h>

//#include "filter.h"
//#include "fTrackBar.h"
#include "pluginterfaces/vst2.x/aeffectx.h"
#include "common/fFilterBase.h"
#include "VstHost/fVSTHostFilter.h"

//static TrackBar	*tracks;

//AviutlFilter::FILTER_DLL	oTestFilter1;

AviutlFilter::FILTER_DLL	**pFilterTable;
fVSTHostFilter	*oVSTFilter1;
fVSTHostFilter	*oVSTFilter2;


//void hoge(void)
//{
#if 0
	tracks = new TrackBar();

	tracks->push_back(oTrackBar(_T("Test1"), 50, 0, 100));
	tracks->push_back(oTrackBar(_T("Test2"), 30, 10, 50));

	tracks->AssignStorage(
		*tracks,
		oTestFilter1.track_name,
		oTestFilter1.track_default,
		oTestFilter1.track_s,
		oTestFilter1.track_e
		);

	tracks->ReleaseStorage(
		*tracks,
		oTestFilter1.track_name,
		oTestFilter1.track_default,
		oTestFilter1.track_s,
		oTestFilter1.track_e
	);
	delete tracks;

#endif
//	oVSTFilter = new fVSTHostFilter(TEXT("Filter1"));

//	filter1 = oVSTFilter->getFilterStruct();


//	delete oVSTFilter;
//}


/* フィルタ情報を渡す */

//#ifndef MULTI_FILTER
//EXTERN_C __declspec(dllexport) AviutlFilter::FILTER_DLL* __stdcall GetFilterTable(void)
//{
//}
//#else
//FILTER_DLL* filter_list[] = { &filter, /*+ 追加フィルター */ NULL };
EXTERN_C __declspec(dllexport)  AviutlFilter::FILTER_DLL** __stdcall GetFilterTableList(void)
{
	oVSTFilter1 = new fVSTHostFilter(TEXT("Filter1"));
	oVSTFilter2 = new fVSTHostFilter(TEXT("Filter2"));

	pFilterTable = new AviutlFilter::FILTER_DLL *[3];
	pFilterTable[0] = oVSTFilter1->getFilterStruct();
	pFilterTable[1] = oVSTFilter2->getFilterStruct();

	return pFilterTable;
}
//#endif

