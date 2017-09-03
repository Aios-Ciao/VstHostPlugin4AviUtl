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
 *	@brief	�t�B���^���I/F
 * 
 */
class fFilterInfo
{
	TCHAR	mFilterName;

public:
	/**
	 *	@brief	�R���X�g���N�^
	 *	@param	_FilterName	�t�B���^��
	 */
	fFilterInfo(TCHAR *_FilterName)
	{
		mFilterName = *_FilterName;
	};

	/**
	 *	@brief	�t�B���^�\���̂�Ԃ�
	 */
	virtual AviutlFilter::FILTER_DLL *getFilterStruct(void) = 0;

	/**
	 *	@brief	�t�B���^����Ԃ�
	 */
	TCHAR *getFilterName()
	{
		return (&mFilterName);
	};


	// ���ƕK�v�Ȃ��̂��擾����C���^�t�F�[�X���`
};


#endif // ___fFILTERBASE_H___

