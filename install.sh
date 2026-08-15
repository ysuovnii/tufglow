#!/bin/bash

echo "Installing TUFGlow..."

mkdir -p build
if ! g++ -std=c++17 ./src/main.cpp -o ./build/tufglow; then
  echo "Build failed" >&2 
  exit 1
fi 

sudo mkdir -p /usr/local/bin
sudo cp build/tufglow /usr/local/bin/tufglow
sudo chmod +x /usr/local/bin/tufglow

echo
echo "TUFGlow installed successfully"
echo 
echo "Run with: "
echo "  sudo tufglow"
