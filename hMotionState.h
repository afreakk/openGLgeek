#ifndef HMOTIONSTATE_H
#define HMOTIONSTATE_H
#include "Object3D.h"
#include <LinearMath/btMotionState.h>
class hMotionState:public btMotionState
{
    public:
        hMotionState(Object3D* RENDEROBJECT=0, const btTransform& startTrans = btTransform::getIdentity(),glm::vec3 offset=glm::vec3(0.0,0.0,0.0)
        ,const btTransform& centerOfMassOffset = btTransform::getIdentity());
		virtual void    getWorldTransform(btTransform& centerOfMassWorldTrans ) const;
        virtual void	setWorldTransform(const btTransform& centerOfMassWorldTrans);
        virtual ~hMotionState();
    protected:
    private:
        Object3D* renderObject;
        btTransform m_graphicsWorldTrans;
        btTransform	m_centerOfMassOffset;
        btTransform m_startWorldTrans;
        glm::vec3 renderOffset;
        void*		m_userPointer;
};

#endif // HMOTIONSTATE_H
