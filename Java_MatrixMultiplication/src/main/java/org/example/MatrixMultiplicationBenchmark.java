package org.example;

import org.openjdk.jmh.annotations.*;
import java.util.concurrent.TimeUnit;

@BenchmarkMode(Mode.AverageTime) // Measure average time per operation
@OutputTimeUnit(TimeUnit.MILLISECONDS) // Output time in milliseconds
@State(Scope.Thread)
public class MatrixMultiplicationBenchmark {

    private int[][] A;
    private int[][] B;

    @Setup
    public void setup() {
        int n = 1024; // Matrix size (100x100)
        A = new int[n][n];
        B = new int[n][n];

        // Fill matrices with random values
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = (int) (Math.random() * 100);
                B[i][j] = (int) (Math.random() * 100);
            }
        }
    }

    @Benchmark
    @Measurement(iterations = 5, time = 1, timeUnit = TimeUnit.SECONDS) // Run 5 iterations of 1 second each
    public int[][] benchmarkMatrixMultiplication() {
        // Get memory usage before the multiplication
        long beforeUsedMem = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();

        // Perform matrix multiplication
        int[][] result = Main.multiplyMatrices(A, B);

        // Get memory usage after the multiplication
        long afterUsedMem = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();

        // Calculate memory usage difference
        long memoryUsed = afterUsedMem - beforeUsedMem;

        // Print or log the memory usage (for testing purposes)
        System.out.println("Memory used (bytes): " + memoryUsed);

        return result;
    }
}
