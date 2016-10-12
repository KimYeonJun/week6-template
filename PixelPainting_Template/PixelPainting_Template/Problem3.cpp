#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <time.h>
#include <vector>
#include "math.h"

const int width = 1200;
const int height = 500;
float* pixels = new float[width*height * 3];
void drawSquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue);
void drawCircle(const int& i0, const int& j0, const int& r, const float& red, const float& green, const float& blue);



class Box
{
public:
	void draw()
	{
		drawSquare(50, 50, 200, 200, 0.0f, 0.0f, 1.0f);
	}
};
class Circle
{
public:
	void draw()
	{
		drawCircle(400, 150, 100, 1.0f, 0.0f, 0.0f);
	}
};
class GeometricObjectInterface
{
public:
	virtual void draw() = 0;
};
template<class T_HOW_TO_DRAW>
class GeometricObject :public GeometricObjectInterface
{
public:
	void draw()
	{
		T_HOW_TO_DRAW drawObject;
		drawObject.draw();
	}
};

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1)
	{
		for (int j = j0;j < j1;j++)
		{
			drawPixel(i0, j, red, green, blue);
		}
		return;
	}
	for (int i = i0; i <= i1; i++)
	{

		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}
void drawThickLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{

	for (int i = i0; i <= i1; i++)
	{

		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j - 1, red, green, blue);
		drawPixel(i, j, red, green, blue);
		drawPixel(i, j + 1, red, green, blue);
	}
}
//void drawCircle(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
void drawCircle(const int& i0, const int& j0, const int& r, const float& red, const float& green, const float& blue)
{

	for (int i = i0 - r;i <= i0 + r;i++)
	{
		for (int j = j0 - r;j <= j0 + r;j++)
		{
			int f = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;

			int f1 = (i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 3)*(r - 3);
			if (f <= 0 && f1 >= 0)
			{

				drawPixel(i, j, red, blue, green);

			}

		}
	}


}
void drawIcon(const int& i0, const int& j0, const int& r, const float& red, const float& green, const float& blue, GLFWwindow* window)
{
	double xpos, ypos;

	for (int i = i0 - r;i <= i0 + r;i++)
	{
		for (int j = j0 - r;j <= j0 + r;j++)
		{
			glfwGetCursorPos(window, &xpos, &ypos);
			ypos = height - ypos - 1;
			int f = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;
			int f2 = (xpos - i0)*(xpos - i0) + (ypos - j0)*(ypos - j0) - r*r;
			int f1 = (i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 3)*(r - 3);
			if (f2 <= 0)
			{
				if (f <= 0 && f1 >= 0)
				{
					drawPixel(i, j, red, green, blue);
				}
			}


		}
	}


}
void drawSmallCircle(const int& i0, const int& j0, const int& r, const float& red, const float& green, const float& blue)
{

	for (int i = i0 - r;i <= i0 + r;i++)
	{
		for (int j = j0 - r;j <= j0 + r;j++)
		{
			int f = (i - i0)*(i - i0) + (j - j0)*(j - j0) - r*r;

			int f1 = (i - i0)*(i - i0) + (j - j0)*(j - j0) - (r - 10)*(r - 10);
			if (f <= 0 && f1 >= 0)
			{

				drawPixel(i, j, red, blue, green);

			}

		}
	}


}
void drawSquare(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	drawLine(i0, j0, i1, j0, red, green, blue);
	drawLine(i1, j0, i1, j1, red, green, blue);
	drawLine(i0, j1, i1, j1, red, green, blue);
	drawLine(i0, j0, i0, j1, red, green, blue);

}
void drawOnPixelBuffer(GLFWwindow* window)
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
													//}

	const int i = rand() % width, j = rand() % height;
	/*drawPixel(i, j, 0.0f, 0.0f, 0.0f);*/

	// drawing a line
	//TODO: anti-aliasing
	
	std::vector<GeometricObjectInterface*> obj_list;
	obj_list.push_back(new GeometricObject< Box>);
	obj_list.push_back(new GeometricObject <Circle>);
	
	
	for (auto itr : obj_list)
	{
		itr->draw();
	}
}

int main(void)
{
	/*for (int i = 0;i < 2;i++)
	{
		if (i == 0)
		{
			my_objects[i] = new GeometricObjectInColor<DrawInYellow>;
			
		}
		if (i == 1)
		{
			my_objects[i] = new GeometricObjectInColor<DrawInRed>;
			
		}
	}*/
	
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer(window);

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}

