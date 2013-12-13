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
// Copyright 2012-2013 Dalerank, dalerankn8@gmail.com


#ifndef _CAESARIA_WALLGUARD_INCLUDE_H_
#define _CAESARIA_WALLGUARD_INCLUDE_H_

#include "soldier.hpp"
#include "building/predefinitions.hpp"

/** Soldier, friend or enemy */
class WallGuard : public Soldier
{
public:
  static WallGuardPtr create( PlayerCityPtr city, constants::walker::Type type );

  void send2city(TowerPtr base , Pathway pathway);

  virtual void die();
  virtual void timeStep(const unsigned long time);

  virtual void save(VariantMap &stream) const;
  virtual void load(const VariantMap &stream);


protected:
  virtual void _centerTile();
  virtual void _reachedPathway();
  virtual void _brokePathway(TilePos pos);

  void _init( constants::walker::Type type);
  void _back2tower();
  void _back2patrol();
  bool _tryAttack();
  Pathway _findPathway2NearestEnemy();

  WalkerList _findEnemiesInRange(unsigned int range);

  Pathway _attackEnemyInRange(unsigned int range);
private:
  WallGuard(PlayerCityPtr city, constants::walker::Type type);

  class Impl;
  ScopedPtr< Impl > _d;
};


#endif //_CAESARIA_WALLGUARD_INCLUDE_H_