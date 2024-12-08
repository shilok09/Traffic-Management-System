# Traffic Management System
**Data Structures Final Project**
This project implements a comprehensive traffic management and congestion monitoring system. It combines features like vehicle routing, congestion monitoring, road closures, and emergency vehicle management to optimize road network operations.

## Features

1. **Road Network Management**
   - Represented as an adjacency list.
   - Dynamic addition of roads and their distances.

2. **Vehicle Routing**
   - Calculates the shortest path for vehicles using Dijkstra's algorithm.
   - Supports routing for emergency vehicles with priority.

3. **Congestion Monitoring**
   - Tracks vehicle counts on roads using a hash table.
   - Displays congestion details for the road network.

4. **Road Closure Management**
   - Tracks road statuses (e.g., blocked, under repair).
   - Dynamically updates road statuses based on real-time data.

5. **Emergency Vehicle Management**
   - Assigns high-priority paths for emergency vehicles.
   - Adjusts signals and routing to accommodate emergency situations.

6. **Signal Management**
   - Prioritizes intersections using a max-heap.
   - Dynamically adjusts signal timings based on vehicle density and emergency vehicle presence.

## Files Used

### Input Files
- **`road_network.csv`**: Defines the road network with distances.
  - Columns: `Source`, `Destination`, `Distance`
- **`vehicles.csv`**: Lists vehicles and their paths.
  - Columns: `Vehicle ID`, `Start`, `End`
- **`emergency_vehicles.csv`**: Lists emergency vehicles and their details.
  - Columns: `Vehicle ID`, `Start`, `End`, `Priority`
- **`road_closures.csv`**: Tracks road closures or maintenance statuses.
  - Columns: `Source`, `Destination`, `Status`

## Key Classes and Structures

1. **`road`**: Represents a road segment in the network.
2. **`vehicle`**: Manages individual vehicle data and routing.
3. **`track`**: Tracks road usage for congestion monitoring.
4. **`CongestionMonitoring`**: Implements a hash table to monitor congestion.
5. **`Status` and `RoadStatusList`**: Handle road statuses like blocked or under repair.
6. **`roadNetworks`**: Manages the overall road network and vehicle routing.
7. **`Signal` and `PriorityQueue`**: Implement signal management using a max-heap.

## How It Works

1. **Initialization**:
   - Load road network and vehicle data from CSV files.
   - Construct the adjacency list and hash table for roads and vehicles.

2. **Shortest Path Calculation**:
   - Uses Dijkstra's algorithm to determine the shortest path while avoiding blocked roads.

3. **Dynamic Updates**:
   - Road closures and new vehicles are dynamically added and handled in real-time.

4. **Emergency Handling**:
   - Emergency vehicles are routed with the highest priority.
   - Signals are adjusted to facilitate smooth movement of emergency vehicles.

5. **Congestion Monitoring**:
   - Tracks the density of vehicles on roads and displays congestion reports.

6. **Signal Management**:
   - Adjusts signal timings dynamically based on vehicle density and emergency presence.

## Compilation and Execution

### Prerequisites
- C++ compiler (e.g., g++)
- Input CSV files (`road_network.csv`, `vehicles.csv`, `emergency_vehicles.csv`, `road_closures.csv`)

### Compilation
```bash
 g++ -o traffic_management traffic_management.cpp
```

### Execution
```bash
 ./traffic_management
```

### Sample Input
#### `road_network.csv`
```
Source,Destination,Distance
A,B,10
B,C,15
C,D,20
```

#### `vehicles.csv`
```
Vehicle ID,Start,End
V1,A,C
V2,B,D
```

#### `emergency_vehicles.csv`
```
Vehicle ID,Start,End,Priority
E1,A,D,High
```

#### `road_closures.csv`
```
Source,Destination,Status
B,C,Blocked
```

### Output
- Displays the road network, vehicle routes, congestion status, and dynamic signal management.

## Future Enhancements
- Integration with real-time traffic data APIs.
- GUI for visualizing the road network and vehicle routes.
- Support for additional road and vehicle attributes (e.g., speed limits, vehicle types).



## Contributions
Contributions are welcome! Please fork the repository, create a new branch, and submit a pull request with detailed information on your changes.

---

## DONE BY
 **Shilok Kumar**.
 **Sabeel Nadeem**.
 **Affaf Mehmood**.


