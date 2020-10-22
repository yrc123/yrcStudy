#!/bin/bash
n=10
datesize=(10 10 100 100 1000 1000 1000 10000 100000 100000)
echo compile "./标程/std.cpp"
g++ ./标程/std.cpp -o ./std
echo compile "./date.cpp"
g++ ./date.cpp -o ./date
echo --------------------------
for((i=0;i<n;i++));  
do   
	echo "${datesize[i]}">./tmp
	echo $i.in
    echo "数据大小:${datesize[i]}"
	time ./date<./tmp>./数据/$i.in
	echo $i.out
	time ./std<./数据/$i.in>./数据/$i.out
	echo
done

echo --------------------------
echo rm ./tmp
rm ./tmp
echo remove "./std"
rm ./std
echo remove "./date"
rm ./date
