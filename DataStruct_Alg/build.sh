machine_type=$(uname -m)
echo "Machine type is: $machine_type"
if [ $# != 1 ];
then
    echo "Invalid argument!"
    exit 1
fi

MakeProject=$1
echo "tttt = $MakeProject"
cd ./build/
cmake -DVAR_NAME="$MakeProject" ..
echo "project $0 make $1"
make $1
rm -rf ./*
