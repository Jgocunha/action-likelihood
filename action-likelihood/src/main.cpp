// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>

struct Position
{
    double x, y, z;
};

double calculateDistance(const Position& p1, const Position& p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

double calculateVelocity(const Position& handPos, const Position& handPosPrev)
{
    // Assuming a fixed polling rate, e.g., 100 Hz
    constexpr double deltaTime = 0.01; // Time between measurements in seconds

    const double deltaX = handPos.x - handPosPrev.x;
    const double deltaY = handPos.y - handPosPrev.y;
    const double deltaZ = handPos.z - handPosPrev.z;

    // Calculate the velocity magnitude
    const double velocityMagnitude = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2)) / deltaTime;
    return velocityMagnitude;
}

double calculateLikelihood(const Position& handPos, const Position& handPosPrev, const Position& componentPos, double tau, double sigma)
{
    const double distance = calculateDistance(handPos, componentPos);
    const double distancePrev = calculateDistance(handPosPrev, componentPos);
    //const double rateOfChange = distance - distancePrev; // Simplified rate of change calculation
    const double rateOfChange = calculateVelocity(handPos, handPosPrev); // More accurate rate of change calculation

    // Implementing equation 8
    const double exponent = -pow((distance + tau * rateOfChange), 2) / (2 * pow(sigma, 2));
    const double likelihood = (1 / sqrt(2 * std::numbers::pi * pow(sigma, 2))) * exp(exponent);

    return likelihood;
}

int main()
{
    constexpr Position handCurrent = { 3.0, 4.0, 1.0 }; // Current hand position
    constexpr Position handPrevious = { 3.0, 3.9, 0.98 }; // Previous hand position (to calculate velocity)
    constexpr Position component = { 3.0, 4.0, 1.0 }; // Position of a component (static)
    constexpr double tau = 0.1; // Time constant
    constexpr double sigma = 0.2; // Uncertainty

    const double likelihood = calculateLikelihood(handCurrent, handPrevious, component, tau, sigma);
    std::cout << "Likelihood: " << likelihood << std::endl;

    return 0;
}