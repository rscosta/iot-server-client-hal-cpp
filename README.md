# server-client-hal-cpp
A simple C++ IOT server-client solution over socket and interfacing with Hardware Abstraction Layer (HAL).
The messages are exchanged using JSON. 


Build from source
=================

```sh
git clone https://github.com/rscosta/client-server-hal-cpp.git
mkdir -p client-server-hal-cpp/build
cd client-server-hal-cpp/build
cmake .. && make
sudo make install
sudo ldconfig          #only required for linux
```

Run Server
=================

```sh
IOTServerApp
```

Run Client
=================

```sh
IOTClientApp
```

Run Demo HAL Application
========================

This application will test Camera and GPS HAL API.

```sh
HALTestApp
```



