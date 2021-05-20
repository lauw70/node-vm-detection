const vm_detection = require('./build/Release/vm_detection.node');

console.log('Running test');

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
console.log('cpuRdtsc', vm_detection.cpuRdtsc(false, 10, 500));
console.log('cpuRdtsc+vm exit', vm_detection.cpuRdtsc(true, 10, 500));

console.log('cpu info', vm_detection.cpuInfo());
console.log('vmware', vm_detection.vmware());
console.log('virtual box', vm_detection.virtualBox());
console.log('qemu', vm_detection.qemu());
console.log('wine', vm_detection.wine());
console.log('sandboxie', vm_detection.sandboxie());
