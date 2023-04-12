/*
Реализовать класс CompositeShape, производный от Shape (см. раздел «Фигуры»),
представляющий собой составную фигуру и хранящий массив в динамической памяти
из произвольных фигур, реализованных в вашей программе. Объекты класса
должны корректно копироваться и перемещаться. При добавлении базовой
(прямоугольник, круг и т.п.) фигуры в составную, добавляться должна копия базовой
фигуры.
Составная фигура. Состоит из нескольких простых (не составных) фигур.
Описывается на нескольких строках, начинаясь и завершаясь специальными
командами (всегда находятся на отдельных строках). В первой строке указывается
параметр – максимально возможное количество простых фигур. Центром фигуры
считается центр ограничивающего прямоугольника
COMPLEX 5
ELLIPSE 2.0 3.0 15.0
RECTANGLE -5.0 -3.0 3.0 4.0
ELLIPSE 1.0 1.0 10.0
SQUARE -1.5 -1.5 10.0
SQUARE 0.0 0.0 5.0
COMPLEXEND
*/
#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include "shapecollection.h"
class CompositeShape : public Shape
{
public:
	// construct/copy/move/destrust
	CompositeShape(ShapeCollection&& src);
	CompositeShape(const CompositeShape& other);
	CompositeShape(CompositeShape&& other)                 = delete;
	CompositeShape& operator=(const CompositeShape& other) = delete;
	CompositeShape& operator=(CompositeShape&& other)      = delete;
	~CompositeShape() = default;
	// members
	double		getArea() const override;
	rectangle_t getFrameRect() const override;
	void		move(const point_t& point) override;
	void		move(const double dx, const double dy) override;
	void		scale(const double zoomRatio) override;
	std::string getName() const override;
	shape_ptr_t clone() const override;
private:
	ShapeCollection _shapes;
	rectangle_t     _frameRect;
};
#endif