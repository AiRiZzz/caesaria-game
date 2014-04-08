// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com

#include "base.hpp"

#include "gfx/engine.hpp"
#include "core/exception.hpp"
#include "core/event.hpp"
#include "core/eventconverter.hpp"
#include "core/time.hpp"

namespace scene
{

//1000 / 30
#define TICK_PER_FRAME 33

Base::Base()
{
  _isStopped = false;
}

Base::~Base() {}

void Base::drawFrame(gfx::Engine& engine )
{
   engine.startRenderFrame();
   
   draw();
   
   engine.endRenderFrame();
}

void Base::handleEvent( NEvent& event) {}
void Base::afterFrame() {}
void Base::stop(){ _isStopped = true;}

void Base::update(gfx::Engine& engine )
{
  static unsigned int lastTimeUpdate = DateTime::elapsedTime();

  drawFrame( engine );
  afterFrame();

  NEvent nEvent;
  while( engine.haveEvent( nEvent )  )
  {
    handleEvent( nEvent );
  }

  unsigned int ticks = DateTime::elapsedTime() - lastTimeUpdate;
  if( ticks < TICK_PER_FRAME )
  {
    engine.delay( TICK_PER_FRAME - ticks );
  }
  lastTimeUpdate = DateTime::elapsedTime();
}

bool Base::isStopped() const{  return _isStopped;}
bool Base::installEventHandler(EventHandlerPtr) { return false; }

}//end namespace scene