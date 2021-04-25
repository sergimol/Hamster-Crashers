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
class Ability;
class GetItem;
class Item;
class Cloud;
class MapMngr;
class EnemyStun;
class Stun;
class Gravity;
class DeadBody;
class Knockback;
class HeartUI;
class TileRender;
class PossesionGame;
class GhostCtrl;
class ContactDamage;
class AnimHamsterStateMachine;
class KeyGame;
class HeightObject;
class Camera;
class Swallow;
class EnemyBehaviour;
class Behavior;
class InfarctedBody;
class ReanimationGame;
class Dying;
class FirstBossBehaviour;
class FirstBossAttack;
class EnemyStrongAttack;
class StrongFollowPlayer;
class BackGround;
class CollisionDetec;
class Parallax;
class NewScene;
class Transition;
class MenuButton;
class menuButtonManager;
class GameStates;
class EnemyMother;

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
	EnemyAttack, \
	Cloud, \
	Item, \
	GetItem, \
	EnemyStateMachine, \
	EnemyStun, \
	Stun, \
	MapMngr, \
	Ability, \
	Gravity, \
	DeadBody, \
	Knockback, \
	HeartUI, \
	MapMngr,\
	TileRender, \
	GhostCtrl, \
	HeightObject, \
	PossesionGame,\
	ContactDamage,\
	Swallow,\
	AnimHamsterStateMachine,\
	KeyGame,\
	HeightObject,\
	Camera, \
	EnemyBehaviour, \
	Behavior, \
	Camera, \
	InfarctedBody, \
	ReanimationGame, \
	Dying, \
	FirstBossAttack, \
	FirstBossBehaviour, \
	FollowPlayer, \
	BackGround, \
	CollisionDetec, \
	NewScene, \
	StrongFollowPlayer, \
	EnemyStrongAttack, \
	Parallax, \
	MenuButton,\
	menuButtonManager,\
	Transition, \
	GameStates, \
	EnemyMother

//FollowPlayer, \

// groups

struct Enemy;
struct Ally;
struct Bullet_group;
struct Item_group;
struct Dead;

#define _GRPS_LIST_  Enemy, Ally, Bullet_group, Item_group, Dead

// handlers
//Creo que hay que hacer un handler por cada player
struct Hamster1;
struct Hamster2;
struct Hamster3;
struct Hamster4;
struct Camera__;
struct Map;
struct Trans;
struct StateMachine;
struct Mother;
#define _HDLRS_LIST_ Hamster1 , \
					Hamster2, \
					Hamster3, \
					Hamster4, \
					Camera__, \
					Map, \
					Trans, \
					StateMachine, \
					Mother


//systems

class HamsterSystem;

#define _SYS_LIST_ HamsterSystem