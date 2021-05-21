
const projectRoot = `${__dirname}/..`;
const binding = require('node-gyp-build')(projectRoot);

module.exports = {
    /**
     * @typedef {Object} RtdscResult
     * @property {Number} average - the average value between samples
     * @property {Boolean} isVM - whether the average sample rate was above 1000 (forceVMexit=true) or above 750 (forceVMexit=false)
     * @property {Array} samples - an array containing all the samples that were taken
     */

    /**
     * RDTSC performs a timing trick on the CPU that forces the hypervisor, if active to suspend execution, which in turn forces a context switch.
     * This allows us to sample the timing between the RTDSC calls and, if a hypervisor is running, introduce a measurable lag in sample timings.
     * 
     * @param forceVMexit {Boolean} - Force the hypervisor to interrupt normal flow. Required on modern CPUs for this check to work.
     * @param numSamples {Number} - The amount of samples to take
     * @param intervalMs {Number} - The amount of milliseconds to sleep between samples
     * 
     * @returns {RtdscResult}
     * 
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