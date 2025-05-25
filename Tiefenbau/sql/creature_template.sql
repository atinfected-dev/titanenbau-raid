-- Bosses
DELETE FROM `creature_template` WHERE `entry` IN (90001,90002,90003,90004);
INSERT INTO `creature_template` (`entry`, `name`, `subname`, `minlevel`, `maxlevel`, `exp`, `faction`, `rank`, `unit_class`, `modelid1`, `lootid`, `ScriptName`)
VALUES
(90001, 'Azurion', 'Warden of the Threshold', 83, 83, 2, 14, 3, 1, 26344, 90001, 'boss_azurion'),
(90002, 'Kyron', 'Forgemaster of the Deep Forge', 83, 83, 2, 14, 3, 1, 26340, 90002, 'boss_kyron'),
(90003, 'Kaldrak', 'Vault Warden', 83, 83, 2, 14, 3, 1, 26349, 90003, 'boss_kaldrak'),
(90004, 'Altherion', 'Core Ascendant', 83, 83, 2, 14, 3, 1, 26347, 90004, 'boss_altherion');

-- Kaldrak’s fragments
DELETE FROM `creature_template` WHERE `entry` IN (90020,90021,90022);
INSERT INTO `creature_template` (`entry`, `name`, `subname`, `minlevel`, `maxlevel`, `exp`, `faction`, `rank`, `unit_class`, `modelid1`)
VALUES
(90020, 'Fragment of Arcane', '', 83, 83, 2, 14, 1, 1, 26343),
(90021, 'Fragment of Frost', '', 83, 83, 2, 14, 1, 1, 26341),
(90022, 'Fragment of Shadow', '', 83, 83, 2, 14, 1, 1, 26342);
