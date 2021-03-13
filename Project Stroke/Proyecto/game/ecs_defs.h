// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class FighterCtrl;
class Bounce;
class Image;
class DeAcceleration;
class LightAttack;
class StrongAttack;
class Movement;
class Life;
class UI;

#define _CMPS_LIST_  \
	Transform,\
	FighterCtrl,\
	Image,\
	DeAcceleration,\
	Bounce, \
	LightAttack, \
	StrongAttack, \
	Movement, \
	Life, \
	UI

// groups

struct Enemy;
#define _GRPS_LIST_  Enemy

// handlers
//Creo que hay que hacer un handler por cada player
struct Player;
#define _HDLRS_LIST_ Player
