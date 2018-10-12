@cd "D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/Simulation"
@set OCAMLRUNPARAM=b
"C:/Program Files/ANSYS Inc/v192/SCADE/SCADE/bin/uaadaptor.exe" -sdy "D:\gd\ITA\CE-235\scade\fuel\FuelManagement_\FuelManagement_.sdy" -n "C:\Program Files\ANSYS Inc\v192\SCADE\SCADE Display\config\a661_description\a661.xml" -outdir "D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/Simulation" -k "D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/Simulation/kcg_trace.xml" -o "Main_UA_1" -i "FuelManagement__interface.h"  -encoding "ASCII"  "D:\gd\ITA\CE-235\scade\fuel\fuelManagement\fuelManagement.sgfx"
@IF ERRORLEVEL 1 GOTO failed
@move "Main_UA_1.log" "Main_UA_1_uaadaptor.log"
"C:\Program Files\ANSYS Inc\v192\SCADE\SCADE Display\bin\ScadeDisplayConsole.exe" batch generate "D:\gd\ITA\CE-235\scade\fuel\fuelManagement\fuelManagement.etp" -conf "DF Generation" -source "fuelManagement.sgfx" -outdir "D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/Simulation" -prefix "Main_UA_1"
@IF ERRORLEVEL 1 GOTO failed
@move "Main_UA_1.log" "Main_UA_1_dfgen.log"
"C:\Program Files\ANSYS Inc\v192\SCADE\SCADE Display\bin\ScadeDisplayConsole.exe" batch  generateServerConf "D:\gd\ITA\CE-235\scade\fuel\fuelManagement\fuelManagement.etp" -conf "DF Generation" -spec "fuelManagement.sgfx" -out "D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/Simulation/Main_UA_1_conf.xml"
@exit 0
:failed
@exit 1
