# Store Generator

The generator generates the store library and a store for each module.
Each store can be included in your project as a static libray.

- A store takes the last name of the module a the store name.
- For each interface a sub store is created.
- Each sub store contains its own operations.
- All operations of the interface are exposed on the sub store
- All properties of the interface form the state of the store
- All signals can be used to inform the user about an event. The event needs to be triggered by an operation.
- The state is immutable
- The store state is the modules store state combined with all sub store states combined
- A state is a QSharedData class
- The store has only one reducer function. This might call an internal reducer function of the sub-store if required.
-
