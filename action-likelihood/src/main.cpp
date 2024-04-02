// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>
#include <chrono>
#include "client.h"

struct Position
{
    double x, y, z;
};

double calculateDistance(const Position& p1, const Position& p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
}

double calculateVelocity(const Position& handPos, const Position& handPosPrev, double deltaTime)
{
    const double deltaX = handPos.x - handPosPrev.x;
    const double deltaY = handPos.y - handPosPrev.y;
    const double deltaZ = handPos.z - handPosPrev.z;

    // Calculate the velocity magnitude
    const double velocityMagnitude = sqrt(pow(deltaX, 2) + pow(deltaY, 2) + pow(deltaZ, 2)) / deltaTime;
    return velocityMagnitude;
}

double calculateLikelihood(const Position& handPos, const Position& handPosPrev, const Position& componentPos, double deltaTime, double tau, double sigma)
{
    const double distance = calculateDistance(handPos, componentPos);
    const double velocityMagnitude = calculateVelocity(handPos, handPosPrev, deltaTime);

    // Implementing equation 8
    const double exponent = -pow((distance + tau * velocityMagnitude), 2) / (2 * pow(sigma, 2));
    const double likelihood = (1 / sqrt(2 * std::numbers::pi * pow(sigma, 2))) * exp(exponent);

    return likelihood;
}

int main()
{
    try
    {
        coppeliasim_cpp::CoppeliaSimClient client;
        client.setLogMode(coppeliasim_cpp::LogMode::LOG_CMD);

        while (!client.initialize());

        client.startSimulation();
        constexpr Position component = { 0.0, 0.0, 0.85107 };
        constexpr double tau = 0.1;
        constexpr double sigma = 0.2;
        const int handHandle = client.getObjectHandle("hand");
        coppeliasim_cpp::Position handPrevious = client.getObjectPosition(handHandle);

        using Clock = std::chrono::high_resolution_clock;
        auto lastTime = Clock::now();

        while (client.isConnected())
        {
            const coppeliasim_cpp::Position handCurrent = client.getObjectPosition(handHandle);
            //std::cout << "Hand position: " << handCurrent.x << ", " << handCurrent.y << ", " << handCurrent.z << std::endl;
            auto currentTime = Clock::now();
            std::chrono::duration<double> elapsed = currentTime - lastTime;
            const double deltaTime = elapsed.count();

            const double likelihood = calculateLikelihood({ handCurrent.x, handCurrent.y, handCurrent.z }, { handPrevious.x, handPrevious.y, handPrevious.z }, component, deltaTime, tau, sigma);
            std::cout << "Likelihood: " << likelihood << std::endl;

            handPrevious = handCurrent;
            lastTime = currentTime;
        }

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }
}
