/* Copyright 2018 The Wallpaper Authors.All Rights Reserved.

@Author: Aaron Vu
@Date: 2018-05-26
@Email: fetaxyu@gmail.com
=============================================================== */

#ifndef WALLPAPER_ASM_OPENCV_H_
#define WALLPAPER_ASM_OPENCV_H_

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QtGlobal>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"


#if Q_BYTE_ORDER == Q_BIG_ENDIAN
#error Some of QImage's formats are endian-dependant. This file assumes little endian. See comment at top of header.
#endif

namespace ASM {
	inline QImage  cvMatToQImage(const cv::Mat &inMat) {
		switch (inMat.type()) {
			// 8-bit, 4 channel
		case CV_8UC4:
		{
			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_ARGB32);

			return image;
		}

		// 8-bit, 3 channel
		case CV_8UC3:
		{
			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_RGB888);

			return image.rgbSwapped();
		}

		// 8-bit, 1 channel
		case CV_8UC1:
		{
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_Grayscale8);
#else
			static QVector<QRgb>  sColorTable;

			// only create our color table the first time
			if (sColorTable.isEmpty())
			{
				sColorTable.resize(256);

				for (int i = 0; i < 256; ++i)
				{
					sColorTable[i] = qRgb(i, i, i);
				}
			}

			QImage image(inMat.data,
				inMat.cols, inMat.rows,
				static_cast<int>(inMat.step),
				QImage::Format_Indexed8);

			image.setColorTable(sColorTable);
#endif

			return image;
		}

		default:
			break;
		}

		return QImage();
	}

	inline QPixmap cvMatToQPixmap(const cv::Mat &inMat) {
		return QPixmap::fromImage(cvMatToQImage(inMat));
	}
}
#endif