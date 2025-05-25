-- Boss Spawns on map 5000
DELETE FROM `creature` WHERE `id` IN (90001,90002,90003,90004);

INSERT INTO `creature` (`id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `spawnMask`, `curhealth`, `curmana`)
VALUES
(90001, 5000, 2500.0, 2500.0, 100.0, 0.0, 15, 3200000, 100000), -- Azurion
(90002, 5000, 2550.0, 2550.0, 100.0, 0.0, 15, 3500000, 100000), -- Kyron
(90003, 5000, 2600.0, 2600.0, 100.0, 0.0, 15, 4000000, 100000), -- Kaldrak
(90004, 5000, 2650.0, 2650.0, 100.0, 0.0, 15, 5000000, 120000); -- Altherion
