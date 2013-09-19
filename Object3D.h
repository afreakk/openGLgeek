#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "ImportModel.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "BaseGL.h"
class Object3D:public BaseGL
{
    public:
        Object3D();
        virtual ~Object3D();
        void init(const char* filename,unsigned int SHADER);
        void init(ImportModel* model,unsigned int SHADER);
        void draw();
        void translate(glm::vec3 with);
        void rotation(float angle, glm::vec3 axis);
        void setOrientation(glm::quat orient);
        void scale(glm::vec3 scaleVec );
        void position(glm::vec3 pos);
        glm::vec3 getTranslation();
        ImportModel* getModel();
        glm::quat getOrientation();
        glm::vec3 getScale();
    protected:
        glm::quat orientationV;
        glm::vec3 translationV;
        glm::vec3 scaleV;
    private:
        ImportModel* object;
        unsigned int shader;
        glm::mat4 modelM;
        glm::mat4 rotationM;
        glm::mat4 scaleM;
        glm::mat4 translationM;

};

#endif // OBJECT3D_H
