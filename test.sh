#!/bin/bash 
for i in {1..9}  
do  
./parser test4/Test/$i.cmm test4/Test/output/$i.ir test4/Test/output/$i.s
done  
for i in {1..2}
do
./parser test4/TestA/$i.cmm test4/TestA/output/$i.ir test4/TestA/output/$i.s
done  