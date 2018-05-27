/* Copyright 2018 The Wallpaper Authors.All Rights Reserved.

@Author: Aaron Vu
@Date: 2018-05-26
@Email: fetaxyu@gmail.com
=============================================================== */

#ifndef WALLPAPER_WALLPAPER_H_
#define WALLPAPER_WALLPAPER_H_

#include <QtWidgets/QWidget>
#include <opencv2/opencv.hpp>
#include "ui_wallpaper.h"



class Wallpaper : public QWidget
{
	Q_OBJECT

public:

	const QString title = "Wallpaper";

	Wallpaper(int&&, int&&, std::string&, QWidget *parent = Q_NULLPTR);


	void timerEvent(QTimerEvent *e);

	void Init();
	void SetWallpaper();
	void SetDesktopWallpaper();

private:
	Ui::WallpaperClass ui;
	int wid;
	int heigh;
	std::string& src;
	cv::VideoCapture capture;
	
};
#endif