import numpy as np
import matplotlib.pyplot as plt

dimension_data = np.loadtxt("results/lyapunov_dimension.dat", skiprows=1)

dimensioni = dimension_data[:, :15]

p = np.array([
    0.5,
    0.555556,
    0.625,
    0.666667,
    0.769231,
    0.8,
    0.806452,
    0.813008,
    0.833333,
    0.847458,
    0.862069,
    0.877193,
    0.909091,
    1.0,
    1.11111
])

# Select four representative cases
selected = [0, 4, 9, 14]

n = np.arange(len(dimensioni))

plt.figure(figsize=(10, 6))

for i in selected:
    plt.plot(n, dimensioni[:, i], label=f"p = {p[i]:.3f}")

plt.xlabel("Measurement")
plt.ylabel("Lyapunov dimension")
plt.title("Convergence of the Lyapunov dimension")
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig("results/dimensioni_lyapunov.png", dpi=300)
plt.show()
