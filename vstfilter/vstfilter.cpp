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

AviutlFilter::FILTER_DLL	*filter1;
fVSTHostFilter	*oVSTFilter;

void hoge(void)
{
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
	oVSTFilter = new fVSTHostFilter(TEXT("Filter1"));

	filter1 = oVSTFilter->getFilterStruct();


	delete oVSTFilter;
}


