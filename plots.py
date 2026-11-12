import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np

# ============================================================
# Читаем данные
# ============================================================

df = pd.read_csv("summary.csv", dtype={"q": str, "k": int})
df["p_theor"] = df["p_theor"].astype(float)
df["P_obs"]   = df["P_obs"].astype(float)
df["P_actual"] = df["P_actual"].astype(float)
df["R_avg"]   = df["R_avg"].astype(float)
df["N"]       = df["N"].astype(int)

# ============================================================
# ГРАФИК 1: P_target vs P_actual vs P_obs — гистограмма по k
# ============================================================

g = df.groupby("k").agg(
    p_mean=("p_theor", "mean"),
    P_actual_mean=("P_actual", "mean"),
    P_obs_mean=("P_obs", "mean"),
).reset_index()

fig, ax = plt.subplots(figsize=(14, 6))

x = np.arange(len(g))
w = 0.27
P_target = 0.95

ax.bar(x - w, [P_target] * len(g), w,
       label="P_target = 0.95 (цель)",
       color="red", alpha=0.8, edgecolor="black")

ax.bar(x, g["P_actual_mean"], w,
       label="P_actual = 1−(1−p)^N (теория)",
       color="steelblue", edgecolor="black")

ax.bar(x + w, g["P_obs_mean"], w,
       label="P_obs (эксперимент)",
       color="orange", edgecolor="black")

labels = [f"k={int(k)}\np≈{p:.2f}"
          for k, p in zip(g["k"], g["p_mean"])]
ax.set_xticks(x)
ax.set_xticklabels(labels, fontsize=9)

ax.axhline(0.95, color="red", linestyle="--", linewidth=1.2, alpha=0.6)
ax.set_ylabel("Вероятность успеха")
ax.set_ylim(0.90, 1.01)
ax.set_title("Три вероятности для разных k (среднее по 5 trial, M=1000)")
ax.legend(loc="lower right", fontsize=10)
ax.grid(alpha=0.3, axis="y")

plt.tight_layout()
plt.savefig("P_vs_p.png", dpi=150, bbox_inches="tight")
plt.close()
print("saved P_vs_p.png")

# ============================================================
# ГРАФИК 2: R_avg vs p, теоретическая кривая 1/p
# ============================================================

fig, ax = plt.subplots(figsize=(10, 6))

ax.scatter(df["p_theor"], df["R_avg"],
           s=60, marker="o", color="orange",
           label="R_avg (эксперимент)", zorder=3)

p_range = np.linspace(df["p_theor"].min(), df["p_theor"].max(), 200)
ax.plot(p_range, 1.0 / p_range, "r-", linewidth=2,
        label="R_avg = 1/p (теория)")

ax.set_xlabel("p = φ(q)/q")
ax.set_ylabel("Среднее число раундов R_avg")
ax.set_title("Среднее число раундов vs p\n(подтверждение геометрического распределения)")
ax.legend()
ax.grid(alpha=0.3)

plt.tight_layout()
plt.savefig("R_avg_vs_p.png", dpi=150, bbox_inches="tight")
plt.close()
print("saved R_avg_vs_p.png")

# ============================================================
# ГРАФИК 3: гистограммы N(R) для разных k
# ============================================================

hist = pd.read_csv("rounds.csv", dtype={"k": int, "trial": int})
hist["R"] = hist["R"].astype(int)
hist["N_R"] = hist["N_R"].astype(int)

ks_to_show = [1, 2, 4, 6, 8]

fig, axes = plt.subplots(1, len(ks_to_show), figsize=(18, 4))

for ax, k in zip(axes, ks_to_show):
    sub = hist[(hist["k"] == k) & (hist["trial"] == 0)]
    if sub.empty:
        ax.set_visible(False)
        continue

    p_k = df[(df["k"] == k) & (df["trial"] == 0)]["p_theor"].values
    p_k = p_k[0] if len(p_k) else 0.5

    ax.bar(sub["R"], sub["N_R"], color="steelblue",
           edgecolor="black", width=0.7, label="эксперимент")

    R_theor = np.arange(1, sub["R"].max() + 1)
    M = 1000
    ax.plot(R_theor, M * (1 - p_k) ** (R_theor - 1) * p_k,
            "ro-", markersize=5, label=f"теория (p={p_k:.2f})")

    ax.set_xlabel("R — номер раунда успеха")
    ax.set_ylabel("Запусков, шт.")
    ax.set_title(f"k = {k}, p = {p_k:.2f}")
    ax.legend(fontsize=8)
    ax.grid(alpha=0.3)

plt.suptitle("Распределение числа раундов N(R) при разной структуре q",
             fontsize=13, y=1.02)
plt.tight_layout()
plt.savefig("hist_by_k.png", dpi=150, bbox_inches="tight")
plt.close()
print("saved hist_by_k.png")