#include "al/LiveActor/LiveActor.h"
#include "al/util.hpp"
#include "al/layout/LayoutActor.h"
#include "game/StageScene.hpp"
#include "game/Layouts/CoinCounter.h"
#include "rs/util.hpp"
#include <cmath>
#include <stdio.h>
#include "game/Coin/Coin.h"
#include "al/sensor/HitSensor.h"
#include "game/Player/PlayerModelChangerHakoniwa.h"

#include "sead/math/seadVector.h"
#include "sead/math/seadMatrix.h"
#include "sead/prim/seadSafeString.h"
#include "types.h"

#include "helpers.hpp"

static bool isEndSpiral = false;

void coinControlHook() {

    __asm ("MOV X19, X0");

    Coin* coin;
    __asm ("MOV %[result], X0" : [result] "=r" (coin));

    PlayerActorHakoniwa* player = al::getPlayerActor(coin, 0);
    HackCap* cap = player->mHackCap;
    sead::Vector3f* playerTrans = al::getTrans(player);
    const char* curAnimName = player->mPlayerAnimator->mAnimFrameCtrl->getActionName();
    const char* capAnimName = al::getActionName(cap);


    if (al::isEqualString(coin->mActorName,"pos")) {
        al::setTrans(coin, *playerTrans);

        static bool showActors = true;

        if (al::isPadHoldZL(-1) && al::isPadTriggerZR(-1)) {
            showActors = !showActors;
        }
        if (showActors) {
            player->mPlayerModelChanger->showModel();
            if (cap->isFlying()) {
                al::showModel(cap);
            } else {
                al::hideModel(cap);
            }
            
        } else {
            player->mPlayerModelChanger->hideModel();
            al::hideModel(cap);
        }

    }

    if (al::isEqualString(curAnimName, "Rolling") || al::isEqualString(curAnimName, "RollingStart") 
        || al::isEqualString(curAnimName, "RollingEnd") || al::isEqualString(curAnimName, "SquatWalk") 
        || al::isEqualString(curAnimName, "SquatWait") || al::isEqualString(curAnimName, "SquatStart") 
        || al::isEqualString(curAnimName,"SquatEnd")) {

        if (al::isEqualString(coin->mActorName, "head")) {

            sead::Vector3f* playerHead = al::getSensorPos(player, "SquatHead");
            al::setTrans(coin, *playerHead);
            al::setScaleAll(coin, al::getSensorRadius(player, "SquatHead"));

        } else if (al::isEqualString(coin->mActorName, "foot")) {

            sead::Vector3f* playerFoot = al::getSensorPos(player, "SquatFoot");
            al::setTrans(coin, *playerFoot);
            al::setScaleAll(coin, al::getSensorRadius(player, "SquatFoot"));

        } else if (al::isEqualString(coin->mActorName, "body")) {

            sead::Vector3f* playerBody = al::getSensorPos(player, "SquatBody");
            al::setTrans(coin, *playerBody);
            al::setScaleAll(coin, al::getSensorRadius(player, "SquatBody"));

        }
    } else if (al::isEqualString(curAnimName, "WallCatch") || al::isEqualString(curAnimName,"WallCatchMoveL") 
        || al::isEqualString(curAnimName,"WallCatchMoveR") || al::isEqualString(curAnimName,"WallCatchStart") 
        || al::isEqualString(curAnimName,"WallCatchEnd") || al::isEqualString(curAnimName,"WallCatchEndFast") 
        || al::isEqualString(curAnimName, "GrabCeilWait") || al::isEqualString(curAnimName, "GrabCeilSwing")
        || al::isEqualString(curAnimName,"GrabCeilStart")) {

        if (al::isEqualString(coin->mActorName, "head") ) {

            sead::Vector3f* playerHead = al::getSensorPos(player, "WallGrabHead");
            al::setTrans(coin, *playerHead);
            al::setScaleAll(coin, al::getSensorRadius(player, "WallGrabHead"));

        }  else if (al::isEqualString(coin->mActorName, "foot") ) {

            sead::Vector3f* playerFoot = al::getSensorPos(player, "WallGrabFoot");
            al::setTrans(coin, *playerFoot);
            al::setScaleAll(coin, al::getSensorRadius(player, "WallGrabFoot"));

        } else if (al::isEqualString(coin->mActorName, "body") ) {

            sead::Vector3f* playerBody = al::getSensorPos(player, "WallGrabBody");
            al::setTrans(coin, *playerBody);
            al::setScaleAll(coin, al::getSensorRadius(player, "WallGrabBody"));
        }
    } else if (al::isEqualString(curAnimName,"PoleWait") || al::isEqualString(curAnimName,"PoleTurn") 
        || al::isEqualString(curAnimName,"PoleClimb") || al::isEqualString(curAnimName,"PoleFall")) {

        if (al::isEqualString(coin->mActorName, "head")) {

            sead::Vector3f* playerHead = al::getSensorPos(player, "PoleClimbHead");
            al::setTrans(coin, *playerHead);
            al::setScaleAll(coin, al::getSensorRadius(player, "PoleClimbHead"));

        } else if (al::isEqualString(coin->mActorName, "foot")) {

            sead::Vector3f* playerFoot = al::getSensorPos(player, "PoleClimbFoot");
            al::setTrans(coin, *playerFoot);
            al::setScaleAll(coin, al::getSensorRadius(player, "PoleClimbFoot"));

        } else if (al::isEqualString(coin->mActorName, "body")) {

            sead::Vector3f* playerBody = al::getSensorPos(player, "PoleClimbBody");
            al::setTrans(coin, *playerBody);
            al::setScaleAll(coin, al::getSensorRadius(player, "PoleClimbBody"));
        }
    } else if (al::isEqualString(coin->mActorName, "head")) {

        sead::Vector3f* playerHead = al::getSensorPos(player, "Head");
        al::setTrans(coin, *playerHead);
        al::setScaleAll(coin, al::getSensorRadius(player, "Head"));

    } else if (al::isEqualString(coin->mActorName, "foot")) {

        sead::Vector3f* playerFoot = al::getSensorPos(player, "Foot");
        al::setTrans(coin, *playerFoot);
        al::setScaleAll(coin, al::getSensorRadius(player, "Foot"));

    } else if (al::isEqualString(coin->mActorName, "body")) {

        sead::Vector3f* playerBody = al::getSensorPos(player, "Body");
        al::setTrans(coin, *playerBody);
        al::setScaleAll(coin, al::getSensorRadius(player, "Body"));
    }

    if (al::isEqualString(coin->mActorName, "pos") || al::isEqualString(coin->mActorName,"head") 
        || al::isEqualString(coin->mActorName,"body") || al::isEqualString(coin->mActorName,"foot")) {

        al::invalidateHitSensors(coin);
        sead::Quatf* playerQuat = al::getQuat(player);
        al::setQuat(coin, *playerQuat);
    }

    if (al::isEqualString(coin->mActorName, "Trample")) {
        al::invalidateHitSensors(coin);
        if (cap->isFlying()) {
            al::showModel(coin);
            al::setTrans(coin, *al::getSensorPos(cap, "Attack"));
            al::setScaleAll(coin, al::getSensorRadius(cap, "Attack"));
        } else if (!cap->isFlying()) {
            al::hideModel(coin);
            al::setTrans(coin, *playerTrans);
        }
    }

    if (!cap->isFlying() && isEndSpiral) {
        isEndSpiral = false;
    }

    if (al::isEqualString(coin->mActorName, "SpiralTail1")) {
        static int frameNo = 0;
        al::invalidateHitSensors(coin);
        if (cap->isFlying() && cap->isThrowTypeSpiral() && (frameNo == 10) && !isEndSpiral) {
            al::showModel(coin);
            al::setTrans(coin, *al::getSensorPos(cap, "SpiralTail1"));
            al::setScaleAll(coin, al::getSensorRadius(cap,"SpiralTail1"));
        } else if (!cap->isFlying() || isEndSpiral) {
            al::hideModel(coin);
            al::setTrans(coin, *playerTrans);
            frameNo = 0;
        } else frameNo++;
    }

    if (al::isEqualString(coin->mActorName, "SpiralTail2")) {
        static int frameNo = 0;
        al::invalidateHitSensors(coin);
        if (cap->isFlying() && cap->isThrowTypeSpiral() && (frameNo == 10) && !isEndSpiral) {
            al::showModel(coin);
            al::setTrans(coin, *al::getSensorPos(cap, "SpiralTail2"));
            al::setScaleAll(coin, al::getSensorRadius(cap,"SpiralTail2"));
        } else if (!cap->isFlying() || isEndSpiral) {
            al::hideModel(coin);
            al::setTrans(coin, *playerTrans);
            frameNo = 0;
        } else frameNo++;
    }

    if (al::isEqualString(coin->mActorName, "SpiralTail3")) {
        static int frameNo = 0;
        al::invalidateHitSensors(coin);
        if (cap->isFlying() && cap->isThrowTypeSpiral() && (frameNo == 10) && !isEndSpiral) {
            al::showModel(coin);
            al::setTrans(coin, *al::getSensorPos(cap, "SpiralTail3"));
            al::setScaleAll(coin, al::getSensorRadius(cap,"SpiralTail3"));
        } else if (!cap->isFlying() || isEndSpiral) {
            al::hideModel(coin);
            al::setTrans(coin, *playerTrans);
            frameNo = 0;
        } else frameNo++;
    }

    if (al::isEqualString(coin->mActorName, "SpiralTail4")) {
        static int frameNo = 0;
        al::invalidateHitSensors(coin);
        if (cap->isFlying() && cap->isThrowTypeSpiral() && (frameNo == 10) && !isEndSpiral) {
            al::showModel(coin);
            al::setTrans(coin, *al::getSensorPos(cap, "SpiralTail4"));
            al::setScaleAll(coin, al::getSensorRadius(cap,"SpiralTail4"));
        } else if (!cap->isFlying() || isEndSpiral) {
            al::hideModel(coin);
            al::setTrans(coin, *playerTrans);
            frameNo = 0;
        } else frameNo++;
    }

    if (al::isEqualString(coin->mActorName, "SpiralTail5")) {
        static int frameNo = 0;
        al::invalidateHitSensors(coin);
        if (cap->isFlying() && cap->isThrowTypeSpiral() && (frameNo == 10) && !isEndSpiral) {
            al::showModel(coin);
            al::setTrans(coin, *al::getSensorPos(cap, "SpiralTail5"));
            al::setScaleAll(coin, al::getSensorRadius(cap,"SpiralTail5"));
        } else if (!cap->isFlying() || isEndSpiral) {
            al::hideModel(coin);
            al::setTrans(coin, *playerTrans);
            frameNo = 0;
        } else frameNo++;
    }

    if (al::isEqualString(coin->mActorName, "capPos")) {
        al::invalidateHitSensors(coin);
        if (cap->isFlying()){
            al::setTrans(coin, *al::getTrans(cap));
            al::setQuat(coin, *al::getQuat(cap));
        } else if (!cap->isFlying()) {
            al::setTrans(coin, *al::getTrans(player));
            al::setQuat(coin, *al::getQuat(player));
    }
}
    
    __asm ("MOV X0, %[input]" : [input] "=r" (coin));
}

void endThrowSpiralHook() {

    __asm ("LDR X19, [X1]");

    isEndSpiral = true;

}