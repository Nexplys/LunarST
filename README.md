# LunarST

> **Early prototype — working title**

LunarST is a solo-developed isometric action RPG prototype built with Unreal Engine 5.

Set in a new archipelago within the lunarpunk universe of a novel I am currently writing, the game follows an astromancer and their shapeshifting nebula companion through a world of eternal night. Fast, responsive combat combines stellar magic, exploration and secrets whose discovery may completely change how the world is understood.

The project currently focuses on building and validating its core gameplay foundations before defining the scope of a complete game.

## Design direction

- Fast isometric combat inspired by *Tunic*, *Hades* and *Windblown*
- Responsive movement with directional dodging and soft aim assistance
- Several astromancy playstyles, beginning with:
  - **Sidereal Blade** - aggressive close-range combat
  - **Stellar Shards** - fast and mobile ranged attacks
- A branching, snowflake-shaped progression system powered by gathered light
- A nebula companion intended to interact with and transform the player's abilities
- A compact, interconnected world focused on exploration, shortcuts and hidden rules
- Player choices that influence the archipelago and its ecosystem

The intended vertical slice will concentrate on a small number of polished systems rather than attempting to represent the full game immediately.

## Current prototype

The following foundations are implemented on the `main` branch:

- Isometric camera and character movement
- Enhanced Input-based prototype controls
- Gameplay Ability System integration
- Health and Astral Energy attributes
- Directional dodge ability
  - animation montage
  - cooldown
  - temporary invulnerability
- Basic Astral Bolt ability
  - Astral Energy cost
  - cooldown
  - projectile movement
  - damage and knockback
- Native gameplay tags for abilities, inputs, states and cooldowns

## In development

- GAS-based damage pipeline and reusable test enemy
- Sidereal Blade melee combat
- Light absorption and character progression
- Rest anchors and build reconfiguration
- First compact combat and exploration area
- Initial nebula companion functionality

Everything listed here is subject to change while the prototype is being evaluated.

## Technology

- **Engine:** Unreal Engine 5.8
- **Languages:** C++ and Blueprint
- **Gameplay framework:** Gameplay Ability System
- **Input:** Enhanced Input
- **Version control:** Git and Git LFS
- **Primary IDE:** JetBrains Rider
- **3D tools:** Blender

## Getting started

### Requirements

- Unreal Engine 5.8
- Git
- Git LFS
- A C++ toolchain compatible with Unreal Engine 5.8
- JetBrains Rider for Unreal Engine or another supported C++ IDE

### Clone and open the project

```bash
git lfs install
git clone https://github.com/Nexplys/LunarST.git
cd LunarST
git lfs pull
```

Then:

1. Generate the Unreal project files from `LunarST.uproject` if required.
2. Open the project in Rider or Unreal Editor.
3. Build the `LunarSTEditor` target.
4. Launch the project with Unreal Engine 5.8.

Unreal assets (`.uasset` and `.umap`) are tracked through Git LFS. Make sure Git LFS is installed before cloning or pulling the repository.

## Project structure

The custom C++ code is progressively being organized by responsibility:

```text
Source/LunarST/
├── AbilitySystem/
│   ├── Abilities/
│   ├── Attributes/
│   └── Tags/
├── Characters/
│   └── Player/
├── Combat/
│   └── Projectiles/
└── Variant_Combat/
```

Some content from Unreal Engine's Combat variant is still present while the prototype is being separated into its own systems.

## Development status

LunarST is an experimental, pre-production project. It is not currently a playable release, and no stable build is available.

The immediate objective is to produce a focused vertical slice demonstrating:

- the core movement and combat feel;
- the Sidereal Blade and Stellar Shards playstyles;
- one enemy encounter;
- a first progression choice;
- a small explorable area with at least one meaningful secret.

## License

No open-source license is currently provided. Unless stated otherwise, the project's original code, world, characters and assets are all rights reserved.
