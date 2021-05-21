
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "types.h"
#include "cpu.h"

static inline uint64_t rdtsc_diff()
{
	uint64_t ret = __rdtsc();
	uint64_t ret2 = __rdtsc();
	return ret2 - ret;
}

static inline uint64_t rdtsc_diff_vmexit()
{
	uint64_t ret = __rdtsc();

	int cpuid[4];
	__cpuid(cpuid, 0);

	uint64_t ret2 = __rdtsc();

	return ret2 - ret;
}

static inline void cpuid_vendor(char *vendor, uint32_t eax_value, int * reg_order) // vendor: char[13], reg_order: int[3]
{
	// get cpu identity data
	int cpuinfo[4];
	__cpuid(cpuinfo, eax_value);

	// construct vendor string
	for (int i = 0; i < 3; i++)
	{
		sprintf(vendor + 4 * i, "%c%c%c%c", cpuinfo[reg_order[i]], cpuinfo[reg_order[i]] >> 8, cpuinfo[reg_order[i]] >> 16, cpuinfo[reg_order[i]] >> 24);
	}
	vendor[12] = 0x00;
}

static inline void cpuid_brand(char *brand, uint32_t eax_value) // brand: char[16]
{
	// get cpu identity data
	int cpuinfo[4];
	__cpuid(cpuinfo, eax_value);

	// construct vendor string
	int reg[] = {0, 1, 2, 3};
	for (int i = 0; i < 4; i++)
	{
		sprintf(brand + 4 * i, "%c%c%c%c", cpuinfo[reg[i]], cpuinfo[reg[i]] >> 8, cpuinfo[reg[i]] >> 16, cpuinfo[reg[i]] >> 24);
	}
}

static inline int cpuid_hv_bit()
{
	int cpuinfo[4];
	__cpuid(cpuinfo, 1);
	return (cpuinfo[2] >> 31) & 0x1;
}

CpuRdtscResult cpu_rdtsc(int force_vm_exit, int n_samples, uint64_t *samples, int interval)
{
	CpuRdtscResult result = {0};
	for (int i = 0; i < n_samples; i++)
	{
		if (i > 0)
			Sleep(interval);
		
		uint64_t sample;
		if (force_vm_exit)
		{
			sample = rdtsc_diff();
		}
		else
		{
			sample = rdtsc_diff_vmexit();
		}
		samples[i] = sample;
		result.average += samples[i];
	}

	result.average /= n_samples;
	result.is_vm = result.average >= (force_vm_exit ? 1000 : 750);
	return result;
}

int cpu_hv()
{
	return cpuid_hv_bit() ? TRUE : FALSE;
}

void cpu_write_vendor(char *vendor) // char[13]
{
	int reg_order[] = {1,3,2};
	cpuid_vendor(vendor, 0, reg_order);
}

void cpu_write_hv_vendor(char *vendor)
{
	int reg_order[] = {1,2,3};
	cpuid_vendor(vendor, 0x40000000, reg_order);
}

void cpu_write_brand(char *brand) // brand: char[49]
{
	cpuid_brand(brand, 0x80000002);
	cpuid_brand(brand + 16, 0x80000003);
	cpuid_brand(brand + 32, 0x80000004);
	brand[48] = 0x00;
}

int cpu_known_vm_vendors()
{
	char cpu_hv_vendor[13];
	string strs[] = {
		"KVMKVMKVM\0\0\0", /* KVM */
		"Microsoft Hv",	   /* Microsoft Hyper-V or Windows Virtual PC */
		"VMwareVMware",	   /* VMware */
		"XenVMMXenVMM",	   /* Xen */
		"prl hyperv  ",	   /* Parallels */
		"VBoxVBoxVBox",	   /* VirtualBox */
	};

	cpu_write_hv_vendor(cpu_hv_vendor);
	for (int i = 0; i < 6; i++)
	{
		if (!memcmp(cpu_hv_vendor, strs[i], 12))
			return TRUE;
	}
	return FALSE;
}
