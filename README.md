# Efficient Gradient Computation for Model Predictive Control of a Double Pendulum

## Overview

This project focuses on efficient gradient computation for Model Predictive Control (MPC) of a double pendulum on a cart. It constitutes preliminary research for a master's thesis.

The three main objectives of the project are:
- Discretization of the equations of motion.
- Implementation of the discrete adjoint method.
- Implementation of Model Predictive Control.

## Current state

The continuous and discrete formulations of the system dynamics have been implemented. Further numerical verification and investigation are required.

The project is currently under active development.

## Build and run

From the project root directory:

```bash
cmake -S . -B build
cmake --build build
cd build
./cartpole
```

The executable performs dynamics simulations and saves the results in HDF5 files, which can subsequently be analyzed and visualized using the Python scripts provided in the `python/` directory.
