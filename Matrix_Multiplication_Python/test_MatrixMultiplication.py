import pytest_benchmark
import random
from MatrixMultiplication import multiplication
import tracemalloc


def test_matrix_multiplication(benchmark):
    A = [[random.random() for _ in range(1024)] for _ in range(1024)]
    B = [[random.random() for _ in range(1024)] for _ in range(1024)]
    benchmark(multiplication, A, B)

def test_matrix_multiplication_memory():
    tracemalloc.start()
    A = [[random.random() for _ in range(1024)] for _ in range(1024)]
    B = [[random.random() for _ in range(1024)] for _ in range(1024)]
    multiplication(A, B)
    current, peak = tracemalloc.get_traced_memory()
    tracemalloc.stop()
    print(f"Current memory usage is {current / 10**6}MB; Peak was {peak / 10**6}MB")


test_matrix_multiplication_memory()