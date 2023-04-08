<p align="center">

# Defend The Castle

</p>

## Introduction

A little game where you have to kill the enemy by sending units in its direction.

![](/img/game_screen.jpg)

---

## Mechanics

When you start the program, you can either start new game or continue.
You can pause the game by pressing ESC key

- Starting a new game will take you to menu where you have to select the difficulty.
  - Easy: multiplies enemy stats by 1.05 per cleared level
  - Medium: multiplies enemy stats by 1.1 per cleared level
  - Hard: multiplies enemy stats by 1.15 per cleared level
- Continuing will load data from `assets/save.json`
  - You can only have 1 active save so use it wisely

There are currently 3 different units that you can summon

- Warrior
- Tank
- Mage

Each unit has different stats which you can modify by changing `"summons"` object in `assets/objects.json` file \
You can also add custom units by modifying that object

### Currency

- With each second you get 2 Fujika
  - You can spend Fujika by summoning units.
- When you reach Fujika limit of 20 you start gaining 1 Fuko every second.
  - You can spend Fuko on equipement in Shop menu after you pass a level.

![](/img/shop_menu.jpg)

### Equipement

- You can add or modify equipement in `assets/objects.json` file by modifying `"items"` object
- Each piece of Equipement has predefined cost
- The Equipement can be bought only when it doesn't decrease one of the stats of the unit to a value lower than 1
- Buying the Equipement doesn't change its cost

### Enemy

- Enemy has starting stats which can be edited in `assets/objects.json`
- With each level enemy stats are multiplied
  - The stats are rounded down to integer
- Enemy info label doesn't update, so the only way to guess current health is to see how fast it moves
  - The lower the health, the lower the movement speed, capped at 6
- Hits everyone within range
  - Only starts hitting when directly next to at least one entity
    - Doesn't stop hitting until every entity within range is dead

---

## How to compile yourself

### example for g++

```bash
g++ -g ./src/Engine/*.cpp ./src/Managers/*.cpp ./src/Objects/*.cpp ./src/UserInterface/*.cpp -o ./build/game.exe -I"./include" -L"./lib" -lSDL2 -lSDL2_image -lSDL2_ttf --std=c++14
```

and copy `bin` folder' contents into `build/` directory that contains `game.exe` file
