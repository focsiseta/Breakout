// openglsetup.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "breakout/rendering/rendering.h"
#include "components/input/input.h"
#include "breakout/game/game.h"
#include "components/particles/particles.h"


#define vec2(a,b) glm::vec2(a,b)

int main()
{
    GLFWwindow* window = createWindow("Breakout");
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glClearColor(0, 0, 0, 1);
    if (window == nullptr) return -1;

    Sprite::initSprites();
    Shader shader2D;
    Shader particles;
    glm::mat4 projection = glm::ortho(0.f, float(WIN_WIDTH),float(WIN_HEIGHT), 0.f, 0.f, 1.f);
    glm::mat4 model = glm::mat4(1.);

    try
    {
        shader2D = Shader("./components/shader/sources/vertex2D.glsl", "./components/shader/sources/frag2D.glsl");
        shader2D.use();
        shader2D.u_mat4(projection, "projection", false);
        shader2D.u_mat4(model, "model", false);
        shader2D.u_int(0, "tex");

        particles = Shader("./components/shader/sources/particleVS.glsl", "./components/shader/sources/particleFS.glsl");
        particles.use();
        particles.u_mat4(projection, "projection", false);
        particles.u_int(0, "particle");
        

    }
    catch (std::string err)
    {
        std::cout << "Catched error:" << std::endl;
        std::cout << err << std::endl;
        return 0;
    }

    Game tmp{ "./breakout/assets/paddle.png",
                "./breakout/assets/cursor.png",15.f,vec2(-3.,-3.)};
    tmp.addLevel("./breakout/levels/first");
    Sprite background{ "./breakout/assets/test.png",glm::vec3(1.)};
    background.scale(vec2(WIN_WIDTH ,WIN_HEIGHT));
    

    //Initializing ParticlesGenerator class
    Particle p = Particle(tmp.ball.position,tmp.ball.direction,glm::vec4(1),Texture("./breakout/assets/cursor.png"),1.0f);
    ParticleGenerator::init();
    
    ParticleGenerator gen = ParticleGenerator(p,tmp.ball,5000,1);

    while (!glfwWindowShouldClose(window))
    {
        
        Input::readInput(window);
        gen.update();
        tmp.doCollisions();
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader2D.use();
        background.bindTexture();
        shader2D.u_vec3(background.color, "blockColor");
        background.draw(shader2D);
        tmp.drawLevel(shader2D,0);
        tmp.drawPaddleAndBall(shader2D);
        gen.render(particles);
        tmp.movement();
        glfwSwapBuffers(window);
        glfwPollEvents();
        std::cout << glGetError() << "\n";

    }
    glfwTerminate();
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    return 0;
}


//TODO Fixare le cose che cambiano colore dopo un certo numero di hit

/*TODO Aggiungere background per livello, aggiungere la paddle e farla muovere e continuare 
* con la pallina e implementare il movimento
*DONE

*/