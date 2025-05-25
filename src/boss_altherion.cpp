#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedInstance.h"
#include "instance_titanenbau.h"

enum AltherionSpells
{
    SPELL_VOID_LANCE         = 99031,
    SPELL_DARK_IMPLSION      = 99032,
    SPELL_GRAV_PULL          = 99033,
    SPELL_FALLING_ORBS       = 99034,
    SPELL_HARDMODE_OVERLOAD  = 99035,
    SPELL_SUMMON_PYLON_ADDS  = 99036,
};

enum AltherionEvents
{
    EVENT_VOID_LANCE = 1,
    EVENT_IMPLSION,
    EVENT_PULL,
    EVENT_ORBS,
    EVENT_OVERLOAD,
    EVENT_ADDS
};

class boss_altherion : public CreatureScript
{
public:
    boss_altherion() : CreatureScript("boss_altherion") { }

    struct boss_altherionAI : public BossAI
    {
        boss_altherionAI(Creature* creature) : BossAI(creature, DATA_ALTHERION) {}

        bool phase2 = false;
        bool overloadTriggered = false;

        void Reset() override
        {
            _Reset();
            phase2 = false;
            overloadTriggered = false;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_VOID_LANCE, 8000);
            events.ScheduleEvent(EVENT_IMPLSION, 12000);
        }

        void DamageTaken(Unit* /*who*/, uint32& /*damage*/) override
        {
            if (!phase2 && HealthBelowPct(70))
            {
                phase2 = true;
                events.ScheduleEvent(EVENT_PULL, 3000);
                events.ScheduleEvent(EVENT_ORBS, 5000);
                if (IsHeroic())
                    events.ScheduleEvent(EVENT_ADDS, 10000);
            }

            if (!overloadTriggered && HealthBelowPct(30))
            {
                overloadTriggered = true;

                if (!CrystalsDestroyed())
                    DoCastAOE(SPELL_HARDMODE_OVERLOAD);
            }
        }

        bool CrystalsDestroyed()
        {
            // Optional: instance check for destroyed crystals
            return false;
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
                    case EVENT_VOID_LANCE:
                        DoCastVictim(SPELL_VOID_LANCE);
                        events.ScheduleEvent(EVENT_VOID_LANCE, 10000);
                        break;

                    case EVENT_IMPLSION:
                        DoCastAOE(SPELL_DARK_IMPLSION);
                        events.ScheduleEvent(EVENT_IMPLSION, 15000);
                        break;

                    case EVENT_PULL:
                        DoCastAOE(SPELL_GRAV_PULL);
                        events.ScheduleEvent(EVENT_PULL, 20000);
                        break;

                    case EVENT_ORBS:
                        DoCastAOE(SPELL_FALLING_ORBS);
                        events.ScheduleEvent(EVENT_ORBS, 25000);
                        break;

                    case EVENT_ADDS:
                        DoCast(SPELL_SUMMON_PYLON_ADDS);
                        events.ScheduleEvent(EVENT_ADDS, 30000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_altherionAI(creature);
    }
};

void AddSC_boss_altherion() { new boss_altherion(); }
