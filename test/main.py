# -*- coding: utf-8 -*-

import configparser

import nose


config_file_path = 'etc/test.ini'


def init_config():
    cf = configparser.ConfigParser()
    cf.read(config_file_path)


def run_test():
    init_config()
    nose.main()


if __name__ == '__main__':
    run_test()
