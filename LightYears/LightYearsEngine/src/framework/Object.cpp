#include "framework/Object.h"
#include "framework/Core.h"

namespace LightYears
{
    unsigned int Object::uniqueIDCounter_ = 0;
    Object::Object()
        : isPendingDestory_{false},
          uniqueID_{GetNextAvaliableID()}
    {
    }

    Object::~Object()
    {
        LOG("Object Destory");
    }

    void Object::Destroy()
    {
        onDestory_.Broadcast(this);
        isPendingDestory_ = true;
    }

    weak<Object> Object::GetWeakRef()
    {
        return shared_from_this();
    }

    weak<const Object> Object::GetWeakRef() const
    {
        return shared_from_this();
    }

    unsigned int Object::GetNextAvaliableID()
    {
        return uniqueIDCounter_++;
    }
}