import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import binom

#Letras A e B da questão

n = 15  # número de questões
p = 1/4  # probabilidade de acertar cada questão

# gerando os valores de x
x = np.arange(0, n+1)

# probabilidade binomial para x
pmf_values = binom.pmf(x, n, p)

# Criando histograma
plt.bar(x, pmf_values, color='blue', alpha=0.7)
plt.title('Histograma da Distribuição Binomial para 15 Questões')
plt.xlabel('Número de Acertos')
plt.ylabel('Probabilidade')
plt.xticks(x)
plt.grid(axis='y', alpha=0.75)

# Mostrando o gráfico
plt.show()

#Para a Letra C, somaremos as probabilidades dos alunos acertarem 0, 1 e 2 questões e subtrairemos esse valor de 1,
# de forma a obter a probabilidade de acertarem pelo menos 3 questões
# após isso, multiplicaremos esse valor por 1000 (número de alunos que realizarão a prova).
probabilidade_0_1_2 = binom.pmf(0, 15, 0.25) + binom.pmf(1, 15, 0.25) + binom.pmf(2, 15, 0.25)

prob_pelo_menos_3 = 1 - probabilidade_0_1_2

media_alunos_acertam_pelo_menos_3 = prob_pelo_menos_3 * 1000

print("em média, dentre 1000 alunos,", media_alunos_acertam_pelo_menos_3, "acertarão pelo menos 3 questões")