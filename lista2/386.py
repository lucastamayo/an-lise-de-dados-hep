from scipy.stats import norm

# Média e desvio
media = 170  # em cm
desvio_padrao = 5  # em cm

# O percentil para os 10% mais altos
percentil_90 = 0.90

# Usando a função PPF para encontrar a altura correspondente ao percentil 90
altura_percentil_90 = norm.ppf(percentil_90, media, desvio_padrao)

print(f"A altura acima da qual estão os 10% mais altos é: {altura_percentil_90} cm")