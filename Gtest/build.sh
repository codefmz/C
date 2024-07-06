echo "begin compile gtest!"
script_dir="$(cd "$(dirname "$0")" && pwd)" # $0表示当前脚本的名字
echo "cur script path name : $script_dir"

cd ${script_dir}/googletest/build/
cmake ..
make

# 如果是其他脚本来执行本脚本，就将本脚本的动态库与头文件分别拷贝到目标项目的lib目录与include目录
if [ $# == 0 ];
then
    exit 0
fi

target_dir=$1
target_include="${target_dir}/include/"
target_lib="${target_dir}/lib/"

echo "gtest : target_dir = ${target_dir} target_include = $target_include target_lib = $target_lib"
cp lib/* ${target_lib}
cd ${script_dir}/googletest/googletest/
cp -rf include/* ${target_include}