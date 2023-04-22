// openglsetup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "breakout/rendering/rendering.h"

#define vec2(a,b) glm::vec2(a,b)

int main()
{
    GLFWwindow* window = createWindow("Breakout");
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glClearColor(1,0,1,1);
    if (window == nullptr) return -1;
    
    Sprite::initSprites();
    Shader shader2D;
    glm::mat4 projection = glm::ortho(0.f,800.f,800.f,0.f,-1.f,1.f);
    glm::mat4 model = glm::mat4(1.);

    try
    {
       shader2D = Shader("./components/shader/sources/vertex2D.glsl", "./components/shader/sources/frag2D.glsl");

    }
    catch (std::string err)
    {
        std::cout << "Catched error" << std::endl;
        std::cout << err << std::endl;
        return 0;
    }
    shader2D.use();
    shader2D.mat4(projection, "projection", false);
    shader2D.mat4(model, "model", false);
    Sprite sp;
    float count = 0;
    sp.traslate(vec2(400., 400.));
    sp.rotate(10.);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        sp.scale(100);
        
        sp.draw(shader2D);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwTerminate();
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    return 0;
}

/*TODO Testare gli shaders :
 1) Inserire le funzioni per passare gli uniform nella classe shader DONE
 1.1) Usare il metodo per parsare gli shader descritto nella pagina del DSA (Direct state access) (Da fare al fisso)
 1.11) Parsare gli shader nel vecchio modo e tirare fuori gli uniform
 1.111) Ricordarsi la matrice di proiezione, altrimenti non se fa un cazzo

 2) Codice per disegnare le sprites
 2.1) Matematica per poter muovere le sprite 
    (L'approccio del tutorial e' buono, ma non mi piace come viene tutto messo in una sola funzione
     sarebbe interessante provare un altro modo, ma prima devo finire di scrivere il progetto in generale)



*/