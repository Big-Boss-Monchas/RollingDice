#pragma once

#include <GL/glut.h>
#include "Shapes3d.h"
#include "Vertex3d.h"
#include "Color.h"
#include "Texture3d.h"
#include <iostream>
#include <stdio.h>
/*
GLuint texture[6];

struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char* data;
};
typedef struct Image Image;

#define checkImageWidth 64
#define checkImageHeight 64

GLubyte checkImage[checkImageWidth][checkImageHeight][3];
*/
#define VERTEXNUMBER 8
#define FACESNUMBER 6
#define EDGENUMBER 12

// ------- CLASE HIJA / CUBE --------------------------------
class Cube : public Shapes3d
{
	// ----- ATRIBUTOS PERTENECIENTES A CUBO -------------
private:

	
	Texture3d text[6];
	Vertex3d vertexPos[8];				// NUMERO DE VERTICES
	Color colors[6];				// NUMERO DE COLORES DE CARAS
	double dimension;				// DIMENSION DEL CUBO
	double vertex[6];
	//char* files[6];// = { (char*)"1.bmp", (char*)"2.bmp", (char*)"3.bmp", (char*)"4.bmp", (char*)"5.bmp", (char*)"6.bmp" };
	

public:

	// ----- CONSTRUCTORES DEL CUBO ---------------------
	Cube() {
		setOrigin(0, 0, 0);
		setColor(1);
		setDimension(1);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(double x, double y, double z) {
		setOrigin(x, y, z);
		setColor(1);
		setDimension(1);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(double x, double y, double z, double dim) {
		setOrigin(x, y, z);
		setColor(1);
		setDimension(dim);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(double x, double y, double z, double dim, int col) {
		setOrigin(x, y, z);
		setColor(col);
		setDimension(dim);
		setNumVertex(8);
		calculateVertex();
	}

	Cube(const Cube& cube) {
		Vertex3d pos = cube.getOrigin();
		setOrigin(pos.getX(), pos.getY(), pos.getZ());
		setColor(cube.getNumColor());
		setDimension(cube.getDimension());
		setNumVertex(8);
		calculateVertex();
	}

	// ----- ESTABLECE LOS COLORES DEPENDIENDO DEL NUMERO DE PARAMETRO --------------------
	// ENTRA A UN SWITCH QUE ASIGNA UN COLOR A CADA ELEMENTO DEL ARREGLO COLOR
	void setColor(int colorNumber)
	{
		numColor = colorNumber;
		switch (colorNumber)
		{
		case 1:
			   colors[0].setRGB(1.0, 1.0, 0.0);	colors[1].setRGB(0.0, 1.0, 1.0);
			   colors[2].setRGB(1.0, 0.0, 1.0);	colors[3].setRGB(1.0, 0.0, 0.0);
			   colors[4].setRGB(0.0, 1.0, 0.0);	colors[5].setRGB(0.0, 0.0, 1.0);
			   break;
		case 2:
			   colors[0].setRGB(1.0, 0.0, 1.0);	colors[1].setRGB(1.0, 0.0, 0.0);
			   colors[2].setRGB(0.0, 0.0, 0.75);	colors[3].setRGB(0.0, 1.0, 1.0);
			   colors[4].setRGB(1.0, 0.75, 0.75);	colors[5].setRGB(0.75, 1.0, 1.0);
			   break;
		case 3:
			   colors[0].setRGB(0.5, 0.5, 0.5);	colors[1].setRGB(0.9, 0.8, 0.7);
			   colors[2].setRGB(0.6, 0.5, 0.4);	colors[3].setRGB(1.0, 1.0, 0.75);
			   colors[4].setRGB(0.75, 1.0, 1.0);	colors[5].setRGB(1.0, 0.75, 1.0);
			   break;
		case 4:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(1.0, 0.0, 0.0); }
			   break;
		case 5:
			   for (int i = 0; i < getNumVertex() - 2; i++)	{ colors[i].setRGB(0.0, 1.0, 0.0); }
			   break;
		case 6:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(0.0, 0.0, 1.0); }
			   break;
		case 7:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(1.0, 1.0, 0.0); }
			   break;
		case 8:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(1.0, 0.0, 1.0); }
			   break;
		case 9:
			   for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(0.0, 1.0, 1.0); }
			   break;
		default:
			numColor = 0;
			for (int i = 0; i < getNumVertex() - 2; i++) { colors[i].setRGB(0.0, 0.0, 0.0); }
			break;
		}
	}
	
	// ----- SETTERS & GETTERS ----------------------------------
	void setDimension(double _dimension)
	{
		if (_dimension > 0) { dimension = _dimension; }
		else { setDimension(1); }
		assignProperties();
	}

	void assignProperties()
	{
		text[0] = Texture3d((char*)"1.bmp");
		text[1] = Texture3d((char*)"2.bmp");
		text[2] = Texture3d((char*)"3.bmp");
		text[3] = Texture3d((char*)"4.bmp");
		text[4] = Texture3d((char*)"5.bmp");
		text[5] = Texture3d((char*)"6.bmp");

		perimeter = calculatePerimeter();
		area = calculateArea();
		volume = calculateVolume();
		calculateVertex();

	}

	double getDimension()	const { return dimension; }

	double calculatePerimeter() { return getDimension() * 12; }
	double calculateArea() { return (getDimension() * getDimension()) * 6; }
	double calculateVolume() { return (getDimension() * getDimension() * getDimension()); }

	// ----- ASIGNA LAS COORDENADAS EN X, Y, Z EN CADA VERTICE DEL CUBO ---------------------
	void setVertex(double _x1, double _y1, double _z1, double _x2, double _y2, double _z2)
	{
		vertexPos[0].setXYZ(_x1, _y1, _z1);		vertexPos[1].setXYZ(_x1, _y1, _z2);
		vertexPos[2].setXYZ(_x1, _y2, _z2);		vertexPos[3].setXYZ(_x1, _y2, _z1);
		vertexPos[4].setXYZ(_x2, _y1, _z1);		vertexPos[5].setXYZ(_x2, _y1, _z2);
		vertexPos[6].setXYZ(_x2, _y2, _z2);		vertexPos[7].setXYZ(_x2, _y2, _z1);

		vertex[0] = _x1;
		vertex[1] = _y1;
		vertex[2] = _z1;
		vertex[3] = _x2;
		vertex[4] = _y2;
		vertex[5] = _z2;
		for (size_t i = 0; i < 6; i++)
		{
			text[i].loadTexture();
		}
		
	}

	// ----- CALCULA LAS COORDENADAS DEL VERTICE INICIAL PARTIENDO DEL CENTRO DEL CUBO COMO ORIGEN -------
	void calculateVertex()
	{
		Vertex3d aux_origin = getOrigin();
		double aux_dimension = getDimension();
		double x1 = aux_origin.getX() + (aux_dimension / 2);
		double y1 = aux_origin.getY() - (aux_dimension / 2);
		double z1 = aux_origin.getZ() - (aux_dimension / 2);
		double x2 = x1 - aux_dimension;
		double y2 = y1 + aux_dimension;
		double z2 = z1 + aux_dimension;
		setVertex(x1, y1, z1, x2, y2, z2);	// LLAMA LA ASIGNACION DE LOS VERTICES
	}
	
	// DIBUJA LA FIGURA PINTANDO CADA UNA DE LAS CARAS CON DIFERENTE COLOR
	void drawFigure()
	{
		// ----- POR CADA CARA TOMA EL COLOR DEL ARREGLO ---------------------
		Color aux_color = colors[0];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		for (int i = 0; i < getNumVertex() / 2; i++)
		{
			glVertex3f(vertexPos[i].getX(), vertexPos[i].getY(), vertexPos[i].getZ());
		}
		glEnd();

		aux_color = colors[1];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glEnd();

		aux_color = colors[2];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[0].getX(), vertexPos[0].getY(), vertexPos[0].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glEnd();

		aux_color = colors[3];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glVertex3f(vertexPos[3].getX(), vertexPos[3].getY(), vertexPos[3].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glEnd();

		aux_color = colors[4];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[4].getX(), vertexPos[4].getY(), vertexPos[4].getZ());
		glVertex3f(vertexPos[7].getX(), vertexPos[7].getY(), vertexPos[7].getZ());
		glEnd();

		aux_color = colors[5];
		glColor3f(aux_color.getR(), aux_color.getG(), aux_color.getB());
		glBegin(GL_POLYGON);
		glVertex3f(vertexPos[6].getX(), vertexPos[6].getY(), vertexPos[6].getZ());
		glVertex3f(vertexPos[5].getX(), vertexPos[5].getY(), vertexPos[5].getZ());
		glVertex3f(vertexPos[1].getX(), vertexPos[1].getY(), vertexPos[1].getZ());
		glVertex3f(vertexPos[2].getX(), vertexPos[2].getY(), vertexPos[2].getZ());
		glEnd();
	}

	void drawFigureDice()
	{

		//text.init();
		
		glEnable(GL_TEXTURE_2D);

		float x0 = vertex[0], y0 = vertex[1], z0 = vertex[2], x1 = vertex[3], y1 = vertex[4], z1 = vertex[5];
		float face[6][4][3] = { { {x0, y0, z0}, {x1, y0, z0}, {x1, y1, z0}, {x0, y1, z0} },
		  {{x0, y1, z1}, {x1, y1, z1}, {x1, y0, z1}, {x0, y0, z1}},    //back
		  {{x1, y0, z0}, {x1, y0, z1}, {x1, y1, z1}, {x1, y1, z0}},    //right
		  {{x0, y0, z0}, {x0, y1, z0}, {x0, y1, z1}, {x0, y0, z1}},    //left
		  {{x0, y1, z0}, {x1, y1, z0}, {x1, y1, z1}, {x0, y1, z1}},    //top
		  {{x0, y0, z0}, {x0, y0, z1}, {x1, y0, z1}, {x1, y0, z0}}    //bottom
		};


		for (int i = 0; i < 6; ++i) {
			//draw cube with texture images
			text[i].useTexture();
			glBindTexture(GL_TEXTURE_2D, text[i].texture);
			glBegin(GL_QUADS);
			glTexCoord2f(1.0, 1.0); glVertex3fv(face[i][0]);
			glTexCoord2f(0.0, 1.0); glVertex3fv(face[i][1]);
			glTexCoord2f(-1.0, 0.0); glVertex3fv(face[i][2]);
			glTexCoord2f(0.0, 0.0); glVertex3fv(face[i][3]);
			glEnd();
		}
		

		glBindTexture(GL_TEXTURE_2D, 0);

		//delete[] face;
		glDisable(GL_TEXTURE_2D);
		//text.clearTexture();
	}

	void moveFigure(double _x, double _y, double _z)
	{
		origin.moveVertex3d(_x, _y, _z);
		calculateVertex();
	}

	void scaleFigure(double factor)
	{
		setDimension(factor * getDimension());
		calculateVertex();
	}
	/*
	void makeCheckImage(void) {

		int i, j, c;
		for (i = 0; i < checkImageWidth; i++) {
			for (j = 0; j < checkImageHeight; j++) {
				c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255;

				checkImage[i][j][0] = (GLubyte)c;
				checkImage[i][j][1] = (GLubyte)c;
				checkImage[i][j][2] = (GLubyte)c;
			}
		}
	}

	int ImageLoad(char* filename, Image* image) {
		FILE* file;
		unsigned long size; // size of the image in bytes.
		unsigned long i; // standard counter.
		unsigned short int planes; // number of planes in image (must be 1)
		unsigned short int bpp; // number of bits per pixel (must be 24)

		char temp; // temporary color storage for bgr-rgb conversion.

		file = fopen(filename, "rb");

		fseek(file, 18, SEEK_CUR);

		i = fread(&image->sizeX, 4, 1, file);

		i = fread(&image->sizeY, 4, 1, file);

		size = image->sizeX * image->sizeY * 3;

		fread(&planes, 2, 1, file);

		if (planes != 1) {
			printf("Planes from %s is not 1: %u\n", filename, planes);
			system("PAUSE");
			return 0;
		}

		i = fread(&bpp, 2, 1, file);

		fseek(file, 24, SEEK_CUR);

		image->data = (char*)malloc(size);

		if (image->data == NULL) {
			printf("Error allocating memory for color-corrected image data");
			system("PAUSE");
			return 0;
		}

		if ((i = fread(image->data, size, 1, file)) != 1) {
			printf("Error reading image data from %s.\n", filename);
			system("PAUSE");
			return 0;
		}

		for (i = 0; i < size; i += 3) { // reverse all of the colors. (bgr -> rgb)
			temp = image->data[i];
			image->data[i] = image->data[i + 2];
			image->data[i + 2] = temp;
		}
		return 1;
	}*/
	/*
	void myinit(void)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		Image* image[6];

		for (int i = 0; i < 6; i++)
		{
			image[i] = (Image*)malloc(sizeof(Image));
		}


		if ((!ImageLoad((char*)"1.bmp", image[0])) || (!ImageLoad((char*)"2.bmp", image[1]))
			|| (!ImageLoad((char*)"3.bmp", image[2])) || (!ImageLoad((char*)"4.bmp", image[3])) 
			|| (!ImageLoad((char*)"5.bmp", image[4])) || (!ImageLoad((char*)"6.bmp", image[5]))) {
			system("PAUSE");
			exit(1);
		}


		makeCheckImage();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(6, texture);

		for (int i = 0; i < 6; i++)
		{
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //scale linearly when image bigger than texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //scale linearly when image smalled than texture
			glTexImage2D(GL_TEXTURE_2D, 0, 3, image[i]->sizeX, image[i]->sizeY, 0,
				GL_RGB, GL_UNSIGNED_BYTE, image[i]->data);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		}

		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_FLAT);
	}
	*/
	~Cube()
	{
	}
};
