/**
*	@file   fCallbackAdapter.h
*	@brief  Callback handler
*			Copyright (c) 2017 aios-ciao
*			All rights reserved.<BR>
*			License AviUtlPluginSDK License<BR>
*	@date	2017/09/5
*	@author	aios-ciao
*
$Revision$
$Date$
*/
#ifndef ___fCALLBACKADAPTER_H___
#define ___fCALLBACKADAPTER_H___
#include "AviutlFilter.h"
#include "fFilterFxIF.h"

class fCallbackAdapter
{
private:
	AviutlFilter::FILTER_DLL *filter_dll;
public:

	/** fCallbackAdapter
		@brief	コンストラクタ
	 */
	fCallbackAdapter( fFilterFxIF *_this )
		: filter_dll( new AviutlFilter::FILTER_DLL() )
	{
		filter_dll->func_proc = &this->onProc;
		filter_dll->func_exit = &this->onExit;
		filter_dll->func_init = &this->onInit;
		filter_dll->func_update = &this->onUpdate;
		filter_dll->func_WndProc = &this->onNotifyWndProc;
		filter_dll->func_is_saveframe = &this->isSaveframe;
		filter_dll->func_modify_title = &this->onModifyTitle;
		filter_dll->func_project_load = &this->onProjectLoad;
		filter_dll->func_project_save = &this->onProjectSave;
		filter_dll->func_save_start = &this->onSaveStart;
		filter_dll->func_save_end = &this->onSaveEnd;
		filter_dll->ex_data_ptr = _this;		// 直接ではなく拡張データの管理クラスを介して登録する
		filter_dll->ex_data_size = sizeof(fFilterFxIF *);

		/* その他のパラメータも登録する必要あり */
	};

	/**
	 *	@func	fCallbackAdapter
	 *	@brief	デストラクタ
	 */
	~fCallbackAdapter()
	{
		delete filter_dll;
	};

	/**
	 *	@brief	フィルタDLL構造体の取得
	 *	@return	フィルタDLL構造体のポインタ
	 */
	AviutlFilter::FILTER_DLL *getFilterDll() { return(filter_dll); };

	static BOOL onProc(AviutlFilter::FILTER *fp, AviutlFilter::FILTER_PROC_INFO *fpip)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_proc(fp, fpip);
	};

	static BOOL	onInit(AviutlFilter::FILTER *fp)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_init(fp);
	};

	static BOOL	onExit(AviutlFilter::FILTER *fp)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_exit(fp);
	};

	static BOOL	onUpdate(AviutlFilter::FILTER *fp, int status)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_update(fp, status);
	};

	static BOOL	onNotifyWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, AviutlFilter::FILTER *fp)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_WndProc(hwnd, message, wparam, lparam, editp, fp);
	};

	static BOOL	onSaveStart(AviutlFilter::FILTER *fp, int s, int e, void *editp)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_save_start(fp, s, e, editp);
	};

	static BOOL	onSaveEnd(AviutlFilter::FILTER *fp, void *editp)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_save_end(fp, editp);
	};

	static BOOL	isSaveframe(AviutlFilter::FILTER *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_is_saveframe(fp, editp, saveno, frame, fps, edit_flag, inter);
	};

	static BOOL	onProjectLoad(AviutlFilter::FILTER *fp, void *editp, void *data, int size)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_project_load(fp, editp, data, size);
	};

	static BOOL	onProjectSave(AviutlFilter::FILTER *fp, void *editp, void *data, int *size)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_project_save(fp, editp, data, size);
	};

	static BOOL	onModifyTitle(AviutlFilter::FILTER *fp, void *editp, int frame, LPSTR title, int max_title)
	{
		fFilterFxIF	*obj = static_cast<fFilterFxIF *>(fp->ex_data_ptr);
		obj->func_modify_title(fp, editp, frame, title, max_title);
	};
};

#endif /* ___fCALLBACKADAPTER_H___ */
