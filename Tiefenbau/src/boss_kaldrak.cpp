#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedInstance.h"
#include "instance_titanenbau.h"

enum KaldrakSpells
{
    SPELL_SPLIT_FORM      = 99021,
    SPELL_BARRIER_ZONE    = 99022,
    SPELL_WRONG_TARGET    = 99023,
    SPELL_CALL_ADDS       = 99024,
    SPELL_AURA_SHADOW     = 99025,
    SPELL_AURA_ARCANE     = 99026,
    SPELL_AURA_FROST      = 99027,
};

enum KaldrakEvents
{
    EVENT_BARRIER = 1,
    EVENT_CALL_ADDS,
};

enum KaldrakNpcs
{
    NPC_KALDRAK_ARCANE = 90020,
    NPC_KALDRAK_FROST  = 90021,
    NPC_KALDRAK_SHADOW = 90022,
};

class boss_kaldrak : public CreatureScript
{
public:
    boss_kaldrak() : CreatureScript("boss_kaldrak") { }

    struct boss_kaldrakAI : public BossAI
    {
        boss_kaldrakAI(Creature* creature) : BossAI(creature, DATA_KALDRAK) { }

        bool split66 = false;
        bool split33 = false;

        void Reset() override
        {
            _Reset();
            split66 = false;
            split33 = false;
        }

        void EnterCombat(Unit* /*who*/) override
        {
            _EnterCombat();
            events.ScheduleEvent(EVENT_BARRIER, 12000);
            events.ScheduleEvent(EVENT_CALL_ADDS, 20000);
        }

        void DamageTaken(Unit* /*who*/, uint32& /*damage*/) override
        {
            if (!split66 && HealthBelowPct(66))
            {
                split66 = true;
                DoCast(me, SPELL_SPLIT_FORM);
                SummonFragments();
            }
            else if (!split33 && HealthBelowPct(33))
            {
                split33 = true;
                DoCast(me, SPELL_SPLIT_FORM);
                SummonFragments();
            }
        }

        void SummonFragments()
        {
            Position pos = me->GetPosition();
            me->SetVisible(false);
            me->AttackStop();

            SummonWarden(NPC_KALDRAK_ARCANE, pos, SPELL_AURA_ARCANE);
            SummonWarden(NPC_KALDRAK_FROST,  pos, SPELL_AURA_FROST);
            SummonWarden(NPC_KALDRAK_SHADOW, pos, SPELL_AURA_SHADOW);
        }

        void SummonWarden(uint32 entry, Position basePos, uint32 auraSpell)
        {
            Position spawn = basePos;
            spawn.m_positionX += irand(-5, 5);
            spawn.m_positionY += irand(-5, 5);

            if (Creature* warden = me->SummonCreature(entry, spawn, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000))
            {
                warden->AddAura(auraSpell, warden);
                warden->SetInCombatWithZone();
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
                    case EVENT_BARRIER:
                        DoCastAOE(SPELL_BARRIER_ZONE);
                        events.ScheduleEvent(EVENT_BARRIER, 20000);
                        break;

                    case EVENT_CALL_ADDS:
                        DoCast(SPELL_CALL_ADDS);
                        events.ScheduleEvent(EVENT_CALL_ADDS, 30000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_kaldrakAI(creature);
    }
};

void AddSC_boss_kaldrak() { new boss_kaldrak(); }
