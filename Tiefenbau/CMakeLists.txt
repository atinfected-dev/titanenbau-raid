# titanenbau_raid/CMakeLists.txt

set(scripts_STAT_SRCS
    ${scripts_STAT_SRCS}
    src/boss_azurion.cpp
    src/boss_kyron.cpp
    src/boss_kaldrak.cpp
    src/boss_altherion.cpp
    src/instance_titanenbau.cpp
)

message("  -> Loaded Titanenbau Raid custom module")