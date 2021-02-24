# What is the game about
A little game where you have to kill the enemy by sending units in its direction.

## Mechanics
When you start the program, you can either start a new game or continue.
You can pause the game by pressing ESC key

- Starting a new game will take you to menu where you have to select the difficulty.
  - Easy: multiplies enemy stats by 1.05 per cleared level
  - Medium: multiplies enemy stats by 1.1 per cleared level
  - Hard: multiplies enemy stats by 1.15 per cleared level
- Continuing will load data from [ assets/save.json ]
  - You can only have 1 active save so use it wisely

There are currently 3 different units that you can summon
- Warrior
- Tank
- Mage

Each unit has different stats which you can modify by changing [ "summons" ] object in [ assets/objects.json ] file
You can also add custom units by modifying that object

Currency
- With each second you get 2 Fujika 
  - You can spend Fujika by summoning units.
- When you reach Fujika limit of 20 you start gaining 1 Fuko every second.
  - You can spend Fuko on equipement in Shop menu after you pass a level.
  
Equipement
- The equipement hasn't been made modular yet but will most likely be before initial release
- Each piece of Equipement has predefined cost
- The Equipement can be bought only when it doesn't decrease one of the stats of the unit to a value lower than 1
- Buying the Equipement doesn't change its cost

Enemy
- Enemy has starting stats which can be edited in [ assets/objects.json ]
- With each level enemy stats are multiplied 
  - The stats are rounded down to integer
- Enemy info label doesn't update, so the only way to guess current health is to see how fast it moves
  - The lower the health, the lower the movement speed, capped at 6
- Hits everyone within range
  - Only starts hitting when directly next to at least one entity
    - Doesn't stop hitting until every entity within range is dead

# Disclaimer
This is a side project and there are no plans for further developement after the initial release

As such pull requests will most likely not be handled

This is my first attempt at creating a game so it's probably filled with bad quality code by professional standards.
I tried to improve the quality as much as I could and learnt a lot while doing that,
so overall I think that the project was a success.
