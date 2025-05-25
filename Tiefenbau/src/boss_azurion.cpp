#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedInstance.h"
#include "instance_titanenbau.h"

enum Spells
{
    SPELL_ARCANE_OVERLOAD = 99001,
    SPELL_RUNE_DETONATION = 99002,
    SPELL_TITANS_GAZE = 99003,
    SPELL_SUMMON_ADD = 99004,
};

enum Events
{
    EVENT_ARCANE_OVERLOAD = 1,
    EVENT_RUNE_DETONATION,
    EVENT_TITANS_GAZE,
    EVENT_SUMMON_ADDS,
};

enum Phases
{
    PHASE_ONE = 1,
    PHASE_TWO,
    PHASE_THREE,
};

class boss_azurion : public CreatureScript
{
public:
    boss_azurion() : CreatureScript("boss_azurion") { }

    struct boss_azurionAI : public BossAI
    {
        boss_azurionAI(Creature* creature) : BossAI(creature, DATA_AZURION) {}

        uint8 phase;

        void Reset() override
        {
            _Reset();
            phase = PHASE_ONE;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_ARCANE_OVERLOAD, 15000);
            events.ScheduleEvent(EVENT_RUNE_DETONATION, 20000);
            events.ScheduleEvent(EVENT_TITANS_GAZE, 10000);
        }

        void DamageTaken(Unit* /*who*/, uint32& /*damage*/) override
        {
            if (phase == PHASE_ONE && HealthBelowPct(66))
            {
                phase = PHASE_TWO;
                events.ScheduleEvent(EVENT_ARCANE_OVERLOAD, 10000);
                events.ScheduleEvent(EVENT_RUNE_DETONATION, 10000);
            }
            else if (phase == PHASE_TWO && HealthBelowPct(33))
            {
                phase = PHASE_THREE;
                events.ScheduleEvent(EVENT_SUMMON_ADDS, 15000);
                events.RescheduleEvent(EVENT_ARCANE_OVERLOAD, 8000);
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
                    case EVENT_ARCANE_OVERLOAD:
                        DoCastAOE(SPELL_ARCANE_OVERLOAD);
                        events.ScheduleEvent(EVENT_ARCANE_OVERLOAD, 15000);
                        break;
                    case EVENT_RUNE_DETONATION:
                        DoCastAOE(SPELL_RUNE_DETONATION);
                        events.ScheduleEvent(EVENT_RUNE_DETONATION, 20000);
                        break;
                    case EVENT_TITANS_GAZE:
                        if (Unit* tank = me->GetVictim())
                            DoCast(tank, SPELL_TITANS_GAZE);
                        events.ScheduleEvent(EVENT_TITANS_GAZE, 10000);
                        break;
                    case EVENT_SUMMON_ADDS:
                        DoCast(SPELL_SUMMON_ADD);
                        events.ScheduleEvent(EVENT_SUMMON_ADDS, 20000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_azurionAI(creature);
    }
};

void AddSC_boss_azurion() { new boss_azurion(); }

