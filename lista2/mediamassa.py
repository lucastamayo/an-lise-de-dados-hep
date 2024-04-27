#importando o numpy para iterar sobre as listas na definição da função
import numpy as np
#massas e erros do K+, D0, B0, B+ e Bc+ respectivamente
massas = np.array([493.677, 1880.66, 5279.34, 5279.66, 6274.47])
erros = np.array([0.013, 0.05, 0.12, 0.12, 0.32])


def formula_massa(x,y):
    pesos = 1 / y**2
    massa_ponderada = np.sum(x * pesos) / np.sum(pesos)
    erro_ponderado = np.sqrt(1 / np.sum(pesos))
    return massa_ponderada, erro_ponderado

massa_ponderada, erro_ponderado = formula_massa(massas, erros)
print("a massa ponderada é:", massa_ponderada)
print("O erro ponderado é:", erro_ponderado)