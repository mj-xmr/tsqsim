import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


import statsmodels.api as sm
from statsmodels.tsa.arima.model import ARIMA

#dta.plot(figsize=(12,4));
#plt.show()

#print(arma_mod20.params)

#fig = plt.figure(figsize=(12,8))
#ax1 = fig.add_subplot(211)
#fig = sm.graphics.tsa.plot_acf(dta.values.squeeze(), lags=40, ax=ax1)
#ax2 = fig.add_subplot(212)
#fig = sm.graphics.tsa.plot_pacf(dta, lags=40, ax=ax2)
#plt.show()

def pred_function(dtaExp, lagg):
    model = sm.tsa.statespace.SARIMAX(dtaExp, order=(lagg,0,0), trend='c').fit(disp=False)
    #model = ARIMA(dtaExp, order=(lagggg,0,0), trend='c').fit()
    pred = model.predict() # TODO: , dynamic=True and longer end for longer horizon
    return pred

pred_mov, pred_mov_lst = moving_window(pred_function)
store(pred_mov_lst)
#plot(pred_mov)
