#include "../vec3.h"
#include "../planet.hpp"
#include "../system.hpp"

double mass_sun = 1.988500*1E30;
double mass_mercury = 3.302*1E23/mass_sun;
double mass_venus = 4.8685*1E24/mass_sun;
double mass_earth = 5.97219*1E24/mass_sun;
double mass_mars = 6.4171*1E23/mass_sun;
double mass_jupiter = 1.89813*1E28/mass_sun;
double mass_saturn = 5.6834*1E26/mass_sun;
double mass_uranus = 8.6813*1E25/mass_sun;
double mass_neptune = 1.02*1E26/mass_sun;

// moons & dwarf planet Pluto
double mass_pluto = 1.307*1E22/mass_sun;
double mass_Luna = 7.349*1E22/mass_sun;
double mass_Io = 893.3*1E20/mass_sun;
double mass_Europa = 479.7*1E20/mass_sun;
double mass_Ganymede = 1482*1E20/mass_sun;


double j = 365.25;

/*
SUN DATA
 */

double XS =-6.129737383707927*1E-3; double YS = 6.405371281081122*1E-3; double ZS = 8.959139263600595*1E-5;

double VXS = -7.260672606291386*1E-6; double VYS = -5.115343779622854*1E-6; double VZS = 2.179205533471483*1E-7;


planet sun(XS,YS, ZS, VXS*j, VYS*j,VZS*j, 1.0);

/*
MERCURY DATA
 */
double XM = 3.501723281044439*1E-1; double YM = -9.556443087796402*1E-3; double ZM = -3.3898846690969951*1E-2;
double VXM = -4.184011287696504*1E-3; double VYM = 2.935891161884956*1E-2; double VZM= 2.782855284617702*1E-3;

planet mercury(XM,YM,ZM, VXM*j, VYM*j, VZM*j, mass_mercury);

/*
VENUS DATA
 */
double XV = -2.782079554133768*1E-1; double YV = 6.711413293489558*1E-1; double ZV = 2.491233404821817*1E-2;
double VXV = -1.879456455461377*1E-2; double VYV = -7.780734970299152*1E-3; double VZV = 9.776558484441351*1E-4;


planet venus(XV,YV,ZV, VXV*j, VYV*j, VZV*j, mass_venus);

/*
EARTH DATA
 */
double XE = 8.907825486734252*1E-1; double YE = 4.396506241573193*1E-1; double ZE = 6.565015058670386*1E-5;
double VXE = -7.776615948578309*1E-3; double VYE = 1.542644409377417*1E-2; double VZE = 1.263167140692514*1E-7;

planet earth(XE,YE,ZE, VXE*j, VYE*j, VZE*j, mass_earth);

/*
MARS DATA
 */
double XMA = 1.293770370519704; double YMA = 5.802277711174851*1E-1; double ZMA = -1.977374402568726*1E-2;
double VXMA = -5.123105928170994*1E-3; double VYMA = 1.399145197669362*1E-2; double  VZMA = 4.190339668246554*1E-4;

planet mars(XMA,YMA,ZMA, VXMA*j, VYMA*j, VZMA*j, mass_mars);

/*
JUPITER DATA
 */
double XJ = 2.575956863567940; double YJ = -4.416159673726113; double ZJ = -3.931176078837768*1E-2;
double VXJ = 6.425396334484731*1E-3; double VYJ = 4.160219877822326*1E-3; double VZJ= -1.609910003540274*1E-4;


planet jupiter(XJ,YJ,ZJ, VXJ*j, VYJ*j, VZJ*j, mass_jupiter);

/*
SATURN DATA
 */
double XSA = 5.157437677160017; double YSA = -8.555115825023062; double ZSA = -5.657189829285234*1E-2;
double VXSA = 4.466361653682236*1E-3; double VYSA = 2.865834227290038*1E-3; double VZSA = -2.275757417995623*1E-4;


planet saturn(XSA,YSA,ZSA, VXSA*j, VYSA*j, VZSA*j, mass_saturn);

/*
URANUS DATA
 */
double XU = 1.552744956821468*1E1; double YU = 1.225398561365152*1E1; double ZU = -1.556486139011366*1E-1;
double VXU = -2.465536298101529*1E-3; double VYU = 2.904225782075057*1E-3; double VZU = 4.279514670752644*1E-5;


planet uranus(XU,YU,ZU, VXU*j, VYU*j, VZU*j, mass_uranus);

/*
NEPTUNE DATA
 */
double XN = 2.941394147793647*1E1; double YN = -5.455762940819030; double ZN =-5.655230296053286*1E-1;
double VXN = 5.521299038063001*1E-4; double VYN = 3.105312239370362*1E-3; double VZN = -7.686111060441345*1E-5;

planet neptune(XN,YN,ZN, VXN*j, VYN*j, VZN*j, mass_neptune);

/*
PLUTO DATA
 */
double XP = 1.383650408484720*1E1; double YP = -3.119739619942865*1E1; double ZP = -6.640411699647492*1E-1;
double VXP = 2.934056141182749*1E-3; double VYP = 5.895418585103645*1E-4; double VZP = -9.178573011725345*1E-4;


planet pluto(XP,YP,ZP, VXP*j, VYP*j, VZP*j, mass_pluto);

/*
Luna DATA
 */
double XL = 8.894622896970551*1E-1; double YL = 4.376343881982676*1E-1; double ZL = 1.542606001581796*1E-4;
double VXL = -7.266663974387404*1E-3; double VYL = 1.506081452245701*1E-2; double VZL = -4.992812432535253*1E-5;

planet luna(XL,YL,ZL, VXL*j, VYL*j, VZL*j, mass_Luna);

/*
Io DATA
 */
double XI = 2.578652007041349; double YI = -4.417021223898337; double ZI = -3.930255752252233*1E-2;
double VXI = 9.477859042542031*1E-3; double VYI = 1.365051558733890*1E-2; double VZI = 2.308056508220923*1E-4;


planet io(XI,YI,ZI, VXI*j, VYI*j, VZI*j, mass_Io);

/*
Europa DATA
 */
double XEU = 2.575552684629729; double YEU = -4.420633585823910; double ZEU = -3.949697404731697*1E-2;
double VXEU = 1.431680521579167*1E-2; double VYEU = 3.516327162403115*1E-3; double VZEU = -1.365011231067895*1E-5;


planet europa(XEU,YEU,ZEU, VXEU*j, VYEU*j, VZEU*j, mass_Europa);

/*
Ganymede DATA
 */
double XG = 2.570657060355334; double YG = -4.411339213328689; double ZG = -3.920083709960680*1E-2;
double VXG = 2.204412754643837*1E-3; double VYG = -4.770263345095837*1E-4; double VZG = -3.948297031509242*1E-4;

planet ganymede(XG,YG,ZG, VXG*j, VYG*j, VZG*j, mass_Ganymede);

SolarSystem.add(&sun);
SolarSystem.add(&mercury);
SolarSystem.add(&venus);
SolarSystem.add(&earth);
SolarSystem.add(&mars);
SolarSystem.add(&jupiter);
SolarSystem.add(&saturn);
SolarSystem.add(&uranus);
SolarSystem.add(&neptune);
SolarSystem.add(&pluto);
//SolarSystem.add(&luna);
//SolarSystem.add(&io);
//SolarSystem.add(&europa);
