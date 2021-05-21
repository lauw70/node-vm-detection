# Windows VM detection based on pafish

This addon wraps a copy of [pafish](https://github.com/a0rtega/pafish) for easy detection if you're running
in a VM or not.

Currently the following features/vendors are supported:

- basic CPU information
- RDTSC timing attack
- vmware
- virtualbox
- qemu
- wine
- sandboxie

## Get started
This node addon only works on Windows for now. No effort is made to even attempt to support MacOS or Linux.

In order to compile this addon, you'll need the following:
* Visual Studio 2017 or later
* The windows visual C++ libraries
* python
* Node 12+ (prefer LTS versions over current and uneven releases)


From there, just run:
```bash
$ npm install
$ npm run build
$ npm run test
```

For more examples, take a look at `test.js` on how the API can be used.
