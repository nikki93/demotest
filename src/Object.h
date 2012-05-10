#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <map>
#include <list>

class Object
{
    public:
        typedef unsigned int ID;

    private:
        typedef std::map<ID, Object *> ObjectMap;
        static ObjectMap _objects;
        static std::list<ID> _toRemove;
        static ID _newID;

        ID id;

    public:
        // --- override ------

        virtual void update(float elapsed) {}
        virtual void draw() {}

        // --- object API ----

        inline ID getID()
        {
            return id;
        }

        // --- manager API ---

        inline static void add(Object *object)
        {
            //if used, make new [infinite loop if too many objects!]
            while (_objects.find(_newID) != _objects.end())
                ++_newID;

            _objects.insert(std::make_pair(_newID, object));
            object->id = _newID++;
        }
        inline static void remove(ID id)
        {
            _toRemove.push_back(id);
        }
        static void updateAll(float elapsed);
        static void drawAll();
};

#endif
