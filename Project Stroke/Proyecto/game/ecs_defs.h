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
class ControlHandler;
class MovementSimple;
class FollowPlayer;
class EnemyAttack;
class EnemyStateMachine;
class Poison;
class Cloud;
class MapMngr;


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
	ControlHandler, \
	MovementSimple,\
	FollowPlayer, \
	EnemyAttack, \
	Cloud, \
	EnemyStateMachine, \
	MapMngr

// groups

struct Enemy; 
struct Ally;
struct Bullet_group;
#define _GRPS_LIST_  Enemy, Ally, Bullet_group

// handlers
//Creo que hay que hacer un handler por cada player
struct Hamster1;
struct Hamster2;
struct Hamster3;
struct Hamster4;
#define _HDLRS_LIST_ Hamster1 , \
					Hamster2, \
					Hamster3, \
					Hamster4


//systems

class HamsterSystem;

#define _SYS_LIST_ HamsterSystem