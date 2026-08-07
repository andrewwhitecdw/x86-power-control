#!/usr/bin/env python3
import re
import sys


def main():
    with open('service_files/xyz.openbmc_project.Chassis.Control.Power@.service', 'r') as f:
        text = f.read()
    m = re.search(r'^BusName=(.*)$', text, re.MULTILINE)
    if not m:
        print('FAIL: BusName not found in templated service file')
        sys.exit(1)
    bus_name = m.group(1)
    if '%' not in bus_name:
        print(f'FAIL: templated service BusName must contain an instance specifier, got {bus_name}')
        sys.exit(1)
    print(f'PASS: BusName contains instance specifier: {bus_name}')


if __name__ == '__main__':
    main()
