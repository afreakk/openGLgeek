#include "hMotionState.h"


hMotionState::hMotionState(Object3D* RENDEROBJECT, const btTransform& startTrans,glm::vec3 offset
,const btTransform& centerOfMassOffset)
    :   m_graphicsWorldTrans(startTrans),
		m_centerOfMassOffset(centerOfMassOffset),
		m_startWorldTrans(startTrans),
		renderObject(RENDEROBJECT),
		renderOffset(offset),
		m_userPointer(0)
{
}
hMotionState::~hMotionState()
{
    //dtor
}
void hMotionState::getWorldTransform(btTransform& centerOfMassWorldTrans ) const
{
    centerOfMassWorldTrans = 	m_centerOfMassOffset.inverse() * m_graphicsWorldTrans ;
}
void hMotionState::setWorldTransform(const btTransform& centerOfMassWorldTrans)
{
    m_graphicsWorldTrans = centerOfMassWorldTrans * m_centerOfMassOffset ;
    btQuaternion rot = centerOfMassWorldTrans.getRotation();
    renderObject->setOrientation(glm::quat(rot.w(),rot.x(),rot.y(),rot.z()));
    btVector3 pos = centerOfMassWorldTrans.getOrigin();
    renderObject->position(glm::vec3(pos.x()+renderOffset.x, pos.y()+renderOffset.y, pos.z()+renderOffset.z));
}
