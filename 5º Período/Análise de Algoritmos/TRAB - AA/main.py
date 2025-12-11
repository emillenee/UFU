from mochila import mochila, mochila_memorizacao, mochila_PD, mochila_PD_com_solucao
from gerador_dados import gerar_dados_mochila, carregar_dados_mochila, medir_tempo_execucao
import matplotlib.pyplot as plt

def rodar_teste(arquivo):
    capacidade, valores, pesos = carregar_dados_mochila(arquivo)

    print("\n==========================================================")
    print(f" Teste com {len(valores)} itens | Capacidade: {capacidade}")
    print("===========================================================")

    funcoes = [mochila, mochila_PD, mochila_PD_com_solucao]

    for func in funcoes:
        resultado, tempo = medir_tempo_execucao(func, capacidade, valores, pesos)
        
        if isinstance(resultado, tuple):
            custo, itens = resultado
            print(f"{func.__name__:>25} -> Resultado: {custo:3d} | Itens: {itens} | Tempo: {tempo:.6f}s")
        else:
            print(f"{func.__name__:>25} -> Resultado: {resultado:3d} | Tempo: {tempo:.6f}s")
            

def rodar_varios_testes():
    tamanhos = [5000, 10000, 15000, 20000, 25000]
    tempos = { "recursiva": [], "iterativa": [] }

    for n in tamanhos:
        gerar_dados_mochila(num_itens=n, capacidade=1000, arquivo="dados_mochila.json", seed=42)
        capacidade, valores, pesos = carregar_dados_mochila("dados_mochila.json")

        _, t1 = medir_tempo_execucao(mochila, capacidade, valores, pesos)
        _, t2 = medir_tempo_execucao(mochila_PD, capacidade, valores, pesos)

        tempos["recursiva"].append(t1)
        tempos["iterativa"].append(t2)

    # Gerar gráfico
    plt.plot(tamanhos, tempos["recursiva"], label="Recursiva sem memo")
    plt.plot(tamanhos, tempos["iterativa"], label="PD iterativa")
    plt.xlabel("Número de itens")
    plt.ylabel("Tempo (s)")
    plt.title("Comparação de desempenho - Mochila 0/1")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    #Alterar a quantidade de itens e a capacidade
    #gerar_dados_mochila(num_itens=5, capacidade=10, arquivo="dados_mochila.json", seed=42)
    rodar_teste("dados_mochila.json")
    #rodar_varios_testes()
