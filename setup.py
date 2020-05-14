from distutils.core import setup, Extension

module1 = Extension('pyternals',
                    sources = ['main.cpp'])

setup (name = 'pyternals',
       version = '1.0',
       description = 'Parse python3.8 interpretor environment',
       ext_modules = [module1])
