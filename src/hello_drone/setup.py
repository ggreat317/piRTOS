from setuptools import find_packages, setup

package_name = 'hello_drone'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ggrea',
    maintainer_email='ggreat317@gmail.com',
    description='Heartbeat publisher for testing the companion computer environment.',
    license='MIT',
    entry_points={
        'console_scripts': [
            'heartbeat = hello_drone.heartbeat:main',
        ],
    },
)
