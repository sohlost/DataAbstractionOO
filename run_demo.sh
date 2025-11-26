#!/bin/bash
echo "Building CLI Pipeline..."
g++ -std=c++20 -Wall -I. -o cli_pipeline cli_pipeline.cpp

echo ""
echo "========================================"
echo "Build Complete."
echo "Launching CLI Pipeline Demo..."
echo "========================================"
echo ""
./cli_pipeline
