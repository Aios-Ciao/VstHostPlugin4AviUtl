/*!
	\file   AviutlFilter.h
	\brief  Header for aviutl filter
			Copyright (c) 2017 aios-ciao
			All rights reserved.<BR>
	\b License AviUtlPluginSDK License<BR>
	\b Create 2017/05/10
	\author  aios-ciao

	$Revision$
	$Date$
*/
#ifndef ___AVIUTLFILTER_H___
#define ___AVIUTLFILTER_H___
#include <Windows.h>

namespace AviutlFilter
{

	struct PIXEL_YC
	{
		short y;							//	��f(�P�x    )�f�[�^ (     0 �` 4096 )
		short cb;							//	��f(�F��(��))�f�[�^ ( -2048 �` 2048 )
		short cr;							//	��f(�F��(��))�f�[�^ ( -2048 �` 2048 )

											//	��f�f�[�^�̒l�͔͈͊O�ɂȂ��Ă��邱�Ƃ�����B
											//	�܂��͈͓��Ɏ��߂Ȃ��Ă����܂�Ȃ��B
	};

	struct PIXEL
	{
		unsigned char b;					//	��f(RGB)�f�[�^ (0�`255)
		unsigned char g;
		unsigned char r;
	};


	struct FILTER_PROC_INFO
	{
		unsigned long		flags;			// �t�B���^�̃t���O
		static const unsigned long FLAG_INVERT_FIELD_ORDER = 0x00010000;	// �t�B�[���h�I�[�_�[��W���Ƌt�Ɉ��� ( �W���̓{�g��->�g�b�v )
		static const unsigned long FLAG_INVERT_INTERLACE = 0x00020000;	// �������@�𔽓]���� ( �C���^�[���[�X�����t�B���^�̂� )

		PIXEL_YC			*ycp_edit;		//	�摜�f�[�^�ւ̃|�C���^ ( ycp_edit��ycp_temp�͓���ւ��\ )
		PIXEL_YC			*ycp_temp;		//	�e���|�����̈�ւ̃|�C���^
		// ���C���^�[���[�X�����t�B���^������
		//		ycp_edit�ɂ͏����摜�f�[�^�������Ă��Ȃ��B
		//		ycp_edit, ycp_temp, frame_width,frmae_height�͕ύX�s�B

		int					frame_width;	//	���݂̉摜�̃T�C�Y ( �摜�T�C�Y�͕ύX�\ )
		int					frame_height;

		int					max_width;		//	�摜�̈�̃T�C�Y
		int					max_height;

		int					cur_framepos;	//	���݂̃t���[���ԍ�(�ԍ���0����)
		int					total_frame_n;	//	���t���[����

		int					org_width;		//	���̉摜�̃T�C�Y ( �I�[�f�B�I�t�B���^�̎��̂� )
		int					org_height;

		short				*audiobuffer;	//	�I�[�f�B�I�f�[�^�ւ̃|�C���^
											//	�I�[�f�B�I�`����PCM16bit ( 1�T���v���F mono = 2byte , stereo = 4byte )
		int					audio_samples;	//	�I�[�f�B�I�T���v���̑���
		int					audio_ch;		//	�I�[�f�B�I�`�����l����

		PIXEL				*pixels;		//	�g�p�񐄏�(�ߋ��Ƃ̌݊����̂���)

		void				*hEdit;			//	�G�f�B�b�g�n���h��

		int					yc_size;		//	�摜�̈�̉�f�̃o�C�g�T�C�Y
		int					stride_width;	//	�摜�̈�̕��̃o�C�g�T�C�Y
		int					reserved[8];	//	�g���p�ɗ\��
	};
//	const int ns = sizeof(FILTER_PROC_INFO);	// 104

	struct FRAME_STATUS
	{
		int					video_num;		//	���ۂ̉f���f�[�^�ԍ�
		int					audio_num;		//	���ۂ̉����f�[�^�ԍ�

		int					interlace_type;	//	�t���[���̃C���^�[���[�X����
		static const int	INTER_NORMAL = 0;			// �W��
		static const int	INTER_REVERSE = 1;			// ���]
		static const int	INTER_ODD = 2;				// �
		static const int	INTER_EVEN = 3;				// ����
		static const int	INTER_MIX = 4;				// ��d��
		static const int	INTER_AUTO = 5;				// ����

		int					idx24fps;		//	�g�p�񐄏�(�ߋ��Ƃ̌݊����̂���)

		int					profile_idx;	//	�t���[���̃v���t�@�C�����̔ԍ�
		int					vcm_cfgidx;		//	�t���[���̈��k�ݒ�̔ԍ�

		int					edit_flags;		//	�ҏW�t���O
		static const int	EDIT_FLAG_KEYFRAME = 0;		// �L�[�t���[��
		static const int	EDIT_FLAG_MARKFRAME = 1;	// �}�[�N�t���[��
		static const int	EDIT_FLAG_DELFRAME = 2;		// �D��Ԉ����t���[��
		static const int	EDIT_FLAG_NULLFRAME = 3;	// �R�s�[�t���[��

		int					reserved[9];	//	�g���p�ɗ\��
	};
//	const int fs = sizeof(FRAME_STATUS);	// 64

	struct FILE_INFO
	{
		unsigned long		flags;			//	�t�@�C���̃t���O
		static const unsigned long	FLAG_VIDEO = 1;				// �f�������݂���
		static const unsigned long	FLAG_AUDIO = 2;				// ���������݂���

		LPSTR				filename;		//	�t�@�C���� ( avi_file_open()�ł�NULL )

		int					width;			//	���̃T�C�Y
		int					height;

		int					framerate;		//	�t���[�����[�g
		int					video_scale;	//	�t���[���X�P�[��

		int					audio_rate;		//	�����T���v�����O���[�g
		int					audio_ch;		//	�����`�����l����

		int					frame_count;	//	���t���[����

		DWORD				video_decode_format;	//	�r�f�I�W�J�`��
		int					video_decode_bits;		//	�r�f�I�W�J�`���̃r�b�g��

		int					autio_samples;	//	�����̑��T���v���� ( avi_file_open()�̎��̂ݐݒ� )

		int					reserved[4];	//	�g���p�ɗ\��
	};
//	const int fi = sizeof(FILE_INFO);	// 64

	struct SYS_INFO
	{
		unsigned long		flags;			//	�V�X�e���t���O
		static const unsigned long	FLAG_EDIT = 1;			// �ҏW��
		static const unsigned long	FLAG_VFAPI = 2;			// VFAPI���쎞
		static const unsigned long	FLAG_USE_SSE = 4;		// SSE�g�p
		static const unsigned long	FLAG_USE_SSE2 = 8;		// SSE2�g�p

		LPSTR				verinfo;		//	�o�[�W�������

		int					filter_count;	//	�o�^����Ă�t�B���^�̐�

		int					min_width;		//	�ҏW�o����ŏ��摜�T�C�Y
		int					min_height;
		int					max_width;		//	�ҏW�o����ő�摜�T�C�Y
		int					max_height;
		int					max_framelen;	//	�ҏW�o����ő�t���[����

		LPSTR				edit_filename;	//	�ҏW�t�@�C���� (�t�@�C���������܂��Ă��Ȃ�����NULL)
		LPSTR				proj_filename;	//	�v���W�F�N�g�t�@�C���� (�t�@�C���������܂��Ă��Ȃ�����NULL)
		LPSTR				output_filename;//	�o�̓t�@�C���� (�t�@�C���������܂��Ă��Ȃ�����NULL)

		int					vram_width;		//	�ҏW�p�摜�̈�̃T�C�Y
		int					vram_height;

		int					vram_yc_size;	//	�ҏW�p�摜�̈�̉�f�̃o�C�g��
		int					vram_stride;	//	�ҏW�p�摜�̈�̕��̃o�C�g��

