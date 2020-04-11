from setuptools import setup, Extension

spam = Extension('spam', sources=['spam.c'])

setup (
    name = 'spam',
    version = '0.1',
    description = 'Trying to instantiate an object from C',
    ext_modules = [spam],
    packages = [],
)

