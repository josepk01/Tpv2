# Entity-Component-System v1

This version implements only Entity-Component. Components inherit from the class Component, Entity maintains an array with a fixed number of (possible) components, and Manager maintains a list of entities. 

It also support groups of entities and handlers (assigning identifiers to entities for fast global access). Groups are maintains in the class Entity using std::bitset, the manager knows nothing about groups.