		HFONT				hfont;			//	�t�B���^�ݒ�E�B���h�E�Ŏg�p���Ă���t�H���g�̃n���h��
		int					buildinfo;		//	�r���h�ԍ� (�V�����o�[�W�����ɂȂ�قǑ傫�Ȓl)
		int					reserved[2];	//	�g���p�ɗ\��
	};
//	const int si = sizeof(SYS_INFO);	// 76

	//	�}���`�X���b�h�֐��p�̒�`
	using MULTI_THREAD_FUNC = void(*)(int thread_id, int thread_num, void *param1, void *param2);
//	typedef void(*MULTI_THREAD_FUNC)(int thread_id, int thread_num, void *param1, void *param2);
									//	thread_id	: �X���b�h�ԍ� ( 0 �` thread_num-1 )
									//	thread_num	: �X���b�h�� ( 1 �` )
									//	param1		: �ėp�p�����[�^
									//	param2		: �ėp�p�����[�^

	using AVI_FILE_HANDLE = void*;
	//	typedef void*	AVI_FILE_HANDLE;

	struct EXFUNC
	{
		void(*get_ycp_ofs)(void *editp, int n, int ofs);
		//	���o���邾��get_ycp_source_cache()�̕����g�p����悤�ɂ��Ă�������
		//	�w�肵���t���[����AVI�t�@�C����ł̃I�t�Z�b�g���ړ�����
		//	�t���[���̉摜�f�[�^�̃|�C���^���擾���܂�
		//	�f�[�^�̓t�B���^�O�̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//	ofs	 	: �t���[������̃I�t�Z�b�g
		//  �߂�l	: �摜�f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
		void		*(*get_ycp)(void *editp, int n);
		//	���o���邾��get_ycp_source_cache()�̕����g�p����悤�ɂ��Ă�������
		//	�w�肵���t���[���̉摜�f�[�^�̃|�C���^���擾���܂�
		//	�f�[�^�̓t�B���^�O�̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//  �߂�l	: �摜�f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
		void		*(*get_pixelp)(void *editp, int n);
		//	�w�肵���t���[����DIB�`��(RGB24bit)�̉摜�f�[�^�̃|�C���^���擾���܂�
		//	�f�[�^�̓t�B���^�O�̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n		: �t���[���ԍ�
		//  �߂�l	: DIB�`���f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
		int(*get_audio)(void *editp, int n, void *buf);
		//	�w�肵���t���[���̃I�[�f�B�I�f�[�^��ǂݍ��݂܂�
		//	�f�[�^�̓t�B���^�O�̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n		: �t���[���ԍ�
		//	buf 	: �i�[����o�b�t�@ (NULL�Ȃ�T���v�����̎擾�̂�)
		//  �߂�l	: �ǂݍ��񂾃T���v����
		BOOL(*is_editing)(void *editp);
		//	���ݕҏW�������ׂ܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  �߂�l	: TRUE�Ȃ�ҏW��
		BOOL(*is_saving)(void *editp);
		//	���ݕۑ��������ׂ܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  �߂�l	: TRUE�Ȃ�ۑ���
		int(*get_frame)(void *editp);
		//	���݂̕\���t���[�����擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  �߂�l	: ���݂̃t���[���ԍ�
		int(*get_frame_n)(void *editp);
		//	���t���[�������擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  �߂�l	: ���݂̑��t���[����
		BOOL(*get_frame_size)(void *editp, int *w, int *h);
		//	�t�B���^�O�̃t���[���̃T�C�Y���擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	w,h 	: �摜�T�C�Y�̊i�[�|�C���^
		//  �߂�l	: TRUE�Ȃ琬��
		int(*set_frame)(void *editp, int n);
		//	���݂̕\���t���[����ύX���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[���ԍ�
		//  �߂�l	: �ݒ肳�ꂽ�t���[���ԍ�
		int(*set_frame_n)(void *editp, int n);
		//	���t���[������ύX���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[����
		//  �߂�l	: �ݒ肳�ꂽ���t���[����
		BOOL(*copy_frame)(void *editp, int d, int s);
		//	�t���[���𑼂̃t���[���ɃR�s�[���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	d	 	: �R�s�[��t���[���ԍ�
		//	s	 	: �R�s�[���t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*copy_video)(void *editp, int d, int s);
		//	�t���[���̉f�������𑼂̃t���[���ɃR�s�[���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	d	 	: �R�s�[��t���[���ԍ�
		//	s	 	: �R�s�[���t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*copy_audio)(void *editp, int d, int s);
		//	�t���[���̉��������𑼂̃t���[���ɃR�s�[���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	d	 	: �R�s�[��t���[���ԍ�
		//	s	 	: �R�s�[���t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*copy_clip)(HWND hwnd, void *pixelp, int w, int h);
		//	�N���b�v�{�[�h��DIB�`��(RGB24bit)�̉摜���R�s�[���܂�
		//	hwnd 	: �E�B���h�E�n���h��
		//	pixelp	: DIB�`���f�[�^�ւ̃|�C���^
		//	w,h 	: �摜�T�C�Y
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*paste_clip)(HWND hwnd, void *editp, int n);
		//	�N���b�v�{�[�h����摜�𒣂���܂�
		//	hwnd 	: �E�B���h�E�n���h��
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*get_frame_status)(void *editp, int n, FRAME_STATUS *fsp);
		//	�t���[���̃X�e�[�^�X���擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[���ԍ�
		//  fps		: �t���[���X�e�[�^�X�ւ̃|�C���^
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*set_frame_status)(void *editp, int n, FRAME_STATUS *fsp);
		//	�t���[���̃X�e�[�^�X��ύX���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[���ԍ�
		//  fps		: �t���[���X�e�[�^�X�ւ̃|�C���^
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*is_saveframe)(void *editp, int n);
		//	���ۂɕۑ������t���[�������ׂ܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ�ۑ�����܂�
		BOOL(*is_keyframe)(void *editp, int n);
		//	�L�[�t���[�����ǂ������ׂ܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ�L�[�t���[��
		BOOL(*is_recompress)(void *editp, int n);
		//	�Ĉ��k���K�v�����ׂ܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ�Ĉ��k���K�v
		BOOL(*filter_window_update)(void *fp);
		//	�ݒ�E�B���h�E�̃g���b�N�o�[�ƃ`�F�b�N�{�b�N�X���ĕ`�悵�܂�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*is_filter_window_disp)(void *fp);
		//	�ݒ�E�B���h�E���\������Ă��邩���ׂ܂�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//  �߂�l	: TRUE�Ȃ�\������Ă���
		BOOL(*get_file_info)(void *editp, FILE_INFO *fip);
		//	�ҏW�t�@�C���̏����擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  fip		: �t�@�C���C���t�H���[�V�����\���̂ւ̃|�C���^
		//  �߂�l	: TRUE�Ȃ琬��
		LPSTR(*get_config_name)(void *editp, int n);
		//	���݂̃v���t�@�C���̖��O���擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �v���t�@�C�����̔ԍ�
		//  �߂�l	: �v���t�@�C���̖��O�ւ̃|�C���^ (NULL�Ȃ玸�s)
		BOOL(*is_filter_active)(void *fp);
		//	�t�B���^���L���ɂȂ��Ă��邩���ׂ܂�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//  �߂�l	: TRUE�Ȃ�t�B���^�L��
		BOOL(*get_pixel_filtered)(void *editp, int n, void *pixelp, int *w, int *h);
		//	�w�肵���t���[����DIB�`��(RGB24bit)�̉摜�f�[�^��ǂݍ��݂܂�
		//	�f�[�^�̓t�B���^��̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n		: �t���[���ԍ�
		//  pixelp	: DIB�`���f�[�^���i�[����|�C���^ (NULL�Ȃ�摜�T�C�Y������Ԃ��܂�)
		//	w,h		: �摜�̃T�C�Y (NULL�Ȃ�DIB�`���f�[�^������Ԃ��܂�)
		//  �߂�l	: TRUE�Ȃ琬��
		int(*get_audio_filtered)(void *editp, int n, void *buf);
		//	�w�肵���t���[���̃I�[�f�B�I�f�[�^��ǂݍ��݂܂�
		//	�f�[�^�̓t�B���^��̂��̂ł�
		//	editp* 	: �G�f�B�b�g�n���h��
		//	n		: �t���[���ԍ�
		//	buf 	: �i�[����o�b�t�@ (NULL�Ȃ�T���v�����̎擾�̂�)
		//  �߂�l	: �ǂݍ��񂾃T���v����
		BOOL(*get_select_frame)(void *editp, int *s, int *e);
		//	�I���J�n�I���t���[�����擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	s		: �I���J�n�t���[��
		//	e		: �I���I���t���[��
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*set_select_frame)(void *editp, int s, int e);
		//	�I���J�n�I���t���[����ݒ肵�܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	s		: �I���J�n�t���[��
		//	e		: �I���I���t���[��
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*rgb2yc)(PIXEL_YC *ycp, PIXEL *pixelp, int w);
		//	PIXEL����PIXEL_YC�ɕϊ����܂�
		//	ycp		: PIXEL_YC�\���̂ւ̃|�C���^
		//	pixelp 	: PIXEL�\���̂ւ̃|�C���^
		//	w		: �\���̂̐�
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*yc2rgb)(PIXEL *pixelp, PIXEL_YC *ycp, int w);
		//	PIXEL_YC����PIXEL�ɕϊ����܂�
		//	pixelp 	: PIXEL�\���̂ւ̃|�C���^
		//	ycp		: PIXEL_YC�\���̂ւ̃|�C���^
		//	w		: �\���̂̐�
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*dlg_get_load_name)(LPSTR name, LPSTR filter, LPSTR def);
		//	�t�@�C���_�C�A���O���g���ēǂݍ��ރt�@�C�������擾���܂�
		//	name	: �t�@�C�������i�[����|�C���^
		//	filter	: �t�@�C���t�B���^
		//  def		: �f�t�H���g�̃t�@�C����
		//  �߂�l	: TRUE�Ȃ琬�� FALSE�Ȃ�L�����Z��
		BOOL(*dlg_get_save_name)(LPSTR name, LPSTR filter, LPSTR def);
		//	�t�@�C���_�C�A���O���g���ď������ރt�@�C�������擾���܂�
		//	name	: �t�@�C�������i�[����|�C���^
		//	filter	: �t�@�C���t�B���^
		//  def		: �f�t�H���g�̃t�@�C����
		//  �߂�l	: TRUE�Ȃ琬�� FALSE�Ȃ�L�����Z��
		int(*ini_load_int)(void *fp, LPSTR key, int n);
		//	INI�t�@�C�����琔�l��ǂݍ���
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	key		: �A�N�Z�X�p�̃L�[�̖��O
		//  n		: �f�t�H���g�̐��l
		//  �߂�l	: �ǂݍ��񂾐��l
		int(*ini_save_int)(void *fp, LPSTR key, int n);
		//	INI�t�@�C���ɐ��l����������
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	key		: �A�N�Z�X�p�̃L�[�̖��O
		//  n		: �������ސ��l
		//  �߂�l	: �������񂾐��l
		BOOL(*ini_load_str)(void *fp, LPSTR key, LPSTR str, LPSTR def);
		//	INI�t�@�C�����當�����ǂݍ���
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	key		: �A�N�Z�X�p�̃L�[�̖��O
		//  str		: �������ǂݍ��ރo�b�t�@
		//  def		: �f�t�H���g�̕�����
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*ini_save_str)(void *fp, LPSTR key, LPSTR str);
		//	INI�t�@�C���ɕ��������������
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	key		: �A�N�Z�X�p�̃L�[�̖��O
		//  n		: �������ޕ�����
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*get_source_file_info)(void *editp, FILE_INFO *fip, int source_file_id);
		//	�w�肵���t�@�C��ID�̃t�@�C���̏����擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  fip		: �t�@�C���C���t�H���[�V�����\���̂ւ̃|�C���^
		//	souce_file_id
		//			: �t�@�C��ID
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*get_source_video_number)(void *editp, int n, int *source_file_id, int *source_video_number);
		//	�w�肵���t���[���̃\�[�X�̃t�@�C��ID�ƃt���[���ԍ����擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n		: �t���[���ԍ�
		//	souce_file_id
		//			: �t�@�C��ID���i�[����|�C���^
		//	souce_video_number
		//			: �t���[���ԍ����i�[����|�C���^
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*get_sys_info)(void *editp, SYS_INFO *sip);
		//	�V�X�e���̏����擾���܂�
		//	editp 	: �G�f�B�b�g�n���h�� (NULL�Ȃ�sip�̕ҏW���̃t���O�Ƃ��ׂẴt�@�C�����������ɂȂ�܂�)
		//  sip		: �V�X�e���C���t�H���[�V�����\���̂ւ̃|�C���^
		//  �߂�l	: TRUE�Ȃ琬��
		void 		*(*get_filterp)(int filter_id);
		//	�w��̃t�B���^ID�̃t�B���^�\���̂ւ̃|�C���^���擾���܂�
		//	filter_id
		//		 	: �t�B���^ID (0�`�o�^����Ă�t�B���^�̐�-1�܂ł̒l)
		//  �߂�l	: �t�B���^�\���̂ւ̃|�C���^ (NULL�Ȃ玸�s)
		void		*(*get_ycp_filtering)(void *fp, void *editp, int n, void *reserve);
		//	���o���邾��get_ycp_filtering_cache_ex()�̕����g�p����悤�ɂ��Ă�������
		//	�w�肵���t���[���̉摜�f�[�^�̃|�C���^���擾���܂�
		//	�f�[�^�͎����̃t�B���^�̒��O�܂Ńt�B���^�������̂ł�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//	reserve	: NULL���w�肵�Ă�������
		//  �߂�l	: �摜�f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
		int(*get_audio_filtering)(void *fp, void *editp, int n, void *buf);
		//	�w�肵���t���[���̃I�[�f�B�I�f�[�^��ǂݍ��݂܂�
		//	�f�[�^�͎����̃t�B���^�̒��O�܂Ńt�B���^�������̂ł�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	editp 	: �G�f�B�b�g�n���h��
		//	n		: �t���[���ԍ�
		//	buf 	: �i�[����o�b�t�@ (NULL�Ȃ�T���v�����̎擾�̂�)
		//  �߂�l	: �ǂݍ��񂾃T���v����
		BOOL(*set_ycp_filtering_cache_size)(void *fp, int w, int h, int d, int flag);
		//	get_ycp_filtering_cache_ex()�̃L���b�V���̐ݒ�����܂�
		//	�ݒ�l���ς�������̂݃L���b�V���̈���Ċm�ۂ��܂�
		//	�L���b�V���̈�̓t�B���^���A�N�e�B�u�̎��̂݊m�ۂ���܂�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	w	 	: �L���b�V���̈�̕�
		//	h	 	: �L���b�V���̈�̍���
		//	d	 	: �L���b�V������t���[����
		//	flag 	: NULL���w�肵�Ă�������
		//  �߂�l	: TRUE�Ȃ琬��
		void		*(*get_ycp_filtering_cache)(void *fp, void *editp, int n);
		//	���o���邾��get_ycp_filtering_cache_ex()�̕����g�p����悤�ɂ��Ă�������
		//	�w�肵���t���[���̉摜�f�[�^�̃L���b�V���|�C���^���擾���܂�
		//	set_ycp_filtering_cache_size()�̐ݒ�ɂ��������ăL���b�V������܂�
		//	�f�[�^�͎����̃t�B���^�̒��O�܂Ńt�B���^�������̂ł�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//  �߂�l	: �摜�f�[�^�ւ̃L���b�V���|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�̓L���b�V������j�������܂ŗL��
		void		*(*get_ycp_source_cache)(void *editp, int n, int ofs);
		//	�w�肵���t���[���̉摜�f�[�^�̃|�C���^���擾���܂�
		//	�f�[�^�̓t�B���^�O�̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//	ofs	 	: ����AVI��ł̃t���[���̃I�t�Z�b�g
		//  �߂�l	: �摜�f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�̓L���b�V������j�������܂ŗL��
		void		*(*get_disp_pixelp)(void *editp, DWORD format);
		//	�\������Ă���t���[���̉摜�f�[�^�̃|�C���^���擾���܂�
		//	�f�[�^�̓t�B���^��̂��̂ł�
		//	�\���t�B���^�̂ݎg�p�\�ł��B
		//	editp 	: �G�f�B�b�g�n���h��
		//	format	: �摜�t�H�[�}�b�g( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
		//  �߂�l	: �摜�f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
		BOOL(*get_pixel_source)(void *editp, int n, void *pixelp, DWORD format);
		//	�w�肵���t���[���̉摜�f�[�^��ǂݍ��݂܂�
		//	�f�[�^�̓t�B���^�O�̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//  pixelp	: DIB�`���f�[�^���i�[����|�C���^
		//	format	: �摜�t�H�[�}�b�g( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*get_pixel_filtered_ex)(void *editp, int n, void *pixelp, int *w, int *h, DWORD format);
		//	�w�肵���t���[���̉摜�f�[�^��ǂݍ��݂܂�
		//	�f�[�^�̓t�B���^��̂��̂ł�
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//  pixelp	: DIB�`���f�[�^���i�[����|�C���^ (NULL�Ȃ�摜�T�C�Y������Ԃ��܂�)
		//	w,h		: �摜�̃T�C�Y (NULL�Ȃ�DIB�`���f�[�^������Ԃ��܂�)
		//	format	: �摜�t�H�[�}�b�g( NULL = RGB24bit / 'Y''U''Y''2' = YUY2 )
		//  �߂�l	: TRUE�Ȃ琬��
		PIXEL_YC	*(*get_ycp_filtering_cache_ex)(void *fp, void *editp, int n, int *w, int *h);
		//	�w�肵���t���[���̉摜�f�[�^�̃L���b�V���|�C���^���擾���܂�
		//	set_ycp_filtering_cache_size()�̐ݒ�ɂ��������ăL���b�V������܂�
		//	�f�[�^�͎����̃t�B���^�̒��O�܂Ńt�B���^�������̂ł�
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	editp 	: �G�f�B�b�g�n���h��
		//	n	 	: �t���[���ԍ�
		//	w,h		: �擾�����摜�̃T�C�Y (NULL�Ȃ疳������܂�)
		//  �߂�l	: �摜�f�[�^�ւ̃L���b�V���|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�̓L���b�V������j�������܂ŗL��
		BOOL(*exec_multi_thread_func)(MULTI_THREAD_FUNC func, void *param1, void *param2);
		//	�w�肵���֐����V�X�e���̐ݒ�l�ɉ������X���b�h���ŌĂяo���܂�
		//	�Ăяo���ꂽ�֐�������Win32API��O���֐�(rgb2yc,yc2rgb�͏���)���g�p���Ȃ��ł�������
		//	func	: �}���`�X���b�h�ŌĂяo���֐�
		//	param1 	: �Ăяo���֐��ɓn���ėp�p�����[�^
		//	param2 	: �Ăяo���֐��ɓn���ėp�p�����[�^
		//  �߂�l	: TRUE�Ȃ琬��
		PIXEL_YC	*(*create_yc)(void);
		//	��̃t���[���摜�f�[�^�̈���쐬���܂�
		//	ycp_edit�Ɠ��l�ɊO���֐��Ŏg�p�ł��܂���
		//	FILTER_PROC_INFO��ycp_edit,ycp_temp�Ɠ���ւ��邱�Ƃ͏o���܂���
		//  �߂�l	: �쐬�����t���[���摜�f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		void(*delete_yc)(PIXEL_YC *ycp);
		//	create_yc�ō쐬�����̈���폜���܂�
		BOOL(*load_image)(PIXEL_YC *ycp, LPSTR file, int *w, int *h, int flag);
		//	�t���[���摜�f�[�^��BMP�t�@�C������摜��ǂݍ��݂܂�
		//	ycp     : �摜��ǂݍ��ރt���[���摜�ւ̃|�C���^ (NULL�Ȃ�`��������ɃT�C�Y��Ԃ��܂�)
		//	file	: �ǂݍ���BMP�t�@�C����
		//	w,h		: �ǂݍ��񂾉摜�̃T�C�Y (NULL���w��ł��܂�)
		//	flag 	: NULL���w�肵�Ă�������
		//  �߂�l	: TRUE�Ȃ琬��
		void(*resize_yc)(PIXEL_YC *ycp, int w, int h, PIXEL_YC *ycp_src, int sx, int sy, int sw, int sh);
		//	�t���[���摜�f�[�^�����T�C�Y���܂�
		//	���摜�̔C�ӂ̉摜�̈�����T�C�Y���邱�Ƃ��o���܂�
		//	ycp     : ���T�C�Y��̃t���[���摜���i�[����|�C���^
		//	w,h     : ���T�C�Y�̉𑜓x
		//	ycp_src	: ���摜�̃t���[���摜�ւ̃|�C���^(NULL�Ȃ�ycp�Ɠ���)
		//	sx,sy	: ���摜�̃��T�C�Y�Ώۗ̈�̍���̍��W
		//	sw,sh	: ���摜�̃��T�C�Y�Ώۗ̈�̃T�C�Y
		void(*copy_yc)(PIXEL_YC *ycp, int x, int y, PIXEL_YC *ycp_src, int sx, int sy, int sw, int sh, int tr);
		//	�t���[���摜�f�[�^�̔C�ӂ̗̈���R�s�[���܂�
		//	�`��̍ۂ͍ő�摜�T�C�Y�̗̈�Ɏ��܂�悤�ɃN���b�s���O�����܂�
		//	�R�s�[���ƃR�s�[��̗̈�͏d�Ȃ�Ȃ��悤�ɂ��Ă�������
		//	ycp     : �R�s�[��̃t���[���摜�ւ̃|�C���^
		//	x,y		: �R�s�[��̍���̍��W
		//	ycp_src	: �R�s�[���̃t���[���摜�ւ̃|�C���^
		//	sx,sy	: �R�s�[���̍���̍��W
		//	sw,sh	: �R�s�[���̃T�C�Y
		//	tr      : �R�s�[���̓����x (0�`4096)
		void(*draw_text)(PIXEL_YC *ycp, int x, int y, LPSTR text, int r, int g, int b, int tr, HFONT hfont, int *w, int *h);
		//	�t���[���摜�f�[�^�Ƀe�L�X�g��`�悵�܂�
		//	�`��̍ۂ͍ő�摜�T�C�Y�̗̈�Ɏ��܂�悤�ɃN���b�s���O�����܂�
		//	ycp     : �`�悷��t���[���摜�f�[�^�ւ̃|�C���^ (NULL�Ȃ�`��������ɃT�C�Y��Ԃ��܂�)
		//	x,y		: �`�悷�鍶��̍��W
		//	text	: �`�悷��e�L�X�g�̓��e
		//	r,g,b	: �`��F (0�`255)
		//	tr      : �����x (0�`4096)
		//	hfont	: �`��Ŏg�p����t�H���g (NULL�Ȃ�f�t�H���g�̃t�H���g)
		//	w,h		: �`�悵���e�L�X�g�̈�̃T�C�Y (NULL���w��ł��܂�)
		AVI_FILE_HANDLE(*avi_file_open)(LPSTR file, FILE_INFO *fip, int flag);
		//	AVI�t�@�C�����I�[�v������avi_file_read_video(),avi_file_read_audio()��
		//	�f�[�^��ǂݍ��ވׂ̃n���h�����擾���܂��B
		//	���ҏW���̃t�@�C���ƃt�H�[�}�b�g(fps��T���v�����O���[�g��)���قȂ�ꍇ������̂Œ��ӂ��Ă��������B
		//	file    : �ǂݍ���AVI�t�@�C���� (���̓v���O�C���œǂݍ��߂�t�@�C�����w��ł��܂�)
		//  fip		: �t�@�C���C���t�H���[�V�����\���̂ւ̃|�C���^ (�ǂݍ��񂾃t�@�C���̏�񂪓���܂�)
		//	flag 	: �ǂݍ��݃t���O
		//	AVI_FILE_OPEN_FLAG_ONLY_YUY2		: YUY2 �œW�J����悤�ɂ��܂�
		//	AVI_FILE_OPEN_FLAG_ONLY_RGB24		: RGB24�œW�J����悤�ɂ��܂�
		//	AVI_FILE_OPEN_FLAG_ONLY_RGB32		: RGB32�œW�J����悤�ɂ��܂�
		//	AVI_FILE_OPEN_FLAG_VIDEO_ONLY		: �r�f�I�̂ݓǂݍ��ނ悤�ɂ��܂�
		//	AVI_FILE_OPEN_FLAG_AUDIO_ONLY		: �I�[�f�B�I�̂ݓǂݍ��ނ悤�ɂ��܂�
		//  �߂�l	: AVI�t�@�C���n���h�� (NULL�Ȃ玸�s)
		struct AVI_FILE_OPEN {
			static const int	FLAG_VIDEO_ONLY = 16;
			static const int	FLAG_AUDIO_ONLY = 32;
			static const int	FLAG_ONLY_YUY2 = 0x10000;
			static const int	FLAG_ONLY_RGB24 = 0x20000;
			static const int	FLAG_ONLY_RGB32 = 0x40000;
		};


		void(*avi_file_close)(AVI_FILE_HANDLE afh);
		//	AVI�t�@�C�����N���[�Y���܂�
		//	afh		: AVI�t�@�C���n���h��
		BOOL(*avi_file_read_video)(AVI_FILE_HANDLE afh, PIXEL_YC *ycp, int n);
		//	�t���[���摜�f�[�^��AVI�t�@�C������摜�f�[�^��ǂݍ��݂܂�
		//	afh		: AVI�t�@�C���n���h��
		//	ycp     : �摜�f�[�^��ǂݍ��ރt���[���摜�ւ̃|�C���^
		//	n		: �t���[���ԍ�
		//  �߂�l	: TRUE�Ȃ琬��
		int(*avi_file_read_audio)(AVI_FILE_HANDLE afh, void *buf, int n);
		//	AVI�t�@�C�����特���f�[�^��ǂݍ��݂܂�
		//	afh		: AVI�t�@�C���n���h��
		//	buf     : ������ǂݍ��ރo�b�t�@�ւ̃|�C���^
		//	n		: �t���[���ԍ�
		//  �߂�l	: �ǂݍ��񂾃T���v����
		void 		*(*avi_file_get_video_pixelp)(AVI_FILE_HANDLE afh, int n);
		//	AVI�t�@�C������ǂݍ���DIB�`���̉摜�f�[�^�̃|�C���^���擾���܂�
		//	�擾�ł���摜�f�[�^�̃t�H�[�}�b�g��avi_file_open()�Ŏ擾����
		//	FILE_INFO�̃r�f�I�W�J�`���ɂȂ�܂��B
		//	afh		: AVI�t�@�C���n���h��
		//	n		: �t���[���ԍ�
		//  �߂�l	: DIB�`���f�[�^�ւ̃|�C���^ (NULL�Ȃ玸�s)
		//			  �摜�f�[�^�|�C���^�̓��e�͎��ɊO���֐����g�������C���ɏ�����߂��܂ŗL��
		LPSTR(*get_avi_file_filter)(int type);
		//	avi_file_open()�œǂݍ��߂�t�@�C���̃t�@�C���t�B���^���擾���܂�
		//	type	: �t�@�C���̎��
		//	GET_AVI_FILE_FILTER_TYPE_VIDEO	: �r�f�I��
		//	GET_AVI_FILE_FILTER_TYPE_AUDIO	: �I�[�f�B�I
		//  �߂�l	: �t�@�C���t�B���^�ւ̃|�C���^
		struct GET_AVI_FILE_FILTER
		{
			static const int		TYPE_VIDEO = 0;
			static const int		TYPE_AUDIO = 1;
		};

		int(*avi_file_read_audio_sample)(AVI_FILE_HANDLE afh, int start, int length, void *buf);
		//	AVI�t�@�C�����特���f�[�^��ǂݍ��݂܂�
		//	afh		: AVI�t�@�C���n���h��
		//	start   : �ǂݍ��݊J�n�T���v���ԍ�
		//	length	: �ǂݍ��ރT���v����
		//	buf		: �f�[�^��ǂݍ��ރo�b�t�@�ւ̃|�C���^
		//  �߂�l	: �ǂݍ��񂾃T���v����
		int(*avi_file_set_audio_sample_rate)(AVI_FILE_HANDLE afh, int audio_rate, int audio_ch);
		//	avi_file_read_audio_sample()�œǂݍ��މ����̃T���v�����O���[�g����ύX���܂�
		//	afh		: AVI�t�@�C���n���h��
		//	audio_rate	: �����T���v�����O���[�g
		//	audio_ch	: �����`�����l����
		//  �߂�l	: �ύX�����T���v�����O���[�g�ł̑��T���v����
		BYTE		*(*get_frame_status_table)(void *editp, int type);
		//	�t���[���̃X�e�[�^�X���i�[����Ă���o�b�t�@�ւ̃|�C���^���擾���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  type	: �X�e�[�^�X�̎��
		//	FARME_STATUS_TYPE_EDIT_FLAG	: �ҏW�t���O
		//	FARME_STATUS_TYPE_INTER		: �C���^�[���[�X
		//  �߂�l	: �o�b�t�@�ւ̃|�C���^
		//			  �o�b�t�@�ւ̃|�C���^�̓��e�͕ҏW�t�@�C�����N���[�Y�����܂ŗL��
		struct GET_FRAME_STATUS
		{
			static const int TYPE_EDIT_FLAG = 0;
			static const int TYPE_INTER = 1;
		};

		BOOL(*set_undo)(void *editp);
		//	���݂̕ҏW�󋵂��A���h�D�o�b�t�@�ɐݒ肵�܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*add_menu_item)(void *fp, LPSTR name, HWND hwnd, int id, int def_key, int flag);
		//	���C���E�B���h�E�̐ݒ胁�j���[���ڂ�ǉ����܂�
		//	���j���[���I�����ꂽ����hwnd�Ŏw�肵���E�B���h�E��
		//	WM_FILTER_COMMAND�̃��b�Z�[�W�𑗂�܂�
		//	���K��func_init()��WM_FILTER_INIT����Ăяo���悤�ɂ��Ă��������B
		//	fp	 	: �t�B���^�\���̂̃|�C���^
		//	name 	: ���j���[�̖��O
		//	hwnd 	: WM_FILTER_COMMAND�𑗂�E�B���h�E�n���h��
		//	id	 	: WM_FILTER_COMMAND��WPARAM
		//	def_key	: �W���̃V���[�g�J�b�g�L�[�̉��z�L�[�R�[�h (NULL�Ȃ疳��)
		//	flag	: �t���O
		//	ADD_MENU_ITEM_FLAG_KEY_SHIFT	: �W���̃V���[�g�J�b�g�L�[��SHIFT+�L�[�ɂ���
		//	ADD_MENU_ITEM_FLAG_KEY_CTRL		: �W���̃V���[�g�J�b�g�L�[��CTRL+�L�[�ɂ���
		//	ADD_MENU_ITEM_FLAG_KEY_ALT		: �W���̃V���[�g�J�b�g�L�[��ALT+�L�[�ɂ���
		//  �߂�l	: TRUE�Ȃ琬��
		struct ADD_MENU_ITEM
		{
			static const int FLAG_KEY_SHIFT = 1;
			static const int FLAG_KEY_CTRL = 2;
			static const int FLAG_KEY_ALT = 4;
		};

		BOOL(*edit_open)(void *editp, LPSTR file, int flag);
		//	�ҏW�t�@�C�����J���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	file 	: �t�@�C����
		//	flag 	: �t���O
		//	EDIT_OPEN_FLAG_ADD			: �ǉ��ǂݍ��݂����܂�
		//	EDIT_OPEN_FLAG_AUDIO		: �����ǂݍ��݂����܂�
		//	EDIT_OPEN_FLAG_PROJECT		: �v���W�F�N�g�t�@�C�����J���܂�
		//	EDIT_OPEN_FLAG_DIALOG		: �ǂݍ��݃_�C�A���O��\�����܂�
		//  �߂�l	: TRUE�Ȃ琬��
		struct EDIT_OPEN
		{
			static const int FLAG_ADD = 2;
			static const int FLAG_AUDIO = 16;
			static const int FLAG_PROJECT = 512;
			static const int FLAG_DIALOG = 65536;
		};

		BOOL(*edit_close)(void *editp);
		//	�ҏW�t�@�C������܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  �߂�l	: TRUE�Ȃ琬��
		BOOL(*edit_output)(void *editp, LPSTR file, int flag, LPSTR type);
		//	�ҏW�f�[�^��AVI�o�͂��܂�
		//	WAV�o�͂�v���O�C���o�͂��o���܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//	file 	: �o�̓t�@�C����
		//	flag	: �t���O
		//	EDIT_OUTPUT_FLAG_NO_DIALOG	: �o�̓_�C�A���O��\�����܂���
		//	EDIT_OUTPUT_FLAG_WAV		: WAV�o�͂����܂�
		//	type	: �o�̓v���O�C���̖��O (NULL�Ȃ�AVI/WAV�o��)
		//  �߂�l	: TRUE�Ȃ琬��
		struct EDIT_OUTPUT
		{
			const static int FLAG_NO_DIALOG = 2;
			const static int FLAG_WAV = 4;
		};

		BOOL(*set_config)(void *editp, int n, LPSTR name);
		//	�v���t�@�C����ݒ肵�܂�
		//	editp 	: �G�f�B�b�g�n���h��
		//  n		: �v���t�@�C�����̔ԍ�
		//  name	: �v���t�@�C���̖��O
		//  �߂�l	: TRUE�Ȃ琬��

		int			reserved[7];
	};
