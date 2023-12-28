# c-map (hash map in C)
## Information
This repository contains a hash map in C.  
The focus of this repository is to have a simple implementation, while also being fully featured.  
This is far from finished, I plan on adding more features.  

## Planned features
Currently, the hash map is only able to use a string as its hash.  
This implementation also has no form of type-safety, everything is implemented via `void*`'s.

Here are my planned features:  
- [ ] Allowing for any kind of key (`void*` with a size)
- [ ] Implementing type safety with macros

