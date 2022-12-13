from non_stationary_heat_equation import NonStationaryHeatEquation
from nshe_solver import nshe_solve
import pandas as pd
import numpy as np

t = np.linspace(0, 100, 5)
x = np.linspace(0, 1, 5)
z = nshe_solve(NonStationaryHeatEquation(), 4, 4)
df = pd.DataFrame(z).transpose()
df.to_excel('my_calc_by_hand.xlsx', index=False)



