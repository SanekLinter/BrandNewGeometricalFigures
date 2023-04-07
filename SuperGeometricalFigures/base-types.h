/*
содержащий определени€ следующих структур:
point_t, представл€ющую собой точку на плоскости. оординаты должны
хранитьс€ в пол€х x и y.
rectangle_t, описывающую пр€моугольник шириной width и высотой height с
центром в точке pos.
*/
#ifndef BASE_TYPES_H
#define BASE_TYPES_H
struct point_t {
	double x;
	double y;
};

struct rectangle_t {
	double width;
	double height;
	point_t pos;
};
#endif