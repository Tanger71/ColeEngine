#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

//TODO: deepen understanding of this file

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t; 

inline ComponentID getNewComponentTypeID(){
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline
ComponentID getComponentTypeID() noexcept{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;

class Controller {
public:
    Entity* entity;

    Controller(){
        //std::cout << "HERECONSDTOG" << std::endl;
}

    virtual void init() { std::cout << "HEREWRONG" << std::endl; }
    virtual void update() {}

    virtual void onDeath() {}

    virtual ~Controller() = default;

};

/**
 * @brief Class *interface* for Entity Component
 *
 * @author sawyercoletang
 *
 */
class Component{
public:
    Entity* entity;

    virtual void init(){}
    virtual void update(){}
    virtual void draw(){}

    virtual ~Component() = default;
};

/**
 * @brief Class for Game Entity
 *
 * @author sawyercoletang
 *
 */
class Entity{
public:

    bool hasController = false;
    Controller* controller; // TODO: do error check for initialized before update

    /**
     *
     * @param mManager game instance manager
     */
    Entity(Manager& mManager) : manager(mManager) {}

    void setController(Controller& cont) {
        std::cout << "HERESET" << std::endl;
        controller = &cont;
        controller->entity = this;
        controller->init();
        hasController = true;
    }

    /**
     * @brief update all components in Entity
     */
    void update(){
        for(auto& c : components) c->update();
        if(hasController) 
            controller->update();
    }

    /**
     * @brief draw all components in Entity
     */
    void draw(){
        for(auto& c : components) c->draw();
    }

    /**
     * @todo look more
     *
     * @return true if Entity is active
     */
    bool isActive() const { return active; }

    /**
     * @brief to destroy Entity (set active to false)
     */
    void destroy(){ active = false; }

    /**
     *
     * @param mGroup group to check inclusion
     * @return true if this Entity belongs to mGroup
     */
    bool hasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }

    /**
     *
     * @param mGroup group to add this Entity to
     */
    void addGroup(Group mGroup);

    /**
     *
     * @param mGroup group to remove this Entity from
     */
    void delGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }

    /**
     * @todo
     *
     * @tparam T
     * @return
     */
    template <typename T>
    bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()]; //TODO: learn
    }

    /**
     * @todo
     *
     * @tparam T
     * @tparam TArgs
     * @param mArgs
     * @return
     */
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs){ //TODO: learn
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr { c };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    /**
     * @todo
     *
     * @tparam T
     * @return
     */
    template<typename T> T& getComponent() const{ //TODO: learn
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

private:
    Manager& manager;
    bool active = true;
    std::vector< std::unique_ptr<Component> > components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
};

/**
 * @brief Class for Game Manager
 *
 * @author sawyercoletang
 *
 */
class Manager{
public:

    /**
     * @brief update all Entities in Game
     */
    void update(){
        for (auto& e : entities) e->update(); 

        
    }

    /**
     * @brief draw all Entities in Game
     */
    void draw(){
        for (auto& e : entities) e->draw();
    }

    /**
     * @todo
     *
     * @brief remove all inactive Entities
     */
    void refresh(){ //TODO: learn UnaryPredicate
        for (auto i(0u); i < maxGroups; i++) {
            auto& v(groupedEntities[i]);
            v.erase(
                std::remove_if(std::begin(v), std::end(v),
                    [i](Entity* mEntity) {
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }),
                std::end(v)
            );
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity){
                return !mEntity->isActive();
            }), std::end(entities)
        );
    }

    /**
     * @brief add Entity to Group
     *
     * @param mEntity Entity to be added
     * @param mGroup Group to be added to
     */
    void AddToGroup(Entity* mEntity, Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    /**
     * @todo
     *
     * @return
     */
    Entity& addEntity(){
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr {e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

private:
    std::vector< std::unique_ptr<Entity> > entities; //TODO: learn... smart pointer
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

};
