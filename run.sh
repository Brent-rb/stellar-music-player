#!/bin/zsh
opt_build=false
opt_test=false
opt_docs=false
opt_run=false

mkdir -p logs

while getopts "btfdr" flag; do
 case $flag in
   b) # Handle the -h flag
    opt_build=true
   ;;
   t) # Handle the -v flag
    opt_test=true
   ;;
   d)
    opt_docs=true
    ;;
    r)
    opt_run=true
    ;;
   \?)
   # Handle invalid options
   ;;
 esac
done

if [ "$opt_build" = true ]; then
    echo "Building..."
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S all -B build 
    cmake --build build 
    echo "Building complete"
fi

if [ "$opt_test" = true ]; then
    ./build/test/StellarTests
fi

if [ "$opt_docs" = true ]; then
    echo "Generating docs..."
    source ./.venv/bin/activate 
    cmake -S documentation -B build/doc &> logs/build_docs.txt
    cmake --build build/doc --target GenerateDocs &>> logs/build_docs.txt
    deactivate
    echo "Docs generated"
fi

if [ "$opt_run" = true ]; then
    ./build/standalone/Stellar
fi