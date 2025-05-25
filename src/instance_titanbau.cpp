// src/instance_titanenbau.cpp

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "Map.h"
#include "Creature.h"
#include "GameObject.h"
#include "instance_titanenbau.h"

class instance_titanenbau : public InstanceMapScript
{
public:
    instance_titanenbau() : InstanceMapScript("instance_titanenbau", 5000) { }

    struct instance_titanenbau_InstanceMapScript : public InstanceScript
    {
        instance_titanenbau_InstanceMapScript(Map* map) : InstanceScript(map) 
        {
            SetBossNumber(MAX_ENCOUNTERS);
        }

        void Initialize() override
        {
            memset(_bossGuids, 0, sizeof(_bossGuids));
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
                case 90001: _bossGuids[DATA_AZURION] = creature->GetGUID(); break;
                case 90002: _bossGuids[DATA_KYRON] = creature->GetGUID(); break;
                case 90003: _bossGuids[DATA_KALDRAK] = creature->GetGUID(); break;
                case 90004: _bossGuids[DATA_ALTHERION] = creature->GetGUID(); break;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            if (type < MAX_ENCOUNTERS)
                SetBossState(type, EncounterState(data));
        }

        uint32 GetData(uint32 type) const override
        {
            if (type < MAX_ENCOUNTERS)
                return GetBossState(type);

            return 0;
        }

        ObjectGuid GetGuidData(uint32 type) const override
        {
            if (type < MAX_ENCOUNTERS)
                return _bossGuids[type];

            return ObjectGuid::Empty;
        }

    private:
        ObjectGuid _bossGuids[MAX_ENCOUNTERS];
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_titanenbau_InstanceMapScript(map);
    }
};

void AddSC_instance_titanenbau()
{
    new instance_titanenbau();
}
