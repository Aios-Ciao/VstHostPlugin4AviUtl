/*!
\file   fFilterBase.h
\brief  Creator of filter instance
Copyright (c) 2017 aios-ciao
All rights reserved.<BR>
\b License AviUtlPluginSDK License<BR>
\b Create 2017/09/3
\author  aios-ciao

$Revision$
$Date$
*/
#ifndef ___fFILTERBASE_H___
#define ___fFILTERBASE_H___
#include "AviutlFilter.h"

/**
 *	@class	fFilterInfo
 *	@brief	フィルタ情報I/F
 * 
 */
class fFilterInfo
{
	TCHAR	mFilterName;

public:
	/**
	 *	@brief	コンストラクタ
	 *	@param	_FilterName	フィルタ名
	 */
	fFilterInfo(TCHAR *_FilterName)
	{
		mFilterName = *_FilterName;
	};

	/**
	 *	@brief	フィルタ構造体を返す
	 */
	virtual AviutlFilter::FILTER_DLL *getFilterStruct(void) = 0;

	/**
	 *	@brief	フィルタ名を返す
	 */
	TCHAR *getFilterName()
	{
		return (&mFilterName);
	};


	// あと必要なものを取得するインタフェースを定義
};


#endif // ___fFILTERBASE_H___

