

#include "EnemyShip.h"
#include "EnemyPeeShooter.h"

#include "resources.h"

EnemyShip::EnemyShip(Game* owner,int x,int y):
  Ship(owner,
       owner->imageManager.createImage(resourcePathFor("enemy.png")),
       x,y)
{
  _weapon = new EnemyPeeShooter(owner, this);
  setVeloY(100);
}

EnemyShip::~EnemyShip()
{
}

void EnemyShip::handleEvent(SDL_Event* event)
{
  //stop propogation
}



