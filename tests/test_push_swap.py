#!/usr/bin/env python3
"""Tests internes : aucun lien avec le programme bonus checker."""

import itertools
import random
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
BINARY = ROOT / "push_swap"
VALID_OPS = {
    "sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"
}


def replay(values, operations):
    """Exécute les instructions avec le sommet à l'indice zéro."""
    a = list(values)
    b = []
    for op in operations:
        assert op in VALID_OPS, f"Instruction inconnue : {op!r}"
        if op in ("sa", "ss") and len(a) > 1:
            a[0], a[1] = a[1], a[0]
        if op in ("sb", "ss") and len(b) > 1:
            b[0], b[1] = b[1], b[0]
        if op == "pa" and b:
            a.insert(0, b.pop(0))
        if op == "pb" and a:
            b.insert(0, a.pop(0))
        if op in ("ra", "rr") and a:
            a.append(a.pop(0))
        if op in ("rb", "rr") and b:
            b.append(b.pop(0))
        if op in ("rra", "rrr") and a:
            a.insert(0, a.pop())
        if op in ("rrb", "rrr") and b:
            b.insert(0, b.pop())
    return a, b


def check_sort(values, strategy):
    """Vérifie qu'une stratégie trie et laisse la pile b vide."""
    run = subprocess.run(
        [BINARY, strategy, *map(str, values)],
        text=True, capture_output=True, check=False,
    )
    assert run.returncode == 0, (strategy, values, run.stderr)
    assert not run.stderr, (strategy, values, run.stderr)
    operations = run.stdout.splitlines()
    a, b = replay(values, operations)
    assert a == sorted(values) and not b, (strategy, values, operations)
    return len(operations)


def test_sorts():
    """Teste exhaustivement les petites tailles puis quelques grands cas."""
    cases = []
    for size in range(1, 6):
        cases.extend(itertools.permutations(range(size)))
    for size in (6, 7, 10, 20, 100, 500):
        for _ in range(5):
            values = random.sample(range(-10000, 10000), size)
            random.shuffle(values)
            cases.append(values)
    for strategy in ("--simple", "--medium", "--complex", "--adaptive"):
        counts = [check_sort(values, strategy) for values in cases]
        print(f"{strategy}: {len(cases)} tris valides, maximum {max(counts)}")


def test_errors():
    """Les entrées invalides ne doivent produire que Error sur stderr."""
    invalid = [
        ["0", "one", "2"], ["3", "2", "3"], ["2147483648"],
        ["-2147483649"], ["+"], ["-"], ["1", "2x"], ["", "1"],
        ["--unknown", "1"], ["--simple", "--medium", "2", "1"],
        ["9" * 10000], ["1.0"], ["0x10"],
    ]
    for args in invalid:
        run = subprocess.run(
            [BINARY, *args], text=True, capture_output=True, check=False
        )
        assert run.returncode == 1, (args, run.returncode)
        assert run.stdout == "" and run.stderr == "Error\n", args
    print(f"Parsing : {len(invalid)} erreurs correctement rejetées")


def test_bench():
    """Le banc d'essai ne doit jamais polluer le flux d'opérations."""
    values = [2, 1, 3, 6, 5, 8]
    run = subprocess.run(
        [BINARY, "--bench", *map(str, values)],
        text=True, capture_output=True, check=False,
    )
    assert run.returncode == 0
    assert "[bench] disorder: 13.33%" in run.stderr
    assert "[bench] strategy: Adaptive -> Simple (O(n^2))" in run.stderr
    assert "[bench] total operations:" in run.stderr
    a, b = replay(values, run.stdout.splitlines())
    assert a == sorted(values) and not b
    print("Benchmark : désordre, stratégie et compteurs présents sur stderr")


if __name__ == "__main__":
    random.seed(42)
    test_errors()
    test_bench()
    test_sorts()
    print("Tous les tests sont passés.")
