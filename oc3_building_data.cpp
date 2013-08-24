// This file is part of openCaesar3.
//
// openCaesar3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// openCaesar3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with openCaesar3.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com

#include "oc3_building_data.hpp"

#include <map>
#include "oc3_gettext.hpp"
#include "oc3_saveadapter.hpp"
#include "oc3_stringhelper.hpp"
#include "oc3_enums_helper.hpp"

BuildingData BuildingData::invalid = BuildingData( B_NONE, "unknown", 0 );

class BuildingTypeHelper : public EnumsHelper<BuildingType>
{
public:
  static BuildingTypeHelper& instance()
  {
    static BuildingTypeHelper inst;
    return inst;
  }

  virtual BuildingType getInvalid() const { return B_NONE; }

private:
  BuildingTypeHelper()
  {
    TypeEquale bldTypeEquales[] = {
      { B_AMPHITHEATER,   "amphitheater"},
      { B_THEATER,        "theater" },
      { B_HIPPODROME,     "hippodrome" },
      { B_COLLOSSEUM,     "colloseum" },
      { B_ACTOR_COLONY,          "artist_colony" },
      { B_GLADIATOR_SCHOOL,      "gladiator_pit" },
      { B_LION_HOUSE,           "lion_pit" },
      { B_CHARIOT_MAKER,        "chatioteer_school" },
      { B_HOUSE,          "house" },
      { B_ROAD,           "road" },
      { B_PLAZA,          "plaza" },
      { B_GARDEN,         "garden" },
      { B_SENATE,         "senate_1" },
      { B_FORUM,          "forum_1" },
      { B_GOVERNOR_HOUSE, "governor_palace_1" },
      { B_GOVERNOR_VILLA, "governor_palace_2" },
      { B_GOVERNOR_PALACE,"governor_palace_3" },
      { B_FORT_LEGIONNAIRE, "fort_legionaries" },
      { B_FORT_JAVELIN,   "fort_javelin" },
      { B_FORT_MOUNTED,   "fort_horse" },
      { B_PREFECTURE,        "prefecture" },
      { B_BARRACKS,       "barracks" },
      { B_MILITARY_ACADEMY, "military_academy" },
      { B_DOCTOR,         "clinic" },
      { B_HOSPITAL,       "hospital" },
      { B_BATHS,          "baths" },
      { B_BARBER,         "barber" },
      { B_SCHOOL,         "school" },
      { B_COLLEGE,        "academy" },
      { B_LIBRARY,        "library" },
      { B_MISSION_POST,   "mission post" },
      { B_TEMPLE_CERES,   "small_ceres_temple" },
      { B_TEMPLE_NEPTUNE, "small_neptune_temple" },
      { B_TEMPLE_MARS,    "small_mars_temple" },
      { B_TEMPLE_MERCURE, "small_mercury_temple" },
      { B_TEMPLE_VENUS,   "small_venus_temple" },
      { B_BIG_TEMPLE_CERES,  "big_ceres_temple" },
      { B_BIG_TEMPLE_NEPTUNE,"big_neptune_temple" },
      { B_BIG_TEMPLE_MARS,   "big_mars_temple"},
      { B_BIG_TEMPLE_MERCURE,"big_mercury_temple"},
      { B_BIG_TEMPLE_VENUS,  "big_venus_temple"},
      { B_TEMPLE_ORACLE,     "oracle"},
      { B_MARKET,            "market"},
      { B_GRANARY,        "granery"},
      { B_WAREHOUSE,      "warehouse"},
      { B_WHEAT_FARM,          "wheat_farm"},
      { B_FRUIT_FARM,          "fig_farm"},
      { B_VEGETABLE_FARM,      "vegetable_farm"},
      { B_OLIVE_FARM,          "olive_farm"},
      { B_GRAPE_FARM,          "vinard"},
      { B_PIG_FARM,           "meat_farm"},
      { B_MARBLE_QUARRY,         "quarry"},
      { B_IRON_MINE,           "iron_mine"},
      { B_TIMBER_YARD,         "lumber_mill"},
      { B_CLAY_PIT,       "clay_pit"},
      { B_WINE_WORKSHOP,           "wine_workshop"},
      { B_OIL_WORKSHOP,            "oil_workshop"},
      { B_WEAPONS_WORKSHOP,         "weapons_workshop"},
      { B_FURNITURE,      "furniture_workshop"},
      { B_POTTERY,        "pottery_workshop"},
      { B_ENGINEER_POST,       "engineering_post"},
      { B_STATUE1,        "statue_small"},
      { B_STATUE2,        "statue_middle"},
      { B_STATUE3,        "statue_big"},
      { B_LOW_BRIDGE,     "low_bridge"},
      { B_HIGH_BRIDGE,    "high_bridge"},
      { B_DOCK,           "dock"},
      { B_SHIPYARD,       "shipyard"},
      { B_WHARF,          "wharf"},
      { B_TRIUMPHAL_ARCH, "triumphal_arch"},
      { B_WELL,           "well"},
      { B_FOUNTAIN,       "fountain"},
      { B_AQUEDUCT,       "aqueduct"},
      { B_RESERVOIR,      "reservoir"},
      { B_NATIVE_HUT,     "native_hut"},
      { B_NATIVE_CENTER,  "native_center"},
      { B_NATIVE_FIELD,   "native_field"},
      { B_BURNING_RUINS,  "burning_ruins"},
      { B_BURNED_RUINS,   "burned_ruins"},
      { B_COLLAPSED_RUINS,"collapsed_ruins"},
      { B_FORUM_2, "forum_2" },
      { B_GATEHOUSE, "gatehouse" },
      { B_SENATE_2, "senate_2" },
      { B_TOWER, "tower" },
      { B_WALL, "wall"  },

      { B_NONE, "" }
    };

    _init( bldTypeEquales, B_NONE );
  }
};

