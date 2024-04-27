# Importando a biblioteca necessária para realizar os cálculos
import numpy as np
from scipy.stats import poisson
import matplotlib.pyplot as plt

# Frequências das contagens em cada intervalo, fornecidas no problema
frequencias = np.array([57, 203, 383, 525, 532, 408, 273, 139, 45, 27, 10, 4, 0, 2, 1])

# Número total de intervalos
N = 2608

# Contagens correspondem aos índices do array de frequências
contagens = np.arange(len(frequencias))

# Cálculo do número total de contagens
total_contagens = np.sum(frequencias * contagens)

# Cálculo do número médio de contagens por intervalo
numero_medio_contagens = total_contagens / N

frequencias_esperadas = poisson(mu=numero_medio_contagens).pmf(contagens) * N

# Exibe o número médio de contagens
print("Número médio de contagens por intervalo:", numero_medio_contagens)
print("O número de frequências esperadas é de:", frequencias_esperadas)


# Criando histogramas para comparar as frequências observadas e esperadas
plt.bar(contagens - 0.15, frequencias, width=0.3, label='Observado', align='center')
plt.bar(contagens + 0.15, frequencias_esperadas, width=0.3, label='Esperado (Poisson)', align='center')
plt.xlabel('Número de Contagens')
plt.ylabel('Frequência')
plt.title('Comparação das Frequências Observadas e Esperadas')
plt.legend()
plt.xticks(contagens)
plt.show()