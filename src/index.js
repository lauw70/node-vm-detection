
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
     * @typedef {Object} CpuInfoResult
     * @property {String} vendor - the vendor string of the current CPU
     * @property {String} hypervisorVendor - the vendor string of the hypervisor, if applicable
     * @property {Boolean} hv_bit - indicates if the current CPU has the hypvervisor bit set
     * @property {String} brand - the full brand of the current CPU, as reported by the OS
     * @property {Boolean} knownVMVendor - indicates if the VM vendor is a well known VM vendor
    */

    /**
     * @typedef {Object} VMWareResult
     * @property {Boolean} scsi - 
     * @property {Boolean} registry -
     * @property {Boolean} mouseDriver -
     * @property {Boolean} graphicsDriver -
     * @property {Boolean} macAddress -
     * @property {Boolean} devices -
     * @property {Boolean} wmiSerial -
    */

    /**
     * @typedef {Object} VMWareResult
     * @property {Boolean} scsi - 
     * @property {Boolean} registry -
     * @property {Boolean} mouseDriver -
     * @property {Boolean} graphicsDriver -
     * @property {Boolean} macAddress -
     * @property {Boolean} devices -
     * @property {Boolean} wmiSerial -
     */

    /**
     * @typedef {Object} VirtualBoxResult
     * @property {Boolean} scsi - 
     * @property {Boolean} biosVersion -
     * @property {Boolean} guestAdditions -
     * @property {Boolean} videoBiosVersion -
     * @property {Boolean} acpi -
     * @property {Boolean} fadtAcpi -
     * @property {Boolean} rsdtAcpi -
     * @property {Boolean} service -
     * @property {Boolean} systemBiosDate -
     * @property {Boolean} deviceDrivers -
     * @property {Boolean} systemFiles -
     * @property {Boolean} nicMacAddress -
     * @property {Boolean} trayWindow -
     * @property {Boolean} sharedNetwork -
     * @property {Boolean} processes -
     * @property {Boolean} wmi -
     */

    /**
     * @typedef {Object} QEMUResult
     * @property {Boolean} scsi - 
     * @property {Boolean} systemBios -
     * @property {Boolean} cpuBrand -
     */

     /**
     * @typedef {Object} WineResult
     * @property {Boolean} unixFileName - 
     * @property {Boolean} systemBios -
     * @property {Boolean} cpuBrand -
     */

     /**
     * @typedef {Object} SandboxieResult
     * @property {Boolean} dll - 
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
    cpuRdtsc: (forceVMexit, numSamples, intervalMs) => {
        return binding.cpuRdtsc(forceVMexit, numSamples, intervalMs);
    },
    /**
     * @returns {CpuInfoResult}
     */
    cpuInfo: () => binding.cpuInfo(),
    /**
     * @returns {VMWareResult}
     */
    vmware:() => binding.vmware(),
    /**
     * @returns {VirtualBoxResult}
     */
    virtualBox: () => binding.virtualBox(),
    /**
     * @returns {QEMUResult}
     */
    qemu: () => binding.qemu(),
    /**
     * @returns {WineResult}
     */
    wine: () => binding.wine(),
    /**
     * @returns {SandboxieResult}
     */
    sandboxie: () => binding.sandboxie(),
    
};