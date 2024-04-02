# Computational Approach to Action Observation Likelihood

This project implements a computational model for evaluating the likelihood of a hand's movement towards a specific object in a simulated environment. The core algorithm is inspired by the principles outlined in the research article "Goals and Means in Action Observation: A Computational Approach" by Raymond H. Cuijpers, Hein T. van Schie, Mathieu Koppen, Wolfram Erlhagen, and Harold Bekkering. This model integrates real-time tracking data with a mathematical framework to predict action goals, providing insights into human and robotic interaction dynamics.

## Concept

The algorithm calculates the likelihood of an observed action (e.g., hand moving towards an object) based on a computational model that considers the observer's perspective. It employs the concepts of distance and velocity between the hand and objects in the environment, leveraging these dynamics to infer the intention behind the movement. This approach is pivotal for understanding and predicting actions in human-robot interaction scenarios.

## Implementation

The project uses CoppeliaSim for simulation and real-time hand tracking, with a C++ application performing the computational analysis. The algorithm processes the hand's positional data to calculate velocities and subsequently evaluates the likelihood of the hand's goal-directed actions towards predefined components in the simulation.

### Prerequisites

- [CoppeliaSim](https://www.coppeliarobotics.com/) for the simulation environment.
- [coppeliasim-cpp-client](https://github.com/Jgocunha/coppeliasim-cpp) for interfacing with CoppeliaSim.
- A modern C++ compiler supporting C++17 standards for the computational model implementation.

### Key Components

- **Position and Velocity Calculations**: Utilizes real-time spatial data to compute the hand's movement metrics.
- **Likelihood Estimation**: Applies the mathematical model to estimate action goals based on movement dynamics, focusing on the interaction with specific objects.

## Based on Academic Research

The foundational algorithm and computational approach are directly inspired by the article:

> "Goals and Means in Action Observation: A Computational Approach" by Raymond H. Cuijpers, Hein T. van Schie, Mathieu Koppen, Wolfram Erlhagen, and Harold Bekkering, which investigates the cognitive processes underlying action observation and goal inference.

This project seeks to apply theoretical insights from the paper to practical simulations, providing a framework for analyzing and understanding action goals in a controlled environment.

## Usage

The application connects to a CoppeliaSim simulation, tracking the hand object's position and calculating its movement's likelihood toward a designated target. This process involves real-time data analysis, underlining the algorithm's potential in interactive and adaptive systems.
