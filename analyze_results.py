import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results.csv")

# Serial runtime als Referenz
t_serial = df[df["version"] == "serial"]["runtime"].iloc[0]

df["speedup"] = t_serial / df["runtime"]
df["efficiency"] = df["speedup"] / df["processes"]

print(df)

df.to_csv("results_analyzed.csv", index=False)

# Nur MPI-Daten für Skalierungsplots
mpi_df = df[df["version"] == "mpi"]

plt.figure()
plt.plot(df["processes"], df["runtime"], marker="o")
plt.xlabel("Number of processes")
plt.ylabel("Runtime (s)")
plt.title("Runtime Comparison")
plt.grid(True)
plt.savefig("runtime.png")

plt.figure()
plt.plot(
    mpi_df["processes"],
    mpi_df["speedup"],
    marker="o",
    label="Measured speedup"
)

plt.plot(
    mpi_df["processes"],
    mpi_df["processes"],
    marker="x",
    label="Ideal speedup"
)

plt.xlabel("Number of processes")
plt.ylabel("Speedup")
plt.title("MPI Speedup")
plt.legend()
plt.grid(True)
plt.savefig("speedup.png")

plt.figure()
plt.plot(
    mpi_df["processes"],
    mpi_df["efficiency"] * 100,
    marker="o"
)

plt.xlabel("Number of processes")
plt.ylabel("Efficiency (%)")
plt.title("MPI Efficiency")
plt.grid(True)
plt.savefig("efficiency.png")

print("\nAnalysis complete.")
print("Generated:")
print("- results_analyzed.csv")
print("- runtime.png")
print("- speedup.png")
print("- efficiency.png")