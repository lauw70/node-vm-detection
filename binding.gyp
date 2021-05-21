{
    "conditions": [
        ['OS=="win"', {
            "targets": [
                {
                    "target_name": "vm_detection",
                    "sources": [
                        "src/binding.c",
                        "src/pafish/utils.c",
                        "src/pafish/cpu.c",
                        "src/pafish/vmware.c",
                        "src/pafish/vbox.c",
                        "src/pafish/qemu.c",
                        "src/pafish/wine.c",
                        "src/pafish/sandboxie.c"
                    ],
                    "libraries": [
                        "-lwsock32",
                        "-liphlpapi",
                        "-lsetupapi",
                        "-lmpr",
                        "-lole32",
                        "-lwbemuuid",
                        "-loleaut32",
                        "-lws2_32"
                    ],
                    "include_dirs": [
                        "<!(node -e \"require('napi-macros')\")"
                    ],
                }
            ]
        }]
    ],
    "targets": [
        {
            'target_name': 'node_winreglib',
            'type': 'none'
        }
    ]
}
