# -*- coding: utf-8 -*-

import kage

from test.base import BaseTestCase


class CommonFunctionTest(BaseTestCase):

    def test_show_version(self):
        self.assertEqual(type(kage.ext_version()), type('str type'))
