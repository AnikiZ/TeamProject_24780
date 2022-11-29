//
//  gamemenu.hpp
//  final-project
//
//  Created by Xinlu Liu on 11/28/22.
//

#ifndef gamemenu_hpp
#define gamemenu_hpp

#include <stdio.h>
class GameMenu
{
public:
    int aircraft;
    int difficulty;
    int state;
    
    void Initialize(void);
    void Run(void);
    void Welcome(void);
    void ChooseAircraft(void);
    void ChooseDifficulty(void);
    void DrawStart(void);
    int GetMenuState(void);
    int GetAircraft(void);
    int GetDifficulty(void);
    void Replay(void);
};

#endif /* gamemenu_hpp */
