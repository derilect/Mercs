#include <GL/glew.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


int main()
{
	sf::ContextSettings settings;
	settings.majorVersion = 4;
	settings.minorVersion = 1;

	sf::RenderWindow window(sf::VideoMode(800,600), "SFML WORKS", sf::Style::Default, settings);


	GLenum err = glewInit();

	if(GLEW_OK != err)
		std::cout << "Error encountered in GLEW" << std::endl;

	int indices[] = {0,0,0,100,100,0,100,0,0};
	GLuint elementBuffer;

	glGenBuffers(1,&elementBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
//	glVertexPointer(3, GL_INT, 0, nullptr);
	sf::Shader simpShader;
	if(!simpShader.loadFromFile("vertex_shader.vert", sf::Shader::Vertex))
	{
		std::cout << "Error loading vertex shader." << std::endl;
		return 0;
	}

	if(!simpShader.loadFromFile("fragment_shader.frag", sf::Shader::Fragment))
	{
		std::cout << "Error loading fragment shader." << std::endl;
		return 0;
	}

	sf::Shader::bind(&simpShader);
	window.pushGLStates();

	while(window.isOpen())
	{
		sf::Event event;

		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

		}
		window.popGLStates();
		window.clear();
		window.display();
		window.pushGLStates();

		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, elementBuffer);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	glDeleteBuffers(1, &elementBuffer);
	 
	return 0;
}