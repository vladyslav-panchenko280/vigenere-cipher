{
  'targets': [
    {
      'target_name': 'vigenere_plus',
      'sources': [ 'src/vigenere_plus.c' ],
      'include_dirs': [
          "<!@(node -p \"require('node-addon-api').include\")",
          "../node_modules/node-addon-api",                                                    
          "node_modules/node-addon-api",                                                       
          "/usr/include/node",                                                                 
          "/usr/local/include/node",
          ],
      "libraries": [ "-lcs50" ], 
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7'
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      }
    }
  ]
}