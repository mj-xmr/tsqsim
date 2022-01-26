# -*- coding: utf-8 -*-
"""
Created on Fri Oct  3 15:30:42 2014

@author: enjo
"""

#from pylab import *
#import matplotlib
#matplotlib.use('Agg')

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
#from pandas.plotting import register_matplotlib_converters
#from statsmodels.graphics.tsaplots import plot_acf, plot_pacf
#register_matplotlib_converters()
from statsmodels.tsa.stattools import acf, pacf

        
def plotACF(data, lags, title):
    obj = pd.plotting.autocorrelation_plot(data)
    obj.set_xlim([0, lags])
    obj.set_title("Autocorr. (" + str(lags) + ") " + title)
    plt.show()
    
def plotPACF(data, lags, title):
    pacf_vals = pacf(data)
    #fig = plt.figure()
    y = pacf_vals#[:lags]
    length = len(y)
    if lags > length:
        lags = length
    x = list(range(lags))
    print(len(x))
    print(length)
    plt.bar(x, y)
    plt.ylim([-1, 1])
    plt.grid()
    plt.xlabel("Lag")
    plt.ylabel("Autocorrelation")
    plt.title("Partial Autocorr. (" + str(lags) + ") " + title)
    plt.show()
        
def demo():
    #df_ice_cream = pd.read_csv('ice_cream.csv')
    #rename columns to something more understandable
    #df_ice_cream.rename(columns={'DATE':'date', 'IPN31152N':'production'}, inplace=True)
    #convert date column to datetime type
    #df_ice_cream['date'] = pd.to_datetime(df_ice_cream.date)

    #set date as index
    #df_ice_cream.set_index('date', inplace=True)

    #just get data from 2010 onwards
    #start_date = pd.to_datetime('2010-01-01')
    #show result
    
    #df_ice_cream = df_ice_cream[start_date:]
    #print(df_ice_cream.head())
    #acf_plot = plot_acf(df_ice_cream.production, lags=100)

    a = [1, 2, 3, 4, 5, 6]
    plotACF(a, 4, "demo")
    plotPACF(a, 4, "demo")
    #obj = pd.plotting.autocorrelation_plot(df_ice_cream.production)
    #plt.show()

    
    #acf_plot = plot_acf(a, lags=5)
    #acf_plot.show()

#demo()
