# Entity-Component-System v1

This version implements only Entity-Component. Components inherit from the class Component, Entity maintains an array with a fixed number of (possible) components, and Manager maintains a list of entities. 

It also support groups of entities and handlers (assigning identifiers to entities for fast global access). Groups are kept in the entity (using std::bitset), and also the manager maintains lists of groups to allow traversing them in a faster way, however, this also introduce some overhead in the group management methods.
