#!/bin/bash

echo "Installing TUFGlow..."

mkdir -p build
if ! g++ -std=c++17 ./src/main.cpp -o ./build/tufglow; then
  echo "Build failed" >&2 
  exit 1
fi 

mkdir -p ~$HOME/.local/bin 
cp build/tufglow ~$HOME/.local/bin/tufglow
chmod +x ~$HOME/.local/bin/tufglow 

echo
echo "TUFGlow installed successfully"
echo 
echo "Run with: "
echo "  sudo tufglow"
