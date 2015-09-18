#!/bin/bash

for IND in $(seq 166188 166242)
do
    condor_rm ${IND}.0
done