//	const static int ef = sizeof(EXFUNC);	// 320

	struct FILTER
	{
		unsigned long	flags;				//	�t�B���^�̃t���O
		static const unsigned long	FLAG_ACTIVE = 0x00000001;				//	�t�B���^���A�N�e�B�u�ɂ��܂�
		static const unsigned long	FLAG_ALWAYS_ACTIVE = 0x00000004;		//	�t�B���^����ɃA�N�e�B�u�ɂ��܂�
		static const unsigned long	FLAG_CONFIG_POPUP = 0x00000008;			//	�ݒ���|�b�v�A�b�v���j���[�ɂ��܂�
		static const unsigned long	FLAG_CONFIG_CHECK = 0x00000010;			//	�ݒ���`�F�b�N�{�b�N�X���j���[�ɂ��܂�
		static const unsigned long	FLAG_CONFIG_RADIO = 0x00000020;			//	�ݒ�����W�I�{�^�����j���[�ɂ��܂�
		static const unsigned long	FLAG_EX_DATA = 0x00000400;				//	�g���f�[�^��ۑ��o����悤�ɂ��܂�
		static const unsigned long	FLAG_PRIORITY_HIGHEST = 0x00000800;		//	�t�B���^�̃v���C�I���e�B����ɍŏ�ʂɂ��܂�
		static const unsigned long	FLAG_PRIORITY_LOWEST = 0x00001000;		//	�t�B���^�̃v���C�I���e�B����ɍŉ��ʂɂ��܂�
		static const unsigned long	FLAG_WINDOW_THICKFRAME = 0x00002000;	//	�T�C�Y�ύX�\�ȃE�B���h�E�����܂�
		static const unsigned long	FLAG_WINDOW_SIZE = 0x00004000;			//	�ݒ�E�B���h�E�̃T�C�Y���w��o����悤�ɂ��܂�
		static const unsigned long	FLAG_DISP_FILTER = 0x00008000;			//	�\���t�B���^�ɂ��܂�
		static const unsigned long	FLAG_REDRAW = 0x00020000;				//	�ĕ`���plugin���ŏ�������悤�ɂ��܂�
		static const unsigned long	FLAG_EX_INFORMATION = 0x00040000;		//	�t�B���^�̊g������ݒ�ł���悤�ɂ��܂�
		static const unsigned long	FLAG_INFORMATION = 0x00080000;          //	FILTER_FLAG_EX_INFORMATION ���g���悤�ɂ��ĉ�����
		static const unsigned long	FLAG_NO_CONFIG = 0x00100000;            //	�ݒ�E�B���h�E��\�����Ȃ��悤�ɂ��܂�
		static const unsigned long	FLAG_AUDIO_FILTER = 0x00200000;         //	�I�[�f�B�I�t�B���^�ɂ��܂�
		static const unsigned long	FLAG_RADIO_BUTTON = 0x00400000;         //	�`�F�b�N�{�b�N�X�����W�I�{�^���ɂ��܂�
		static const unsigned long	FLAG_WINDOW_HSCROLL = 0x00800000;       //	�����X�N���[���o�[�����E�B���h�E�����܂�
		static const unsigned long	FLAG_WINDOW_VSCROLL = 0x01000000;       //	�����X�N���[���o�[�����E�B���h�E�����܂�
		static const unsigned long	FLAG_INTERLACE_FILTER = 0x04000000;     //	�C���^�[���[�X�����t�B���^�ɂ��܂�
		static const unsigned long	FLAG_NO_INIT_DATA = 0x08000000;         //	func_proc()�̉摜�̏����f�[�^���쐬���Ȃ��悤�ɂ��܂�
		static const unsigned long	FLAG_IMPORT = 0x10000000;               //	�C���|�[�g���j���[�����܂�
		static const unsigned long	FLAG_EXPORT = 0x20000000;               //	�G�N�X�|�[�g���j���[�����܂�
		static const unsigned long	FLAG_MAIN_MESSAGE = 0x40000000;         //	func_WndProc()��WM_FILTER_MAIN_???�̃��b�Z�[�W�𑗂�悤�ɂ��܂�

		int			cfgdlg_width;		//	�ݒ�E�C���h�E�̃T�C�Y (FILTER_FLAG_WINDOW_SIZE�������Ă��鎞�ɗL��)
		int			cfgdlg_height;
		//	�ݒ�l�� FILTER_WINDOW_SIZE_CLIENT ��OR���Đݒ肷��ƃN���C�A���g�̈�ł̃T�C�Y�w��ɂȂ�܂��B
		//	�ݒ�l�� FILTER_WINDOW_SIZE_ADD ��OR���Đݒ肷��ƕW���̃T�C�Y����̒ǉ����̎w��ɂȂ�܂��B
		struct FILTER_WINDOW_SIZE
		{
			static const unsigned long	CLIENT = 0x10000000;		// OR���Đݒ肷��ƃN���C�A���g�̈�ł̃T�C�Y�w��
			static const unsigned long	ADD = 0x30000000;			// OR���Đݒ肷��ƕW���̃T�C�Y����̒ǉ����̎w��
		};

		TCHAR		*filtername;		//	�t�B���^�̖��O

		int			trackbar_num;		//	�g���b�N�o�[�̐�
		TCHAR		**trackbar_name;	//	�g���b�N�o�[�̖��O�Q�ւ̃|�C���^(�g���b�N�o�[����0�Ȃ�NULL�ł悢)
		int			*trackbar_default;	//	�g���b�N�o�[�̏����l�Q�ւ̃|�C���^(�g���b�N�o�[����0�Ȃ�NULL�ł悢)
		int			*trackbar_low;		//	�g���b�N�o�[�̐��l�̉��� (NULL�Ȃ�S��0)
		int			*trackbar_high;		//	�g���b�N�o�[�̐��l�̏�� (NULL�Ȃ�S��256)

		int			chkbox_num;			//	�`�F�b�N�{�b�N�X�̐�
		TCHAR		**chkbox_name;		//	�`�F�b�N�{�b�N�X�̖��O�S�ւ̃|�C���^(�`�F�b�N�{�b�N�X����0�Ȃ�NULL�ł悢)
		int			*chkbox_default;	//	�`�F�b�N�{�b�N�X�̏����l�S�ւ̃|�C���^(�`�F�b�N�{�b�N�X����0�Ȃ�NULL�ł悢)
										//	�����l���}�C�i�X�l�̏ꍇ�̓{�^���ɂȂ�܂��B
										//	�{�^�����������Ƃ���WM_COMMAND( WPARAM = MID_FILTER_BUTTON + n )�̃E�B���h�E���b�Z�[�W�������܂�

		BOOL		(*func_proc)(void *fp, FILTER_PROC_INFO *fpip);
		//	�t�B���^�����֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		BOOL		(*func_init)(void *fp);
		//	�J�n���ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		BOOL		(*func_exit)(void *fp);
		//	�I�����ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		BOOL		(*func_update)(void *fp, int status);
		//	�����̐ݒ肪�ύX���ꂽ�Ƃ��ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		//	FILTER_UPDATE_STATUS_ALL		: �S���ڂ��ύX���ꂽ
		//	FILTER_UPDATE_STATUS_TRACK + n	: n�Ԗڂ̃g���b�N�o�[���ύX���ꂽ
		//	FILTER_UPDATE_STATUS_CHECK + n	: n�Ԗڂ̃`�F�b�N�{�b�N�X���ύX���ꂽ
		struct FUNC_UPDATE
		{
			static const unsigned long	FILTER_UPDATE_STATUS_ALL = 0x00000000;
			static const unsigned long	FILTER_UPDATE_STATUS_TRACK = 0x00010000;
			static const unsigned long	FILTER_UPDATE_STATUS_CHECK = 0x00020000;
		};

		BOOL		(*func_WndProc)(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, void *fp);
		//	�ݒ�E�B���h�E�ɃE�B���h�E���b�Z�[�W���������ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		//	VFAPI���쎞�ɂ͌Ă΂�܂���
		//	�ʏ�̃��b�Z�[�W�ȊO�Ɉȉ��̊g�����b�Z�[�W�������܂�
		struct FUNC_WNDPROC
		{
			static const UINT			WM_FILTER_UPDATE = (WM_USER + 100);					//	�e�t�B���^�ݒ��ҏW���e���ύX���ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_FILE_OPEN = (WM_USER + 101);				//	�ҏW�t�@�C�����I�[�v�����ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_FILE_UPDATE = (WM_USER + 114);			//	�ҏW�t�@�C���̍X�V(�ǉ��≹���ǂݍ��ݓ�)������������ɑ����܂�
			static const UINT			WM_FILTER_FILE_CLOSE = (WM_USER + 102);				//	�ҏW�t�@�C�����N���[�Y����钼�O�ɑ����܂�
			static const UINT			WM_FILTER_INIT = (WM_USER + 103);					//	�J�n����ɑ����܂�
			static const UINT			WM_FILTER_EXIT = (WM_USER + 104);					//	�I�����O�ɑ����܂�
			static const UINT			WM_FILTER_SAVE_START = (WM_USER + 105);				//	�Z�[�u���J�n����钼�O�ɑ����܂�
			static const UINT			WM_FILTER_SAVE_END = (WM_USER + 106);				//	�Z�[�u���I�����ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_IMPORT = (WM_USER + 107);					//	�C���|�[�g���I�����ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_EXPORT = (WM_USER + 108);					//	�G�N�X�|�[�g���I�����ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_CHANGE_ACTIVE = (WM_USER + 109);			//	�t�B���^�̗L��/�������ύX���ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_CHANGE_WINDOW = (WM_USER + 110);			//	�t�B���^�E�B���h�E�̕\��/��\�����ύX���ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_CHANGE_PARAM = (WM_USER + 111);			//	�����̃t�B���^�̐ݒ肪�ύX���ꂽ����ɑ����܂�
			static const UINT			WM_FILTER_CHANGE_EDIT = (WM_USER + 112);			//	�ҏW��/��ҏW�����ύX���ꂽ����ɑ����܂�

			static const UINT			WM_FILTER_COMMAND = (WM_USER + 113);
			static const WPARAM			MID_FILTER_BUTTON = 12004;
			// �{�^��(�Ƃ��č쐬�����`�F�b�N�{�b�N�X)���������Ƃ���WM_COMMAND( WPARAM = MID_FILTER_BUTTON + n )�̃E�B���h�E���b�Z�[�W�������܂�

			//	����ȍ~�̃��b�Z�[�W��FILTER_FLAG_MAIN_MESSAGE�ݒ莞�̂ݑ����܂�
			static const UINT			WM_FILTER_MAIN_MOUSE_DOWN = (WM_USER + 120);		//	���C���E�B���h�E�Ń}�E�X�̍��{�^���������ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_MOUSE_UP = (WM_USER + 121);			//	���C���E�B���h�E�Ń}�E�X���ړ��������ɑ����܂�
			static const UINT			WM_FILTER_MAIN_MOUSE_MOVE = (WM_USER + 122);		//	���C���E�B���h�E�Ń}�E�X�̍��{�^���������ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_KEY_DOWN = (WM_USER + 123);			//	���C���E�B���h�E�Ń}�E�X�̍��{�^�����_�u���N���b�N���ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_KEY_UP = (WM_USER + 124);			//	���C���E�B���h�E�Ń}�E�X�̉E�{�^���������ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_MOVESIZE = (WM_USER + 125);			//	���C���E�B���h�E�Ń}�E�X�̉E�{�^���������ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_MOUSE_DBLCLK = (WM_USER + 126);		//	���C���E�B���h�E�Ń}�E�X�̃z�C�[������]�������ɑ����܂�
			static const UINT			WM_FILTER_MAIN_MOUSE_R_DOWN = (WM_USER + 127);		//	���C���E�B���h�E�ŃL�[�������ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_MOUSE_R_UP = (WM_USER + 128);		//	���C���E�B���h�E�ŃL�[�������ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_MOUSE_WHEEL = (WM_USER + 129);		//	���C���E�B���h�E�̈ʒu��T�C�Y���ύX���ꂽ���ɑ����܂�
			static const UINT			WM_FILTER_MAIN_CONTEXTMENU = (WM_USER + 130);		//	���C���E�B���h�E�ŃR���e�L�X�g���j���[���\������鎞�ɑ����܂�
			//	WM_FILTER_MAIN_MOUSE_???��lparam�ɂ͕ҏW�摜��ł̍��W������܂�(�ҏW���ȊO��0�ɂȂ�܂�)
			//	WM_FILTER_MAIN_MOUSE_WHEEL��wparam�̏�ʃ��[�h�Ƀz�C�[���̉�]�ʂ�����܂�
			//	WM_FILTER_MAIN_KEY_???��wparam�ɂ͉��z�L�[�R�[�h������܂�
			//	WM_FILTER_MAIN_MOVESIZE��lparam�ɂ̓��C���E�B���h�E�̃E�B���h�E�n���h��������܂�
			//	WM_FILTER_MAIN_CONTEXTMENU��lparam�ɂ̓X�N���[�����W������܂�
			//	WM_FILTER_MAIN_CONTEXTMENU�Ń��j���[��\���������͖߂�l��TRUE�ɂ��Ă�������(�ĕ`��͂���܂���)
			//	�߂�l��TRUE�ɂ���ƕҏW���e���X�V���ꂽ�Ƃ��đS�̂��ĕ`�悳��܂�
		};


		int			*track_value;		//	�g���b�N�o�[�̐ݒ�l�S�ւ̃|�C���^ (AviUtl���Őݒ肳��܂�)
		int			*check_value;		//	�`�F�b�N�{�b�N�X�̐ݒ�l�S�ւ̃|�C���^ (AviUtl���Őݒ肳��܂�)

		void		*ex_data_ptr;		//	�g���f�[�^�̈�ւ̃|�C���^ (FILTER_FLAG_EX_DATA�������Ă��鎞�ɗL��)
		int			ex_data_size;		//	�g���f�[�^�T�C�Y (FILTER_FLAG_EX_DATA�������Ă��鎞�ɗL��)
		TCHAR		*information;		//	�t�B���^���ւ̃|�C���^ (FILTER_FLAG_EX_INFORMATION�������Ă��鎞�ɗL��)

		BOOL		(*func_save_start)(void *fp, int s, int e, void *editp);
		//	�Z�[�u���J�n����钼�O�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		//	s	 	: �Z�[�u����擪�t���[��
		//	e 		: �Z�[�u����ŏI�t���[��
		//  �߂�l	: �����Ȃ�TRUE
		BOOL		(*func_save_end)(void *fp, void *editp);
		//	�Z�[�u���I���������O�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)

		EXFUNC		*exfunc;			//	�O���֐��e�[�u���ւ̃|�C���^ (AviUtl���Őݒ肳��܂�)
		HWND		hwnd;				//	�E�B���h�E�n���h�� (AviUtl���Őݒ肳��܂�)
		HINSTANCE	dll_hinst;			//	DLL�̃C���X�^���X�n���h�� (AviUtl���Őݒ肳��܂�)
		void		*ex_data_def;		//	�g���f�[�^�̏����l�f�[�^�̈�ւ̃|�C���^ (NULL�Ȃ珉��������܂���)

		BOOL		(*func_is_saveframe)(void *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter);
		//	�C���^�[���[�X�����t�B���^�ŕۑ�����t���[�������߂鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		//	saveno		: �Z�[�u����͈͂̐擪����̃t���[���ԍ�
		//	frame		: �ҏW�t���[���ԍ�
		//	fps			: �t���[�����[�g�̕ύX�̐ݒ�l (30,24,20,15,10)
		//	edit_flag	: �ҏW�t���O
		//	inter		: �t���[���̃C���^�[���[�X
		//	�߂�l		: TRUE��Ԃ��ƕۑ��t���[���AFALSE��Ԃ��ƊԈ����t���[���ɂȂ�܂��B
		BOOL		(*func_project_load)(void *fp, void *editp, void *data, int size);
		//	�v���W�F�N�g�t�@�C������f�[�^��ǂݍ��񂾎��ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		//	�v���W�F�N�g�t�@�C���ɕۑ������f�[�^�������ꍇ�͌Ă΂�܂���
		//	data 	: �v���W�F�N�g����ǂݍ��񂾃f�[�^�ւ̃|�C���^
		//	size 	: �v���W�F�N�g����ǂݍ��񂾃f�[�^�̃o�C�g��
		//  �߂�l	: �����Ȃ�TRUE
		BOOL		(*func_project_save)(void *fp, void *editp, void *data, int *size);
		//	�v���W�F�N�g�t�@�C�����Z�[�u���Ă��鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		//	�v���W�F�N�g�t�@�C���Ƀt�B���^�̃f�[�^��ۑ����܂�
		//	��AviUtl����͎n�߂ɕۑ��T�C�Y�擾�ׂ̈�data��NULL�ŌĂяo����A�����Ď��ۂ̃f�[�^���擾����ׂɌĂяo����܂��B
		//	data 	: �v���W�F�N�g�ɏ������ރf�[�^���i�[����o�b�t�@�ւ̃|�C���^ (NULL�̏ꍇ�̓f�[�^�̃o�C�g���̂ݕԂ�)
		//	size 	: �v���W�F�N�g�ɏ������ރf�[�^�̃o�C�g����Ԃ��|�C���^
		//  �߂�l	: �ۑ�����f�[�^������Ȃ�TRUE
		BOOL		(*func_modify_title)(void *fp, void *editp, int frame, LPSTR title, int max_title);
		//	���C���E�B���h�E�̃^�C�g���o�[��\�����鎞�ɌĂ΂��֐��ւ̃|�C���^ (NULL�Ȃ�Ă΂�܂���)
		//	�^�C�g���o�[�̕������ύX�ł��܂� (���ҏW���A�o�͎��͌Ă΂�܂���)
		//	frame		: �ҏW�t���[���ԍ�
		//	title 		: �\������^�C�g���o�[�̕�����
		//	max_title 	: title�̃o�b�t�@�T�C�Y
		//  �߂�l	: �����Ȃ�TRUE

		TCHAR		*dll_path;			//	Plugins�f�B���N�g���̃T�u�f�B���N�g����DLL�����鎞�̂݁A�T�u�f�B���N�g����������܂��B

		int			reserved[2];		// �g���p�ɗ\��	NULL
	};
