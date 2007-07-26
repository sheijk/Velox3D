@echo Please enter the name and path of the scene you want to start
@echo Use the velox vfs name
@echo Example: /edit/simple to load ./workspace/edit/simple.v3dscene

::@FOR /F "tokens=*" %%A IN ('TYPE CON') DO SET INPUT=%%A
@set /p INPUT=
:: Use quotes if you want to display redirection characters as well
@ECHO Starting scene "%INPUT%"

@cd workspace
@..\RacerDemo.exe -scene %INPUT%.v3dscene
@cd ..
@echo Will continue in one day (unless you exit earlier ;))
@sleep 1d

