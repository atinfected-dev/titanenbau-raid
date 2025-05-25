#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedInstance.h"
#include "instance_titanenbau.h"

enum KyronSpells
{
    SPELL_MOLTEN_ARMOR       = 99011,
    SPELL_FORGE_SMASH        = 99012,
    SPELL_OVERCHARGED_WEAPON = 99013,
    SPELL_SUMMON_ADDS        = 99014,
    SPELL_LAVA_POOL          = 99015,
};

enum KyronEvents
{
    EVENT_FORGE_SMASH = 1,
    EVENT_OVERCHARGE,
    EVENT_SUMMON_ADDS,
    EVENT_LAVA_PHASE
};

class boss_kyron : public CreatureScript
{
public:
    boss_kyron() : CreatureScript("boss_kyron") { }

    struct boss_kyronAI : public BossAI
    {
        boss_kyronAI(Creature* creature) : BossAI(creature, DATA_KYRON) { }

        bool moltenPhaseStarted = false;

        void Reset() override
        {
            _Reset();
            moltenPhaseStarted = false;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _EnterCombat();
            DoCast(me, SPELL_MOLTEN_ARMOR, true);
            events.ScheduleEvent(EVENT_FORGE_SMASH, 8000);
            events.ScheduleEvent(EVENT_OVERCHARGE, 15000);
        }

        void DamageTaken(Unit* /*who*/, uint32& /*damage*/) override
        {
            if (!moltenPhaseStarted && HealthBelowPct(50))
            {
                moltenPhaseStarted = true;
                events.ScheduleEvent(EVENT_SUMMON_ADDS, 5000);
                events.ScheduleEvent(EVENT_LAVA_PHASE, 3000);
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FORGE_SMASH:
                        if (Unit* target = me->GetVictim())
                            DoCast(target, SPELL_FORGE_SMASH);
                        events.ScheduleEvent(EVENT_FORGE_SMASH, 10000);
                        break;

                    case EVENT_OVERCHARGE:
                        DoCast(me, SPELL_OVERCHARGED_WEAPON);
                        events.ScheduleEvent(EVENT_OVERCHARGE, 25000);
                        break;

                    case EVENT_SUMMON_ADDS:
                        DoCast(me, SPELL_SUMMON_ADDS);
                        events.ScheduleEvent(EVENT_SUMMON_ADDS, 20000);
                        break;

                    case EVENT_LAVA_PHASE:
                        DoCastAOE(SPELL_LAVA_POOL);
                        events.ScheduleEvent(EVENT_LAVA_PHASE, 15000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_kyronAI(creature);
    }
};

void AddSC_boss_kyron() { new boss_kyron(); }
