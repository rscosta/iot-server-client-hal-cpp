# IOT Client/Server and HAL 
A simple C++ IOT server-client solution over socket and interfacing with Hardware Abstraction Layer (HAL).

## Overview
- The communication between clients and server is done by TCP socket;
- The IOT Client is divided by: Publisher and Subscriber;
- IOT Server is able to connect N clients;
- IOT Server handles the Queue messages management;
- IOT Server handles the TCP socket connection management.
- IOT Clients (Publishers) interfaces with IOT Client and HAL libraries;
- IOT Clients (Subscribers) interfaces with HAL library.

# Build Instructions

## Prerequisites

* CMake 3.9 and newer
* C++11 capable compiler
* Doxygen for docs (*Graphviz for more graphs in docs, PlantUML for more UML diagrams*, PlantUML needs java)
* Ubuntu 18.04 and newer: `sudo apt-get install graphviz plantuml doxygen`

## Building source

```sh
git clone https://github.com/rscosta/iot-client-server-hal-cpp.git
mkdir -p iot-client-server-hal-cpp/build
cd iot-client-server-hal-cpp/build
cmake .. && make
sudo make install      #optional
sudo ldconfig          #only required for linux
```
## Building doc

```sh
mkdir -p iot-client-server-hal-cpp/build
cd iot-client-server-hal-cpp/build
cmake .. && make doc
```
The documentation will be saved into `[build_directory]/doc/documentation/index.html` folder.

The documentation contains:
* Architecture (Server/Client);
* Subscription types (Publishers/Subscribers);
* Protocol used for client and servers;
* Source Code API.

## Run Server

If installed into local file system, type:
```sh
IOTServerApp
```

Or if you want to run into build folder, type:
```sh
[build_directory]/iot_client_server/src/demo/iot_server_app/IOTServerApp
```

## Run Clients (Publishers)

If installed into local file system, type:
```sh
PubIotClientAccelGyroApp
PubIotClientTempApp
PubIotClientLedApp
```
Or if you want to run into build folder, type:
```sh
[build_directory]/iot_client_server/src/demo/iot_client_app/PubIotClientAccelGyroApp
[build_directory]/iot_client_server/src/demo/iot_client_app/PubIotClientTempApp
[build_directory]/iot_client_server/src/demo/iot_client_app/PubIotClientLedApp
```

## Run Clients (Subscribers)

If installed into local file system, type:
```sh
SubIotClientListenOnePubApp
SubIotClientListenTwoPubsApp
```
Or if you want to run into build folder, type:
```sh
[build_directory]/iot_client_server/src/demo/iot_client_app/SubIotClientListenOnePubApp
[build_directory]/iot_client_server/src/demo/iot_client_app/SubIotClientListenTwoPubsApp
```

## Run Test (IOTServer, IOTClient)

To run into build folder, type:
```sh
[build_directory]/test/src/unit/iot_server/IOTServerTestApp
[build_directory]/test/src/unit/iot_client/IOTClientTestApp
```

## Run Demo HAL Application

This application will test Camera and GPS HAL API in standalone mode. If installed into local file system, type:
```sh
HALTestApp
```
Or if you want to run into build folder, type:
```sh
[build_directory]/hal/src/app/HALTestApp
```
