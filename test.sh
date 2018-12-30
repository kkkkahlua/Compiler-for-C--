#!/bin/bash 
for i in {1..10}  
do  
./parser test4/Test/$i.cmm test4/Test/output/$i.s
done  
for i in {1..3}
do
./parser test4/TestA/$i.cmm test4/TestA/output/$i.s
done  
for i in {1..2}
do
./parser test4/TestB/$i.cmm test4/TestB/output/$i.s
done  
for i in {1..1}
do
./parser test4/TestC/$i.cmm test4/TestC/output/$i.s
done  