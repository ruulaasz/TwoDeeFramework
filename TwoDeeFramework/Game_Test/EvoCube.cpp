#include "EvoCube.h"

EvoCube::EvoCube()
{
	infoBar = nullptr;

	m_jaws = nullptr;
	m_bodyAnim = nullptr;

	m_movementSpeed = 2.0f;
}

EvoCube::~EvoCube()
{

}

void EvoCube::update(float _deltaTime)
{
	_deltaTime;

	m_velocity = m_dynamicBody.getLinearVelocity();

	m_worldPosition = (m_dynamicBody.getPosition() * PHYSICS_TO_WORLD);

	m_boundingBox.m_position.x = m_worldPosition.x;
	m_boundingBox.m_position.y = m_worldPosition.y;

	updateCamera();

	m_bodyAnim->update();

	updateBodyParts(_deltaTime);
}

void EvoCube::updateBodyParts(float _deltaTime)
{
	if (m_flipped)
	{
		m_jaws->m_worldPosition.x = m_worldPosition.x - m_bodyAnim->getSprite().m_dimentions.x * 4 - 10;
		m_jaws->m_worldPosition.y = m_worldPosition.y - m_bodyAnim->getSprite().m_dimentions.y * 2;
	}
	else
	{
		m_jaws->m_worldPosition.x = m_worldPosition.x + m_bodyAnim->getCurrentSprite().m_dimentions.x * 2 - 10;
		m_jaws->m_worldPosition.y = m_worldPosition.y - m_bodyAnim->getCurrentSprite().m_dimentions.y * 2;
	}

	m_jaws->update(_deltaTime);
}


void EvoCube::init()
{
	//anttweak bars init
	TDF::AntTweakBarInfo info;
	info.size = " size='300 300' ";
	info.position = " position='0 700' ";
	infoBar = TDF::AnttweakbarManager::GetInstance().createCustomBar(TEXT("Cube_info"), info);

	TwAddVarRO(infoBar, TEXT("position x:"), TW_TYPE_FLOAT, &m_worldPosition.x, TEXT(" label='position x:' precision=2"));
	TwAddVarRO(infoBar, TEXT("position y:"), TW_TYPE_FLOAT, &m_worldPosition.y, TEXT(" label='position y:' precision=2"));
	TwAddVarRO(infoBar, TEXT("velocity x:"), TW_TYPE_FLOAT, &m_velocity.x, TEXT(" label='velocity x:' precision=2"));
	TwAddVarRO(infoBar, TEXT("velocity y:"), TW_TYPE_FLOAT, &m_velocity.y, TEXT(" label='velocity y:' precision=2"));
	TwAddVarRW(infoBar, TEXT("movementSpeed:"), TW_TYPE_FLOAT, &m_movementSpeed, TEXT(" group='Stats' label='movementSpeed:' step=0.1"));

	String name = "Cube_info";
	name = name + " visible=false";
	TwDefine(name.c_str());

	TDF::InputManager::GetInstance().subscribe(TDF::KEYBOARD_INPUT, m_id);
	TDF::InputManager::GetInstance().subscribe(TDF::CONTROLLER_INPUT, m_id);

	m_jaws = new Jaws();
	m_jaws->init();

	m_bodyAnim = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("animations\\body.xml");
	m_bodyAnim->setAnimationSpeed(0.25f);

	m_boundingBox.m_width = m_bodyAnim->getSprite(0).m_dimentions.x * 4;
	m_boundingBox.m_height = m_bodyAnim->getSprite(0).m_dimentions.y * 4;
}

