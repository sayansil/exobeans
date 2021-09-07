# ExoBeanstalkd - Consumer

Comsumer (worker) application for ExoBeanstalkd

## Getting Started

### Installing

- Make sure you are connected to internet to download any required libraries for the project.

- Run the `setup.sh` script to build the application.

```sh
./setup.sh
```

### Usage

- Make sure the Broker application is already running on `port 15000`. If not, refer to [/broker/README.md]().

- Make necessary changes to the `/src/main.cpp` file to use the consumer functions defined in `/include/consumer.hpp`.


- Navigate to the new `/build` directory and re-build the project to use new `main.cpp`.

```sh
cd build
cmake ..
make
```

- Run the consumer script (in `main.cpp`) with the following command:

```sh
./run
```

- Consumer will try to connect with Broker on `port 15000`.
