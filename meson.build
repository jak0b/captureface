project('captureface',
        'cpp',
        version : '0.1',
        license: 'MIT',
        default_options : [
          'warning_level=2',
          'werror=true',
          'cpp_std=c++17'
        ]
  )

opencv = dependency('opencv4')

executable('captureface',
           'main.cpp',
           dependencies : opencv,
           install : true
)