class BuildingClassHelper : public EnumsHelper<BuildingClass>
{
public:
  static BuildingClassHelper& instance()
  {
    static BuildingClassHelper inst;
    return inst;
  }

  virtual BuildingClass getInvalid() const { return BC_NONE; }

private:
  BuildingClassHelper()
  {
    append( BC_INDUSTRY, "industry" );
    append( BC_RAWMATERIAL, "rawmaterial" );
    append( BC_FOOD, "food" );
    append( BC_DISASTER, "disaster" );
    append( BC_RELIGION, "religion" );
    append( BC_MILITARY, "military" );
    append( BC_NATIVE, "native" );
    append( BC_WATER, "water" );
    append( BC_ADMINISTRATION, "administration" );
    append( BC_BRIDGE, "bridge" );
    append( BC_ENGINEERING, "engineer" );
    append( BC_TRADE, "trade" );
    append( BC_TOWER, "tower" );
    append( BC_GATE, "gate" );
    append( BC_SECURITY, "security" );
    append( BC_EDUCATUION, "education" );
    append( BC_HEALTH, "health" );
    append( BC_SIGHT, "sight" );
    append( BC_GARDEN, "garden" );
    append( BC_ROAD, "road" );
    append( BC_ENTERTAINMENT, "entertainment" );
    append( BC_HOUSE, "house" );
    append( BC_WALL, "wall" );
    append( BC_NONE, "" );
    };
  }
};


BuildingData::BuildingData(const BuildingType buildingType, const std::string &name, const int cost)
{
  _buildingType = buildingType;
  _buildingClass = BC_NONE;
  _name = name;
  std::string key = "building_"+name;
  _prettyName = _(key.c_str());  // i18n translation
  _cost = cost;
  _baseDesirability = 0;
  _desirabilityRange = 0;
  _desirabilityStep = 0;
}

std::string BuildingData::getName() const
{
  return _name;
}

std::string BuildingData::getPrettyName() const
{
  return _prettyName;
}

BuildingType BuildingData::getType() const
{
  return _buildingType;
}

int BuildingData::getCost() const
{
  return _cost;
}

int BuildingData::getEmployers() const
{
  return _employers;
}

const Picture &BuildingData::getBasePicture() const
{
  return _basePicture;
}

char BuildingData::getDesirbilityInfluence() const
{
  return _baseDesirability;
}

char BuildingData::getDesirbilityRange() const
{
  return _desirabilityRange;
}

char BuildingData::getDesirabilityStep() const
{
  return _desirabilityStep;
}

BuildingClass BuildingData::getClass() const
{
  return _buildingClass;
}

class BuildingDataHolder::Impl
{
public:
  typedef std::map<BuildingType, BuildingData> BuildingsMap; 
  typedef std::map<GoodType, BuildingType> FactoryInMap;

  BuildingsMap buildings;// key=building_type, value=data
  FactoryInMap mapBuildingByInGood;
};

BuildingDataHolder& BuildingDataHolder::instance()
{
  static BuildingDataHolder inst;
  return inst;
}

