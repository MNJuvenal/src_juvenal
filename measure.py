import subprocess
import re
import numpy as np
import matplotlib.pyplot as plt

# Génère les 10 points par zone de cache
def get_n_values():
    regions = [
        (44, 60),     # L1
        (89, 161),    # L2
        (255, 723),   # L3
        (1447, 3620)  # RAM
    ]
    n_values = []
    for start, end in regions:
        points = np.linspace(start, end, 10, dtype=int)
        n_values.extend(points)
    return n_values

# Extraction des cycles par inner-iter
def extract_cycles(output):
    min_pattern = r"MIN\s+\d+\s+RDTSC-cycles\s+\(([\d.]+)\s+per inner-iter\)"
    med_pattern = r"MED\s+\d+\s+RDTSC-cycles\s+\(([\d.]+)\s+per inner-iter\)"
    min_vals = [float(m) for m in re.findall(min_pattern, output)]
    med_vals = [float(m) for m in re.findall(med_pattern, output)]
    return min_vals + med_vals

# Exécution de ./measure
def run_and_collect():
    all_n = get_n_values()
    x_vals, y_vals = [], []

    for n in all_n:
        print(f"Mesure pour n = {n}")
        try:
            result = subprocess.run(
                ["./measure", str(n), "5", "200"],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True,
                check=True
            )
            output = result.stdout
            cycles = extract_cycles(output)

            if cycles:
                x_vals.append(n)
                y_vals.append(np.median(cycles))
            else:
                print(f"Aucune donnée pour n = {n}")
        except subprocess.CalledProcessError as e:
            print(f"Erreur à n = {n}: {e}")
    return x_vals, y_vals

# Tracer avec fond coloré par zone de cache
def plot(x, y):
    plt.figure(figsize=(12, 6))

    # Zones colorées
    cache_zones = {
        "L1": ((44, 60), '#ffcccc'),
        "L2": ((89, 161), '#ccffcc'),
        "L3": ((255, 723), '#ccccff'),
        "RAM": ((1447, 3620), '#ffffcc')
    }

    for label, (xrange, color) in cache_zones.items():
        plt.axvspan(xrange[0], xrange[1], color=color, alpha=0.3, label=label)

    # Courbe des cycles
    plt.plot(x, y, marker='o', color='black', linewidth=2)

    plt.xlabel('n (taille mesurée)', fontsize=14)
    plt.ylabel('Cycles par itération (médiane)', fontsize=14)
    plt.title('Cycles par itération selon la taille (n)', fontsize=16)
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

# Main
if __name__ == "__main__":
    n_vals, cycle_vals = run_and_collect()
    plot(n_vals, cycle_vals)

