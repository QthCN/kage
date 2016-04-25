# -*- coding: utf-8 -*-

try:
    import kageext
except:
    # Sphinx-doc need to import modules first to generate auto docs,
    # but I cann't figure out how to let it import C extension
    kageext = None


def ext_version():
    return kageext.eversion()


class DataRobot2D(object):
    """DataRobot 2D,用于操作二维数据"""

    def __init__(self, data, columns, index):
        columns = tuple(columns)
        index = tuple(index)

        self._cpp_obj_id = kageext.call('create_datarobot2d',
                                        (data, columns, index))
        print(u'obj_id: {0}'.format(self._cpp_obj_id))

    def __get_cpp_obj_id(self):
        return self._cpp_obj_id

    def get_metadata(self):
        """获取DataRobot2D的元数据

        :returns: (numpy矩阵, 列名, 行名)
        :rtype: 元组
        """
        datarobot2d = kageext.call('get_datarobot2d_content',
                                   (self.__get_cpp_obj_id(),))
        return datarobot2d

    def __str__(self):
        datarobot2d = self.get_metadata()
        datarobot2d_str = 'columns: {c}\nindex: {i}\nndarray:\n {a}'.format(
            c=datarobot2d[1],
            i=datarobot2d[2],
            a=datarobot2d[0]
        )
        return datarobot2d_str

    def __del__(self):
        kageext.call('deconstruct_datarobot2d', (self.__get_cpp_obj_id(),))
