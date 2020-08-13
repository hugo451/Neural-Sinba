# -*- coding: utf-8 -*-
"""
Created on Mon Jul 22 20:12:55 2019

Description: Implementação de Rede Neural para robô cão guia

@author: Andre
"""
import pandas as pd
import numpy as np
from keras.models import Sequential
from keras.layers import Dense

entrada = np.array([[32.5, 45, 100],
                     [50.2, 24,105.2],
                     [70.25,34,2.23],
                     [69.23,123,23],[2,45.20,13]
                     ,[143.45, 37.2,69.2]
                     ,[236.49,103.50,209.68]
                     ,[400,209.3, 62.19]
                     ,[12.21, 37.9,47.14]
                     ,[23.54, 200.15, 33.8]
                     ,[65.34, 63.26, 67.12]
                     ,[24.56, 203.4, 12.3],
                     [23.67, 34.28, 67.30],
                     [45.20, 84.68, 35.20],
                     [400, 230.54, 308.23],
                     [259.43, 19.2, 34.5],
                     [327.30, 236.34, 54.28],
                     [35.2, 45.1, 29.0],
                     [23.4, 56.78, 20.40],
                     [125.56, 23.00, 40.30],
                     [45.57, 87.34,67.30],
                     [79.24, 32.40, 99.20],
                     [23.40, 25.60, 35.40],
                     [43.30, 22.40, 12.5],
                     [400, 39.58, 389.3],
                     [230, 340.20, 389.40],
                     [56.79, 345.22, 45.2],
                     [43.28, 56.73, 61.29],
                     [56.24, 31.12, 75.37]])
saida = np.array([[0, 0, 1],
                [0, 0, 1],
                [1, 0, 0],
                [0, 1, 0],
                [0, 1, 0],
                [1, 0, 0],
                [1, 0, 0],
                [1, 0, 0],
                [0, 0, 1],
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 0],
                [1, 0, 0],
                [1, 0, 0],
                [1, 0, 0],
                [0, 1, 0],
                [0, 1, 0],
                [1, 0, 0],
                [0, 1, 0],
                [0, 0, 1],
                [0, 0, 1],
                [1, 0, 0],
                [1, 0, 0],
                [0, 0, 1],
                [0, 1, 0],
                [0, 0, 1],
                [0, 0, 1]])



rede_neural = Sequential()

rede_neural.add(Dense(units = 3, activation = 'softmax', input_dim = 3))
rede_neural.add(Dense(units = 3, activation = 'softmax'))
rede_neural.add(Dense(units = 3, activation = 'sigmoid'))

rede_neural.compile(optimizer = 'adam', loss = 'mse', metrics = ['accuracy'])

rede_neural.fit(x = entrada, y = saida, epochs = 10000)



score = rede_neural.evaluate(x = entrada, y = saida)

rede_neural.predict(np.array([[31, 220.34, 206]]))

a = rede_neural.get_weights()

print(a)
