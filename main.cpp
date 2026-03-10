#include <iostream>
#include <iomanip>

extern "C"
{
#include "SpiceUsr.h"
}

int main()
{
    // Load the Map (Planets) AND the Clock (Leap Seconds)
    furnsh_c("data/naif0012.tls");
    furnsh_c("data/de440.bsp");

    double et;       // Ephemeris Time (seconds past J2000)
    double state[6]; // Position (x,y,z) and Velocity (vx,vy,vz)
    double lt;       // Light time between Earth and Mars

    // 2. Convert a human string to Space Time
    str2et_c("2026 MARCH 10 12:00:00 UTC", &et);

    // 3. Get the State of MARS_BARYCENTER (4) relative to EARTH (399)
    // in the J2000 frame, corrected for light-time (LT)
    spkezr_c("MARS BARYCENTER", et, "J2000", "LT", "EARTH", state, &lt);

    std::cout << "--- Mars Orbit Data ---" << std::endl;
    std::cout << "Date: 2026-03-10 12:00:00 UTC" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "X Position: " << state[0] << " km" << std::endl;
    std::cout << "Y Position: " << state[1] << " km" << std::endl;
    std::cout << "Z Position: " << state[2] << " km" << std::endl;

    // Calculate distance (Pythagorean theorem)
    double dist = sqrt(state[0] * state[0] + state[1] * state[1] + state[2] * state[2]);
    std::cout << "Distance:   " << dist / 1000000.0 << " million km" << std::endl;

    return 0;
}
