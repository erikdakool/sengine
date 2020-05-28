//
// Created by erik on 23.10.2019.
//

#ifndef GLENGINE_GAMEOBJECT_H
#define GLENGINE_GAMEOBJECT_H

#include <vector>

#include "../Components/Component.h"
#include "../Managers.h"
#include "../Transform.h"
#include "../Object/Object.h"

class Gameobject : public Object {
public:
    Gameobject(GameDataRef data);
    ~Gameobject();

    Transform& transform();
    void update(float deltaT) override;

    void AddComponent(std::shared_ptr<Component> component);
    template<typename T>
    T getComponent(){
        for(auto i = components.begin(); i!= components.end(); i++){
            auto com = dynamic_cast<T>(i->get());
            if(com){
                return com;
            }
        }
        return nullptr;
    }

    void AddChild(std::shared_ptr<Gameobject> gameobject);
    std::vector<std::shared_ptr<Gameobject>> getChildren();

    uint32_t getId() const;

    void setId(uint32_t id);

private:

protected:
    //Gameobject info/data
    uint64_t id;
    bool isChild = false;
    Transform* transformcom;

    //Compoents
    std::vector<std::shared_ptr<Component>> components;

    //Gameobject family
    std::vector<std::shared_ptr<Gameobject>> children;
    std::shared_ptr<Gameobject> parrent;
};

#endif //GLENGINE_GAMEOBJECT_H
