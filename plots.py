import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

# ============================================================
# ГРАФИК 1: гистограмма N(R) — распределение числа раундов
# ============================================================

df = pd.read_csv("rounds.csv", dtype={"q": str, "bits": int})

configs = [
    (32,  "2",           "Модуль 32 бита, порядок q = 2"),
    (32,  "82886",       "Модуль 32 бита, порядок q = 2·p₁"),
    (32,  "3251369122",  "Модуль 32 бита, порядок q = m−1"),
    (64,  "2",           "Модуль 64 бита, порядок q = 2"),
    (128, "2",           "Модуль 128 бит, порядок q = 2"),
]

fig, axes = plt.subplots(2, 3, figsize=(15, 8))
axes = axes.flatten()

M = 1000
p = 0.5

for i, (bits, q, title) in enumerate(configs):
    ax = axes[i]
    sub = df[(df["bits"] == bits) & (df["q"] == q)]
    if sub.empty:
        ax.set_visible(False)
        print(f"  [пусто] {title}")
        continue

    ax.bar(sub["R"], sub["N_R"], color="steelblue",
           edgecolor="black", label="Результат эксперимента", width=0.7)

    R = np.arange(1, sub["R"].max() + 1)
    ax.plot(R, M * (1 - p) ** (R - 1) * p,
            "ro-", markersize=5, label="Теоретически ожидаемое")

    ax.set_xlabel("Номер попытки (раунда), на которой найден ответ")
    ax.set_ylabel("Запусков, шт.")
    ax.set_title(title)
    ax.legend(fontsize=8)
    ax.grid(alpha=0.3)

axes[-1].set_visible(False)

plt.suptitle("Сколько попыток нужно алгоритму, чтобы найти число x", fontsize=13)
plt.tight_layout()
plt.savefig("hist_rounds.png", dpi=150, bbox_inches="tight")
plt.close()
print("saved hist_rounds.png")

# ============================================================
# ГРАФИК 2: P_actual vs P_obs
# ============================================================

summ = pd.read_csv("summary.csv", dtype={"q": str, "bits": int})
summ["label"] = (summ["bits"].astype(str)
                 + " бит\nq=" + summ["q"])

fig, ax = plt.subplots(figsize=(16, 8))
x = np.arange(len(summ))
w = 0.35

ax.bar(x - w/2, summ["P_actual"], w, label="Ожидаемая вероятность по теории",
       color="steelblue", edgecolor="black")
ax.bar(x + w/2, summ["P_obs"],    w, label="Полученная вероятность в эксперименте",
       color="orange",    edgecolor="black")

ax.axhline(0.95, color="red", linestyle="--", label="Целевая вероятность 95%")

ax.set_xticks(x)
ax.set_xticklabels(summ["label"], rotation=90, ha="center", fontsize=6)
ax.set_ylabel("Вероятность успеха")
ax.set_ylim(0.85, 1.01)
ax.set_title("Совпадает ли эксперимент с теорией?")
ax.legend(loc="lower right")
ax.grid(alpha=0.3, axis="y")

plt.tight_layout()
plt.savefig("P_compare.png", dpi=150, bbox_inches="tight")
plt.close()
print("saved P_compare.png")