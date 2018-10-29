#include "EvoCube.h"

EvoCube::EvoCube()
{
	m_texture = nullptr;
	infoBar = nullptr;

	m_tail = nullptr;
	m_jaws = nullptr;
	m_fin = nullptr;
	m_grassAnim = nullptr;

	m_movementSpeed = 5.0f;
}

EvoCube::~EvoCube()
{

}

void EvoCube::update(float _deltaTime)
{
	_deltaTime;

	m_velocity = m_dynamicBody.getLinearVelocity();

	m_worldPosition = m_dynamicBody.getPosition() * PHYSICS_TO_WORLD;

	m_boundingBox.m_position.x = m_worldPosition.x - m_texture->m_width / 2.0f;
	m_boundingBox.m_position.y = m_worldPosition.y - m_texture->m_height / 2.0f;


	//BODY PARTS
	m_tail->m_worldPosition = m_worldPosition + m_tail->m_offset;
	m_tail->update(_deltaTime);

	m_jaws->m_worldPosition = m_worldPosition + m_jaws->m_offset;
	m_jaws->update(_deltaTime);

	m_fin->m_worldPosition = m_worldPosition + m_fin->m_offset;
	m_fin->update(_deltaTime);

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

	m_grassAnim->update();
}

void EvoCube::init()
{
	//files loaded
	m_texture = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Texture>("textures\\Untitled.png");

	//anttweak bars init
	TDF::AntTweakBarInfo info;
	info.size = " size='300 300' ";
	info.position = " position='0 700' ";
	infoBar = TDF::AnttweakbarManager::GetInstance().createCustomBar(TEXT("Cube_info"), info);

	TwAddVarRO(infoBar, TEXT("position x:"), TW_TYPE_FLOAT, &m_worldPosition.x, TEXT(" label='position x:' precision=2"));
	TwAddVarRO(infoBar, TEXT("position y:"), TW_TYPE_FLOAT, &m_worldPosition.y, TEXT(" label='position y:' precision=2"));
	TwAddVarRO(infoBar, TEXT("velocity x:"), TW_TYPE_FLOAT, &m_velocity.x, TEXT(" label='velocity x:' precision=2"));
	TwAddVarRO(infoBar, TEXT("velocity y:"), TW_TYPE_FLOAT, &m_velocity.y, TEXT(" label='velocity y:' precision=2"));

	String name = "Cube_info";
	name = name + " visible=false";
	TwDefine(name.c_str());

	TDF::InputManager::GetInstance().subscribe(TDF::KEYBOARD_INPUT, m_id);
	TDF::InputManager::GetInstance().subscribe(TDF::CONTROLLER_INPUT, m_id);

	m_tail = new Tail();
	m_tail->init();

	m_jaws = new Jaws();
	m_jaws->init();

	m_fin = new Fin();
	m_fin->init();

	m_grassAnim = TDF::ResourceManager::GetInstance().loadFromFile<TDF::Animation>("animations\\body.xml");
}

void EvoCube::render()
{
	int renderPosx = static_cast<int>(m_screenPosition.x - m_texture->m_width / 2);
	int renderPosy = static_cast<int>(m_screenPosition.y - m_texture->m_height / 2);

	TDF::RenderManager::GetInstance().renderTexture(m_texture, renderPosx, renderPosy);

	TDF::AABB renderBox = m_boundingBox;
	renderBox.m_position.x = renderPosx;
	renderBox.m_position.y = renderPosy;

	TDF::RenderManager::GetInstance().renderBox(renderBox);

	if (m_flipped)
	{
		TDF::RenderManager::GetInstance().renderAnimation(m_grassAnim, renderPosx, renderPosy, 0, 4, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TDF::RenderManager::GetInstance().renderAnimation(m_grassAnim, renderPosx, renderPosy, 0, 4, nullptr, SDL_FLIP_NONE);
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
		vel.x = m_movementSpeed + m_tail->m_speedMod + m_fin->m_speedMod;
		if (!m_grassAnim->isPlaying())
		{
			m_grassAnim->play();
		}
		m_flipped = false;
		break;

	case D_LEFT:
		vel.x = (m_movementSpeed + m_tail->m_speedMod + m_fin->m_speedMod) * -1;
		if (!m_grassAnim->isPlaying())
		{
			m_grassAnim->play();
		}
		m_flipped = true;
		break;

	case D_UP:
		vel.y = (m_movementSpeed + m_tail->m_speedMod + m_fin->m_speedMod) * -1;
		if (!m_grassAnim->isPlaying())
		{
			m_grassAnim->play();
		}
		break;

	case D_DOWN:
		vel.y = m_movementSpeed + m_tail->m_speedMod + m_fin->m_speedMod;
		if (!m_grassAnim->isPlaying())
		{
			m_grassAnim->play();
		}
		break;

	case D_STOPX:
		vel.x = 0;
		m_grassAnim->stop();
		break;

	case D_STOPY:
		vel.y = 0;
		m_grassAnim->stop();
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
	polygonShape.SetAsBox(m_texture->m_width / 2.0f * WORLD_TO_PHYSICS, m_texture->m_height / 2.0f * WORLD_TO_PHYSICS);

	m_boundingBox.m_width = m_texture->m_width;
	m_boundingBox.m_height = m_texture->m_height;

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