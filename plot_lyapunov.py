import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt(
    "results/lyapunov_exponents_group4.dat",
    skiprows=1
)

# Case psi = 1
lambda1 = data[:, 3]
lambda2 = data[:, 4]
lambda3 = data[:, 5]
t = data[:, 9]

plt.figure(figsize=(10, 6))

plt.plot(t, lambda1, label=r"$\lambda_1$")
plt.plot(t, lambda2, label=r"$\lambda_2$")
plt.plot(t, lambda3, label=r"$\lambda_3$")

plt.xlabel("Time")
plt.ylabel("Lyapunov exponent")
plt.title(r"Convergence of the Lyapunov exponents ($\psi = 1$)")
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig("results/lyapunov_exponents_convergence_psi1.png", dpi=300)
plt.show()
