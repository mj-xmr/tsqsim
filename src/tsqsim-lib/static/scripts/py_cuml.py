import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

import cudf
from cuml.cluster import DBSCAN

# Create and populate a GPU DataFrame
gdf_float = cudf.DataFrame()
gdf_float['0'] = [1.0, 2.0, 5.0]
gdf_float['1'] = [4.0, 2.0, 1.0]
gdf_float['2'] = [4.0, 2.0, 1.0]

# Setup and fit clusters
dbscan_float = DBSCAN(eps=1.0, min_samples=1)
dbscan_float.fit(gdf_float)

print(dbscan_float.labels_)


def pred_function(dtaExp, lagg):
    series = TimeSeries.from_dataframe(dtaExp)
    model = ARIMA(p=lagg, d=0, trend='c')
    model.fit(series)
    pred = model.predict(n=1)
    return pred.pd_series()

#pred_mov, pred_mov_lst = moving_window(pred_function)
#store(pred_mov_lst)
#plot(pred_mov)
