import matplotlib.pyplot as plt

# Substitua essas listas pelos seus dados reais
tamanhos_vetor = [10, 100, 500, 1000, 5000]
tempos_selection_sort = [tempo_10_selection, tempo_100_selection, tempo_500_selection, tempo_1000_selection, tempo_5000_selection]
tempos_insertion_sort = [tempo_10_insertion, tempo_100_insertion, tempo_500_insertion, tempo_1000_insertion, tempo_5000_insertion]
tempos_bubble_sort = [tempo_10_bubble, tempo_100_bubble, tempo_500_bubble, tempo_1000_bubble, tempo_5000_bubble]
tempos_shell_sort = [tempo_10_shell, tempo_100_shell, tempo_500_shell, tempo_1000_shell, tempo_5000_shell]
tempos_merge_sort = [tempo_10_merge, tempo_100_merge, tempo_500_merge, tempo_1000_merge, tempo_5000_merge]
tempos_quick_sort = [tempo_10_quick, tempo_100_quick, tempo_500_quick, tempo_1000_quick, tempo_5000_quick]
tempos_bead_sort = [tempo_10_bead, tempo_100_bead, tempo_500_bead, tempo_1000_bead, tempo_5000_bead]

# Criação do gráfico
plt.figure(figsize=(10, 6))

plt.plot(tamanhos_vetor, tempos_selection_sort, label='Selection Sort')
plt.plot(tamanhos_vetor, tempos_insertion_sort, label='Insertion Sort')
plt.plot(tamanhos_vetor, tempos_bubble_sort, label='Bubble Sort')
plt.plot(tamanhos_vetor, tempos_shell_sort, label='Shell Sort')
plt.plot(tamanhos_vetor, tempos_merge_sort, label='Merge Sort')
plt.plot(tamanhos_vetor, tempos_quick_sort, label='Quick Sort')
plt.plot(tamanhos_vetor, tempos_bead_sort, label='Bead Sort')

plt.xlabel('Tamanho do Vetor')
plt.ylabel('Tempo (s)')
plt.title('Desempenho dos Algoritmos de Ordenação')
plt.legend()
plt.grid(True)
plt.show()
