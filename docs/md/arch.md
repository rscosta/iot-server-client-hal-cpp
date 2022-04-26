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

# Architecture 

The IOT Server solution consists basically in two managers:
* TCP Socker Manager - Responsible to connect clients with the server;
* Subscriber List Manager - Responsible to Send/Receive Client messages by Socket ID and Topic ID keys.

The IOT Client (Publisher) solution consists:
* Interfaces with HAL Library to Send/Receive Hardware status, get/set sensor&module parameters;
* Request TCP Socket connection to the Server;
* Publish Hardware data based on topics.

The IOT Client (Subscriber) solution consists:
* Interfaces with IOT Client Library to request TCP Socket connection and Send/Receive messages to/from the Server;
* Reads Hardware notification based on topics subscribed.

The image below shows the entire scope of the architecture of the solution:

![](iot_client_server_arch.drawio.png)

## Subscription Types
The solution is capable to connect the following possibilites are showed below:

### Subscription Type 1
![](n_pub_n_sub_arch.drawio.png)

### Subscription Type 2
![](n_pub_one_sub_arch.drawio.png)

### Subscription Type 3
![](one_pub_one_sub_arch.drawio.png)

# The BIC protocol

The BIC (Basic Iot Communication) protocol is a custom protocol and it contains a basic control & payload to communicate between IOT Client and IOT Server. 
The current solution does not support payload fragmentation, cyclic redundancy check (CRC) for error-detecting code message and QOS Management. 

### Data format

The CSV (comma-separated values) format is used for communication with IOT Server-Client endpoint. The following rules must be followed to ensure a frictionless communication.

* Values are always separated by a comma (,).

### Packet layout

The BIC protocol works by exchanging messages in a defined way. It consists up to three parts, always in the following order:

* Option 1: CONTROL_PACKET_TYPE
* Option 2: CONTROL_PACKET_TYPE,TOPIC_NAME
* Option 3: CONTROL_PACKET_TYPE,TOPIC_NAME,PAYLOAD

## Control Packet Type 

### PUBREG

PUBREG - is a control packet used for authenticating a client as a publisher.

Message Syntax: PUBREG

Message results:
* PUBREGOK - IOT Client (Publisher) registered successfuly as a publisher;
* PUBREGFAILMAXREACHED - IOT Client not registered because of maximum clients are reached;
* PUBREGPARAMERROR - Message parameters syntax is malformed;

The sequence diagram below shows how to authenticate a publisher:

![](ds_pubreg.drawio.png)

### PUBREGTOP

PUBREGTOP - is a control packet used for registering a topic for a publisher. It is allowed 
to register one topic at time.

Message Syntax: PUBREGTOP,TOPIC_NAME

Message results:
* PUBREGTOPOK - Topic registered successfuly;
* PUBREGTOPTOPREGALREADY - Topic registered already for some publisher;
* PUBREGTOPCLIENTLISTEMPTY - IOT Client (Publisher) is not registered (PUBREG not executed);
* PUBREGTOPPARAMERROR - Message parameters syntax is malformed;

The sequence diagram below shows how to register a topic for a publisher:

![](ds_pubregtop.drawio.png)

### PUBLISTTOP

PUBLISTTOP - is a control packet used for listing topics from all publishers.

Message Syntax: PUBLISTTOP

Message results:
* PUBLISTTOPOK,NUM_OF_TOPICS,TOPIC_NAME01,TOPIC_NAME02,TOPIC_NAME_N - List of publishers topics registered;
* PUBLISTTOPCLIENTLISTEMPTY - There is no IOT Client (Publisher) topics registered;
* PUBLISTTOPPARAMERROR - Message parameters syntax is malformed;

The sequence diagram below shows how to get a list of topics for all publishers:

![](ds_publisttop.drawio.png)

### SENDPAYLOAD

SENDPAYLOAD - is a control packet used for publisher/subscriber sending payload. If payload has more than one parameter,
add blank space between parameters.

Message Syntax: SENDPAYLOAD,TOPIC_NAME,PAYLOAD 

Message results:
* SENDPAYLOADOK - Payload sent successfuly;
* SENDPAYLOADTOPNOTFOUND - Topic not found for sending payload;
* SENDPAYLOADCLIENTLISTEMPTY - IOT Client (Publisher/Subscriber) is not registered;
* SENDPAYLOADPARAMERROR - Message parameters syntax is malformed;

The sequence diagram below shows how to send a payload to a topic:

![](ds_sendpayload.drawio.png)

### SUBREG

SUBREG - is a control packet used for authenticating a client as a subscriber.

Message Syntax: SUBREG

Message results:
* SUBREGOK - IOT Client registered successfuly as a subscriber;
* SUBREGFAILMAXREACHED - IOT Client not registered because of maximum clients are reached;
* SUBREGPARAMERROR - Message parameters syntax is malformed;

The sequence diagram below shows how to authenticate a subscriber:

![](ds_subreg.drawio.png)

### SUBLISTENTOP

SUBLISTENTOP - is a control packet used for registering a topic for a subscriber. It is allowed 
to register one topic at time.

Message Syntax: SUBLISTENTOP,TOPIC_NAME

Message results:
* SUBLISTENTOPOK - Topic registered successfuly;
* SUBLISTENTOPREGALREADY - Topic registered already for some publisher;
* SUBLISTENTOPCLIENTLISTEMPTY - IOT Client is not registered;
* SUBLISTENTOPPARAMERROR - Message parameters syntax is malformed;

The sequence diagram below shows how to register a listener for a topic:

![](ds_sublistentop.drawio.png)

### SUBUNREGTOP

SUBUNREGTOP - is a control packet used for unregistering a topic for a subscriber. It is allowed 
to unregister one topic at time.

Message Syntax: SUBUNREGTOP,TOPIC_NAME

Message results:
* SUBUNREGTOPOK - Topic unregistered successfuly;
* SUBUNREGTOPTOPNOTFOUND - Topic request to be unregistered is not found;
* SUBUNREGTOPCLIENTLISTEMPTY - IOT Client is not registered;
* SUBUNREGTOPPARAMERROR - Message parameters syntax is malformed;

The sequence diagram below shows how to unregister a listener of a topic from a subscriber:

![](ds_subunregtop.drawio.png)

## Topic Name

To register a topic, the following examples listed below are allowed:

* sensor/temperature_01
* sensor/temperature
* temperature-sensor
* temperature-sensor_01
* temperature_sensor
* temperature_sensor_01

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










