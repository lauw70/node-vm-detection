const vm_detection = require('./index');

console.log('Running test');

console.log('cpuRdtsc', vm_detection.cpuRdtsc(false, 10, 500));
console.log('cpuRdtsc+vm exit', vm_detection.cpuRdtsc(true, 10, 500));
console.log('cpuRdtsc+max interval', vm_detection.cpuRdtsc(true, 10, 5000));
console.log('cpuRdtsc+max samples+max interval', vm_detection.cpuRdtsc(true, 10 * 1024 * 1024, 5000));

console.log('cpu info', vm_detection.cpuInfo());
console.log('vmware', vm_detection.vmware());
console.log('virtual box', vm_detection.virtualBox());
console.log('qemu', vm_detection.qemu());
console.log('wine', vm_detection.wine());
console.log('sandboxie', vm_detection.sandboxie());
