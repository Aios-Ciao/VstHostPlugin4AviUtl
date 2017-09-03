/*!
\file   fTrackBar.h
\brief  Factory of Trackbar
Copyright (c) 2017 aios-ciao
All rights reserved.<BR>
\b License AviUtlPluginSDK License<BR>
\b Create 2017/06/22
\author  aios-ciao

$Revision$
$Date$
*/

#ifndef ___FTRACKBAR_H___
#define ___FTRACKBAR_H___

#include "common/AviutlFilter.h"
#include <string>
#include <vector>
#include <Windows.h>

using tstring = std::basic_string<TCHAR>;

class oTrackBar
{
	tstring	m_name;
	int		m_defval;
	int		m_start;
	int		m_end;
public:
	oTrackBar(TCHAR *name, int start = 0, int end = 0, int defval = -1)
		: m_name(name), m_start(start), m_end(end), m_defval(defval) {};

	void getName(TCHAR **dest) {
		tstring::size_type	len = m_name.size();
		*dest = new TCHAR[len];
		wcscpy_s(*dest, len, m_name.c_str());
	};
	int getDefault() { return(this->m_defval); };
	int getStart() { return(this->m_start); };
	int getEnd() { return(this->m_end); };
};

class TrackBar : public std::vector<oTrackBar>
{
public:
	TrackBar() {};
	virtual ~TrackBar() {};

	static void _relmemory(
		int size,
		TCHAR **&namelist,
		int *&defval_ary,
		int *&start_ary,
		int *&end_ary
	) {
		delete[] defval_ary;
		delete[] start_ary;
		delete[] end_ary;

		for (int idx = 0; idx < size; ++idx)
		{
			delete[] namelist[idx];
		}
		delete[] namelist;
	};

	static void AssignStorage(
		TrackBar &source,
		TCHAR **&namelist,
		int *&defval_ary,
		int *&start_ary,
		int *&end_ary
	) {
		TrackBar::size_type	len = source.size();

		namelist = new TCHAR *[len];
		defval_ary = new int[len];
		start_ary = new int[len];
		end_ary = new int[len];

		/* データを転記 */
		{
			int id(0);
			for (TrackBar::iterator it = source.begin(); it != source.end(); ++it) {
				TCHAR *pName = namelist[id];
				it->getName(&pName);
				defval_ary[id] = it->getDefault();
				start_ary[id] = it->getStart();
				end_ary[id] = it->getEnd();
			}
		}
	};

	static void ReleaseStorage(
		TrackBar &source,
		TCHAR **&namelist,
		int *&defval_ary,
		int *&start_ary,
		int *&end_ary
	)
	{
		_relmemory(source.size(),
			namelist, defval_ary, start_ary, end_ary);
	};

};



#endif // !___FTRACKBAR_H___

