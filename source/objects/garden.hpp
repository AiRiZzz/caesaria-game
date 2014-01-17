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

#ifndef __CAESARIA_GARDEN_H_INCLUDED__
#define __CAESARIA_GARDEN_H_INCLUDED__

#include "objects/construction.hpp"

class Garden : public Construction
{
public:
  Garden();
  virtual void initTerrain(Tile& terrain);
  virtual bool isWalkable() const;
  virtual bool isFlat() const;
  virtual bool isNeedRoadAccess() const;
  virtual void build(PlayerCityPtr city, const TilePos& pos );
  virtual void load(const VariantMap &stream);
  virtual Desirability getDesirability() const;
  virtual std::string getSound() const;

  void update();
};

#endif //__CAESARIA_GARDEN_H_INCLUDED__