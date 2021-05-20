
#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct
{
    uint64_t average;
    int is_vm;
} CpuRdtscResult;

CpuRdtscResult cpu_rdtsc(int force_vm_exit, int n_samples, uint64_t * samples, int interval);

int cpu_hv();

void cpu_write_vendor(char *);    // char[13]
void cpu_write_hv_vendor(char *); // char[13]
void cpu_write_brand(char *);     // char[49]

int cpu_known_vm_vendors();

#endif
