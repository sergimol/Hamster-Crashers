// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class HamsterStateMachine;
class Image;
class LightAttack;
class StrongAttack;
class Movement;
class EntityAttribs;
class UI;
class Stroke;
class Animator;
class Pray;
class Combos;
class Roll;
class Turret;
class DisableOnExit;
class BulletHit;
class ControlHandeler;
class Poison;

#define _CMPS_LIST_  \
	Transform,\
	HamsterStateMachine, \
	Image,\
	LightAttack, \
	StrongAttack, \
	Movement, \
	EntityAttribs, \
	Stroke, \
	UI, \
	Animator, \
	Pray, \
	Combos, \
	Roll, \
	Turret, \
	DisableOnExit, \
	BulletHit, \
	Poison, \
	ControlHandeler

// groups

struct Enemy; 
struct Ally;
struct Bullet_group;
#define _GRPS_LIST_  Enemy, Ally, Bullet_group

// handlers
//Creo que hay que hacer un handler por cada player
struct Player;
#define _HDLRS_LIST_ Player
