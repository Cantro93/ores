# Ores - useful C++ Randomizers
Ores are objects used to draw one or more elements from a vector acting as a pool.

Aim of the project is to make object randomizing easier.
## Usage - introduction:
### Loading library and creating required objects
```cpp
//<vector> will load automatically
#include "ore.h"
//create ore
ore<int> example_ore({1, 2, 3, 4, 5});
//define "pusher" - function for placing new elements in the container, used by smelters
void PushToVector(vector<int>& container, int data)
{
  container.push_back(data);
}
//create smelter - object which will allow for communication between ore and container, e. g. vector.
ore<int>::smelter<vector<int>> example_smelter(example_ore, PushToVector);
```
For more information about usage, go to [wiki](https://github.com/Cantro93/ores/wiki).
## Changelog
* v.1.0.b - first version

## Required libraries:
* vector
* functional
* random
* ctime

They are loaded automatically.

For more information, open [specification](https://github.com/Cantro93/ores/wiki/Specification).
## Planned updates
- [ ] Remembering the last stable quantity
- [ ] Library with more randomizers
