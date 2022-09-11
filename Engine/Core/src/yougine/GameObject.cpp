#include "GameObject.h"


namespace yougine
{
    GameObject::GameObject(Scene* scene, std::string name, GameObject* gameobject_parent)
    {
        this->scene = scene;
        this->name = name;
        this->gameobject_parent = gameobject_parent;
        layer = new Layer();
        InitializeComponents();
    }

    void GameObject::InitializeComponents()
    {

    }

    std::string GameObject::GetName()
    {
        return name;
    }

    void GameObject::SetName(std::string name)
    {
        this->name = name;
    }

    Layer* GameObject::GetLayer()
    {
        return layer;
    }

    std::vector<components::Component*> GameObject::GetComponents()
    {
        return components;
    }

    void GameObject::AddChild(GameObject* gameobject)
    {
        gameobject_childs.push_back(gameobject);
    }

    GameObject* GameObject::GetParentObject()
    {
        return gameobject_parent;
    }

    std::list<GameObject*> GameObject::GetChildObjects()
    {
        return gameobject_childs;
    }



    bool GameObject::operator==(const GameObject& rhs) const
    {
        return *this == rhs;
    }
}