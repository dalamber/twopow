{
  "targets": [
    {
      "target_name": "twopow",
      "sources": [
        "native/twopow_addon.c",
        "native/vendor/twopow.cpp",
        "native/vendor/twopow_c.cpp"
      ],
      "include_dirs": [ "native/vendor" ],
      "cflags_cc": [ "-std=c++20", "-fexceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "xcode_settings": {
        "CLANG_CXX_LANGUAGE_STANDARD": "c++20",
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
        "MACOSX_DEPLOYMENT_TARGET": "11.0"
      },
      "msvs_settings": {
        "VCCLCompilerTool": { "AdditionalOptions": [ "/std:c++20", "/EHsc" ] }
      }
    }
  ]
}
