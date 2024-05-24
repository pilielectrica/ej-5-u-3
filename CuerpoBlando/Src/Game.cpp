#include "Game.h"
#include "Box2DHelper.h"
#include "b2ExSoftCircleBody.h"
#include "circulo.h"
#include "circulo.cpp"
#include <iostream>
using namespace std;
using namespace sf;
Game::Game(int ancho, int alto,std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom();
	InitPhysics();
}

void Game::Loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();
		
	}
}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
}

void Game::DrawGame()
{ 

	
}

void Game::DoEvents()
{
	
}

void Game::CheckCollitions()
{
	// Veremos mas adelante
}

// Definimos el area del mundo que veremos en nuestro juego
// Box2D tiene problemas para simular magnitudes muy grandes
void Game::SetZoom()
{
	View camara;
	// Posicion del view
	camara.setSize(100.0f, 100.0f);
	camara.setCenter(50.0f, 50.0f);
	wnd->setView(camara); // Asignamos la camara
}

void Game::InitPhysics()
{
	// Inicializamos el mundo con la gravedad por defecto
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	// Creamos el renderer de debug y le seteamos las banderas para que dibuje TODO
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	// Creamos un piso y paredes
	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	groundBody->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	leftWallBody->SetTransform(b2Vec2(0.0f, 50.0f), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	rightWallBody->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	//creamos un techo
	b2Body* topWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	topWallBody->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);

	//------------------------------------
	//Creación del cuerpo blando
	//------------------------------------

	tronco = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 10.0f);
	tronco->SetTransform(b2Vec2(20.0f, 50.0f), 0.0f);

	tronco->SetAwake(true);

	cabeza = Box2DHelper::CreateRectangularStaticBody(phyWorld, 7, 7.0f);
	cabeza->SetTransform(b2Vec2(20.0f, 40.0f), 0.0f);

	cabeza->SetAwake(true);

	brazoderecho = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 10.0f, 0.3, 1, 1);
	brazoderecho->SetTransform(b2Vec2(25.0f, 55.0f), 0.0f);

	brazoderecho->SetAwake(true);

	brazoizquierdo = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 10.0f, 0.3, 1, 1);
	brazoizquierdo->SetTransform(b2Vec2(15.0f, 55.0f), 0.0f);
	brazoizquierdo->SetAwake(true);

	piernaizquierda = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 4, 10.0f, 1, 1, 1);
	piernaizquierda->SetTransform(b2Vec2(18.0f, 60.0f), 0.0f);
	piernaizquierda->SetAwake(true);

	piernaderecha = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 4, 10.0f, 1, 1, 1);
	piernaderecha->SetTransform(b2Vec2(22.0f, 60.0f), 0.0f);
	piernaderecha->SetAwake(true);

	b2Vec2 verticetronco(24.0f, 46.0f);
	b2Vec2 verticetronco2(16.0f, 46.0f);
	b2Vec2 verticetronco3(20, 60);
	b2Vec2 verticetronco4(18, 53);
	b2Vec2 verticetronco5(22, 53);
		b2Vec2 verticepiernaizq(18.0f, 58);
	b2Vec2 verticepiernader(22.0f, 58);
	b2Vec2 verticecabeza(20, 42);
	b2Vec2 verticebrazoder(25.0f, 52);
	b2Vec2 verticebrazoizq(15.0f, 52);

	b2DistanceJointDef jointDef;
	jointDef.Initialize(tronco, brazoderecho, verticetronco, verticebrazoder);
	jointDef.collideConnected = true;
	b2LinearStiffness(jointDef.stiffness, jointDef.damping, 2.0f, 0.5f, tronco, brazoderecho);

	phyWorld->CreateJoint(&jointDef);
	
	b2DistanceJointDef jointDef2;
	jointDef2.Initialize(tronco, brazoizquierdo, verticetronco2, verticebrazoizq);
	jointDef2.collideConnected = true;
	b2LinearStiffness(jointDef2.stiffness, jointDef2.damping, 2.0f, 0.5f, tronco, brazoizquierdo);

	phyWorld->CreateJoint(&jointDef2);

	b2DistanceJointDef jointDef3;
	jointDef3.Initialize(tronco, cabeza, verticetronco3, verticecabeza);
	jointDef3.collideConnected = true;
	b2LinearStiffness(jointDef3.stiffness, jointDef3.damping, 2.0f, 0.5f, tronco, cabeza);

	phyWorld->CreateJoint(&jointDef3);

	b2DistanceJointDef jointDef4;
	jointDef4.Initialize(tronco, piernaizquierda, verticetronco4, verticepiernaizq);
	jointDef4.collideConnected = true;
	b2LinearStiffness(jointDef4.stiffness, jointDef4.damping, 2.0f, 0.5f, tronco, piernaizquierda);

	phyWorld->CreateJoint(&jointDef4);

	b2DistanceJointDef jointDef5;
	jointDef5.Initialize(tronco, piernaderecha, verticetronco5, verticepiernader);
	jointDef5.collideConnected = true;
	b2LinearStiffness(jointDef5.stiffness, jointDef5.damping, 2.0f, 0.5f, tronco, piernaderecha);

	phyWorld->CreateJoint(&jointDef5);
}

Game::~Game(void)
{ }