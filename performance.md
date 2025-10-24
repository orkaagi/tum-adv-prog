_table of contents_
- [Automated Performance Testing for `group_80`](#automated-performance-testing-for-group_80)
- [Performance Results](#performance-results)
- [Optimization Documentation](#optimization-documentation)

# Automated Performance Testing for `group_80`

This project includes Expect scripts designed to automate testing of the `group_80` stock market simulation program. The scripts execute the program with predefined inputs, ensuring repeatability and precision in performance evaluation. 
- `test_script_1.exp` and `test_script_2.exp` 
- Files are included in the `optimization_documentation/performance_test/` directory.
- Move to the `root` directory to run the scripts.

## Test Tool
- **Expect**: Automates interactions with `group_80` by simulating user input.
- **perf stat**: Collects performance metrics of the program.

## Test Requirements
- The `group_80` executable must be present in the working directory.
- The `perf` tool must be installed for performance measurement.
- The scripts should be run in a shell that supports Expect.

## Test Scenarios
Two scripts (`test_script_1` and `test_script_2`) are used to evaluate the program under different input sizes.

## Test Environment
Fedora VM with 2 vCPUs and 4 GB RAM in VMware Workstation Windows 11 Pro
see [optimization_documentation/performance_test/env.txt](optimization_documentation/performance_test/env.txt) for more details.

### **Test Script 1**
- **Input Size**: Small
- **Stocks**: 3
- **Data Points per Stock**: 3
- **Wallets Created**: 3
- **Goal**: Ensure correctness and performance in a basic scenario.

### **Test Script 2**
- **Input Size**: Large
- **Stocks**: 50
- **Data Points per Stock**: 50
- **Wallets Created**: 3
- **Goal**: Stress test the program with a large dataset to measure performance impact.

## Objective
- Automate the testing process to remove human input delays.
- Generate precise performance reports using `perf stat`.
- Evaluate execution time and efficiency under different workloads.

## Execution
Run the test scripts in a compatible shell:
```sh
chmod +x test_script_1 test_script_2
./test_script_1
./test_script_2
````

# Performance Results
## Elapsed Time Comparison

The table below compares the elapsed time (in seconds) for test scripts with different optimization levels in Sprint 3, along with a comparison to Sprint 2 results.

| Optimization Level | Test Script 1 (Sprint 3) | Test Script 1 (Sprint 2) | Test Script 2 (Sprint 3) | Test Script 2 (Sprint 2) |
|--------------------|-------------------------|-------------------------|-------------------------|-------------------------|
| O0                | 0.873 seconds            | 1.35 seconds            | 77.307 seconds         | 132 seconds            |
| O1                | 0.254 seconds            | 0.311 seconds           | 31.219 seconds         | 45.8 seconds           |
| O2                | 0.246 seconds            | 0.291 seconds           | 30.176 seconds         | 43.8 seconds           |
| O3                | 0.274 seconds            | 0.264 seconds           | 27.416 seconds         | 40.91 seconds          |


- Our Optimization significantly reduces execution time both with compiler optimization flags and without them.
- The compiler optimization will reduce the execution time significantly for large input sizes.

---

# Optimization Documentation
See the [Optimization Documentation](optimization.md) for detailed information on the optimization process and results.