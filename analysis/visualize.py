import matplotlib.pyplot as plt
import subprocess
import re

def run_cache_sim(cache_size, ways):
    """Run the cache simulator and extract hit rate from output"""
    result = subprocess.run(
        ['./cache'],
        capture_output=True,
        text=True
    )
    return result.stdout

def parse_hit_rate(output, test_name):
    """Extract hit rate from simulator output"""
    lines = output.split('\n')
    in_test = False
    for line in lines:
        if test_name in line:
            in_test = True
        if in_test and 'Hit Rate' in line:
            rate = re.search(r'[\d.]+', line)
            if rate:
                return float(rate.group())
    return 0.0

# Data from Test 6
programs = ['Matrix Multiply', 'Linked List']
hit_rates = [62.11, 0.0]
miss_rates = [100 - r for r in hit_rates]

# Plot 1 - Hit rate comparison
fig, axes = plt.subplots(1, 2, figsize=(12, 5))

axes[0].bar(programs, hit_rates, color=['#2ecc71', '#e74c3c'])
axes[0].set_title('Cache Hit Rate by Access Pattern')
axes[0].set_ylabel('Hit Rate (%)')
axes[0].set_ylim(0, 100)
for i, v in enumerate(hit_rates):
    axes[0].text(i, v + 1, f'{v}%', ha='center', fontweight='bold')

# Plot 2 - Miss breakdown for matrix multiply
miss_types = ['Compulsory', 'Conflict']
miss_counts = [1632, 296340]
axes[1].pie(miss_counts, labels=miss_types, autopct='%1.1f%%',
            colors=['#3498db', '#e74c3c'])
axes[1].set_title('Matrix Multiply: Miss Classification')

plt.suptitle('Cache Performance Analysis Engine — Phase 3 Results',
             fontsize=14, fontweight='bold')
plt.tight_layout()
plt.savefig('analysis/cache_performance.png', dpi=150, bbox_inches='tight')
plt.show()
print("Graph saved to analysis/cache_performance.png")