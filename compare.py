import re
import numpy as np
import matplotlib.pyplot as plt

# Fonction mise à jour : extrait MIN + MED (per inner-iter) et GOOD STABILITY
def extract_combined_cycles_and_stability(content):
    # Regex pour les valeurs entre parenthèses
    min_pattern = r"MIN\s+\d+\s+RDTSC-cycles\s+\(([\d.]+)\s+per inner-iter\)"
    med_pattern = r"MED\s+\d+\s+RDTSC-cycles\s+\(([\d.]+)\s+per inner-iter\)"
    stability_pattern = r"GOOD STABILITY:\s+([\d.]+)\s+%"

    min_values = [float(m) for m in re.findall(min_pattern, content)]
    med_values = [float(m) for m in re.findall(med_pattern, content)]
    stability_values = [float(s) for s in re.findall(stability_pattern, content)]

    # Combine MIN + MED pour les cycles par inner-iter
    combined_cycles = min_values + med_values

    return combined_cycles, stability_values

# Génère le graphique
def generate_graph(files):
    cycles_per_iteration = []
    stability = []
    version_names = []

    for file_path in files:
        with open(file_path, 'r') as file:
            content = file.read()

        combined_cycles, stability_vals = extract_combined_cycles_and_stability(content)
        version_name = file_path.split('/')[-1].split('.')[0]

        # Ajout des médianes
        cycles_per_iteration.append(np.median(combined_cycles))
        stability.append(np.median(stability_vals))
        version_names.append(version_name)

    # Création du plot
    fig, ax1 = plt.subplots(figsize=(10, 6))

    # Barres rouges
    ax1.bar(version_names, cycles_per_iteration, color='tomato', alpha=0.8)
    ax1.set_xlabel('Version', fontsize=14)
    ax1.set_ylabel('Cycles par itération', color='tomato', fontsize=14)
    ax1.tick_params(axis='y', labelcolor='tomato')

    # Ligne verte
    ax2 = ax1.twinx()
    ax2.plot(version_names, stability, color='yellowgreen', marker='o', linewidth=2)
    ax2.set_ylabel('Stabilité (%)', color='yellowgreen', fontsize=14)
    ax2.tick_params(axis='y', labelcolor='yellowgreen')

    plt.title('Cycles par itération vs Stabilité des différentes versions', fontsize=16)
    fig.tight_layout()
    plt.show()

# Liste des fichiers à analyser
files = ["opt_fast", "opt1_fast","opt2_fast", "opt3_fast"]
generate_graph(files)
