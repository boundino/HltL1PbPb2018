#!/bin/bash

CONFIG="expHLT_102X_cfg_DUMP"
LOG="logs/expmenu"
TXT="logs/expevtmemory"

for i in {0..9}
do
    cmsRun ${CONFIG}_iter0to$i.py 2>&1 | tee ${LOG}_iter0to$i.log
    cat ${LOG}_iter0to$i.log | grep --color=auto MemoryCheck:' 'event > ${TXT}_iter0to$i.txt
    ./sryMemoryEvt.exe ${TXT}_iter0to$i.txt 100 100
done