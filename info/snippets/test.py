from matplotlib.lines import Line2D
from sympy import Point2D

x = Line2D(Point2D(189, 219), Point2D(189, 583))

if isinstance(x, Line2D):
    print("x is a Line2D object.")
elif isinstance(x, Point2D):
    print("x is a Point2D object.")
else:
    print("x is neither a Line2D nor a Point2D.")