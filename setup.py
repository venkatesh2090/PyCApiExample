from distutils.core import setup, Extension

module1 = Extension('spam', sources=['spammodule.c'])

setup (name = 'spam',
       version = '1.0',
       description = 'First c etension \'spam\'',
       ext_modules = [module1])