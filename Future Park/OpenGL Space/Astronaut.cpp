#include "Player.h"
#include "ShapeRectangle.h"

#define SIZE 50.f

#define W_KEY 0x57
#define A_KEY 0x41
#define S_KEY 0x53
#define D_KEY 0x44

Player::Player()
{
	Initialise(0, 0);
}

Player::Player(const float originX, const float originY)
{
	Initialise(originX, originY);
}

void Player::Initialise(const float originX, const float originY)
{
	m_type = "Player";

	m_shapeComponent = new ShapeRectangle(SIZE);
	m_shapeComponent->SetColour(65, 105, 225);

	m_shapeComponent->m_transformComponent = m_transformComponent;
	m_transformComponent->AddTranslation(originX, originY, 0);

	m_collisionComponent.m_transformComponent = m_shapeComponent->m_transformComponent;
	m_collisionComponent.AddVertex(m_shapeComponent->GetVertexList());

	m_speed = 300;
	m_projectileSize = 5.f;
	m_projectileSpeed = 250.f;
}

Player::~Player()
{
}

void Player::Update()
{
	Movement();
	Shoot();

	for (Projectile *proj : m_projectiles)
	{
		proj->Update();
	}

	m_timer += Time::DeltaTime();
}

void Player::Shoot()
{
	// Check for shooting
	if (m_timer > 0.5f)
	{
		if ((unsigned short)GetKeyState(VK_UP) >> 15)
		{
			CreateProjectile(Vector4::MovementUp());
		}
		else if ((unsigned short)GetKeyState(VK_DOWN) >> 15)
		{
			CreateProjectile(Vector4::MovementDown());
		}
		else if ((unsigned short)GetKeyState(VK_LEFT) >> 15)
		{
			CreateProjectile(Vector4::MovementLeft());
		}
		else if ((unsigned short)GetKeyState(VK_RIGHT) >> 15)
		{
			CreateProjectile(Vector4::MovementRight());
		}
	}
}

void Player::CreateProjectile(const Vector4 &direction)
{
	Projectile *proj = new Projectile(m_projectileSize, m_projectileSpeed, m_transformComponent->GetTranslation().GetX(), m_transformComponent->GetTranslation().GetY(), direction, 2.f);
	proj->m_shapeComponent->SetColour(255, 48, 48);

	m_projectiles.push_back(proj);

	// Reset timer
	m_timer = 0;
}

void Player::Movement()
{
	Vector4 translation = m_transformComponent->GetTranslation();

	float movement = m_speed * Time::DeltaTime();
	float padding = SIZE;

	// Check for movement
	if ((unsigned short)GetKeyState(W_KEY) >> 15 && translation.GetY() + padding < m_screenHeight / 2.f)
		m_transformComponent->AddTranslation(0, movement, 0);

	if ((unsigned short)GetKeyState(A_KEY) >> 15 && translation.GetX() - padding > -m_screenWidth / 2.f)
		m_transformComponent->AddTranslation(-movement, 0, 0);

	if ((unsigned short)GetKeyState(S_KEY) >> 15 && translation.GetY() - padding > -m_screenHeight / 2.f)
		m_transformComponent->AddTranslation(0, -movement, 0);

	if ((unsigned short)GetKeyState(D_KEY) >> 15 && translation.GetX() + padding < m_screenWidth / 2.f)
		m_transformComponent->AddTranslation(movement, 0, 0);
}

void Player::Render() const
{
	m_shapeComponent->Render();

	for (const Projectile *proj : m_projectiles)
	{
		proj->Render();
	}
}

void Player::Cleanup()
{
	for (unsigned short index = 0; index < m_projectiles.size(); index++)
	{
		if (m_projectiles[index]->CanDestroy())
		{
			delete m_projectiles[index];
			m_projectiles.erase(m_projectiles.begin() + index);
		}
	}
}