from setuptools import Extension
from setuptools import setup

ext = Extension(
    'pywn',
    sources=['./src/pywn.c', './src/notes.zig'],
    extra_compile_args=['-z', 'relro', '-z', 'lazy'],
)

setup(
    name='pywn',
    version='0.1',
    python_requires='>=3.14.5',
    build_zig=True,
    ext_modules=[ext],
    setup_requires=['setuptools-zig==0.5.3', 'ziglang==0.16.0'],
)
