from PySide6 import QtCore, QtGui
from PySide6.QtCore import Qt

class TableModel(QtCore.QAbstractTableModel):
    def __init__(self, t, x, z):
        super(TableModel, self).__init__()
        self._data = z
        self.time = t
        self.coord = x

    def data(self, index, role):
        if role == Qt.DisplayRole:
            value = round(self._data[index.column(), index.row()], 5)
            return str(value)

    def rowCount(self, index):
        return self._data.shape[0]

    def columnCount(self, index):
        return self._data.shape[1]

    def headerData(self, section, orientation, role):
        # section is the index of the column/row.
        if role == Qt.DisplayRole:
            if orientation == Qt.Horizontal:
                return 'x' + str(section) + '\n' + str(round(self.coord[section], 5))

            if orientation == Qt.Vertical:
                return 't' + str(section) + '\n' + str(round(self.time[section], 5))

        if role == Qt.TextAlignmentRole:
            return Qt.AlignCenter
