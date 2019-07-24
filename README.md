gcc fri_client.cpp -o fri_client
gcc robot_controller.cpp -o robot_controller1
gcc robot_controller.cpp -o robot_controller2

# PC
port: 9000
ip: 192.168.0.170

# Robot1
port: 9000
ip: 192.168.0.105

# Robot2
port: 9000
ip: 192.168.0.111


# PC
./fri_client <pc port> <robot1 port> <robot1 ip> <robot2 port> <robot2 ip>
./fri_client 9000 9000 192.168.0.105 9000 192.168.0.111

# Robot
./robot_controller <robot port>
./robot_controller1 9000
./robot_controller2 9000