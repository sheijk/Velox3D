@echo Please enter the name and path of the scene you want to start
@echo Use the velox vfs name
@echo Example: /edit/simple to load ./workspace/edit/simple.v3dscene

::@FOR /F "tokens=*" %%A IN ('TYPE CON') DO SET INPUT=%%A
@set /p INPUT=
:: Use quotes if you want to display redirection characters as well
@echo Starting scene "%INPUT%"

@cd Workspace
@..\..\Local\Build8\release\RacerDemo.exe -scene %INPUT%.v3dscene
@cd ..
@pause
