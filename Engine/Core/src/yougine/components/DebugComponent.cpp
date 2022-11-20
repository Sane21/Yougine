#include "DebugComponent.h"

namespace yougine::components
{
    DebugComponent::DebugComponent() : Component(managers::ComponentName::kCustom)
    {
        this->vec3val = new utility::Vector3(1, 1, 1);

        accessable_properties_list.push_back(std::vector<std::any>{&intval, GETVALUENAME(intval)});
        accessable_properties_list.push_back(std::vector<std::any>{&intval2, GETVALUENAME(intval2)});
        accessable_properties_list.push_back(std::vector<std::any>{&floatval, GETVALUENAME(floatval)});
        accessable_properties_list.push_back(std::vector<std::any>{vec3val, GETVALUENAME(vec3val)});
        accessable_properties_list.push_back(std::vector<std::any>{&strval, GETVALUENAME(strval)});
        accessable_properties_list.push_back(std::vector<std::any>{&boolval, GETVALUENAME(boolval)});
    }

}
