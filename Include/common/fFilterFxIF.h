/**
 *	@file   fFilterFxIF.h
 *	@brief  Function interface class
 *			Copyright (c) 2017 aios-ciao
 *			All rights reserved.<BR>
 *			License AviUtlPluginSDK License<BR>
 *	@date	2017/09/5
 *	@author	aios-ciao
 *
	$Revision$
	$Date$
*/
#ifndef ___fFILTERFXIF_H___
#define ___fFILTERFXIF_H___
#include <Windows.h>
#include "AviutlFilter.h"

/**
 *		@class	fFilterFxIF
 *		@brief	フィルタ関数インタフェースクラス
 *
 *		このクラスをベースに必要なフィルタクラスを派生する。
 *		メンバ関数として記載されている関数は同名でメソッド定義する必要がある。
 */
class fFilterFxIF
{
public:
	virtual	BOOL	func_proc( AviutlFilter::FILTER *fp, AviutlFilter::FILTER_PROC_INFO *fpip) {};
	virtual BOOL	func_init(AviutlFilter::FILTER *fp) {};
	virtual BOOL	func_exit(AviutlFilter::FILTER *fp) {};
	virtual BOOL	func_update(AviutlFilter::FILTER *fp, int status) {};
	virtual BOOL	func_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, AviutlFilter::FILTER *f) {};
	virtual BOOL	func_save_start(AviutlFilter::FILTER *fp, int s, int e, void *editp) {};
	virtual BOOL	func_save_end(AviutlFilter::FILTER *fp, void *editp) {};
	virtual BOOL	func_is_saveframe(AviutlFilter::FILTER *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter) {};
	virtual BOOL	func_project_load(AviutlFilter::FILTER *fp, void *editp, void *data, int size) {};
	virtual BOOL	func_project_save(AviutlFilter::FILTER *fp, void *editp, void *data, int *size) {};
	virtual BOOL	func_modify_title(AviutlFilter::FILTER *fp, void *editp, int frame, LPSTR title, int max_title) {};
};

#endif /* ___fFILTERFXIF_H___ */