//	const static int fl = sizeof(FILTER);	// 140


	//	�t�B���^DLL�p�\����
	struct FILTER_DLL
	{
		int			flag;
		int			x;
		int			y;
		TCHAR		*name;

		int			track_n;
		TCHAR		**track_name;
		int			*track_default;
		int			*track_s;
		int			*track_e;

		int			check_n;
		TCHAR		**check_name;
		int			*check_default;

		BOOL		(*func_proc)(FILTER *fp, FILTER_PROC_INFO *fpip);
		BOOL		(*func_init)(FILTER *fp);
		BOOL		(*func_exit)(FILTER *fp);
		BOOL		(*func_update)(FILTER *fp, int status);
		BOOL		(*func_WndProc)(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp);

		int			*track, *check;
		void		*ex_data_ptr;
		int			ex_data_size;
		TCHAR		*information;

		BOOL		(*func_save_start)(FILTER *fp, int s, int e, void *editp);
		BOOL		(*func_save_end)(FILTER *fp, void *editp);

		EXFUNC		*exfunc;
		HWND		hwnd;
		HINSTANCE	dll_hinst;
		void		*ex_data_def;

		BOOL		(*func_is_saveframe)(FILTER *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter);
		BOOL		(*func_project_load)(FILTER *fp, void *editp, void *data, int size);
		BOOL		(*func_project_save)(FILTER *fp, void *editp, void *data, int *size);
		BOOL		(*func_modify_title)(FILTER *fp, void *editp, int frame, LPSTR title, int max_title);

		TCHAR		*dll_path;

		int			reserve[2];
	};

//	BOOL func_proc(FILTER *fp, FILTER_PROC_INFO *fpip);
//	BOOL func_init(FILTER *fp);
//	BOOL func_exit(FILTER *fp);
//	BOOL func_update(FILTER *fp, int status);
//	BOOL func_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp);
//	BOOL func_save_start(FILTER *fp, int s, int e, void *editp);
//	BOOL func_save_end(FILTER *fp, void *editp);
//	BOOL func_is_saveframe(FILTER *fp, void *editp, int saveno, int frame, int fps, int edit_flag, int inter);
//	BOOL func_project_load(FILTER *fp, void *editp, void *data, int size);
//	BOOL func_project_save(FILTER *fp, void *editp, void *data, int *size);
//	BOOL func_modify_title(FILTER *fp, void *editp, int frame, LPSTR title, int max_title);


};

#endif ___AVIUTLFILTER_H___
