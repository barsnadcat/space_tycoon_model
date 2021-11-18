#pragma once

#include <vector>
#include <memory>

//1 We need to update parent link too
//2 We can not use unique ptr - we need child to be present in two vectors simultaneusly during transition
//3 We should use raw pointers in interface - to avoid problem of "get shared from this"
// a. use raw pointer in vector, just add destructor
//4 How do we organise deletion of entity with children?
// a. Commit process has to go from leavs to root - when every thing is commited in children, you can move parent
//5 shtore shared ptrs internaly in vector and mAdd vectors - then it does not matter if oringal ovner of child is deleted before child is moved
// a. Then we should use shared ptr in interface as well! Then we facing get shared from this problem again
//6 Back to the begging - use raw pointers interanlly. But since parent does not actully manages it's children life time, 
// we have a problem - how to free memory.
// Ok if entity commits every thing in its vector -- can ve delete it saifly, since id now does manages its children life time?
// Here is the problem - if raw pointer is removed from vector, should we delete it, or not?
// Ok so, using same vector for location, update and memory managment is prolematic. Using separate vector in global state for update and memory management is problematic.
// But, what if same entities are present in two datastructures simultaneously - base class entity forms a double linked list - for updated and memory management, descendants use typed pointes for space and ownership hieracy
// Than we do not need two stage updates, because movemnt of any entity in space does not change it position in update linked list!
// Even better, we can use unique ptr again, because no child need to be present in two placeses simultaneously!
// Lets go deeper. Instead of using containers to sore children, children can form a double linked list. 
// Lists needs head, and we can use null bulding/owner/item for that!
// So when parent is deleted, it can move entire list by attaching it to the others palce end of list!
// When child is moved, you can give it head of other parent
// When child dies, it can delete itself, without relying on parent pointer. 
// Well child will need: entity, parent, and parents null object!
// Another problem - using desturctor for death, means that when we delete entire settlemnt, we will do shit ton of movement, each owner and building will drop their content to parents, which is pointless, since we delete every thing any way.
// Solution - use destructor only for update list mantanance, and delete all children. Use OnEntityDeath for dropping stuff
// Owner inventory problem:
// Keeping inventory types, like food and building/land keys clashes with ProductId from valuation code. 
// In current model there is only on type of building
// Owner vs Person problem...
// Building has to contain people. But, "nobody" should not be a person... Well actually we have owner exactly for this reason - so it can be null object.
// So, for space/position hierarchy I want: 
// 1 use raw pointers
// 2 keep their type
// Question, do I need a separate type for food, key and papers? Yes, key and papers will have relationship maintannece code.
// Ok, for space hierarchy, when child is deleted, you need to go to the parent and do a cleanup... which is mess.
// Will it be better with lists? Well to keep type information with lists, each children type will have to implement list on its own. Or use template hack

// I do not like idea of adding "papers" and "keys" to track ownership
// It is better to directly haw pointers to Farm, Food and Land in Person as owned items
// Consiquently, it looks like it is better to separte Property-Owner relaition ship from Container-Objet relation ship
// For what we know, Land can be container for everything - Food, Person and Farm, i.e. we do not need complicated hierarchy


