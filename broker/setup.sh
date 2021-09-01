git clone https://github.com/whoshuu/cpr
git clone https://github.com/nlohmann/json
git clone --recursive https://github.com/uNetworking/uWebSockets

make -C uWebSockets

mkdir build
cd build
cmake ..
make
cd ..

echo "Setup Complete."