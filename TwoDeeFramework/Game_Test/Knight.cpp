#include "Knight.h"
#include "Platform.h"

#define JOYSTICK_DEAD_ZONE 20000

Knight::Knight()
{
	m_texture = nullptr;
	infoBar = nullptr;

	m_movementSpeed = 5.0f;
	m_jumpSpeed = 10.0f;

	m_canJump = true;
	m_jumpLimit = 2;
	m_currentJumps = 0;

	m_dynamicBody = nullptr;
	m_psysicsWorld = nullptr;
}

Knight::~Knight()
{

}

void Knight::update(float _deltaTime)
{
	_deltaTime;

	if (m_currentJumps >= m_jumpLimit)
	{
		m_canJump = false;
	}

	m_velocity.x = m_dynamicBody->GetLinearVelocity().x;
	m_velocity.y = m_dynamicBody->GetLinearVelocity().y;

	m_physicsPosition.x = m_dynamicBody->GetPosition().x;
	m_physicsPosition.y = m_dynamicBody->GetPosition().y;

	m_worldPosition = m_physicsPosition * SCALE_TO_WORLD;
}

void Knight::init()
{
	m_psysicsWorld = TDF::Box2DManager::GetInstance().m_allWorlds["moon"];

	m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("..\\resources\\textures\\Untitled.png");
	m_jumpSFX = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Sfx>("..\\resources\\sfx\\ui_change_selection.wav");

	TDF::AntTweakBarInfo info;
	info.size = " size='300 300' ";
	info.position = " position='0 500' ";
	infoBar = TDF::AnttweakbarManager::GetInstance().createCustomBar(TEXT("Player_info"), info);

	TwAddVarRO(infoBar, TEXT("position x:"), TW_TYPE_FLOAT, &m_worldPosition.x, TEXT(" label='position x:' precision=2"));
	TwAddVarRO(infoBar, TEXT("position y:"), TW_TYPE_FLOAT, &m_worldPosition.y, TEXT(" label='position y:' precision=2"));
	TwAddVarRO(infoBar, TEXT("velocity x:"), TW_TYPE_FLOAT, &m_velocity.x, TEXT(" label='velocity x:' precision=2"));
	TwAddVarRO(infoBar, TEXT("velocity y:"), TW_TYPE_FLOAT, &m_velocity.y, TEXT(" label='velocity y:' precision=2"));
	TwAddVarRO(infoBar, TEXT("Current_Jumps:"), TW_TYPE_INT32, &m_currentJumps, TEXT(" Current_Jumps:' "));
	TwAddVarRO(infoBar, TEXT("Can_jump?:"), TW_TYPE_BOOL32, &m_canJump, TEXT(" label='Can_jump?:' "));
	TwAddVarRO(infoBar, TEXT("Jump_Limit:"), TW_TYPE_INT32, &m_jumpLimit, TEXT(" label='Jump_Limit:' "));

	String name = "Player_info";
	name = name + " visible=false";
	TwDefine(name.c_str());

	//body definition
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	//shape definition
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_texture->m_width / 2.0f * SCALE_TO_PHYSICS, m_texture->m_height / 2.0f * SCALE_TO_PHYSICS);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
	myFixtureDef.friction = 0.0f;

	//create dynamic body
	myBodyDef.position.Set(900.0f * SCALE_TO_PHYSICS, 500.0f * SCALE_TO_PHYSICS);
	m_dynamicBody = m_psysicsWorld->CreateBody(&myBodyDef);
	m_psysicsWorld->SetContactListener(&m_contactListener);
	m_dynamicBody->SetUserData(this);
	m_dynamicBody->CreateFixture(&myFixtureDef);
	m_dynamicBody->SetFixedRotation(true);
}

void Knight::render()
{
	int renderPosx = static_cast<int>(m_worldPosition.x - m_texture->m_width / 2);
	int renderPosy = static_cast<int>(m_worldPosition.y - m_texture->m_height / 2);

	TDF::RenderManager::GetInstance().renderTexture(m_texture, renderPosx, renderPosy);
}

void Knight::onEnterCollision(int _tag)
{
	if (_tag == CI_PLATFORM)
	{
		m_currentJumps = 0;
		m_canJump = true;
	}
}

void Knight::dispatchMessage(const TDF::InputMessage & _message)
{
	switch (_message.m_data.event.type)
	{
	default:
		break;

	case SDL_KEYDOWN:
		switch (_message.m_data.event.key.keysym.sym)
		{
		case SDLK_d:
			setDirection(1);
			break;

		case SDLK_a:
			setDirection(-1);
			break;

		case SDLK_w:
			jump();
			break;
		}
		break;

	case SDL_KEYUP:
		switch (_message.m_data.event.key.keysym.sym)
		{
		case SDLK_d:
			setDirection(0);
			break;

		case SDLK_a:
			setDirection(0);
			break;
		}
		break;

	case SDL_CONTROLLERAXISMOTION:
		if (true)
		{
			if (_message.m_data.event.caxis.axis == 0)
			{
				if (_message.m_data.event.caxis.value < -JOYSTICK_DEAD_ZONE)
				{
					setDirection(-1);
				}
				else if (_message.m_data.event.caxis.value > JOYSTICK_DEAD_ZONE)
				{
					setDirection(1);
				}
				else
				{
					setDirection(0);
				}
			}
		}
		break;

	case SDL_CONTROLLERBUTTONDOWN:
		switch (_message.m_data.event.cbutton.button)
		{
		default:
			break;

		case SDL_CONTROLLER_BUTTON_A:
			jump();
			break;


		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			setDirection(1);
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			setDirection(-1);
			break;
		}
		break;

	case SDL_CONTROLLERBUTTONUP:
		switch (_message.m_data.event.cbutton.button)
		{
		default:
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			setDirection(0);
			break;

		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			setDirection(0);
			break;
		}
		break;
	}
}

void Knight::setDirection(int _dir)
{
	b2Vec2 vel = m_dynamicBody->GetLinearVelocity();

	vel.x = m_movementSpeed * _dir;

	m_dynamicBody->SetLinearVelocity(vel);
}

void Knight::jump()
{
	if (m_currentJumps >= m_jumpLimit)
	{
		m_canJump = false;
	}

	if (m_canJump)
	{
		m_jumpSFX->play(-1);
		b2Vec2 vel = m_dynamicBody->GetLinearVelocity();
		vel.y = -m_jumpSpeed;
		m_dynamicBody->SetLinearVelocity(vel);
		m_currentJumps++;
	}
}