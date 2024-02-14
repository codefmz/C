machine_type=$(uname -m)
echo "Machine type is: $machine_type"
if [ $# != 1 ];
then
    echo "Invalid argument!"
    exit 1
fi

script_dir="$(cd "$(dirname "$0")" && pwd)"
echo "Script is located in: $script_dir"

if [ -e "lib/gtest/" ] && [ -e "include/gtest" ]; then
    echo "gtest exist "
else
    sh ../Gtest/build.sh $script_dir
fi

if [ -e "lib/util/" ] && [ -e "include/util/" ]; then
    echo "util exist "
else
    sh ../Util/build.sh $script_dir
fi


# cmake -DVAR_NAME="$MakeProject" ..
cd build/
cmake ..
# echo "project $0 make $1"
make ringbuffer_test
rm -rf ./*