void EvoCube::render()
{
	m_renderPos.x = static_cast<int>(m_screenPosition.x) - m_bodyAnim->getSprite(0).m_dimentions.x * 4 / 2;
	m_renderPos.y = static_cast<int>(m_screenPosition.y) - m_bodyAnim->getSprite(0).m_dimentions.y * 4 / 2;

	m_jaws->render();

	if (m_flipped)
	{
		TDF::RenderManager::GetInstance().renderAnimation(m_bodyAnim, m_renderPos.x, m_renderPos.y, 0, 4, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TDF::RenderManager::GetInstance().renderAnimation(m_bodyAnim, m_renderPos.x, m_renderPos.y, 0, 4, nullptr, SDL_FLIP_NONE);
	}

	if (TDF::SystemManager::GetInstance().m_renderDebug)
	{
		TDF::AABB renderBox = m_boundingBox;
		renderBox.m_position.x = m_screenPosition.x - m_boundingBox.m_width / 2;
		renderBox.m_position.y = m_screenPosition.y - m_boundingBox.m_height / 2;

		TDF::RenderManager::GetInstance().renderBox(renderBox);
	}
}

void EvoCube::onEnterCollision(int _tag)
{
	if (_tag == TDF::CI_PLATFORM)
	{
		
	}
}

void EvoCube::dispatchMessage(const TDF::InputMessage & _message)
{
	switch (_message.m_data.event.type)
	{
	default:
		break;

	case SDL_KEYDOWN:
		switch (_message.m_data.event.key.keysym.sym)
		{
		case SDLK_d:
			setDirection(D_RIGHT);
			break;

		case SDLK_a:
			setDirection(D_LEFT);
			break;

		case SDLK_w:
			setDirection(D_UP);
			break;

		case SDLK_s:
			setDirection(D_DOWN);
			break;

		case SDLK_e:
			m_jaws->m_jawsAnim->play(0);
			break;
		}
		break;

	case SDL_KEYUP:
		switch (_message.m_data.event.key.keysym.sym)
		{
		case SDLK_d:
			setDirection(D_STOPX);
			break;

		case SDLK_a:
			setDirection(D_STOPX);
			break;

		case SDLK_w:
			setDirection(D_STOPY);
			break;

		case SDLK_s:
			setDirection(D_STOPY);
			break;
		}
		break;
	}
}

void EvoCube::setDirection(int _dir)
{
	TDF::Vector2D vel = m_dynamicBody.getLinearVelocity();

	switch (_dir)
	{
	case D_RIGHT:
		vel.x = m_movementSpeed;

		if (!m_bodyAnim->isPlaying())
		{
			m_bodyAnim->play();
		}

		m_flipped = false;
		m_jaws->m_flipped = false;
		break;

	case D_LEFT:
		vel.x = m_movementSpeed * -1;

		if (!m_bodyAnim->isPlaying())
		{
			m_bodyAnim->play();
		}

		m_flipped = true;
		m_jaws->m_flipped = true;
		break;

	case D_UP:
		vel.y = m_movementSpeed * -1;

		if (!m_bodyAnim->isPlaying())
		{
			m_bodyAnim->play();
		}
		break;

	case D_DOWN:
		vel.y = m_movementSpeed;

		if (!m_bodyAnim->isPlaying())
		{
			m_bodyAnim->play();
		}
		break;

	case D_STOPX:
		vel.x = 0;
		m_bodyAnim->stop();
		break;

	case D_STOPY:
		vel.y = 0;
		m_bodyAnim->stop();
		break;
	}

	m_dynamicBody.setLinearVelocity(vel);
}

void EvoCube::enterScene(std::string _sceneName)
{
	//body definition
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	
	m_dynamicBody.init(myBodyDef, _sceneName);

	//shape definition
	b2PolygonShape polygonShape;
	float boxw, boxh;
	boxw = (m_bodyAnim->getSprite(0).m_dimentions.x * 3) * WORLD_TO_PHYSICS;
	boxh = (m_bodyAnim->getCurrentSprite().m_dimentions.y * 2) * WORLD_TO_PHYSICS;
	polygonShape.SetAsBox(boxw * .9, boxh * .9);

	//add fixture
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
	myFixtureDef.friction = 0.0f;
	m_dynamicBody.addFixture(myFixtureDef);

	//body setup
	m_dynamicBody.setUserData(this);
	m_dynamicBody.setFixedRotation(true);

	TDF::Box2DManager::GetInstance().m_allWorlds[_sceneName]->m_world->SetContactListener(&m_contactListener);
}

void EvoCube::updateCamera()
{
	//CAMERA TODO Where?
	TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.x = m_worldPosition.x - (TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_width / 2);
	TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.y = m_worldPosition.y - (TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_height / 2);

	if (TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.x < 0)
	{
		TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.x = 0;
	}

	if (TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.x > 1920)
	{
		TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.x = 1920;
	}

	if (TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.y < 0)
	{
		TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.y = 0;
	}

	if (TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.y > 1000)
	{
		TDF::CameraManager::GetInstance().m_camera.m_areaBox.m_position.y = 1000;
	}
}