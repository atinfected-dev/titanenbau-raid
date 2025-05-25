# Titanenbau Raid Module for AzerothCore (WotLK 3.3.5a)

A full 4-boss custom raid built in a titan-themed environment on a custom map (ID: 5000). Supports 10/25 Normal & Heroic modes.

## Features

- 4 fully scripted bosses in C++
- Working loot system
- Instance tracking
- Phases, adds, scaling
- Hardmode support (Boss 4)

## Setup Instructions

### 1. Clone or copy this module into your AzerothCore:

src/modules/titanenbau_raid/

### 2. Compile the core:

```bash
cd azerothcore
mkdir build && cd build
cmake ../ -DTOOLS=1 -DSCRIPTS=static
make -j $(nproc)

3. Import SQL:

mysql -u root -p azerothcore_world < sql/instance_template.sql
mysql -u root -p azerothcore_world < sql/creature_template.sql
mysql -u root -p azerothcore_world < sql/creature_spawn.sql
mysql -u root -p azerothcore_world < sql/creature_loot_template.sql

4. Teleport In-Game:

.tele titanenbau