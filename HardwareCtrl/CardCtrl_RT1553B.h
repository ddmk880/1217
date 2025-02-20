#ifndef CARDCTRL_RT1553B_H
#define CARDCTRL_RT1553B_H

#include"include/busapi.h"
#include"include/pacom.h"
#include"include/visa.h"
#include"include/visatype.h"
#include"include/target_defines.h"
#include"include/rs422.h"

class CardCtrl_RT1553B
{
public:
    CardCtrl_RT1553B();
    ~CardCtrl_RT1553B();

    void Init_RT1553Card();
};

#endif // CARDCTRL_RT1553B_H
