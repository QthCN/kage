# -*- coding: utf-8 -*-

import numpy as np

import kage

from test.base import BaseTestCase


class KageClassTest(BaseTestCase):

    def test_create_object_no_exception(self):
        array = np.array([[1.1, 2.2, 3.3], [1.2, 1.3, 1.4]])
        k = kage.DataRobot2D(array, ['a1', 'b1', 'c1'], ['A2', 'B2'])
