#include "OrbBullet.h"
#include "Bullet.h"
#include "SpiderFish.h"
#include "Game.h"

#include "resources.h"

OrbBullet::OrbBullet(Game* owner,int x,int y):
  Bullet(owner,owner->imageManager.createImage(resourcePathFor("bullet.png")),x,y,0,-250)
{
  //ctor
}

OrbBullet::~OrbBullet()
{
  //dtor
}
