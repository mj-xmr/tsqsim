# -*- coding: utf-8 -*-
"""
Created on Fri Oct  3 15:30:42 2014

@author: enjo
"""

#from pylab import *
#import matplotlib
#matplotlib.use('Agg')
import matplotlib.pyplot as plt

        
class PlotLine:
    def __init__(self):
        self._fig, self._ax = plt.subplots(1, sharex=True)
        self.width = 6
                       
    def addData(self, arg, data):
        self._ax.plot(arg, data)

    def addData1(self, data, colour):
        self._ax.plot(data, color=colour)
        
    def setupFigure(self, title, legend):
        self._ax.grid()
        self._ax.set_title(title)
        self._ax.legend(legend)

    def show(self):
        plt.show()
        
    def close(self):
        plt.close(self._fig)
        
    def save(self, filename):
        self.setupFigure()
        self._fig.set_size_inches(self.width,6)
        self._fig.savefig(filename, bbox_inches='tight', pad_inches=0, dpi=100)

def demo():
    a = [1, 2, 3]
    lines = PlotLine()
    lines.addData1(a, "Blue")
    lines.setupFigure('demo', ["Legend"])
    lines.show()

#demo()
