-- Instance Template: Titanenbau Raid
DELETE FROM `instance_template` WHERE `map` = 5000;
INSERT INTO `instance_template` (`map`, `script`, `reset_delay`, `comment`)
VALUES (5000, 'instance_titanenbau', 604800, 'Titanenbau (Custom Raid)');
