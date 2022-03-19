import numpy as np
import pandas as pd
#from scipy import stats
import matplotlib.pyplot as plt

dta = pd.DataFrame(dat)

lagggg = lag

def moving_window(pred_function):
    end = len(dat)
    #strt = int(len(dat)/4)
    if IS_MOVING_WINDOW:
        strt = 30
    else:
        strt = end
    lst = [0] * strt
    for start in range(strt, len(dat)):
        print(start, "/", end)
        expanding = dat[:start]
        dtaExp = pd.DataFrame(expanding)
        pred_vec = pred_function(dtaExp, lagggg)
        lst.append(pred_vec.iloc[-1])
    dta_pred = pd.DataFrame(lst)
    return dta_pred, lst

def store(pred):
    #pred_list = pred.to_list()
    pred_list = pred
    fname = OUT_FILE
    print("Writing" , len(pred_list), "elements to", fname)
    with open(fname, 'w') as fout:
        for val in pred_list:
            fout.write(str(val) + ' ')
        

def plot(pred):
    fig, ax = plt.subplots(figsize=(12, 8))
    dta.plot(ax=ax)  
    pred.plot(ax=ax, style='g');
    plt.grid()
    plt.show()

#pred_mov, pred_mov_lst = moving_window(pred_function)
#store(pred_mov_lst)
#plot(pred_mov)
