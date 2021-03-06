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

#include "infobox_raw.hpp"
#include "good/helper.hpp"
#include "image.hpp"
#include "core/utils.hpp"
#include "label.hpp"
#include "core/gettext.hpp"
#include "objects/constants.hpp"
#include "dictionary.hpp"
#include "environment.hpp"
#include "objects/factory.hpp"
#include "infobox_factory.hpp"
#include "core/logger.hpp"
#include "widget_helper.hpp"
#include "game/infoboxmanager.hpp"

using namespace gfx;

namespace gui
{

namespace infobox
{

REGISTER_OBJECT_BASEINFOBOX(vinard,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(wheat_farm,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(vegetable_farm,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(olive_farm,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(fig_farm,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(meat_farm,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(clay_pit,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(lumber_mill,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(quarry,AboutRawMaterial)
REGISTER_OBJECT_BASEINFOBOX(iron_mine,AboutRawMaterial)

AboutRawMaterial::AboutRawMaterial(Widget* parent, PlayerCityPtr city, const Tile& tile )
  : AboutConstruction( parent, Rect( 0, 0, 510, 350 ), Rect( 16, 170, 510 - 16, 170 + 74 ) )
{  
  Widget::setupUI( ":/gui/infoboxraw.gui" );

  FactoryPtr rawmb = ptr_cast<Factory>( tile.overlay() );
  _type = rawmb->type();

  setBase( ptr_cast<Construction>( rawmb ) );
  _setWorkingVisible( true );

  INIT_WIDGET_FROM_UI( Label*, lbProductivity )
  INIT_WIDGET_FROM_UI( Label*, lbProgress )
  INIT_WIDGET_FROM_UI( Label*, lbDamage )

  if( rawmb->produceGoodType() != good::none )
  {
    Picture pic = good::Helper::picture( rawmb->produceGoodType() );
    new Image( this, Point( 10, 10 ), pic );
  }

  _updateWorkersLabel( Point( 32, 160 ), 542, rawmb->maximumWorkers(), rawmb->numberWorkers() );

  if( lbDamage != NULL )
  {
    std::string text = utils::format( 0xff, "%d%% damage - %d%% fire",
                                            (int)rawmb->state( pr::damage ),
                                            (int)rawmb->state( pr::fire ) );
    lbDamage->setText( text );
  }

  if( lbProgress != NULL )
  {
    std::string text = utils::format( 0xff, "%s %d%%", _("##rawm_production_complete_m##"), rawmb->progress() );
    lbProgress->setText( text );
  }

  std::string title = MetaDataHolder::findPrettyName( rawmb->type() );
  _lbTitleRef()->setText( _(title) );

  std::string text = rawmb->workersProblemDesc();
  std::string cartInfo = rawmb->cartStateDesc();
  text = ( utils::format( 0xff, "%s\n%s", _(text), _( cartInfo ) ) );

  if( lbProductivity != NULL )
  {
    lbProductivity->setText( _(text) );
  }
}

AboutRawMaterial::~AboutRawMaterial() {}

void AboutRawMaterial::_showHelp()
{
  DictionaryWindow::show( ui()->rootWidget(), _type );
}

}

}//end namespace gui
