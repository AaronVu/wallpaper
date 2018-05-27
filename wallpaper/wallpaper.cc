/* Copyright 2018 The Wallpaper Authors.All Rights Reserved.

@Author: Aaron Vu
@Date: 2018-05-26
@Email: fetaxyu@gmail.com
=============================================================== */

#include <QtWidgets/QApplication>
#include <QtCore/QTimer>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <CommCtrl.h>
#include <atlimage.h>
#include "asm_opencv.h"
#include "wallpaper.h"


Wallpaper::Wallpaper(int&& w, int&& h, std::string& src, QWidget *parent) : QWidget(parent), wid(w), heigh(h), src(src) {
	ui.setupUi(this);
	this->Init();
}

void Wallpaper::Init() {
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowTitle(title);
	this->resize(QSize(this->wid, this->heigh));
	capture.open(src);
	this->startTimer(32);
}


void Wallpaper::SetWallpaper() {
	HWND hwnd_1 = FindWindowEx(FindWindow(L"Progman", NULL), NULL, L"SHELLDLL_DefView", NULL);
	HWND hwnd_2 = FindWindowEx(hwnd_1, NULL, L"SysListView32", NULL);
	HWND self_hwnd = FindWindow(L"Qt5QWindowIcon", L"Wallpaper");
	SetParent(self_hwnd, hwnd_1);
	BringWindowToTop(hwnd_2);
	SetWindowLong(hwnd_2, GWL_EXSTYLE,
		GetWindowLong(hwnd_2, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd_2, 0, 81, LWA_ALPHA);
}

void Wallpaper::SetDesktopWallpaper() {
	char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, (LPWSTR)path);
	CString file = L"\\Resources\\Wallpaper.bmp";
	CString t_path;
	t_path.Format(L"%s", path);
	t_path += file;
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, static_cast<PVOID>(pszFile), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}


void Wallpaper::timerEvent(QTimerEvent * e) {
	cv::Mat frame;
	if (capture.read(frame)) {
		QPixmap pixmap = ASM::cvMatToQPixmap(frame);
		ui.label->setPixmap(pixmap);
	} else {
		capture.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
	}
}

