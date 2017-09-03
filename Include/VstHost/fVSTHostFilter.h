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
	 *	@brief	���ʗp�̏�����������R���X�g���N�^
	 */
	fVSTHostFilter(TCHAR *name)
		: fFilterInfo(name), mFilterData(new AviutlFilter::FILTER_DLL())
	{
		// ����Q�Ǝ��ɃC���X�^���X�𐶐�����
		mFilterData->name = getFilterName();



	};

	/**
	 *	@brief	�f�X�g���N�^
	 */
	~fVSTHostFilter()
	{
		Release();
	};

	// �C���X�^���X���Ƃɕێ�����f�[�^��Ԃ�������
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
