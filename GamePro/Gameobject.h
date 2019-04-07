//
// Created by erik on 22.12.18.
//

#ifndef GAMEPRO_GAMEOBJECT_H
#define GAMEPRO_GAMEOBJECT_H

#include <memory>
#include <list>
#include <string>

#include <jsoncpp/json/json.h>

#include "Components/Transform.h"
#include "Components/RenderCom.h"
#include "Manager.h"

enum ObjectTag{
    TagGameobject = 0,
    TagPlayer = 1,
    TagEnemey = 2,
    TagLayer = 3,
    TagObject = 4
};

class App;
class ObjectFactory;
class Gameobject {
public:
    friend class ObjectFactory;
    Gameobject(unsigned int id, bool active,Manager& manager);
    Gameobject(Manager& manager);
    ~Gameobject();
    virtual void init();
    virtual void update(float deltaT);
    virtual void destroy();

    bool isActive() const {
        return active;
    }
    void setActive(bool active) {
        Gameobject::active = active;
    }

    bool setId(unsigned int id){
        Gameobject::id = id;
    }

    unsigned int getId() const{
        return id;
    }

    template<typename T>
    T getComponentP(){
        for(auto i = components.begin(); i != components.end();i++){
            auto com = dynamic_cast<T>(i->get());
            if(com){
                return com;
            }
        }
        return nullptr;
    }

    void addComponent(std::shared_ptr<Component> component);

    Json::Value getJson();

    Manager &getManager() const;

    Transform* trasform()const { return this->transform.get();}

    const std::shared_ptr<Gameobject> &getParent() const;

    const std::list<std::shared_ptr<Gameobject>> &getChildren() const;

    void setParent(std::shared_ptr<Gameobject> parent);
    void addChildren(std::shared_ptr<Gameobject> child);

    const std::string &getName() const;

    void setName(const std::string &name);

    void setTag(ObjectTag tag);

    ObjectTag getTag() const;

private:
    //Gameobject info
    unsigned int id;
    std::string name;
    bool active;
    bool isChild = false;

    ObjectTag tag = TagGameobject;

    //Controllers
    Manager& manager;

    //transform
    std::shared_ptr<Transform> transform;

    //Components
    std::list<std::shared_ptr<Component>> components;
    void loadComponent(Json::Value& value);

    //Gameobject family
    std::shared_ptr<Gameobject> parent;
    std::list<std::shared_ptr<Gameobject>> children;
};


#endif //GAMEPRO_GAMEOBJECT_H