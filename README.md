gcc fri_client.cpp -o fri_client
gcc robot_controller.cpp -o robot_controller1
gcc robot_controller.cpp -o robot_controller2

## Setting 1

# PC
port: 9000
ip: 192.168.0.170
pc_to_rob1 192.168.1.65
pc_to_rob2 192.168.1.69

# Robot1
port: 9000
ip: 192.168.0.105

# Robot2
port: 9000
ip: 192.168.0.111

## Setting 2

# PC -- mm_master
port: 9000
pc_to_rob1 192.168.1.67
pc_to_rob2 192.168.2.2

# Robot1 -- laptop
port: 9000
ip: 192.168.1.69

# Robot2 -- mm
port: 9000
ip: 192.168.2.3


# PC
./fri_client <pc port> <robot1 port> <robot1 ip> <robot2 port> <robot2 ip>
./fri_client 9000 9000 192.168.1.69 9000 192.168.2.3

# Robot
./robot_controller <robot port>
./robot_controller1 9000
./robot_controller2 9000