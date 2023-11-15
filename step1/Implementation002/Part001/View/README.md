# View
## Description
To improve our solution and make it some kind functional a view is necessary, since this is not part of the test we will not focus so much on this, well, I'll try not.

For this view architecture I'll implement a modular solution using composition, that will be made of, menus and items, each item will have a callback function to work in an event dispatcher fashion, the controller will have the event handlers, but I don't want to do anything too complex here, so I'll use lambdas. Each menu will be able to have sub-menus and a mix of items and menus. To do this I'll have to create some interfaces, I'll think about it after lunch.

Everything will reside inside a loop that I'll call Core, why core you may ask, and the answer is, I have no idea. I'm really bad at naming things.

### Menus
### Items
### Usage

TODO : Do some clean up, a lot has changed