#ifndef __UENGINE_VECTOR2D_H__
#define __UENGINE_VECTOR2D_H__
#include <stdio.h>
class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);

	friend Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2); //Sobrecargando el operador como funcion friend
	friend Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2); //Sobrecargando el operador como funcion friend
	friend Vector2D operator*(const Vector2D& vec1, const Vector2D& vec2); //Sobrecargando el operador como funcion friend
	friend Vector2D operator/(const Vector2D& vec1, const Vector2D& vec2); //Sobrecargando el operador como funcion friend

	friend Vector2D operator+(const Vector2D& vec1, const float scale); //Sobrecargando el operador como funcion friend
	friend Vector2D operator-(const Vector2D& vec1, const float scale); //Sobrecargando el operador como funcion friend
	friend Vector2D operator*(const Vector2D& vec1, const float scale); //Sobrecargando el operador como funcion friend
	friend Vector2D operator/(const Vector2D& vec1, const float scale); //Sobrecargando el operador como funcion friend


	float magnitude() const; //Declarando la funcion para hallar la magnitud
	float dotProduct(Vector2D vec1, Vector2D vec2) const; //Declarando la funcion para hacer el producto escalar
	float Angle(const Vector2D& other) const; //Declarando la funcion para hallar el angulo entre dos vectores
	float Distance(const Vector2D& other) const; //Declarando la funcion para hallar la distancia

	float getX() const { return m_x; } //Funcion que nos retorna el valor de x
	float getY() const { return m_y; } //Funcion que nos retorna el valor de y

	void Setx(float x);
	void Sety(float y);

private:
	float m_x, m_y; //Miembros privados de la calse
};

#endif // !UENGINE-VECTOR2D-H

