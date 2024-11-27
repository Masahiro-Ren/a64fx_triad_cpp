#!/bin/sh -x

# The Fujitsu environment variables must be exported
# It's a good idea to set FLIB_HPCFUNC_INFO=TRUE and
# XOS_MMM_L_PRINT_ENV=on to confirm that the environment
# is configured correctly at runtime
export FLIB_SCCR_CNTL=TRUE
export FLIB_HPCFUNC=TRUE
export FLIB_HPCFUNC_INFO=TRUE
export FLIB_FASTOMP=TRUE
export FLIB_BARRIER=HARD
export OMP_NUM_THREADS=48
export XOS_MMM_L_HPAGE_TYPE=hugetlbfs
export XOS_MMM_L_PAGING_POLICY=demand:demand:demand
export XOS_MMM_L_PRINT_ENV=on

./stream_triad.exe
