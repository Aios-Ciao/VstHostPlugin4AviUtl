/*!
\file   fVSTHostFilter.h
\brief  Filter class deriverd for VST Host Filter
Copyright (c) 2017 aios-ciao
All rights reserved.<BR>
\b License AviUtlPluginSDK License<BR>
\b Create 2017/09/3
\author  aios-ciao

$Revision$
$Date$
*/
#ifndef ___fVSTHostFilter_H___
#define ___fVSTHostFilter_H___
#include "common/fFilterBase.h"
#include "common/fCommon.h"

class fVSTHostFilter : public fFilterInfo
{
	AviutlFilter::FILTER_DLL *mFilterData = nullptr;

public:

	/**
	 *	@brief	識別用の情報を持たせるコンストラクタ
	 */
	fVSTHostFilter(TCHAR *name)
		: fFilterInfo(name), mFilterData(new AviutlFilter::FILTER_DLL())
	{
		// 初回参照時にインスタンスを生成する
		mFilterData->name = getFilterName();



	};

	/**
	 *	@brief	デストラクタ
	 */
	~fVSTHostFilter()
	{
		Release();
	};

	// インスタンスごとに保持するデータを返す感じで
	AviutlFilter::FILTER_DLL *getFilterStruct()
	{

		return (mFilterData);
	};


	void Release()
	{
		delete mFilterData;
	};
};

#endif // ___fVSTHostFilter_H___
