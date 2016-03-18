from biotracker import (
    Signals,
    Helper,
    Button,
    run_client
)
import numpy as np
from scipy import signal

Mat = None
Kx = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])


def track(frame, M):
    global Mat, Kx
    M = Helper.rgb2gray(M)
    Mat = signal.convolve2d(M, Kx, boundary='symm', mode='same')


def paint(frame):
    global Mat
    return Mat


def paint_overlay(qpainter):
    qpainter.setPen((255, 0, 0))
    qpainter.drawRect((100, 50, 100, 50))
    pass


def button_click():
    Signals.notify_gui("Button clicked")


def request_widgets():
    return [Button("Hello", button_click)]


def shutdown():
    pass

run_client(
    track,
    paint,
    paint_overlay,
    shutdown,
    request_widgets=request_widgets)
