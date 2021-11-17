#pragma once

#include "al/actor/ActorInitInfo.h"
#include "al/LiveActor/LiveActor.h"

class Coin : public al::LiveActor
{

public:

	void init(al::ActorInitInfo const&);

	void control(void);

};