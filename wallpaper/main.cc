/* Copyright 2018 The Wallpaper Authors.All Rights Reserved.

@Author: Aaron Vu
@Date: 2018-05-26
@Email: fetaxyu@gmail.com
=============================================================== */

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include "wallpaper.h"


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QDesktopWidget *screen = QApplication::desktop();
	Wallpaper wall(screen->width(), screen->height(), std::string("./Resources/nuva.mov"));
	wall.show();
	wall.SetDesktopWallpaper();
	wall.SetWallpaper();
	return app.exec();
}