BuildingType BuildingDataHolder::getBuildingTypeByInGood(const GoodType inGoodType) const
{
  BuildingType res = B_NONE;

  Impl::FactoryInMap::iterator mapIt;
  mapIt = _d->mapBuildingByInGood.find(inGoodType);
  if (mapIt != _d->mapBuildingByInGood.end())
  {
    res = mapIt->second;
  }
  return res;
}

const BuildingData& BuildingDataHolder::getData(const BuildingType buildingType) const
{
  Impl::BuildingsMap::iterator mapIt;
  mapIt = _d->buildings.find(buildingType);
  if (mapIt == _d->buildings.end())
  {
    StringHelper::debug( 0xff, "Unknown building %d", buildingType );
    return BuildingData::invalid;
  }
  return mapIt->second;
}

bool BuildingDataHolder::hasData(const BuildingType buildingType) const
{
  bool res = true;
  Impl::BuildingsMap::iterator mapIt;
  mapIt = _d->buildings.find(buildingType);
  if (mapIt == _d->buildings.end())
  {
    res = false;
  }
  return res;
}

void BuildingDataHolder::addData(const BuildingData &data)
{
  BuildingType buildingType = data.getType();

  if (hasData(buildingType))
  {
    StringHelper::debug( 0xff, "Building is already set %s", data.getName().c_str() );
    return;
  }

  _d->buildings.insert(std::make_pair(buildingType, data));
}


BuildingDataHolder::BuildingDataHolder() : _d( new Impl )
{
}

void BuildingDataHolder::initialize( const io::FilePath& filename )
{
  // populate _mapBuildingByInGood
  _d->mapBuildingByInGood[G_IRON]   = B_WEAPONS_WORKSHOP;
  _d->mapBuildingByInGood[G_TIMBER] = B_FURNITURE;
  _d->mapBuildingByInGood[G_CLAY]   = B_POTTERY;
  _d->mapBuildingByInGood[G_OLIVE]  = B_OIL_WORKSHOP;
  _d->mapBuildingByInGood[G_GRAPE]  = B_WINE_WORKSHOP;

  VariantMap constructions = SaveAdapter::load( filename.toString() );

  for( VariantMap::iterator it=constructions.begin(); it != constructions.end(); it++ )
  {
    VariantMap options = (*it).second.toMap();

    const BuildingType btype = getType( (*it).first );
    if( btype == B_NONE )
    {
      StringHelper::debug( 0xff, "!!!Warning: can't associate type with %s", (*it).first.c_str() );
      continue;
    }

    Impl::BuildingsMap::const_iterator bdataIt = _d->buildings.find( btype );
    if( bdataIt != _d->buildings.end() )
    {
      StringHelper::debug( 0xff, "!!!Warning: type %s also initialized", (*it).first.c_str() );
      continue;
    }

    BuildingData bData( btype, (*it).first, (int)options[ "cost" ] );
    const std::string pretty = options[ "pretty" ].toString();
    if( !pretty.empty() )
    {
      bData._prettyName = pretty;
    }

    bData._baseDesirability  = (int)options[ "desirability" ];
    bData._desirabilityRange = (int)options[ "desrange" ];
    bData._desirabilityStep  = (int)options[ "desstep" ];
    bData._employers = (int)options[ "employers" ];
    bData._buildingClass = getClass( options[ "class" ].toString() );

    VariantList basePic = options[ "image" ].toList();
    if( basePic.size() == 2 && basePic.back().toInt() > 0 )
    {
      std::string resourceGroup = basePic.front().toString();
      int rcIndex = basePic.back().toInt();
      if( rcIndex > 0 )
      {
        bData._basePicture = Picture::load( resourceGroup, rcIndex );
      }
    }

    addData( bData );
    }
}

BuildingType BuildingDataHolder::getType( const std::string& name ) const
{
  BuildingType type = findEqualeType( name );

  if( type == getInvalid() )
  {
    StringHelper::debug( 0xff, "Can't find type for typeName %s", name.c_str() );
    _OC3_DEBUG_BREAK_IF( "Can't find type for typeName" );
  }

  return type;
}

BuildingClass BuildingDataHolder::getClass( const std::string& name )
{
  int index=0;
  std::string typeName = bldClassEquales[ index ].name;

  while( !typeName.empty() )
  {
    if( name == typeName )
    {
      return bldClassEquales[ index ].type;
    }

    index++;
    typeName = bldClassEquales[ index ].name;
  }

  StringHelper::debug( 0xff, "Can't find building class for building className %s", name.c_str() );
  _OC3_DEBUG_BREAK_IF( "Can't find building class for building className" );
  return BC_NONE;
}
