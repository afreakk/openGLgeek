#ifndef CRUISER_H
#define CRUISER_H
#include "ImportModel.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "BaseGL.h"
class Cruiser:public BaseGL
{
    public:
        Cruiser();
        void init(const char* filename,unsigned int SHADER);
        void draw();
        void translate(glm::vec3 with);
        void rotation(float angle, glm::vec3 axis);
        void scale(glm::vec3 scaleVec );
        glm::vec3 getTranslation();
        virtual ~Cruiser();
        void position(glm::vec3 pos);
    protected:
    private:
        unsigned int shader;
        ImportModel* boat;
        glm::mat4 modelM;
        glm::mat4 rotationM;
        glm::mat4 scaleM;
        glm::mat4 translationM;
        glm::vec3 translationV;

};

#endif // CRUISER_H
