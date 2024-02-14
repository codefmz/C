machine_type=$(uname -m)
echo "Machine type is: $machine_type"

if [ $# != 1 ];
then
    echo "Invalid argument!"
    exit 1
fi

script_dir="$(cd "$(dirname "$0")" && pwd)" #脚本所在的位置
# echo "child Script is located in: $script_dir"

target_dir=$1
target_include="${target_dir}/include/gtest/"
target_lib="${target_dir}/lib/gtest/"
echo "target_dir = ${target_dir}    target_include = $target_include    target_lib = $target_lib"

cd ${script_dir}/googletest/googletest/
cp -rf include/* ${target_include}

cd ${script_dir}/googletest/build/
cmake ..
make
mkdir ${target_lib}
cp lib/* ${target_lib}
rm -rf *





