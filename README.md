# Dungeon of Sorrows 🗡️

**Text-based Dungeon Crawler Roguelike, written entirely in C++**
**University Project**

**Current Version:** Game Engine v1.0

## 🎮 Core Features

* **Custom Game Engine:** Implements a standard, non-blocking `Input -> Update -> Render` game loop using `<conio.h>`.
* **Object-Oriented Architecture:** Heavy utilization of classes, inheritance, and encapsulation (e.g., base `Entity` classes scaling to `Player` and `Enemy`).
* **Procedural Map Generation:** Utilizes a custom **Drunkard's Walk (Random Walker)** algorithm to carve out 100% unique, organic, and interconnected cave systems on every single floor.
* **Dynamic Safe Spawning:** An algorithmic safety net that scans the randomly generated grid to ensure the Player, Enemies, and Exit Stairs only spawn on valid floor tiles.
* **Fog of War:** A localized exploration system that hides unvisited areas of the map, requiring the player to explore the darkness to reveal the layout.
* **Turn-Based Combat:** Proximity-based combat system featuring dynamic UI text updates and a "Tile-Swap Lunge" bump animation for visual game juice.
* **Infinite Progression:** A fully integrated "Stand-and-Interact" staircase system (using the Spacebar) that wipes the board, regenerates a new procedural map, and scales the floor depth infinitely.
* **Aspect Ratio Correction:** Custom render logic that manipulates terminal character spacing to simulate a true 1:1 grid visual format.

## 🛠️ Technical Stack

* **Language:** C++
* **Libraries:** Standard Template Library (`<iostream>`, `<vector>`, `<string>`) and OS-specific console input headers.
* **Environment:** Designed to run via standard terminal/command line.

## 🚀 Roadmap

- [ ] Transition from a single Enemy to an Entity Manager.
- [ ] Implement a collectible Item/Loot system (Gold, Health Potions).
- [ ] Expand the UI to include an event log and player stats.

## 🚀 How to Run (Upcoming)

*Instructions for compiling and running the executable will be added as development progresses.*

---

