﻿#include "ComponentFactory.h"

#include "../components/DebugComponent.h"
#include "../components/RenderComponent.h"
#include "../components/TransformComponent.h"

yougine::components::Component* yougine::componentfactorys::ComponentFacotory::CreateComponent(
    std::string component_class_name)
{
    if (component_class_name == "yougine::components::DebugComponent")
    {
        return new components::DebugComponent();
    }
    else if (component_class_name == "yougine::components::TransformComponent")
    {
        return new components::TransformComponent(0, 0, 0);
    }
    else if (component_class_name == "yougine::components::RenderComponent")
    {
        return new components::RenderComponent();
    }
    //ここにユーザの作ったカスタムコンポーネントのelse if文も動的に入る予定
}