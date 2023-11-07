import matplotlib.pyplot as plt

# Dados dos algoritmos de ordenação para diferentes tamanhos de vetor
algoritmos = ['Selection Sort', 'Bubble Sort', 'Insertion Sort', 'Shell Sort', 'Merge Sort', 'Drop Sort', 'Drop Sort (Recente Memory)', 'Drop Sort (Double Comparison)']
comparacoes_10 = [45, 35, 9, 22, 194, 9, 2, 9]  # Número de comparações para vetor de 10 elementos
comparacoes_100 = [4950, 4929, 99, 503, 35790, 99, 45 ,99]  # Número de comparações para vetor de 100 elementos
comparacoes_1000 = [499500, 499409, 999, 8006, 5047658, 999, 516, 999]  # Número de comparações para vetor de 1000 elementos

# Lista de cores para as barras em hexadecimal
cores = ['#ffb972', '#ffda5f', '#002475', '#006dae', '#00cce8']

# Criando subplots para cada tamanho de vetor
fig, axs = plt.subplots(1, 3, figsize=(18, 6))

# Gráfico para vetor de 10 elementos
bars_10 = axs[0].bar(algoritmos, comparacoes_10, color=cores)
axs[0].set_ylabel('Número de Comparações')
axs[0].set_title('Vetor de 10 Elementos')
axs[0].tick_params(axis='x', rotation=45)

# Gráfico para vetor de 100 elementos
bars_100 = axs[1].bar(algoritmos, comparacoes_100, color=cores)
axs[1].set_ylabel('Número de Comparações')
axs[1].set_title('Vetor de 100 Elementos')
axs[1].tick_params(axis='x', rotation=45)

# Gráfico para vetor de 1000 elementos
bars_1000 = axs[2].bar(algoritmos, comparacoes_1000, color=cores)
axs[2].set_ylabel('Número de Comparações')
axs[2].set_title('Vetor de 1000 Elementos')
axs[2].tick_params(axis='x', rotation=45)

# Adicionando rótulos acima das barras
def autolabel(bars, ax):
    for bar in bars:
        height = bar.get_height()
        ax.annotate('{}'.format(height),
                    xy=(bar.get_x() + bar.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

autolabel(bars_10, axs[0])
autolabel(bars_100, axs[1])
autolabel(bars_1000, axs[2])

# Desativando a notação científica no eixo y
for ax in axs:
    ax.ticklabel_format(axis='y', style='plain')

# Ajustando o layout
plt.tight_layout()

# Exibindo os gráficos
plt.show()
