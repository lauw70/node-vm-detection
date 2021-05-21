const binding = require('node-gyp-build')(`${__dirname}/..`);

module.exports = {
    /**
     * RDTSC performs a timing attach on the hyperversior
     * [0]: force the hypervisor to interrupt normal flow. Required on modern CPUs for this check to work
     * [1]: number of samples to take
     * [2]: miliseconds of sleep between the samples
     * Returns: {
     *   average: number, average between samples
     *   isVM: boolean, whether the average was above 1000 (force=true) or 750 (force=false)
     *   samples: number[], all the samples that were taken
     * }
     */
    cpuRdtsc(forceVMexit, numSamples, intervalMs) {
        return binding.cpuRdtsc(forceVMexit, numSamples, intervalMs);
    },
    cpuInfo() {
        return binding.cpuInfo();
    },
    vmware() {
        return binding.vmware();
    },
    virtualBox() {
        return binding.virtualBox();
    },
    qemu() {
        return binding.qemu();
    },
    wine() {
        return binding.wine();
    },
    sandboxie() {
        return binding.sandboxie();
    }
};