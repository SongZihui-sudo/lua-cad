#include "keyMap.h"

bool keyMap::setKey( QAction*& act, QString keyName ) 
{ 
	if ( !act )
    {
        return false;
    }
    if ( !keymap.count(keyName) )
    {
        return false;
    }
    act->setShortcut( keymap[keyName] );
	return true; 
}
