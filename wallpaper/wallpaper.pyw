# -*- coding:utf-8 -*-
"""
@File      : wallpaper.pyw
@Software  : Wallpaper
@Time      : 2018/5/26 19:39
@Author    : Aaronvu
"""
import os
import sys
import cv2
import win32con
import win32gui
import win32api
from PIL import Image
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtCore import QTimer, Qt, QSize
from PyQt5.QtWidgets import QWidget, QLabel, QApplication, QVBoxLayout



class Wallpaper(QWidget):

    title = 'Wallpaper'

    def __init__(self, src):
        super(Wallpaper, self).__init__()
        self.setWindowFlags(Qt.FramelessWindowHint)
        self.capture = cv2.VideoCapture()
        self.src = src
        self.capture.open(src)
        self.label = QLabel()
        self.layout = QVBoxLayout()
        self.layout.setSpacing(0)
        self.layout.addWidget(self.label)
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.loop_play)
        self.timer.start(32)
        desk = QApplication.desktop()
        self.w = desk.width()
        self.h = desk.height()
        self.setMinimumSize(QSize(self.w, self.h))
        self.setMaximumSize(QSize(self.w, self.h))
        self.layout.setContentsMargins(0, 0, 0, 0)
        self.setLayout(self.layout)
        self.setWindowTitle(self.title)

    def loop_play(self):
        success, frame = self.capture.read()
        if success:
            height, width = frame.shape[:2]
            if frame.ndim == 3:
                rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            elif frame.ndim == 2:
                rgb = cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR)
            temp_image = QImage(rgb.flatten(), width, height, QImage.Format_RGB888)
            temp_pixmap = QPixmap.fromImage(temp_image)
            self.label.setPixmap(temp_pixmap)
        else:
            self.capture.release()
            self.capture.open(self.src)

    def set_dynamic_wallpaper(self):
        hwnd_0 = win32gui.FindWindow('Progman', None)
        hwnd_1 = win32gui.FindWindowEx(hwnd_0, None, 'SHELLDLL_DefView', None)
        hwnd_2 = win32gui.FindWindowEx(hwnd_1, None, 'SysListView32', None)
        self_hwnd = win32gui.FindWindow('Qt5QWindowIcon', self.title)
        win32gui.SetParent(self_hwnd, hwnd_1)
        win32gui.BringWindowToTop(hwnd_2)
        win32gui.SetWindowLong(hwnd_2, win32con.GWL_EXSTYLE,
                               win32gui.GetWindowLong(hwnd_2, win32con.GWL_EXSTYLE) | win32con.WS_EX_LAYERED)
        win32gui.SetLayeredWindowAttributes(hwnd_2, 0, 122, win32con.LWA_ALPHA)


    @staticmethod
    def set_wallpaper(path):
        img_dir = os.path.dirname(path)
        bmpImage = Image.open(path)
        new_bmp_path = os.path.join(img_dir, 'wallpaper.bmp')
        bmpImage.save(new_bmp_path, "BMP")
        Wallpaper.set_wallpaper_from_bmp(new_bmp_path)

    @staticmethod
    def set_wallpaper_from_bmp(bmp_path):
        reg_key = win32api.RegOpenKeyEx(win32con.HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, win32con.KEY_SET_VALUE)
        win32api.RegSetValueEx(reg_key, "WallpaperStyle", 0, win32con.REG_SZ, "2")
        win32api.RegSetValueEx(reg_key, "TileWallpaper", 0, win32con.REG_SZ, "0")
        win32gui.SystemParametersInfo(win32con.SPI_SETDESKWALLPAPER, bmp_path, win32con.SPIF_SENDWININICHANGE)


def main():
    app = QApplication(sys.argv)
    win = Wallpaper("./res/nuva.mov")
    win.show()
    path = os.path.dirname(os.path.realpath(__file__))
    path = os.path.join(path, 'res/wallpaper.jpg')
    Wallpaper.set_wallpaper(path)
    win.set_dynamic_wallpaper()
    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
