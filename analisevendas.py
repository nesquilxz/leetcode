import pandas as pd

# criando conjunto de dados
dados = {
    "produto": ["Mouse", "Teclado", "Monitor", "Mouse", "Teclado", "Monitor"],
    "quantidade": [5, 3, 2, 4, 2, 1],
    "preco_unitario": [50, 120, 900, 50, 120, 900]
}

df = pd.DataFrame(dados)

# nova coluna de faturamento
df["faturamento"] = df["quantidade"] * df["preco_unitario"]

print("Tabela de vendas:\n")
print(df)

# faturamento total
faturamento_total = df["faturamento"].sum()
print("\nFaturamento total:", faturamento_total)

# faturamento por produto
faturamento_por_produto = df.groupby("produto")["faturamento"].sum()

print("\nFaturamento por produto:")
print(faturamento_por_produto)
