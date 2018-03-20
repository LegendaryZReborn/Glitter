#ifndef RENDERER_H
#define RENDERER_H
#include <string>

#include "SimpleModel.hpp"
#include "Shader.hpp"

class Renderer
{
    public:
        Renderer();
        //Renders a SimpleModel to the screen
        void render(const SimpleModel& model, Shader& shader);
        //Prepares screen for rendering
        void prepare();
        ~Renderer();

    protected:

    private:

};

#endif // RENDERER_H
