import numpy as np
import math
from nshe_solver import SolverNSHE, nshe_solve
from non_stationary_heat_equation import NonStationaryHeatEquation
import sys
from matplotlib import cm
from PySide6.QtWidgets import QMainWindow, QApplication, QVBoxLayout, QWidget
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg, NavigationToolbar2QT
from matplotlib.figure import Figure
from mpl_toolkits.mplot3d.axes3d import Axes3D


class MplCanvas(FigureCanvasQTAgg):

    def __init__(self, parent=None):
        fig = Figure(layout='constrained')
        self.axes = fig.add_subplot(projection='3d')
        super(MplCanvas, self).__init__(fig)


class MainWindow(QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)

        task = NonStationaryHeatEquation(
            gamma=5,
            g=lambda x, t: math.sin(t),
            a=0, b=1, T=10,
            phi=lambda x: 1 - x**2,
            mu1=lambda t: math.cos(t),
            mu2=lambda t: math.sin(4*t)
        )
        task1 = NonStationaryHeatEquation(
            gamma=3,
            g=lambda x, t: t * math.cos(x * math.pi) / (t + 1),
            a=0, b=1, T=10,
            phi=lambda x: 1 - x ** 2,
            mu1=lambda t: math.cos(t),
            mu2=lambda t: math.sin(4 * t)
        )
        n = 20
        m = 20
        solver = SolverNSHE(task, n, m)
        solver.calculate_numerical_solution()
        result = solver.get_result()

        time = np.linspace(0, task.T, m+1)
        coord = np.linspace(task.a, task.b, n+1)
        time, coord = np.meshgrid(time, coord)
        z = np.matrix(result)
        # z = nshe_solve()

        sc = MplCanvas(self)
        # sc.axes.get_proj = lambda: np.dot(Axes3D.get_proj(sc.axes), np.diag([1, 0.5, 0.5, 1]))
        sc.axes.plot_surface(time, coord, z, cmap=cm.coolwarm)
        sc.axes.set_ylabel('x (сечение)')
        sc.axes.set_xlabel('t (время)')
        sc.axes.set_zlabel('V (температура)')
        sc.axes.set_title('График температур')

        toolbar = NavigationToolbar2QT(sc, self)

        layout = QVBoxLayout()
        layout.addWidget(toolbar)
        layout.addWidget(sc)

        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)

        self.show()


app = QApplication(sys.argv)
w = MainWindow()
app.exec()
