{
    "targets": [
        {
            "target_name": "vm_detection",
            "sources": [
                "src/binding.c",
                "src/pafish/cpu.c"
            ],
            "include_dirs": [
                "<!(node -e \"require('napi-macros')\")"
            ],
        }
    ]
}
