# -*- coding: utf-8 -*-

try:
    import kageext
except:
    # Sphinx-doc need to import modules first to generate auto docs,
    # but I cann't figure out how to let it import C extension
    kageext = None


def ext_version():
    return kageext.eversion()


class SubscriptProxy(object):

    def __init__(self, datarobot2d, role='row'):
        """下标获取代理

        :param datarobot2d: 代理对象
        :param role: 代理角色, row 或者是 column
        """
        self._datarobot2d = datarobot2d
        self._role = role

    def __getitem__(self, item):
        """根据下标获取数据

        支持的格式有:

            1. sp[0]
            2. sp['name']
            3. sp[-1]
            4. sp[0, 3, 4]
            5. sp['namea', 'nameb', 'namec']
        """
        return self._datarobot2d._get_item(self._role, item)


class DataRobot2D(object):
    """DataRobot 2D,用于操作二维数据"""

    def __init__(self, data=None, columns=tuple(), index=tuple(), obj_id=None):
        if obj_id is None:
            columns = tuple(columns)
            index = tuple(index)

            self._cpp_obj_id = kageext.call('create_datarobot2d',
                                            (data, columns, index))
        else:
            self._cpp_obj_id = obj_id

        self.r = SubscriptProxy(self, 'row')
        self.c = SubscriptProxy(self, 'column')

    def __get_cpp_obj_id(self):
        return self._cpp_obj_id

    def get_cpp_obj_id(self):
        return self.__get_cpp_obj_id()

    def __str__(self):
        datarobot2d_str = kageext.call('str', (self.__get_cpp_obj_id(),))
        return datarobot2d_str

    def __repr__(self):
        return self.__str__()

    def __del__(self):
        kageext.call('deconstruct_datarobot2d', (self.__get_cpp_obj_id(),))

    def __getitem__(self, item):
        return self._get_item('row', item)

    def _get_item(self, role, item):
        if role == 'row':
            return self._get_item_by_row(item)
        elif role == 'column':
            return self._get_item_by_column(item)

    def _get_item_by_row(self, item):
        result = None
        item_type = type(item)
        # 直接通过行标识进行获取,如sp['name']
        if item_type == str:
            obj_id = kageext.call('get_item_by_row_type_str',
                                  (self.__get_cpp_obj_id(), item))
            result = DataRobot2D(obj_id=obj_id)
        else:
            raise KeyError("key type not supported")
        return result

    def _get_item_by_column(self, item):
        pass


