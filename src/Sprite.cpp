// SDL
#include "SDL.h"
#include "SDL_image.h"

// Game
#include "SpiderFish.h"
#include "Sprite.h"


Sprite::Sprite( SDL_Surface* image ):
  _image( image )
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
    this->_id = id;
	this->spriteManager = spriteManager;
	this->_image = image;
=======
  this->id_ = id;
  this->spriteManager = spriteManager;
  this->_image = image;
>>>>>>> aff7312b3e1d020279d95ded9f5ebcb58d411942

  this->x = 0;
  this->y = 0;
>>>>>>> e028beb5b267f8c82a62bc757edfd0a71c842f0f
}

void Sprite::draw( SDL_Surface* screen, int x, int y )
{
<<<<<<< HEAD
  if( _image != NULL )
=======
<<<<<<< HEAD
	if (_image != NULL)
	{
		SDL_Rect offset;
		offset.x = x;
		offset.y = y;

		SDL_BlitSurface(_image, NULL, screen, &offset);
	}
}

Sprite::~Sprite()
{
}
=======
  if (_image != NULL)
>>>>>>> e028beb5b267f8c82a62bc757edfd0a71c842f0f
  {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( _image, NULL, screen, &offset );
  }
}
<<<<<<< HEAD

=======
>>>>>>> aff7312b3e1d020279d95ded9f5ebcb58d411942
>>>>>>> e028beb5b267f8c82a62bc757edfd0a71c842f0f
