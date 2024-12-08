# Traffic-Management-System# Traffic Management System Simulator

## Overview
This project implements a **Traffic Management System Simulator** in C++, using data structures like adjacency lists and hash tables. The system tracks road networks, monitors congestion levels, and assigns vehicles to optimal routes based on the shortest paths calculated using Dijkstra's algorithm. The project also integrates vehicle data read from a CSV file and supports dynamic congestion updates.

---

## Features
- **Road Network Representation**: Uses adjacency lists to represent roads and distances.
- **Shortest Path Calculation**: Implements Dijkstra's algorithm for finding the shortest path between source and destination.
- **Vehicle Management**: Reads vehicle data (IDs, start points, destinations) from a CSV file and assigns optimal routes.
- **Congestion Monitoring**: Tracks the number of vehicles on each road segment and displays congestion levels.

---

## Code Structure

### Key Components
1. **`road` Struct**:
   - Represents a road with destination, distance, and a pointer to the next road.
   
2. **`vehicle` Class**:
   - Manages vehicle IDs, paths, current locations, and dynamic updates of their positions.

3. **`track` Struct**:
   - Stores road information and the number of vehicles on each road.

4. **`CongestionMonitoring` Class**:
   - Implements a hash table to track vehicle counts on roads using a custom hash function.

5. **`roadNetworks` Class**:
   - Manages the road network as an adjacency list.
   - Provides methods for adding roads, finding shortest paths, and integrating vehicle data.

---

## Installation and Usage

### Prerequisites
- C++ Compiler (e.g., GCC or MSVC)
- CSV files:
  - `road_network.csv`: Contains road data in the format `source,destination,distance`.
  - `vehicles.csv`: Contains vehicle data in the format `vehicleID,source,destination`.

### Compilation
Compile the program using a C++ compiler:
```bash
g++ -o traffic_simulator traffic_simulator.cpp
```

### Execution
Run the compiled program:
```bash
./traffic_simulator
```

### Example CSV Files
#### `road_network.csv`:
```
source,destination,distance
A,B,5
B,C,3
C,D,7
```

#### `vehicles.csv`:
```
vehicleID,source,destination
V001,A,D
V002,B,C
```

---

## Features Demonstration

1. **Build Road Network**:
   - Reads from `road_network.csv` to create an adjacency list.
   
2. **Display Roads**:
   - Outputs all roads and distances.

3. **Shortest Path Assignment**:
   - Computes the shortest path for each vehicle and assigns it.

4. **Congestion Monitoring**:
   - Displays the vehicle count on each road segment.

---

## Sample Output
```
Vehicle V001: Path = A -> B -> C -> D
Vehicle V002: Path = B -> C
Congestion Levels:
A to B | Vehicles: 1
B to C | Vehicles: 2
C to D | Vehicles: 1
```

---

## Future Enhancements
- Add real-time updates for vehicle movements.
- Integrate traffic signal prioritization.
- Visualize road networks and congestion levels.



## Contributions
Contributions are welcome! Please fork the repository, create a new branch, and submit a pull request with detailed information on your changes.

---

## DONE BY
 **Shilok Kumar**.
 **Sabeel Nadeem**.
 **Affaf Mehmood**.


