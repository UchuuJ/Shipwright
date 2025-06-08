#include <libultraship/bridge.h>
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "functions.h"
#include "macros.h"
#include "variables.h"
#include "soh/Enhancements/custom-message/CustomMessageManager.h"
#include "soh/Enhancements/debugger/MessageViewer.h"
#include "soh/ActorDB.h"

extern "C" PlayState* gPlayState;

static constexpr int32_t CVAR_RUPEE_TAXMAN_DEFAULT = 0;
#define CVAR_RUPEE_TAXMAN_NAME CVAR_ENHANCEMENT("RupeeTaxman")
#define CVAR_RUPEE_TAXMAN_VALUE CVarGetInteger(CVAR_RUPEE_TAXMAN_NAME, CVAR_RUPEE_TAXMAN_DEFAULT)

static constexpr int32_t CVAR_RUPEE_DASH_INTERVAL_DEFAULT = 5;
#define CVAR_RUPEE_DASH_INTERVAL_NAME CVAR_ENHANCEMENT("RupeeDashInterval")
#define CVAR_RUPEE_DASH_INTERVAL_TIME \
    CVarGetInteger(CVAR_RUPEE_DASH_INTERVAL_NAME, CVAR_RUPEE_DASH_INTERVAL_DEFAULT) * 20

s16 previousScene = 0;

void UpdateRupeeTaxMan() {
    // Initialize Timer
    static uint16_t rupeeDashTimer = 0;
    //Gets our boy the man, the myth the legend, LINK!
    Actor PlayerActor = GET_PLAYER(gPlayState)->actor;


    // Did time change by DashInterval?
    if (rupeeDashTimer < CVAR_RUPEE_DASH_INTERVAL_TIME) {
        rupeeDashTimer++;
        return;
    }

    rupeeDashTimer = 0;
   // if (gSaveContext.rupees > 0) {
        //huh weird code tbh
       // uint16_t walletSize = (CUR_UPG_VALUE(UPG_WALLET) + 1) * -1;
        Rupees_ChangeBy(-1);
        if(gSaveContext.rupees < 0){ 

            //I could draw here however this function seems to be in a process thats not updated every ms so it gets overdrawn wiping the message
            //Interface_DrawTextLineOnBuffer(gPlayState->state.gfxCtx, "The Past Inside the Present!", 0, 0,
              //                     255, 255, 80, 255, 0.8f, true);
            lusprintf(__FILE__, __LINE__, 2, "Oh No Links in debt, Spawning like like :^)");
            lusprintf(__FILE__, __LINE__, 2, "LIKE LIKE POS X: %i, Y: %i Z: %i",PlayerActor.world.pos.x+5, PlayerActor.world.pos.y,PlayerActor.world.pos.z);
            lusprintf(__FILE__, __LINE__, 2, "PlayerActor ID: %i",PlayerActor.id);
            
            // Spawns Like Like
            Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_RR, PlayerActor.world.pos.x+5, PlayerActor.world.pos.y, PlayerActor.world.pos.z+200, 0, 0, 0, 3, false);
            //CustomMessage("Oh No Links in debt, Spawning Like Like :^)", /*german*/"Raubschleims Metallmahlzeit", /*french*/"un amuse-gueule de Pudding");
            if(gPlayState->sceneNum != previousScene){
                lusprintf(__FILE__, __LINE__, 2, "LIKE LIKE POS X: %i, Y: %i Z: %i",PlayerActor.world.pos.x+5, PlayerActor.world.pos.y,PlayerActor.world.pos.z);
               

                //Plays Ganons laugh
                Audio_PlaySoundGeneral(NA_SE_EN_GANON_LAUGH, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                   &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
               
                //Can I spawn a deadhead? 
                //Yes i can lmao, requires ACTOR_EN_DHA (Dead hands, dead hand)
                Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_DHA, PlayerActor.world.pos.x+5, PlayerActor.world.pos.y, PlayerActor.world.pos.z+200, 0, 0, 0, 3, false);
                Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_DH, PlayerActor.world.pos.x+5, PlayerActor.world.pos.y, PlayerActor.world.pos.z+200, 0, 0, 0, 3, false);

                //Supposedly spawns in a bomb (idea is to set the Deadhand off) Doesn't work
                Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_BOM, PlayerActor.world.pos.x+5, PlayerActor.world.pos.y, PlayerActor.world.pos.z+200, 0, 0, 0, 3, false);

                //Breaks Z targeting, reloading scene fixes it (dead head refernce(good song))
               // MessageDebug_DisplayCustomMessage("YOU ARE THE SUN GODDESS UWU");
               
               //Make sure Ganon's laugh and Dead hand only spawn once per scene  
                previousScene = gPlayState->sceneNum;
                lusprintf(__FILE__, __LINE__, 2, "CurrentScene: %i",gPlayState->sceneNum);
            }
        }
}

void RegisterRupeeTaxMan() {
    lusprintf(__FILE__, __LINE__, 2, "Registered File");
    COND_HOOK(OnPlayerUpdate, CVAR_RUPEE_TAXMAN_VALUE, UpdateRupeeTaxMan);
}

static RegisterShipInitFunc initFunc_RupeeTaxMan(RegisterRupeeTaxMan, { CVAR_RUPEE_TAXMAN_NAME });
