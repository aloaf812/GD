#include "CheckpointObject.h"
USING_NS_CC;

bool CheckpointObject::init()
{
	return true;
}

GameObject* CheckpointObject::getObject()
{
	return m_object;
}

void CheckpointObject::setObject(GameObject* obj)
{
	if (m_object != obj) {
		if (obj)
			obj->retain();

		if (m_object)
			m_object->release();
		
		this->m_object = obj;
	}
}