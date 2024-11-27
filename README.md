# a64fx_triad_cpp
 stream triad implemented in cpp

# notes
1. Using `-Krestp=all` or `-Krestp=arg` option make compiler consider pointers are decorated with "restrict" as in C99. Otherwise the compiler cannot apply vectorization and `zfill` to the kernel.
2. Without `zfill`, the kernel can only achieve 620 GB/s Best rate. 
3. Some Fujitsu environment variables should also be exported as shown in job.sh
# result
```
Size per array: 8192 MB
Size per element: 8 bytes
Executing 20 times
Best rate: 820772 MB/s
Max time:0.0300124 s
Min time:0.0299425 s
Avg time:0.0299557 s
```

# references:
1. [Arm HPC Resources/training/arm-sev-tools](https://gitlab.com/arm-hpc/training/arm-sve-tools/-/tree/master/06_A64FX/02_stream/05_stream_fujitsu?ref_type=heads)
2. [Fujitsu C++ Compiler Manual](https://software.fujitsu.com/jp/manual/manualfiles/m230008/j2ul2583/03z004/j2ul-2583-03z0.pdf)