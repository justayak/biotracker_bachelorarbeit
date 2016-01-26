from biotracker import (
    Signals,
    Helper,
    Button,
    run_client
)
import resource
import time
import numpy as np
from scipy import signal

Mat = None
Kx = np.array([[-1,0,1],[-2,0,2],[-1,0,1]])
Ky = Kx.T
KiBs = np.zeros((305,1), dtype=np.float64)
Elap = np.zeros((305,1), dtype=int)
show_x = True
last_elapsed = 0

def inc_time(frame):
    global Elap, last_elapsed
    if frame > 0:
        last_elap = Elap[frame-1]
        current_el = int(time.time() * 1000) - last_elapsed
        Elap[frame] = last_elap + current_el
    last_elapsed = int(time.time() * 1000)

def track(frame, M):
    global Mat, Kx, Ky, show_x, KiBs, Elap
    M = Helper.rgb2gray(M)
    direc = "y"
    if show_x:
        direc = "x"
    Signals.notify_gui(
        "frame:" + str(frame) + " M:" + str(M.shape) + " dir:" + direc)
    if show_x:
        Mat = signal.convolve2d(M, Kx, boundary='symm', mode='same')
    else:
        Mat = signal.convolve2d(M, Ky, boundary='symm', mode='same')

    inc_time(frame)
    KiBs[frame] = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss

def paint(frame):
    global Mat
    return Mat


def paint_overlay(qpainter):
    pass


def toggle_xy():
    global show_x
    show_x = not show_x


def request_widgets():
    return []
    #return [
    #    Button("Toggle X/Y", toggle_xy)
    #]


def shutdown():
    global KiBs, Elap
    with open("mem", 'a') as out:
        for i in range(0, 305):
            out.write(str(Elap[i,0]) + "," + str(KiBs[i,0]) + '\n') 


run_client(
    track,
    paint,
    paint_overlay,
    shutdown,
    request_widgets=request_widgets)
