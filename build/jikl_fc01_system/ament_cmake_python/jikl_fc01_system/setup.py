from setuptools import find_packages
from setuptools import setup

setup(
    name='jikl_fc01_system',
    version='0.1.0',
    packages=find_packages(
        include=('jikl_fc01_system', 'jikl_fc01_system.*')),
)
