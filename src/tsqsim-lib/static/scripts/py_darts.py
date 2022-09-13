import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from darts import TimeSeries
from darts.models import ARIMA


def pred_function(dtaExp, lagg):
    series = TimeSeries.from_dataframe(dtaExp)
    model = ARIMA(p=lagg, d=0, trend='c')
    model.fit(series)
    pred = model.predict(n=1)
    return pred.pd_series()

pred_mov, pred_mov_lst = moving_window(pred_function)
store(pred_mov_lst)
#plot(pred_mov)
