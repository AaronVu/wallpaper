/********************************************************************************
** Form generated from reading UI file 'wallpaper.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WALLPAPER_H
#define UI_WALLPAPER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WallpaperClass
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *mainLayout;
    QLabel *label;

    void setupUi(QWidget *WallpaperClass)
    {
        if (WallpaperClass->objectName().isEmpty())
            WallpaperClass->setObjectName(QStringLiteral("WallpaperClass"));
        WallpaperClass->resize(523, 354);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Wallpaper/Resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        WallpaperClass->setWindowIcon(icon);
        horizontalLayout = new QHBoxLayout(WallpaperClass);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(0);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        label = new QLabel(WallpaperClass);
        label->setObjectName(QStringLiteral("label"));

        mainLayout->addWidget(label);


        horizontalLayout->addLayout(mainLayout);


        retranslateUi(WallpaperClass);

        QMetaObject::connectSlotsByName(WallpaperClass);
    } // setupUi

    void retranslateUi(QWidget *WallpaperClass)
    {
        WallpaperClass->setWindowTitle(QApplication::translate("WallpaperClass", "Wallpaper", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WallpaperClass: public Ui_WallpaperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WALLPAPER_H
