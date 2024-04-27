import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from scipy.stats import linregress

# Dados fornecidos pelo problema
E = np.array([0.07, 0.18, 0.35, 0.45, 0.69])  # energia crítica (E) em joules
D = np.array([4.9, 6.3, 7.7, 8.1, 9.2])       # diâmetro da cratera (D) em cm

# Convertendo o diâmetro para metros
D = D / 100

# Realizando um ajuste linear entre o logaritmo da energia e o logaritmo do diâmetro
# A relação esperada é D = k * E^y, onde y é o expoente.
# Tomando o logaritmo natural dos dois lados da equação, temos ln(D) = y * ln(E) + ln(k)
# Portanto, o coeficiente angular do nosso ajuste linear será o nosso expoente da expressão original.
log_E = np.log(E)
log_D = np.log(D)

incertezas_D = np.array([0.3, 0.3, 0.4, 0.4, 0.4]) / 100  # Convertendo para metros

# Definindo a função que queremos ajustar, neste caso, uma linha reta em log-log
def func(log_E, y, ln_k):
    return y * log_E + ln_k

# Realizando o ajuste linear ponderado
popt, pcov = curve_fit(func, log_E, log_D, sigma=incertezas_D, absolute_sigma=True)

# Extraímos os parâmetros do ajuste e a incerteza em 'y'
y_estimate, ln_k_estimate = popt
y_uncertainty = np.sqrt(np.diag(pcov))[0]

# Realizamos o plot incluindo as incertezas nos diâmetros
plt.errorbar(log_E, log_D, yerr=incertezas_D, fmt='o', label='Dados com Incertezas')
plt.plot(log_E, func(log_E, *popt), 'r-', label=f'Linha de Ajuste: y={y_estimate:.2f}')

# Adicionando títulos, rótulos e legenda
plt.xlabel('log(Energia) [log(J)]')
plt.ylabel('log(Diâmetro) [log(m)]')
plt.legend()
plt.title('Ajuste Linear Ponderado para o Expoente da Relação entre Energia e Diâmetro')
plt.show()

# Retornamos a estimativa do expoente e sua incerteza
print(y_estimate, y_uncertainty)
