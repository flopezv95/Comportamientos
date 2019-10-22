#include "stdafx.h"
#include "Vector2D.h"
#include <math.h>


Vector2D::Vector2D() { //Definicion de nuestro constructor

	this->m_x = 0;
	this->m_y = 0;
}

Vector2D::Vector2D(float x, float y) { //Definicion de nuestro constructor

	this->m_x = x;
	this->m_y = y;
}

Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x + vec2.m_x; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y + vec2.m_y; //Realizando la operacion para la componenete y

	return *vecRet;
}
Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x - vec2.m_x; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y - vec2.m_y; //Realizando la operacion para la componenete y

	return *vecRet;
}

Vector2D operator*(const Vector2D& vec1, const Vector2D& vec2) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x *vec2.m_x; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y *vec2.m_y; //Realizando la operacion para la componenete y

	return *vecRet;
}

Vector2D operator/(const Vector2D& vec1, const Vector2D& vec2) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x / vec2.m_x; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y / vec2.m_y; //Realizando la operacion para la componenete y

	return *vecRet;

}

Vector2D operator+(const Vector2D& vec1, const float scale) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x + scale; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y + scale; //Realizando la operacion para la componenete y

	return *vecRet;
}

Vector2D operator-(const Vector2D& vec1, const float scale) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x + scale; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y + scale; //Realizando la operacion para la componenete y

	return *vecRet;

}

Vector2D operator*(const Vector2D& vec1, const float scale) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x * scale; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y * scale; //Realizando la operacion para la componenete y

	return *vecRet;

}

Vector2D operator/(const Vector2D& vec1, const float scale) { //Definicion de nuestro operador sobrecargado

	Vector2D *vecRet = new Vector2D(0.0f, 0.0f); //Vector a devolver
	vecRet->m_x = vec1.m_x / scale; //Realizando la operacion para la componenete x
	vecRet->m_y = vec1.m_y / scale; //Realizando la operacion para la componenete y

	return *vecRet;
}

float Vector2D::magnitude() const { //Definiendo la funcion para hallar la magnitud

	float posX = static_cast<float>(pow(m_x, 2));
	float posY = static_cast<float>(pow(m_y, 2));
	float absVector = static_cast<float>(sqrt(posX + posY));

	return absVector;

}

float Vector2D::dotProduct(Vector2D vec1, Vector2D vec2) const { //Definir la funcion para hacer el producto punto

	float ret = ((vec1.m_x*vec2.m_x) + (vec1.m_y*vec2.m_y));

	return ret;

}

float Vector2D::Angle(const Vector2D& other) const { //Definir la funcion para sacar el angulo entre dos vectores

	float resultDotProduct = ((other.m_x*m_x) + (other.m_y*m_y));
	float module = magnitude();
	float maduleOther = other.magnitude();
	float angle = static_cast<float>(acos(((resultDotProduct) / (module*maduleOther))));

	return angle;
}

float Vector2D::Distance(const Vector2D& other) const //Definir la funcion para hallar la distancia
{
	float xValue = other.m_x - this->m_x;
	float yValue = other.m_y - this->m_y;

	float xPow = static_cast<float>(pow(xValue, 2));
	float yPow = static_cast<float>(pow(yValue, 2));

	float addPow = xPow + yPow;
	float distance = static_cast<float>(sqrt(addPow));

	return distance;
}

void Vector2D::Setx(float x) {

	this->m_x = x;
}

void Vector2D::Sety(float y) {

	this->m_y = y;
}