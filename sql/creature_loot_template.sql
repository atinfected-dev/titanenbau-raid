-- Azurion
DELETE FROM `creature_loot_template` WHERE `entry` = 90001;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`)
VALUES
(90001, 50343, 25, 1, 1, 1, 1),
(90001, 50643, 30, 1, 2, 1, 1),
(90001, 50730, 20, 1, 3, 1, 1),
(90001, 49908, 100, 1, 4, 1, 1);

-- Kyron
DELETE FROM `creature_loot_template` WHERE `entry` = 90002;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`)
VALUES
(90002, 50786, 28, 1, 1, 1, 1),
(90002, 50619, 24, 1, 2, 1, 1),
(90002, 50415, 22, 1, 3, 1, 1),
(90002, 49908, 100, 1, 4, 1, 1);

-- Kaldrak
DELETE FROM `creature_loot_template` WHERE `entry` = 90003;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`)
VALUES
(90003, 50348, 27, 1, 1, 1, 1),
(90003, 50613, 23, 1, 2, 1, 1),
(90003, 50695, 22, 1, 3, 1, 1),
(90003, 49908, 100, 1, 4, 1, 1);

-- Altherion
DELETE FROM `creature_loot_template` WHERE `entry` = 90004;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`)
VALUES
(90004, 50731, 30, 1, 1, 1, 1),
(90004, 50719, 25, 1, 2, 1, 1),
(90004, 50633, 20, 1, 3, 1, 1),
(90004, 49908, 100, 1, 4, 1, 1);
